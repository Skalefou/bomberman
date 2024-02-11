#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include <SDL2/SDL.h>

typedef struct {
    char *name;
    SDL_Rect position;
} Player;

#endif
