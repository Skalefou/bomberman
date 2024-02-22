#include "Player.h"

static Players players;

int PlayerGetX(int player) {
    return players.player[player].position.x;
};

int PlayerGetY(int player) {
    return players.player[player].position.y;
};

void Player_Init(int nbPlayer, SDL_Rect *pos) {
    players.numberPlayer = nbPlayer;
    players.player = malloc(sizeof(Player) * players.numberPlayer);
    for (int i = 0; i < players.numberPlayer; i++) {
        players.player[i].name = NULL; // You should set this to the actual player name
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
        position.y--;
        position.y *= 48;
        Graphics_DisplayPlayer(i, players.player[i].orientation, position);
    }
}

/*Players* Player_GetPlayers(void) {
    return SDL_Rect position;
}*/

void Player_Move(int player, int x, int y) {
    if(x == -1) {
        players.player[player].orientation = PLAYER_LEFT;

        if(players.player[player].position.x > 0) {
            int var = Map_GetIDTile(players.player[player].position.x - 1, players.player[player].position.y);
            if(var != 3 && var != 0 && var != 4) {
                players.player[player].position.x--;
            };
        };

    } else if(x == 1) {
        players.player[player].orientation = PLAYER_RIGHT;

        if(players.player[player].position.x < Map_GetSizeMapX() - 1) {
            int var = Map_GetIDTile(players.player[player].position.x + 1, players.player[player].position.y);
            if(var != 3 && var != 0 && var != 4) {
                players.player[player].position.x++;
            };
        };

    } else if(y == -1) {
        players.player[player].orientation = PLAYER_UP;

        if(players.player[player].position.y >= 0) {
            int var = Map_GetIDTile(players.player[player].position.x, players.player[player].position.y - 1);
            if(var != 3 && var != 0 && var != 4) {
                players.player[player].position.y--;
            };
        };

    } else if(y == 1) {
        players.player[player].orientation = PLAYER_DOWN;

        if(players.player[player].position.y < Map_GetSizeMapY() + 1) {
            int var = Map_GetIDTile(players.player[player].position.x, players.player[player].position.y + 1);
            if(var != 3 && var != 0 && var != 4) {
                players.player[player].position.y++;
            };
        };

        printf("%d %d\n", players.player[player].position.x, players.player[player].position.y);
        printf("%d\n", Map_GetIDTile(players.player[player].position.x, players.player[player].position.y));
    };
}


void Player_Close() {
    for (int i = 0; i < players.numberPlayer; i++) {
        free(players.player[i].name);
    }
    free(players.player);
}