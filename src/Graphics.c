/*
 * file : graphics.c
 *
 * Ensemble des fonctions utilisé par la structure Graphics gérant les fonctionnalités graphiques du projet
 */

#include "Graphics.h"

static Graphics graphics;

void Graphics_loadGraphicsPlayers() {
    FILE *file = fopen("media/playerTexture.txt", "r");

    graphics.player = malloc(sizeof(SDL_Surface) * NUMBER_MAX_PLAYER);

    if (file != NULL) {
        char line[256];
        while (fgets(line, sizeof(line), file) != NULL) {

        }
    } else {
        fprintf(stderr, "Error opening \"media/playerTexture.txt\"\n");
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

void Graphics_Init() {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error in SDL_Init : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "Error in IMG_Init : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }
    if((graphics.screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE |
    SDL_DOUBLEBUF)) == NULL) {
        fprintf(stderr, "Error in SDL_SetVideoMode : %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Bomberman", NULL);
    Graphics_loadGraphicsPlayers();
}

void Graphics_closePlayer() {
    free(graphics.player);
}

void Graphics_Close() {
    Graphics_closePlayer();
    SDL_Quit();
}