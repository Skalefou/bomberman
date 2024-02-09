/*
 * file : Game.c
 *
 * Regroupe les fonctions utilisé par le noyaux du jeu
 */

#include "Game.h"
#include "Graphics.h"

void Game_RunGame() {
    Graphics_Init();
    atexit(Graphics_Close);
    Map_Init();
    atexit(Map_Close);

    Map_OpenMap(0);


    int active = 1;
    SDL_Event event;
    while(active) {
        SDL_WaitEvent(&event);

        switch(event.type) {
            case SDL_QUIT : active = 0; break;
            case SDL_KEYUP : active = 0; break;
            default : break;
        }

        Graphics_ClearScreen();
        Map_DisplayMap();
        Graphics_RefreshScreen();
    }
}