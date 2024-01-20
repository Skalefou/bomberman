/*
 * file : graphics.c
 *
 * Ensemble des fonctions utilisé par la structure graphics gérant les fonctionnalités graphiques du projet
 */

#include "Graphics.h"

static Graphics graphics;

void Graphics_Init() {
    //Chargement de la fenêtre
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error in SDL_Init : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if((graphics.screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE |
    SDL_DOUBLEBUF)) == NULL) {
        fprintf(stderr, "Error in SDL_SetVideoMode : %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    SDL_WM_SetCaption("Bomberman", NULL);

    //Chargement de la police/SDL_TTF
    if (TTF_Init() != 0) {
        fprintf(stderr, "Error in SDL_TTF : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if ((graphics.font = TTF_OpenFont("media/font.ttf", 16)) == NULL) {
        fprintf(stderr, "Please put a 'media/font.ttf' : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    graphics.debugText = NULL;
}

void Graphics_DebugTextDisplay(const char *text) {
    SDL_Rect position = {10, 10};
    graphics.debugText = TTF_RenderText_Blended(graphics.font, text, (SDL_Color){255, 255, 255});
    SDL_BlitSurface(graphics.debugText, NULL, graphics.screen, &position);

}

void Graphics_ClearScreen() {
    SDL_FillRect(graphics.screen, NULL, 0x000000);
}

void Graphics_UpdateScreen() {
    SDL_Flip(graphics.screen);
}

void Graphics_Close() {
    SDL_FreeSurface(graphics.debugText);
    TTF_CloseFont(graphics.font);
    TTF_Quit();
    SDL_Quit();
}