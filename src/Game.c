/*
 * file : Game.c
 *
 * Regroupe les fonctions utilisé par le noyaux du jeu
 */

#include "Game.h"
#include "Graphics.h"
#include "Map.h"

static Game game;

void Game_RunGame() {
    game.numberPlayer = 1;

    Graphics_Init();
    atexit(Graphics_Close);
    Map_Init();
    atexit(Map_Close);

    Map_OpenMap(0);
    SDL_Rect position = {2,2}; // temp
    Player_Init(1, &position);
    atexit(Player_Close);


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
            default : break;
        }

        Graphics_ClearScreen();
        Map_DisplayMap();
        Player_Display();
        Graphics_RefreshScreen();
    }
}
