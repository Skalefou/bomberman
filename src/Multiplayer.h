#ifndef BOMBERMAN_MULTIPLAYER_H
#define BOMBERMAN_MULTIPLAYER_H

#include <stdlib.h>
#include <string.h>
#include "SDL_net.h"
#include "Graphics.h"

enum {MULTIPLAYER_NONE_STATE, MULTIPLAYER_WAITING_PLAYER, MULTIPLAYER_CONTINUE};

typedef struct {
    IPaddress ip;
    char *host;
    Uint16 port;

} ConnectionInfo;

typedef struct {
    ConnectionInfo *userConnectionInfo;
    ConnectionInfo *opponentConnectionInfo;
    int numberOfPlayer;
    int state;
} Multiplayer;

void Multiplayer_Init();
void Multiplayer_CreateServer(Uint16 port);
void Multiplayer_ServerWaitPlayer();
void Multiplayer_ServerIsWaitingPlaying();
int Multiplayer_State();
void Multiplayer_DisplayTest();
int Multiplayer_IsServer();
void Multiplayer_JoinServer(char *ip, Uint16 port);
void Multiplayer_Close();

#endif //BOMBERMAN_MULTIPLAYER_H
