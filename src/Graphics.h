/*
 * file : graphics.h
 *
 * Ce header gère l'initialisation des structures, prototypes et variable externes liés aux fonctionnalités graphiques
 */

#ifndef BOMBERMAN_GRAPHICS_H
#define BOMBERMAN_GRAPHICS_H

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Game.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define NUMBER_TEXTURE_PLAYER 18

typedef struct {
    SDL_Surface *surface;
    int numberOfSurface;
} Texture;

//Structure Graphics gérant toutes les fonctionnalités graphiques
typedef struct {
    //Rendu et fenêtre
    SDL_Surface *screen;
    Texture *player;

} Graphics;

//Fonction initialisant la SDL, la fenêtre et l'affichage vidéo
void Graphics_Init();
//Fonction fermant la SDL, la fenêtre et l'affichage vidéo
void Graphics_closePlayer();
void Graphics_Close();
void Graphics_loadGraphicsPlayers();

#endif