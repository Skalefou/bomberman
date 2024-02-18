#include "Network.h"

static Network network;

void Network_Init(int modeConnection) {
    SDLNet_Init();
    network.mode = modeConnection;

    if (network.mode == NETWORK_HOST) {
        // Ouvre un port et test s'il est valide
        for (int i = 0; i < LIMIT_TEST_PORT; i++) {
            network.socket = SDLNet_UDP_Open(DEFAULT_PORT_HOST + i);
            if (network.socket) {
                break;
            }
            fprintf(stderr, "Erreur ouverture socket : %s", SDLNet_GetError());
        }
        if (!network.socket) {
            return;
        }
    } else if (network.mode == NETWORK_CLIENT) {
        network.socket = SDLNet_UDP_Open(0);
        if (!network.socket) {
            printf("Erreur lors de l'ouverture du socket : %s\n", SDLNet_GetError());
            return;
        }
    }
    network.packet = SDLNet_AllocPacket(MAX_LEN_PACKET);
}

void Network_ClientPrepareConnection(char *ip, Uint16 port) {
    SDLNet_ResolveHost(&network.ip, ip, port);
    network.packet->address = network.ip;

    char *message = "Connection établie";
    memcpy(network.packet->data, message, strlen(message)+1);
}

void Network_ClientSendRequest() {
    SDLNet_UDP_Send(network.socket, -1, network.packet);
}

void Network_ServerWaitingConnection() {
    if (SDLNet_UDP_Recv(network.socket, network.packet)) {
        printf("Client : %s\n", (char *)network.packet->data);
    }
}

int Network_GetMode() {
    return network.mode;
}

void Network_Close() {
    SDLNet_FreePacket(network.packet);
    SDLNet_UDP_Close(network.socket);
    SDLNet_Quit();
}