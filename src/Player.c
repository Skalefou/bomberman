#include "Player.h"

static Players players;

void Player_Init(int nbPlayer, SDL_Rect *pos) {
    players.numberPlayer = nbPlayer;
    players.player = malloc(sizeof(Player) * players.numberPlayer);
    for (int i = 0; i < players.numberPlayer; i++) {
        players.player[i].position = pos[i];
        players.player[i].orientation = PLAYER_DOWN;
    }
}

void Player_Display() {
/*    const double coefZoomW = Graphics_GetCoefZoomW(), coefZoomY = Graphics_GetCoefZoomH();
    for (int i = 0; i < players.numberPlayer; i++) {
        int w = 16, h = 16;
        SDL_Rect position = {{players.player[i].}};
    }*/
}

void Player_Close() {
    free(players.player);
}