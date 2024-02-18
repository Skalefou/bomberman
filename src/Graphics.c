/*
 * file : graphics.c
 *
 * Ensemble des fonctions utilisé par la structure Graphics gérant les fonctionnalités graphiques du projet
 */

#include "Graphics.h"

static Graphics graphics;

void Graphics_loadGraphicsPlayers() {
    SDL_Surface *surface;
    FILE *file = fopen("media/playerTexture.txt", "r");

    graphics.player = malloc(sizeof(Texture*) * NUMBER_MAX_PLAYER);

    if (file != NULL) {
        char line[256];
        for (int i = 0; i < NUMBER_MAX_PLAYER; i++){
            graphics.player[i].texture = malloc(sizeof(SDL_Texture*) * NUMBER_TEXTURE_PER_PLAYER);
            graphics.player[i].numberOfTexture = NUMBER_TEXTURE_PER_PLAYER;
            for (int y = 0; y < NUMBER_TEXTURE_PER_PLAYER; y++) {
                if (fgets(line, sizeof(line), file) == NULL) {
                    fprintf(stderr, "Error in loading players asset (not enough texture)\n");
                    continue;
                }

                char path[256] = TEXTURE_PATH;
                strcat(path, line);
                Utils_RemoveNewLineAtEnd(path);

                surface = IMG_Load(path);
                if (surface == NULL) {
                    fprintf(stderr, "%s\n", IMG_GetError());
                }
                graphics.player[i].texture[y] = SDL_CreateTextureFromSurface(graphics.renderer, surface);
                if (graphics.player[i].texture[y] == NULL) {
                    fprintf(stderr, "%s\n", IMG_GetError());
                }
                SDL_FreeSurface(surface);
            }
            fclose(file);
        }
    } else {
        fprintf(stderr, "Error opening \"media/playerTexture.txt\"\n");
        exit(EXIT_FAILURE);
    }
}


extern int mode = 0;

void Graphics_DisplayMenu() {
    // Charger l'image à partir d'un fichier
    SDL_Surface *menuSurface = IMG_Load("media/menu/menu.png");
    if (menuSurface == NULL) {
        fprintf(stderr, "Erreur lors du chargement de l'image du menu : %s\n", IMG_GetError());
        return;
    }

    // Créer une texture à partir de l'image
    SDL_Texture *menuTexture = SDL_CreateTextureFromSurface(graphics.renderer, menuSurface);
    if (menuTexture == NULL) {
        fprintf(stderr, "Erreur lors de la création de la texture du menu : %s\n", SDL_GetError());
        SDL_FreeSurface(menuSurface);
        return;
    }

    SDL_FreeSurface(menuSurface);

    // Obtenir la taille actuelle de la fenêtre
    int winWidth, winHeight;
    SDL_GetWindowSize(graphics.window, &winWidth, &winHeight);

    // Créer un rectangle de destination pour la texture du menu
    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = winWidth;
    destRect.h = winHeight;

    // Rendre la texture à l'écran
    SDL_RenderCopy(graphics.renderer, menuTexture, NULL, NULL);

    // Mettre à jour l'écran
    SDL_RenderPresent(graphics.renderer);

    // Attendre un certain temps pour que le menu soit visible
    SDL_Event event;
    while (1) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x;
            int y = event.button.y;
            int width, height;
            SDL_GetWindowSize(graphics.window, &width, &height);

            int centerX = winWidth / 2;
            int centerY = winHeight / 2;

            int intervalX = winWidth * 0.03;
            int intervalY = winHeight * 0.03;

            intervalX += 75;
            intervalY += 75;
            if (x > centerX - intervalX && x < centerX + intervalX && y > centerY - intervalY && y < centerY + intervalY) {
                // Mode solo
                break;
            }
            intervalX += 75;
            intervalY += 75;
            if (x > centerX - intervalX && x < centerX + intervalX && y > centerY - intervalY && y < centerY + intervalY) {
                mode = 2;
                break;
            }
        }

        // Libérer la texture car nous n'en avons plus besoin
        SDL_DestroyTexture(menuTexture);
    }
}

void Graphics_Menu_Multi_Display(){
    // Charger l'image à partir d'un fichier
    SDL_Surface *menuSurface = IMG_Load("media/menu/menuMulti.png");
    if (menuSurface == NULL) {
        fprintf(stderr, "Erreur lors du chargement de l'image du menu : %s\n", IMG_GetError());
        return;
    }

    // Créer une texture à partir de l'image
    SDL_Texture *menuTexture = SDL_CreateTextureFromSurface(graphics.renderer, menuSurface);
    if (menuTexture == NULL) {
        fprintf(stderr, "Erreur lors de la création de la texture du menu : %s\n", SDL_GetError());
        SDL_FreeSurface(menuSurface);
        return;
    }

    SDL_FreeSurface(menuSurface);

    // Obtenir la taille actuelle de la fenêtre
    int winWidth, winHeight;
    SDL_GetWindowSize(graphics.window, &winWidth, &winHeight);

    // Créer un rectangle de destination pour la texture du menu
    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = winWidth;
    destRect.h = winHeight;

    // Rendre la texture à l'écran
    SDL_RenderCopy(graphics.renderer, menuTexture, NULL, &destRect);

    // Mettre à jour l'écran
    SDL_RenderPresent(graphics.renderer);

    // Libérer la texture car nous n'en avons plus besoin
    SDL_DestroyTexture(menuTexture);

    SDL_Event event;
    while (1) {
        SDL_WaitEvent(&event);
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x = event.button.x;
            int y = event.button.y;
            int width, height;
            SDL_GetWindowSize(graphics.window, &width, &height);

            int centerX = winWidth / 10;
            int centerY = winHeight / 1.5;

            int intervalX = winWidth * 0.03;
            int intervalY = winHeight * 0.03;

            if (x > centerX - intervalX && x < centerX + intervalX && y > centerY - intervalY && y < centerY + intervalY) {
                //host
                mode = 4;
                break;
            }
            intervalX += 75;
            intervalY += 25;
            if (x > centerX - intervalX && x < centerX + intervalX && y > centerY - intervalY && y < centerY + intervalY) {
                //join
                mode = 3;
                break;
            }
        }

        // Libérer la texture car nous n'en avons plus besoin
        SDL_DestroyTexture(menuTexture);
    }
}

