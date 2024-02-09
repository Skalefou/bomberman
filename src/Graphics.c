/*
 * file : graphics.c
 *
 * Ensemble des fonctions utilisé par la structure Graphics gérant les fonctionnalités graphiques du projet
 */

#include "Graphics.h"

static Graphics graphics;

SDL_Surface* Graphics_resizeSurface(SDL_Surface *surface, int newWidth, int newHeight) {
    SDL_Surface *resizedSurface = SDL_CreateRGBSurface(SDL_SWSURFACE, newWidth, newHeight, surface->format->BitsPerPixel,
                                                       surface->format->Rmask, surface->format->Gmask,
                                                       surface->format->Bmask, surface->format->Amask);
    SDL_FillRect(resizedSurface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
    return resizedSurface;
}

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

                char path[256] = TEXTURE_PATH;
                strcat(path, line);
                Utils_RemoveNewLineAtEnd(path);
                graphics.player[i].surface[y] = IMG_Load(path);
                if (graphics.player[i].surface[y] == NULL) {
                    fprintf(stderr, "%s\n", IMG_GetError());
                }
            }
            fclose(file);
        }
    } else {
        fprintf(stderr, "Error opening \"media/playerTexture.txt\"\n");
        exit(EXIT_FAILURE);
    }
}

void Graphics_loadGraphicsTiles() {
    FILE *file = fopen("media/tilesTexture.txt", "r");

    graphics.tiles.numberOfSurface = NUMBER_TILES;
    graphics.tiles.surface = malloc(sizeof(SDL_Surface*) * NUMBER_TILES);

    if (file == NULL) {
        fprintf(stderr, "Error opening \"media/tilesTexture.txt\"\n");
        exit(EXIT_FAILURE);
    }

    char line[256];
    for (int i = 0; i < NUMBER_TILES; i++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            fprintf(stderr, "Error in loading players asset (not enough texture)\n");
            continue;
        }

        char path[256] = TEXTURE_PATH;
        strcat(path, line);
        Utils_RemoveNewLineAtEnd(path);
        graphics.tiles.surface[i] = IMG_Load(path);
        if (graphics.tiles.surface[i] == NULL) {
            fprintf(stderr, "%s\n", IMG_GetError());
        }
        graphics.tiles.surface[i] = Graphics_resizeSurface(graphics.tiles.surface[i],
                                                           SIZE_TEXTURE_TILE_ORIGINAL_PIXEL*ZOOM_TEXTURE,
                                                           SIZE_TEXTURE_TILE_ORIGINAL_PIXEL*ZOOM_TEXTURE);
    }
    fclose(file);
}

void Graphics_ClearScreen() {
    SDL_FillRect(graphics.screen, NULL, SDL_MapRGB(graphics.screen->format, 0, 0, 0));
}

void Graphics_RefreshScreen() {
    SDL_Flip(graphics.screen);
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
    Graphics_loadGraphicsTiles();
}

void Graphics_DisplayTile(int idTile, SDL_Rect position) {
    SDL_BlitSurface(graphics.tiles.surface[idTile], NULL, graphics.screen, &position);
}

void Graphics_closePlayer() {
    for(int i = 0; i < NUMBER_MAX_PLAYER; i++) {
        free(graphics.player[i].surface);
    }
    free(graphics.player);
}

void Graphics_Close() {
    Graphics_closePlayer();
    free(graphics.tiles.surface);
    SDL_FreeSurface(graphics.screen);
    SDL_Quit();
}