/*
 * file : graphics.h
 *
 * Ce header gère l'initialisation des structures, prototypes et variable externes liés aux fonctionnalités graphiques
 */

#ifndef BOMBERMAN_GRAPHICS_H
#define BOMBERMAN_GRAPHICS_H

#include <SDL/SDL.h>
#include <SDL_ttf.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

//Structure Graphics gérant toutes les fonctionnalités graphiques
typedef struct {
    //Rendu et fenêtre
    SDL_Surface *screen;
    SDL_Surface *debugText;
    TTF_Font *font;

} Graphics;

//Fonction initialisant la SDL, la fenêtre et l'affichage vidéo
void Graphics_Init();
void Graphics_DebugTextDisplay(const char *text);
void Graphics_ClearScreen();
void Graphics_UpdateScreen();
//Fonction fermant la SDL, la fenêtre et l'affichage vidéo
void Graphics_Close();


#endif