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
    char actionClient;
} Player;

typedef struct {
    Player *player;
    int numberPlayer;
} Players;

void Player_Init(int numberPlayer, SDL_Rect *pos);
void Player_Display();
void Player_Close();
SDL_Rect Player_SetPosition(int id, int x, int y);
SDL_Rect Player_GetPosition(int id);
int Player_GetOrientation(int id);
//Players* Player_GetPlayers(void);
void Player_Move(int player, int x, int y);

#endif