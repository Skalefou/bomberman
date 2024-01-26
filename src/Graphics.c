/*
 * file : graphics.c
 *
 * Ensemble des fonctions utilisé par la structure Graphics gérant les fonctionnalités graphiques du projet
 */

#include "Graphics.h"

static Graphics graphics;

void Graphics_loadGraphicsPlayers() {
    FILE *file = fopen("media/playerTexture.txt", "r");

    graphics.player = malloc(sizeof(Texture) * NUMBER_MAX_PLAYER);

    if (file != NULL) {
        char line[256];
        for (int i = 0; i < NUMBER_MAX_PLAYER; i++){
            graphics.player[i].surface = malloc(sizeof(SDL_Surface*) * NUMBER_TEXTURE_PER_PLAYER);
            graphics.player[i].numberOfSurface = NUMBER_TEXTURE_PER_PLAYER;
            for (int y = 0; y < NUMBER_TEXTURE_PER_PLAYER; y++) {
                if (fgets(line, sizeof(line), file) == NULL) {
                    fprintf(stderr, "Error in loading players asset (not enough texture)\n");
                    continue;
                }
                // CACA
                SDL_Surface *surface = IMG_Load(strcat("Salut", line));
                if (graphics.player[i].surface[y] == NULL) {
                    fprintf(stderr, "Error in loading players assets (error in the texture path)\n");
                } else {
                    fprintf(stderr, "OPEN TEXTURE\n");
                }
            }
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
    for(int i = 0; i < NUMBER_MAX_PLAYER; i++) {
        free(graphics.player[i].surface);
    }
    free(graphics.player);
}

void Graphics_Close() {
    Graphics_closePlayer();
    SDL_Quit();
}