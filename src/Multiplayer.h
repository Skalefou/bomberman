#ifndef BOMBERMAN_MULTIPLAYER_H
#define BOMBERMAN_MULTIPLAYER_H

#include <stdlib.h>
#include <string.h>
#include "SDL_net.h"

typedef struct {
    IPaddress ip;
    char *host;
    Uint16 port;

} ConnectionInfo;

typedef struct {
    ConnectionInfo *userConnectionInfo;
    ConnectionInfo *opponentConnectionInfo;
    int numberOfPlayer;
} Multiplayer;

void Multiplayer_Init();
void Multiplayer_CreateServer(Uint16 port);
void Multiplayer_ServerWaitPlayer();
int Multiplayer_IsServer();
void Multiplayer_JoinServer(char *ip, Uint16 port);
void Multiplayer_Close();

#endif //BOMBERMAN_MULTIPLAYER_H
