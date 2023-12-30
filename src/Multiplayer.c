#include "Multiplayer.h"

static Multiplayer multiplayer;

void Multiplayer_Init() {
    if(SDLNet_Init() < 0) {
        fprintf(stderr, "Error in SDLNet_Init: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }
    multiplayer.numberOfPlayer = 1;
}

void Multiplayer_CreateServer(Uint16 port) {
    
}

void Multiplayer_Close() {
    SDLNet_Quit();
}