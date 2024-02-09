/*
 * file : graphics.h
 *
 * Ce header gère l'initialisation des structures, prototypes et variable externes liés aux fonctionnalités graphiques
 */

#ifndef BOMBERMAN_GRAPHICS_H
#define BOMBERMAN_GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "const.h"
#include "Utils.h"

typedef struct {
    SDL_Surface **surface;
    int numberOfSurface;
} Texture;

//Structure Graphics gérant toutes les fonctionnalités graphiques
typedef struct {
    //Rendu et fenêtre
    SDL_Surface *screen;
    Texture *player;
    Texture tiles;

} Graphics;

//Fonction initialisant la SDL, la fenêtre et l'affichage vidéo
void Graphics_Init();
//Fonction fermant la SDL, la fenêtre et l'affichage vidéo

SDL_Surface* Graphics_resizeSurface(SDL_Surface *surface, int newWidth, int newHeight);
void Graphics_ClearScreen();
void Graphics_RefreshScreen();
void Graphics_DisplayTile(int idTile, SDL_Rect position);
void Graphics_closePlayer();
void Graphics_Close();
void Graphics_loadGraphicsPlayers();
void Graphics_loadGraphicsTiles();

#endif