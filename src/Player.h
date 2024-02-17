#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include <SDL2/SDL.h>
#include "Graphics.h"
#include "const.h"

typedef struct {
    char *name;
    SDL_Rect position;
    int orientation;
} Player;

typedef struct {
    Player *player;
    int numberPlayer;
} Players;

void Player_Init(int numberPlayer, SDL_Rect *pos);
void Player_Display();
void Player_Close();

#endif
