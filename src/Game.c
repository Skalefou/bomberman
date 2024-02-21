/*
 * file : Game.c
 *
 * Regroupe les fonctions utilisé par le noyaux du jeu
 */

#include "Game.h"
#include "Graphics.h"
#include "Map.h"
#include "editor.h"

void Game_RunGame() {
    Graphics_Init();
    atexit(Graphics_Close);

    SDL_ShowCursor(SDL_DISABLE);

    Map_Init();
    atexit(Map_Close);

    Map_OpenMap(0);


    int active = 1;
    SDL_Event event;
    while(active) {
        SDL_WaitEvent(&event);

        switch(event.type) {
            case SDL_QUIT :
                active = 0;
                break;

            case SDL_MOUSEWHEEL :
                
                if(event.wheel.y > 0){
                    DECCursorValue();
                } else if(event.wheel.y < 0){
                    ADDCursorValue();
                };

                break;

            case SDL_MOUSEBUTTONDOWN :
                Map_Modify();
                break;

            case SDL_WINDOWEVENT:
                switch(event.window.event) {
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        Graphics_ResizeWindow(event.window.data1, event.window.data2, Map_GetSize());
                        break;
                };
                break;

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_s){
                    saveMap();
                };
                break;

            default : break;
        };

        Graphics_ClearScreen();

        Graphics_DisplayMenu();
        Graphics_DisplayCell();
        Map_DisplayMap();
        Graphics_show_mouse();
        
        Graphics_RefreshScreen();
    };

    
};
