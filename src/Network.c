#include "Network.h"

static Network network;

void Network_Init(int modeConnection) {
    SDLNet_Init();
    network.mode = modeConnection;

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
    if((network.socket = SDLNet_TCP_Open(&network.ip)) == NULL) {
        fprintf(stderr, "Erreur SDLNet_TCP_Open : %s\n", SDLNet_GetError());
    }
}

int Network_ProcessClient(void *data) {
    char receivedBuffer[4096];
    for(;;) {
        int bytesReceived = SDLNet_TCP_Recv(network.clientPlayer, receivedBuffer, 4096);
        if (bytesReceived <= 0) {
            fprintf(stderr, "Erreur lors de la réception des données : %s\n", SDLNet_GetError());
        } else {
            fprintf(stderr, "%s\n", receivedBuffer);
        }
    }
}

void Network_ClientSendData(void *data, int size) {
    if (SDLNet_TCP_Send(network.socket, (char *)data, size) <= 0) {
        fprintf(stderr, "Erreur lors de l'envoi des données : %s\n", SDLNet_GetError());
    }
}

void Network_ServerWaitingConnection() {
    if((network.clientPlayer = SDLNet_TCP_Accept(network.socket)) != NULL) {
        SDL_Thread *thread;
        int threadData = 42;
        thread = SDL_CreateThread(Network_ProcessClient, "client1", &threadData);
    }
}

int Network_GetMode() {
    return network.mode;
}

void Network_Close() {
    SDLNet_TCP_Close(network.socket);
    SDLNet_Quit();
}