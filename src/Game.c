/*
 * file : Game.c
 *
 * Regroupe les fonctions utilisé par le noyaux du jeu
 */

#include "Game.h"
#include "Graphics.h"
#include "Map.h"
#include "Network.h"

static Game game;

extern int port;

void Game_RunGame() {
    game.numberPlayer = 1;

    Graphics_Init();
    atexit(Graphics_Close);
    Map_Init();
    atexit(Map_Close);

    Network_Init(port);
    atexit(Network_Close);

    if (Network_GetMode() == NETWORK_CLIENT) {
        Network_ClientPrepareConnection("127.0.0.1", DEFAULT_PORT_HOST);
        Network_ClientSendRequest();
    }

    Map_OpenMap(0);
    SDL_Rect position = {2,2}; // temp
    Player_Init(1, &position);
    atexit(Player_Close);

    // Temp
    char action =


    int active = 1;
    SDL_Event event;
    while(active) {
        SDL_WaitEvent(&event);

        switch(event.type) {
            case SDL_QUIT : active = 0; break;
            case SDL_KEYUP : active = 0; break;
            case SDL_WINDOWEVENT:
                switch(event.window.event) {
                    case SDL_WINDOWEVENT_SIZE_CHANGED: Graphics_ResizeWindow(event.window.data1,
                                                                             event.window.data2,
                                                                             Map_GetSize()); break;
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        Network_SetState(PLAY_NETWORK);
                }
                break;
            default : break;
        }

        if (Network_GetState() == PENDING_NETWORK) {
            if(Network_GetMode() == NETWORK_HOST) {
                Network_ServerWaitingConnection();
            } else {
                Network_ClientPrepareConnection("127.0.0.1", DEFAULT_PORT_HOST);
                Network_ClientSendRequest();

            }
        } else if (Network_GetState() == PLAY_NETWORK) {
            if (Network_GetMode() == NETWORK_CLIENT) {
                char *messageToSend = "0 faute";
                Network_ClientSendData(messageToSend, (int)strlen(messageToSend));
            }
        }


        Graphics_ClearScreen();
        Map_DisplayMap();
        Player_Display();
        Graphics_RefreshScreen();
    }
}
