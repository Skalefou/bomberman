/*
 * file : Game.c
 *
 * Regroupe les fonctions utilisé par le noyaux du jeu
 */

#include "Game.h"



//TODO: Cette fonction est un placeholder, elle n'aura plus aucun intérêt une fois qu'on aura créer le menu du multijoueur
int placeholder_startMultiplayer(ConnectionInfo *connectionInfo) {
    FILE *file = fopen("placeholderMultiplayer.txt", "r");
    if(file == NULL) {
        return 0;
    }

    char serverOrClient;

    fscanf(file, "%c %hu", &serverOrClient, &connectionInfo->port);

    connectionInfo->host = serverOrClient == 's' ? NULL : "localhost";

    fclose(file);
    return 1;
}

void Game_RunGame() {
    Graphics_Init();
    Multiplayer_Init();
    atexit(Graphics_Close);
    atexit(Multiplayer_Close);

    ConnectionInfo connectionInfo;

    if(placeholder_startMultiplayer(&connectionInfo) == 1) {
        if(connectionInfo.host == NULL) {
            Multiplayer_CreateServer(connectionInfo.port);
        } else {
            Multiplayer_JoinServer("127.0.0.1", connectionInfo.port);
        }
    }

    int active = 1;
    SDL_Event event;
    while(active) {
        SDL_WaitEvent(&event);

        if(Multiplayer_IsServer()) {
            Multiplayer_ServerWaitPlayer();
        }

        switch(event.type) {
            case SDL_QUIT : active = 0; break;
            case SDL_KEYUP : active = 0; break;
            default : break;
        }
    }
}