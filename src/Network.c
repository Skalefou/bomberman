#include "Network.h"

static Network network;

void Network_DecryptJSON(char *jsonStr) {
    cJSON *json = cJSON_Parse(jsonStr);

    cJSON *position0X = cJSON_GetObjectItem(json, "xPlayer0");
    cJSON *position0Y = cJSON_GetObjectItem(json, "yPlayer0");
    cJSON *position1X = cJSON_GetObjectItem(json, "xPlayer1");
    cJSON *position1Y = cJSON_GetObjectItem(json, "yPlayer1");
    cJSON *orientation0 = cJSON_GetObjectItem(json, "orientation0");
    cJSON *orientation1 = cJSON_GetObjectItem(json, "orientation1");

    Player_SetPosition(0, position0X->valueint, position0Y->valueint);
    Player_SetPosition(1, position1X->valueint, position1Y->valueint);

    cJSON_Delete(json);

}

void Network_EncryptJSON() {
    SDL_LockMutex(network.mutex);
    cJSON_Delete(network.paquetSendServeur);
    network.paquetSendServeur = cJSON_CreateObject();


    const int w = Map_GetSize().w, h = Map_GetSize().h;
    cJSON_AddNumberToObject(network.paquetSendServeur, "widthTileMap", w);
    cJSON_AddNumberToObject(network.paquetSendServeur, "heightTileMap", h);
    cJSON *tileMap = cJSON_CreateArray();
    for (int i = 0; i < h; i++) {
        int *row = Map_GetRow(i);
        cJSON *rowArray = cJSON_CreateIntArray((const int *)row, w);
        cJSON_AddItemToArray(tileMap, rowArray);
    }
    cJSON_AddItemToObject(network.paquetSendServeur, "tileMap", tileMap);

    SDL_Rect positionPlayer0 = Player_GetPosition(0), positionPlayer1 = Player_GetPosition(1);
    int orientationPlayer0 = Player_GetOrientation(0), orientationPlayer1 = Player_GetOrientation(1);
    cJSON_AddNumberToObject(network.paquetSendServeur, "xPlayer0", positionPlayer0.x);
    cJSON_AddNumberToObject(network.paquetSendServeur, "yPlayer0", positionPlayer0.y);
    cJSON_AddNumberToObject(network.paquetSendServeur, "xPlayer1", positionPlayer1.x);
    cJSON_AddNumberToObject(network.paquetSendServeur, "yPlayer1", positionPlayer1.y);
    cJSON_AddNumberToObject(network.paquetSendServeur, "orientation0", orientationPlayer0);
    cJSON_AddNumberToObject(network.paquetSendServeur, "orientation1", orientationPlayer1);
    SDL_UnlockMutex(network.mutex);
}

void Network_Init(int modeConnection) {
    SDLNet_Init();
    network.threadContinue = 1;
    network.mode = modeConnection;
    network.state = PENDING_NETWORK;
    network.paquetSendServeur = cJSON_CreateObject();
    network.mutex = SDL_CreateMutex();
    for(int i = 0; i < SERVEUR_NUMBER_SOCKET; i++) {
        network.thread[i] = NULL;
        network.actionClientReceive[i] = CLIENT_ACTION_NONE;
    }

    if (network.mode == NETWORK_HOST) {

        SDLNet_ResolveHost(&network.ip, NULL, DEFAULT_PORT_HOST);
        network.socket = SDLNet_TCP_Open(&network.ip);
        if (!network.socket) {
            fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
            exit(EXIT_FAILURE);
        }
    }
}

void Network_ClientPrepareConnection(char *ip, Uint16 port) {
    SDLNet_ResolveHost(&network.ip, ip, port);
}

void Network_ClientSendRequest() {
    if (network.socket == NULL) {
        network.socket = SDLNet_TCP_Open(&network.ip);
    }
}

int Network_GetState() {
    return network.state;
}

void Network_SetState(int state) {
    network.state = state;
}

int Network_ProcessClient(void *data) {
    int index = *((int*)data);
    free(data);
    char receivedBuffer[MAX_LEN_PACKET_RECEIVE_SERVEUR];
    while(network.threadContinue) {
        if (network.state == PLAY_NETWORK) {
            int bytesReceived = SDLNet_TCP_Recv(network.client[index], receivedBuffer, MAX_LEN_PACKET_RECEIVE_SERVEUR);
            if (bytesReceived > 0) {
                SDL_LockMutex(network.mutex);
                char *paquetStr = cJSON_Print(network.paquetSendServeur);
                int strSize = strlen(paquetStr) + 1;
                int bytesSent = SDLNet_TCP_Send(network.client[index], paquetStr, strSize);
                SDL_UnlockMutex(network.mutex);
            }
        }
        SDL_Delay(DELAY_REQUEST);
    }
}

void Network_ClientSendData(char data) {
    char dataSend[1];
    dataSend[0] = data;
    if (SDLNet_TCP_Send(network.socket, (char *)dataSend, sizeof(dataSend)) <= 0) {

    }
}

void Network_ClientReceiveData() {
    char buffer[4096];
    if (SDLNet_TCP_Recv(network.socket, buffer, 4096) > 0) {
        Network_DecryptJSON(buffer);
    }
}

void Network_ServerWaitingConnection() {
    for (int i = 0; i < SERVEUR_NUMBER_SOCKET; i++) {
        if (network.client[i] == NULL) {
            if ((network.client[i] = SDLNet_TCP_Accept(network.socket)) != NULL) {
                 int* index = (int*)malloc(sizeof(int));
                *index = i;
                network.thread[i] = SDL_CreateThread(Network_ProcessClient, "client", index);
            }
        }
    }
}

int Network_GetMode() {
    return network.mode;
}

void Network_Close() {
    network.threadContinue = 0;
    for(int i = 0; i < SERVEUR_NUMBER_SOCKET; i++) {
        if (network.thread[i] != NULL) {
            SDL_DetachThread(network.thread[i]);
        }
    }
    SDL_DestroyMutex(network.mutex);
    cJSON_Delete(network.paquetSendServeur);
    SDLNet_TCP_Close(network.socket);
    SDLNet_Quit();
}