#ifndef BOMBERMAN_MAP_H
#define BOMBERMAN_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Le code s'adaptant à windows est inutile si on utilise la msys2 sur windows
#ifdef ____WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif

#include "const.h"
#include "Utils.h"
#include "Graphics.h"

typedef struct {
    char **listNameMap;
    int numberListNameMap;
    int idUsedMap;
    int **tileMap;
    int size_x, size_y;
} Map;

int Map_OpenMap(const int id);
void Map_addListNameMap(char *name);
void Map_Init();
void Map_DisplayMap();
SDL_Rect Map_GetSize();
int* Map_GetRow(int i);
void Map_CloseMap();
void Map_Close();
int Map_GetIDTile(int x, int y);
int Map_GetSizeMapX();
int Map_GetSizeMapY();

#endif