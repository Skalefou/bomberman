#ifndef BOMBERMAN_PLAYER_H
#define BOMBERMAN_PLAYER_H

#include <SDL2/SDL.h>
#include "Graphics.h"
#include "Map.h"
#include "const.h"

typedef struct {
    char *name;
    SDL_Rect position;
    int orientation;
    int *bombe_max;
    int *bombe_posee;
    int bombe_speed;
    int range;
} Player;

typedef struct {
    Player *player;
    int numberPlayer;
} Players;

int PlayerGetX(int player);
int PlayerGetY(int player);
void Player_Init(int numberPlayer, SDL_Rect *pos);
void Player_Display();
void Player_Close();
//Players* Player_GetPlayers(void);
void Player_Move(int player, int x, int y);

#endif