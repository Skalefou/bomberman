#include "Player.h"

static Players players;



void Player_Init(int nbPlayer, SDL_Rect *pos) {
    players.numberPlayer = nbPlayer;
    players.player = malloc(sizeof(Player) * players.numberPlayer);
    for (int i = 0; i < players.numberPlayer; i++) {
        players.player[i].name = NULL;
        players.player[i].position = pos[i];
        players.player[i].orientation = PLAYER_DOWN;
        players.player[i].range = 1;
    }
}

void Player_Display() {
    const double coefZoomW = Graphics_GetCoefZoomW(), coefZoomH = Graphics_GetCoefZoomH();
    for (int i = 0; i < players.numberPlayer; i++) {
        SDL_Rect position = players.player[i].position;
        position.x *= 48;
        position.y *= 48;
        Graphics_DisplayPlayer(i, players.player[i].orientation, position);
    }
}

/*Players* Player_GetPlayers(void) {
    return SDL_Rect position;
}*/

void Player_Move(int player, int x, int y) {/*
    if (SDL_KEYDOWN == SDLK_LEFT && players.player[player].position.x > 0){
        int var = Map_GetIDTile(players.player[player].position.x - 1, players.player[player].position.y);
        if (var != 3 && var != 0 && var != 4){
            x = -1;
        }
        players.player[player].orientation = PLAYER_LEFT;
        int SizeMapX = Map_GetSizeMapX();
    }else if(SDL_KEYDOWN == SDLK_RIGHT && players.player[player].position.x < SizeMapX - 1){
        int var = Map_GetIDTile(players.player[player].position.x + 1, players.player[player].position.y);
        if (var != 3 && var != 0 && var != 4){
            x = 1;
        }
        players.player[player].orientation = PLAYER_RIGHT;
    }
    else if(SDL_KEYDOWN == SDLK_UP && players.player[player].position.y > 0){
        int var = Map_GetIDTile(players.player[player].position.x, players.player[player].position.y + 1);

        if (var != 3 && var != 0 && var != 4){
            y = -1;
        }
        players.player[player].orientation = PLAYER_UP;
        int SizeMapY = Map_GetSizeMapY();
    }
    else if(SDL_KEYDOWN == SDLK_DOWN && players.player[player].position.y < SizeMapY - 1){
        int var = Map_GetIDTile(players.player[player].position.x - 1, players.player[player].position.y - 1);
        if (var != 3 && var != 0 && var != 4){
            y = 1;
        }
        players.player[player].orientation = PLAYER_DOWN;
    }
*/
    if (x == 1) {
        players.player[player].orientation = PLAYER_RIGHT;
    } else if (x == -1) {
        players.player[player].orientation = PLAYER_LEFT;
    } else if (y == 1) {
        players.player[player].orientation = PLAYER_DOWN;
    } else if (y == -1) {
        players.player[player].orientation = PLAYER_UP;
    }

    players.player[player].position.x += x;
    players.player[player].position.y += y;
}

SDL_Rect Player_GetPosition(int id) {
    return players.player[id].position;
}

int Player_GetOrientation(int id) {
    return players.player[id].orientation;
}

SDL_Rect Player_SetPosition(int id, int x, int y) {
    players.player[id].position.x = x;
    players.player[id].position.y = y;
}

void Player_Close() {
    for (int i = 0; i < players.numberPlayer; i++) {
        free(players.player[i].name);
    }
    free(players.player);
}