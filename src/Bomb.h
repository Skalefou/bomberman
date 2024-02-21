#ifndef BOMBERMAN_BOMB_H
#define BOMBERMAN_BOMB_H


#include <stdlib.h>
#include "Player.h"

typedef struct {
    int x;
    int y;
    int range;
    int cell_from;
    int tick;
    int tick_rate;
    Player *origin;
} Bomb;

void Explosion(int** Map, int Line, int Col, Bomb* bombe, Player *Players, int* Item_map);
int make_item();
void update_bomb(Bomb* bomb);
int has_exploded(Bomb* bomb);


#endif