#include "Bomb.h"

void Explosion(int** Map, int Line, int Col, Bomb* bombe, Player* Players, int* Item_map) {
    // Explosion to the right
    for (int i = 1; i <= bombe->range; i++) {
        if ((bombe->x + i) == Col) {
            break;
        }
        int cel = Map[bombe->y][bombe->x + i];
        if (cel == 0) {
            break;
        } else {
            // If the bomb explodes on a player
            for (int j = 0; j < sizeof(Players)/sizeof(Players[0]); j++) {
                if (Players[j].position.x == bombe->x + i && Players[j].position.y + 1 == bombe->y) {
                    printf("Player %s is dead.\n", Players[j].name);
                }
            }
            // If the bomb explodes on a wall
            if (Map[bombe->y][bombe->x + i] == 3) {
                Item_map[bombe->y * Col + bombe->x + i] = make_item();
                Map[bombe->y][bombe->x + i] = (Map[bombe->y - 1][bombe->x + i] != 0 && Map[bombe->y - 1][bombe->x + i] != 3) ? 1 : 2;
                Map[bombe->y + 1][bombe->x + i] = 1;
            }
        }
    }
    // Explosion to the left
    for (int i = 1; i <= bombe->range; i++) {
        if ((bombe->x - i) < 0) {
            break;
        }
        int cel = Map[bombe->y][bombe->x - i];
        if (cel == 0) {
            break;
        } else {
            // If the bomb explodes on a player
            for (int j = 0; j < sizeof(Players)/sizeof(Players[0]); j++) {
                if (Players[j].position.x == bombe->x - i && Players[j].position.y + 1 == bombe->y) {
                    printf("Player %s is dead.\n", Players[j].name);
                }
            }
            // If the bomb explodes on a wall
            if (Map[bombe->y][bombe->x - i] == 3) {
                Item_map[bombe->y * Col + bombe->x - i] = make_item();
                Map[bombe->y][bombe->x - i] = (Map[bombe->y - 1][bombe->x - i] != 0 && Map[bombe->y - 1][bombe->x - i] != 3) ? 1 : 2;
                Map[bombe->y + 1][bombe->x - i] = 1;
            }
        }
    }
    // Explosion downwards
    for (int i = 1; i <= bombe->range; i++) {
        if ((bombe->y + i) == Line) {
            break;
        }
        int cel = Map[bombe->y + i][bombe->x];
        if (cel == 0) {
            break;
        } else {
            // If the bomb explodes on a player
            for (int j = 0; j < sizeof(Players)/sizeof(Players[0]); j++) {
                if (Players[j].position.x == bombe->x && Players[j].position.y + 1 == bombe->y + i) {
                    printf("Player %s is dead.\n", Players[j].name);
                }
            }
            // If the bomb explodes on a wall
            if (Map[bombe->y + i][bombe->x] == 3) {
                Item_map[(bombe->y + i) * Col + bombe->x] = make_item();
                Map[bombe->y + i][bombe->x] = 1;
                Map[bombe->y + i + 1][bombe->x] = 1;
            }
        }
    }
    // Explosion upwards
    for (int i = 1; i <= bombe->range; i++) {
        if ((bombe->y - i) < 0) {
            break;
        }
        int cel = Map[bombe->y - i][bombe->x];
        if (cel == 0) {
            break;
        } else {
            // If the bomb explodes on a player
            for (int j = 0; j < sizeof(Players)/sizeof(Players[0]); j++) {
                if (Players[j].position.x == bombe->x && Players[j].position.y + 1 == bombe->y - i) {
                    printf("Player %s is dead.\n", Players[j].name);
                }
            }
            // If the bomb explodes on a wall
            if (Map[bombe->y - i][bombe->x] == 3) {
                Item_map[(bombe->y - i) * Col + bombe->x] = make_item();
                Map[bombe->y - i][bombe->x] = (Map[bombe->y - i - 1][bombe->x] != 0 && Map[bombe->y - i - 1][bombe->x] != 3) ? 1 : 2;
                Map[bombe->y - i + 1][bombe->x] = 1;
            }
        }
    }
}

int make_item() {
    int r = rand() % 5 + 1;
    printf("%d\n", r);

    int result = 0;
    // Doit-on dropper un item
    switch (r) {
        case 4:
            result = 2;
            break;
        case 5:
            result = 1;
            break;
    }

    return result;
}

void update_bomb(Bomb* bomb) {
    bomb->tick += bomb->tick_rate;
}

int has_exploded(Bomb* bomb) {
    return bomb->tick >= 3;
}

