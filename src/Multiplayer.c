#include "Multiplayer.h"

static Multiplayer multiplayer;
static TCPsocket serveur;
static TCPsocket client;
static Uint32 intip;

void Multiplayer_Init() {
    if(SDLNet_Init() < 0) {
        fprintf(stderr, "Error in SDLNet_Init: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    multiplayer.numberOfPlayer = 1;
    multiplayer.userConnectionInfo = malloc(sizeof(ConnectionInfo));
    multiplayer.state = MULTIPLAYER_NONE_STATE;
}

void Multiplayer_CreateServer(const Uint16 port) {
    multiplayer.userConnectionInfo->port = port;
    multiplayer.userConnectionInfo->host = NULL;
    if(SDLNet_ResolveHost(&multiplayer.userConnectionInfo->ip, multiplayer.userConnectionInfo->host, multiplayer.userConnectionInfo->port) != 0) {
        fprintf(stderr, "Error in SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    if((serveur = SDLNet_TCP_Open(&multiplayer.userConnectionInfo->ip)) == NULL) {
        fprintf(stderr, "Erreur SDLNet_TCP_Open : %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    multiplayer.state = MULTIPLAYER_WAITING_PLAYER;
}

void Multiplayer_JoinServer(char *ip, const Uint16 port) {
    multiplayer.userConnectionInfo->host = malloc(strlen(ip) + 1);
    strcpy(multiplayer.userConnectionInfo->host, ip);
    if(SDLNet_ResolveHost(&multiplayer.userConnectionInfo->ip, ip, port) != 0) {
        fprintf(stderr, "Error in SDLNet_ResolveHost: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }


    intip = SDL_SwapBE32(multiplayer.userConnectionInfo->ip.host);
    fprintf(stdout,
            "Target IP is %s at %d.%d.%d.%d:%u\n",
            SDLNet_ResolveIP(&multiplayer.userConnectionInfo->ip),
            intip >> 24, (intip >> 16) & 0xff,
            (intip >> 8) & 0xff, intip & 0xff,
            multiplayer.userConnectionInfo->ip.port);

    if((serveur = SDLNet_TCP_Open(&multiplayer.userConnectionInfo->ip)) == NULL) {
        fprintf(stderr, "Erreur SDLNet_TCP_Open : %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
}

void Multiplayer_ServerWaitPlayer() {
    if ((client = SDLNet_TCP_Accept(serveur)) != NULL) {
        multiplayer.state = MULTIPLAYER_CONTINUE;
        printf("Heyheyjey");
    }
}

int Multiplayer_State() {
    return multiplayer.state;
}

void Multiplayer_DisplayTest() {
    char text[256];
    sprintf(text, "State : %s\n",
            (multiplayer.state == MULTIPLAYER_WAITING_PLAYER ? "Connected" : "Not connected"));
    Graphics_DebugTextDisplay(text);
}

int Multiplayer_IsServer() {
    return multiplayer.userConnectionInfo->host == NULL;
}

void Multiplayer_Close() {
    free(multiplayer.userConnectionInfo->host);
    free(multiplayer.userConnectionInfo);
    SDLNet_Quit();
}