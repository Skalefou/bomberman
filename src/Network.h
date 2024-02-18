#ifndef BOMBERMAN_SDL2_2_NETWORK_H
#define BOMBERMAN_SDL2_2_NETWORK_H

#include <SDL2/SDL_net.h>

#include "const.h"

typedef struct {
    UDPsocket socket;
    UDPpacket *packet;
    IPaddress ip;

    int mode;
} Network;

void Network_Init(int modeConnection);
void Network_ClientPrepareConnection(char *ip, Uint16 port);

void Network_ClientSendRequest();
void Network_ServerWaitingConnection();
int Network_GetMode();
void Network_Close();

#endif //BOMBERMAN_SDL2_2_NETWORK_H
