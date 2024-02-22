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
    char clientAction = 45;

    Map_OpenMap(0);
    SDL_Rect position[2] = {{1,1}, {4,1}};


    int active = 1;
    SDL_Event event;
    while(active) {
        Graphics_ClearScreen();
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    active = 0;
                    break;
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym) {
                            case SDLK_LEFT:
                                if (Network_GetState() == PLAY_NETWORK) {

                                    Player_Move(0, -1, 0);
                                }
                                break;
                            case SDLK_RIGHT:
                                if (Network_GetState() == PLAY_NETWORK) {
                                    Player_Move(0, 1, 0);
                                }
                                break;
                            case SDLK_UP:
                                if (Network_GetState() == PLAY_NETWORK) {
                                    Player_Move(0, 0, -1);
                                }
                                break;
                            case SDLK_DOWN:
                                if (Network_GetState() == PLAY_NETWORK) {
                                    Player_Move(0, 0, 1);
                                }
                                break;
                            case SDLK_SPACE:
                                if (Network_GetState() == PLAY_NETWORK) {
                                    printf("space\n");
                                }
                                break;
                            case SDLK_c:
                                if (Network_GetState() == PENDING_NETWORK) {
                                    Player_Init(2, position);
                                    atexit(Player_Close);
                                    Network_SetState(PLAY_NETWORK);
                                }

                                break;
                        }
                        break;
                }
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
                Network_ClientSendData(clientAction);
                Network_ClientReceiveData();
            } else {
                Network_EncryptJSON();
            }
        }

        Map_DisplayMap();
        if (Network_GetState() == PLAY_NETWORK) {
            Player_Display();
        }

        if (Network_GetState() == PENDING_NETWORK) {
            int indexDebugGraphics = Network_GetMode() == NETWORK_HOST ? 0 : 1;
            Graphics_DisplayDebugGraphics(indexDebugGraphics);
        }
        Graphics_RefreshScreen();
        SDL_Delay(16);
    }
}
