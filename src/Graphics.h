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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "const.h"
#include "Utils.h"

typedef struct {
    SDL_Texture **texture;
    SDL_Rect *size;
    int numberOfTexture;
} Texture;

//Structure Graphics gérant toutes les fonctionnalités graphiques
typedef struct {
    SDL_Window *window; // Utilisez SDL_Window pour la fenêtre
    SDL_Renderer *renderer; // Utilisez SDL_Renderer pour le rendu
    SDL_Cursor *cursor;
    Texture *player;
    Texture tiles;
    SDL_Texture * background;
    double coefZoomW, coefZoomH;
} Graphics;

//Fonction initialisant la SDL, la fenêtre et l'affichage vidéo
void Graphics_Init();
//Fonction fermant la SDL, la fenêtre et l'affichage vidéo

//SDL_Surface* Graphics_resizeSurface(SDL_Surface *surface, int newWidth, int newHeight);

short GetTileNumber();
int GetCursorValue();
void Graphics_ClearScreen();
void Graphics_RefreshScreen();
void Graphics_DisplayMenu();
void Graphics_DisplayCell();
void Graphics_show_mouse();
double Graphics_Get_Window_Size_H();
double Graphics_Get_Window_Size_W();
void Graphics_DisplayTile(int idTile, SDL_Rect position, int mapx, int mapy);
void Graphics_SetZoomAllTexture(double coefZoomW, double coefZoomH);
SDL_Rect Graphics_GetSizeTile(int idTile);
double Graphics_GetCoefZoomW();
double Graphics_GetCoefZoomH();
void Graphics_ResizeWindow(int win_w, int win_h, SDL_Rect mapSize);
void Graphics_closePlayer();
void Graphics_Close();
void Graphics_loadGraphicsPlayers();
void Graphics_loadGraphicsTiles();

#endif
