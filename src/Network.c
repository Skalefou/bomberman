#include "Network.h"

static Network network;

void Network_EncryptJSON() {
    cJSON_Delete(network.paquetSendServeur);
    network.paquetSendServeur = cJSON_CreateObject();

/*    int w = Map_GetSize().w, h = Map_GetSize().h;
    cJSON *mapArray = cJSON_CreateArray();*/
}

void Network_Init(int modeConnection) {
    SDLNet_Init();
    network.threadContinue = 1;
    network.mode = modeConnection;
    network.state = PENDING_NETWORK;
    network.paquetSendServeur = cJSON_CreateObject();
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
                // Faire un traitement

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
    cJSON_Delete(network.paquetSendServeur);
    SDLNet_TCP_Close(network.socket);
    SDLNet_Quit();
}