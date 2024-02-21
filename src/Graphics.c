/*
 * file : graphics.c
 *
 * Ensemble des fonctions utilisé par la structure Graphics gérant les fonctionnalités graphiques du projet
 */

#include "Graphics.h"

static Graphics graphics;
double win_x = WINDOW_WIDTH;
double win_y = WINDOW_HEIGHT;

double xoffset;
double yoffset;

short til[3] = {0, 1, 3};
short tile_number = 3;

short GetTileNumber(){
    return tile_number;
};

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
    };
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "Error in IMG_Init : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    };

    graphics.window = SDL_CreateWindow("Bomberman Editor",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       WINDOW_WIDTH,
                                       WINDOW_HEIGHT,
                                       SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    SDL_Surface *icon = IMG_Load("media/texture/editor.png");
    if (icon == NULL) {
        fprintf(stderr, "%s\n", IMG_GetError());
    };

    SDL_SetWindowIcon(graphics.window, icon);

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

double Graphics_Get_Window_Size_H(){
    return win_y;
};

double Graphics_Get_Window_Size_W(){
    return win_x;
};

// Ici ca a changé
void Graphics_DisplayTile(int idTile, SDL_Rect position, int mapx, int mapy) {
    xoffset = (win_x/3 - (mapx*graphics.tiles.size[idTile].w)/2);
    yoffset = (win_y - (mapy* graphics.coefZoomH * graphics.tiles.size[idTile].h))/2;
    position.x += xoffset;
    position.y += yoffset;
    position.w = (graphics.coefZoomW * graphics.tiles.size[idTile].w);
    position.h = (graphics.coefZoomH * graphics.tiles.size[idTile].h);

    SDL_RenderCopy(graphics.renderer, graphics.tiles.texture[idTile], NULL, &position);
};

void Graphics_show_mouse(){
    int x, y;
    int buttons = SDL_GetMouseState(&x, &y);

    SDL_Surface *pinceauSurface = IMG_Load("media/texture/pinceau.png");
    if (pinceauSurface == NULL) {
        fprintf(stderr, "Erreur lors du chargement de l'image du pinceau : %s\n", IMG_GetError());
        return;
    };

    SDL_Texture *pinceauTexture = SDL_CreateTextureFromSurface(graphics.renderer, pinceauSurface);
    if (pinceauTexture == NULL) {
        fprintf(stderr, "Erreur lors de la création de la texture du pinceau : %s\n", SDL_GetError());
        SDL_FreeSurface(pinceauSurface);
        return;
    };

    SDL_FreeSurface(pinceauSurface);

    // Créer un rectangle de destination pour la texture du pinceau
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y - 48;
    destRect.w = 48;
    destRect.h = 48;

    SDL_RenderCopy(graphics.renderer, pinceauTexture, NULL, &destRect);

    SDL_DestroyTexture(pinceauTexture);
    
};

SDL_Rect Graphics_GetSizeTile(int idTile) {
    return graphics.tiles.size[idTile];
}

double Graphics_GetCoefZoomW() {
    return graphics.coefZoomW;
}

double Graphics_GetCoefZoomH() {
    return graphics.coefZoomH;
}

// Ici ca a changé
void Graphics_ResizeWindow(int win_w, int win_h, SDL_Rect mapSize) {
    double width = (double)((double)win_w / (MAP_SIZE_BASE_X * SIZE_TEXTURE_TILE_ORIGINAL_PIXEL*ZOOM_TEXTURE_ORIGINAL))*ZOOM_TEXTURE_ORIGINAL;
    double height = (double)((double)win_h / (MAP_SIZE_BASE_Y * SIZE_TEXTURE_TILE_ORIGINAL_PIXEL*ZOOM_TEXTURE_ORIGINAL))*ZOOM_TEXTURE_ORIGINAL;
    
    win_x = win_w;
    win_y = win_h;

    double min = (width<height?width:height)*2/3;
    Graphics_SetZoomAllTexture(min, min);
};

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

    
    SDL_DestroyTexture(graphics.background);

    free(graphics.tiles.texture);
    SDL_DestroyRenderer(graphics.renderer);
    SDL_DestroyWindow(graphics.window);
    SDL_Quit();
}

