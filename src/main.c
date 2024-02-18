#define SDL_MAIN_HANDLED
#include "Game.h"

// Temporaire
int port;

int main(int argc, char * argv[]) {
    port = strcmp(argv[1], "1") == 0 ? NETWORK_HOST : NETWORK_CLIENT;
    Game_RunGame();
    return EXIT_SUCCESS;
}