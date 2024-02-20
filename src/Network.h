#ifndef BOMBERMAN_SDL2_2_NETWORK_H
#define BOMBERMAN_SDL2_2_NETWORK_H

#include <SDL2/SDL_net.h>

#include "const.h"

typedef struct {
    TCPsocket socket;
//    UDPpacket *packet;
    IPaddress ip;

    TCPsocket clientPlayer;
    SDL_Thread *thread;
    int mode;
} Network;

void Network_Init(int modeConnection);
void Network_ClientPrepareConnection(char *ip, Uint16 port);
int Network_ProcessClient(void *data);
void Network_ClientSendData(void *data, int size);
void Network_ClientSendRequest();
void Network_ServerWaitingConnection();
int Network_GetMode();
void Network_Close();

#endif //BOMBERMAN_SDL2_2_NETWORK_H