void Graphics_DisplayCell() {
    SDL_Surface *IconSurface = IMG_Load("media/texture/icon.png");
    if (IconSurface == NULL) {
        fprintf(stderr, "Erreur lors du chargement de l'image du Icon : %s\n", IMG_GetError());
        return;
    };

    SDL_Texture *IconTexture = SDL_CreateTextureFromSurface(graphics.renderer, IconSurface);
    if (IconTexture == NULL) {
        fprintf(stderr, "Erreur lors de la création de la texture du Icon : %s\n", SDL_GetError());
        SDL_FreeSurface(IconSurface);
        return;
    };
    
    SDL_FreeSurface(IconSurface);

    SDL_Surface *IconActive = IMG_Load("media/texture/icon_active.png");
    if (IconActive == NULL) {
        fprintf(stderr, "Erreur lors du chargement de l'image du Icon : %s\n", IMG_GetError());
        return;
    };

    SDL_Texture *IconActiveTexture = SDL_CreateTextureFromSurface(graphics.renderer, IconActive);
    if (IconTexture == NULL) {
        fprintf(stderr, "Erreur lors de la création de la texture du Icon : %s\n", SDL_GetError());
        SDL_FreeSurface(IconActive);
        return;
    };
    
    SDL_FreeSurface(IconActive);


    
    short template = 32;
    short item = 16;
    short x = MapGetX();
    short y = MapGetY();

    int xoffset = (win_x/3*2 - (x*graphics.tiles.size[0].w)/2);
    int yoffset = (win_y - (y* graphics.coefZoomH * graphics.tiles.size[0].h))/2;

    int h = (y* graphics.coefZoomH * graphics.tiles.size[0].h) / (tile_number+1);

    int cursor_value = GetCursorValue();

    for (short i = 0; i < tile_number; i++){

        SDL_Rect destRect;
        destRect.x = xoffset;
        destRect.y = i * h + yoffset + 5*template/2;
        destRect.w = graphics.coefZoomW * template;
        destRect.h = graphics.coefZoomH * template;

        SDL_RenderCopy(graphics.renderer, (i==cursor_value?IconActiveTexture:IconTexture), NULL, &destRect);

        destRect.x = xoffset + 3*(template - item)/2;
        destRect.y = i * h + template - item/2 + yoffset + 5*template/2;
        destRect.w = graphics.coefZoomW * item;
        destRect.h = graphics.coefZoomH * item;
        SDL_RenderCopy(graphics.renderer, graphics.tiles.texture[til[i]], NULL, &destRect);
        
    };

    SDL_DestroyTexture(IconActiveTexture);
    SDL_DestroyTexture(IconTexture);
};

void Graphics_DisplayMenu() {
    // Charger l'image à partir d'un fichier
    SDL_Surface *menuSurface = IMG_Load("media/texture/background.png");
    if (menuSurface == NULL) {
        fprintf(stderr, "Erreur lors du chargement de l'image du menu : %s\n", IMG_GetError());
        return;
    };

    // Créer une texture à partir de l'image
    SDL_Texture *menuTexture = SDL_CreateTextureFromSurface(graphics.renderer, menuSurface);
    if (menuTexture == NULL) {
        fprintf(stderr, "Erreur lors de la création de la texture du menu : %s\n", SDL_GetError());
        SDL_FreeSurface(menuSurface);
        return;
    };

    SDL_FreeSurface(menuSurface);

    // Obtenir la taille actuelle de la fenêtre
    int winWidth, winHeight;
    SDL_GetWindowSize(graphics.window, &winWidth, &winHeight);


    // Créer un rectangle de destination pour la texture du menu
    SDL_Rect destRect;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = win_x>win_y?win_x:win_y*16/9;
    destRect.h = win_x>win_y?win_x*9/16:win_y;


    // Rendre la texture à l'écran
    SDL_RenderCopy(graphics.renderer, menuTexture, NULL, &destRect);

    SDL_DestroyTexture(menuTexture);
};