void Graphics_SetFullScreen() {
    if (SDL_SetWindowFullscreen(graphics.window, SDL_WINDOW_FULLSCREEN) < 0) {
        fprintf(stderr, "Erreur lors du passage en plein écran : %s\n", SDL_GetError());
    }
}

void Graphics_loadGraphicsTiles() {
    SDL_Surface *surface;
    FILE *file = fopen("media/tilesTexture.txt", "r");

    graphics.tiles.numberOfTexture = NUMBER_TILES;
    graphics.tiles.texture = malloc(sizeof(SDL_Texture*) * NUMBER_TILES);
    graphics.tiles.size = malloc(sizeof(SDL_Rect) * NUMBER_TILES);

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
        surface = IMG_Load(path);
        if (surface == NULL) {
            fprintf(stderr, "%s\n", IMG_GetError());
        }

        graphics.tiles.texture[i] = SDL_CreateTextureFromSurface(graphics.renderer, surface);
        if (graphics.tiles.texture[i] == NULL) {
            fprintf(stderr, "%s\n", IMG_GetError());
        }
        SDL_FreeSurface(surface);
        SDL_QueryTexture(graphics.tiles.texture[i], NULL, NULL, &graphics.tiles.size[i].w, &graphics.tiles.size[i].h);

    }
    fclose(file);
}

void Graphics_SetZoomAllTexture(double coefZoomW, double coefZoomH) {
    graphics.coefZoomW = coefZoomW;
    graphics.coefZoomH = coefZoomH;
}

void Graphics_ClearScreen() {
    SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 0);
    SDL_RenderClear(graphics.renderer);
}

void Graphics_RefreshScreen() {
    SDL_RenderPresent(graphics.renderer);
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

    graphics.window = SDL_CreateWindow("Bomberman",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       WINDOW_WIDTH,
                                       WINDOW_HEIGHT,
                                       SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    SDL_SetWindowMinimumSize(graphics.window,
                             SIZE_TEXTURE_TILE_ORIGINAL_PIXEL*MAP_SIZE_BASE_X,
                             MAP_SIZE_BASE_Y*SIZE_TEXTURE_TILE_ORIGINAL_PIXEL);

    if(graphics.window == NULL) {
        fprintf(stderr, "Error in creation window : %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    graphics.renderer = SDL_CreateRenderer(graphics.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(graphics.renderer == NULL) {
        fprintf(stderr, "Error in creation render : %s\n", SDL_GetError());
        SDL_DestroyWindow(graphics.window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    Graphics_SetZoomAllTexture(ZOOM_TEXTURE_ORIGINAL, ZOOM_TEXTURE_ORIGINAL);
    //Graphics_loadGraphicsPlayers();
    Graphics_loadGraphicsTiles();
}

void Graphics_DisplayTile(int idTile, SDL_Rect position) {
    SDL_Surface *surface = IMG_Load("media/texture/explosion_1.png");
    if (surface == NULL) {
        fprintf(stderr, "%s\n", IMG_GetError());
    }
    position.w = (int)(graphics.coefZoomW * graphics.tiles.size[idTile].w);
    position.h = (int)(graphics.coefZoomH * graphics.tiles.size[idTile].h);

    SDL_RenderCopy(graphics.renderer, graphics.tiles.texture[idTile], NULL, &position);
}

SDL_Rect Graphics_GetSizeTile(int idTile) {
    return graphics.tiles.size[idTile];
}

double Graphics_GetCoefZoomW() {
    return graphics.coefZoomW;
}

double Graphics_GetCoefZoomH() {
    return graphics.coefZoomH;
}

void Graphics_ResizeWindow(int win_w, int win_h, SDL_Rect mapSize) {
    double width = (double)((double)win_w / (MAP_SIZE_BASE_X * SIZE_TEXTURE_TILE_ORIGINAL_PIXEL*ZOOM_TEXTURE_ORIGINAL))*ZOOM_TEXTURE_ORIGINAL;
    double height = (double)((double)win_h / (MAP_SIZE_BASE_Y * SIZE_TEXTURE_TILE_ORIGINAL_PIXEL*ZOOM_TEXTURE_ORIGINAL))*ZOOM_TEXTURE_ORIGINAL;
    Graphics_SetZoomAllTexture(width, height);
}

void Graphics_closePlayer() {
    for(int i = 0; i < NUMBER_MAX_PLAYER; i++) {
        for(int y = 0; y < NUMBER_TEXTURE_PER_PLAYER; y++) {
            SDL_DestroyTexture(graphics.player[i].texture[y]);
        }
        free(graphics.player[i].texture);
    }
    free(graphics.player);
}

void Graphics_Close() {
    //Graphics_closePlayer();
    free(graphics.tiles.size);
    for(int i = 0; i < NUMBER_TILES; i++) {
        SDL_DestroyTexture(graphics.tiles.texture[i]);

    }

    free(graphics.tiles.texture);
    SDL_DestroyRenderer(graphics.renderer);
    SDL_DestroyWindow(graphics.window);
    SDL_Quit();
}
