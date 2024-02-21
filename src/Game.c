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
    SDL_Rect position = {1,1};
    Player_Init(1, &position);
    atexit(Player_Close);

    int active = 1;
    SDL_Event event;
    while(active) {
            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_QUIT:
                        active = 0;
                        break;
                    case SDL_KEYDOWN:
                        printf("key pressed\n");
                        switch(event.key.keysym.sym) {
                            case SDLK_LEFT:
                                Player_Move(0, -1, 0);
                                printf("left\n");
                                break;
                            case SDLK_RIGHT:
                                Player_Move(0, 1, 0);
                                printf("right\n");
                                break;
                            case SDLK_UP:
                                Player_Move(0, 0, -1);
                                printf("up\n");
                                break;
                            case SDLK_DOWN:
                                Player_Move(0, 0, 1);
                                printf("down\n");
                                break;
                            case SDLK_SPACE:
                                printf("space\n");
                                break;
                            case SDLK_a:
                                Network_SetState(PLAY_NETWORK);
                                break;
                        }
                        break;
                }
            }
        SDL_WaitEvent(&event);

        switch(event.type) {
            case SDL_QUIT : active = 0; break;
            case SDL_WINDOWEVENT:
                switch(event.window.event) {
                    case SDL_WINDOWEVENT_SIZE_CHANGED: Graphics_ResizeWindow(event.window.data1,
                                                                             event.window.data2,
                                                                             Map_GetSize()); break;
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        Network_SetState(PLAY_NETWORK);
                }
                break;
            default : break;
        }

        Network_EncryptJSON();
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
            }
        }


        Graphics_ClearScreen();
        Map_DisplayMap();
        Player_Display();
        Graphics_RefreshScreen();
        SDL_Delay(16);
    }
}
