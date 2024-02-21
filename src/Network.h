#ifndef BOMBERMAN_SDL2_2_NETWORK_H
#define BOMBERMAN_SDL2_2_NETWORK_H

#include <SDL2/SDL_net.h>

#include "const.h"

typedef unsigned char ClientPacket;

typedef struct {
    TCPsocket socket;
//    UDPpacket *packet;
    IPaddress ip;

    TCPsocket client[SERVEUR_NUMBER_SOCKET];
    SDL_Thread *thread[SERVEUR_NUMBER_SOCKET];
    int mode, threadContinue, state;
} Network;

void Network_Init(int modeConnection);
void Network_ClientPrepareConnection(char *ip, Uint16 port);
int Network_ProcessClient(void *data);
void Network_ClientSendData(char data);
void Network_ClientSendRequest();
int Network_GetState();
void Network_SetState(int state);
void Network_ServerWaitingConnection();
int Network_GetMode();
void Network_Close();

#endif //BOMBERMAN_SDL2_2_NETWORK_H
