/*
 * file : Game.c
 *
 * Regroupe les fonctions utilisé par le noyaux du jeu
 */

#include "Game.h"

static Game game;

void Game_RunGame() {
    game.numberPlayer = 1;

    Graphics_Init();
    atexit(Graphics_Close);
    Map_Init();
    atexit(Map_Close);

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
                                PoserBombe(0);
                                printf("space\n");
                                break;
                        }
                        break;
                }
            }

        Graphics_ClearScreen();
        Map_DisplayMap();
        Player_Display();
        Graphics_RefreshScreen();
    }
}