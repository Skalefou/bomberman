#include "Map.h"

static Map map;

int cursor_value;
short tils[3] = {0, 1, 3};

int GetTileFromMap(short x, short y){
    return map.tileMap[y][x];
};

int GetCursorValue(){
    return cursor_value;
};

void ADDCursorValue(){
    cursor_value = (cursor_value+1)%GetTileNumber();
};

void DECCursorValue(){
    cursor_value = (cursor_value-1+GetTileNumber())%GetTileNumber();
};

void Map_Modify(){
    int x, y;
    int buttons = SDL_GetMouseState(&x, &y);
    const double coefZoomW = Graphics_GetCoefZoomW(), coefZoomY = Graphics_GetCoefZoomH();
    SDL_Rect sizeTile = Graphics_GetSizeTile(map.tileMap[0][0]);

    double win_x = Graphics_Get_Window_Size_W();
    double win_y = Graphics_Get_Window_Size_H();

    int xoffset = (win_x/3 - (map.size_x*sizeTile.w)/2);
    int yoffset = (win_y - (map.size_y* coefZoomY * sizeTile.h))/2;

    x -= xoffset;
    y -= yoffset;

    int nx = x/(sizeTile.w * coefZoomW);
    int ny = y/(sizeTile.h * coefZoomY);

    int width = map.size_x * sizeTile.w * coefZoomW;
    int height = map.size_y * sizeTile.h * coefZoomY;

    int col = map.size_x;
    double x_size = sizeTile.w * coefZoomW;

    // Si on est en dehors des clous
    if(ny < 0 || ny >= map.size_y || nx < 0 || nx >= map.size_x){

        // On considère l'appui sur un autre bouton
    } else {
        // Sinon on change la map
        map.tileMap[ny][nx] = tils[cursor_value];
        ny++;
        printf("curseur %d\n", cursor_value);
        switch (cursor_value){
            case 0: case 2:
                if((!(ny < 0 || ny >= map.size_y || nx < 0 || nx >= map.size_x)) && (map.tileMap[ny][nx] == 1)){
                    map.tileMap[ny][nx] = 2;
                };
                break;
            
            case 1:
                if((!(ny < 0 || ny >= map.size_y || nx < 0 || nx >= map.size_x)) && (map.tileMap[ny][nx] == 2)){
                    map.tileMap[ny][nx] = 1;
                };

                
                --ny;
                if(!(ny-1 < 0 || ny-1 >= map.size_y || nx < 0 || nx >= map.size_x)){
                    if(map.tileMap[ny-1][nx] == 0 || map.tileMap[ny-1][nx] == 3){
                        map.tileMap[ny][nx] = 2;
                    };
                };
                break;
            
            default:
                break;
        };
    };
};

int Map_OpenMap(const int id) {
    if (id >= map.numberListNameMap || id < 0) {
        fprintf(stderr, "id file invalid\n");
        return 1;
    }

    char path[512] = MAP_PATH;
    strcat(path, map.listNameMap[id]);
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        fprintf(stderr, "Can't open %s\n", map.listNameMap[id]);
        return 1;
    }

    char line[LIMIT_SIZE_LINE_MAP_FILE];
    int firstLine = 1;
    map.size_y = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        Utils_splitChar(line, ',');
        if (firstLine) {
            map.size_x = (int)strlen(line);
            firstLine = 0;
        }
        else if (strlen(line) != map.size_x) {
            fprintf(stderr, "Invalid map : %s\n", map.listNameMap[id]);
            return 1;
        }
        map.size_y++;

        int **tmpTileMap = realloc(map.tileMap, map.size_y * sizeof(int*));
        if (tmpTileMap == NULL) {
            fprintf(stderr, "Error Allocation Memory tmpTileMap");
            return 1;
        }
        tmpTileMap[map.size_y-1] = malloc(map.size_x * sizeof(int));
        if (tmpTileMap[map.size_y-1] == NULL) {
            fprintf(stderr, "Error Allocation Memory tmpTileMap");
            return 1;
        }
        map.tileMap = tmpTileMap;

        for(int i = 0; i < map.size_x; i++) {
            if ((line[i] - '0') < 0 || (line[i] - '0') > NUMBER_TILES) {
                map.tileMap[map.size_y-1][i] = 0;
                fprintf(stderr, "Invalid tile id map : %s\n", map.listNameMap[id]);
            }
            else {
                map.tileMap[map.size_y-1][i] = (line[i] - '0');
            }
        }
    }
    fclose(file);
    return 0;
}

void Map_addListNameMap(char *name) {
    if (Utils_VerifyExtensionFile(name, ".map") == 1) {
        map.numberListNameMap++;
        char **tmpMap = realloc(map.listNameMap, map.numberListNameMap * sizeof(char*));

        if (tmpMap == NULL) {
            fprintf(stderr, "Erreur allocation memoire map\n");
            Map_Close();
            exit(EXIT_FAILURE);
        }
        map.listNameMap = tmpMap;
        map.listNameMap[map.numberListNameMap - 1] = malloc((strlen(name) + 1) * sizeof(char));
        if(map.listNameMap[map.numberListNameMap - 1] == NULL) {
            fprintf(stderr, "Erreur allocation memoire map\n");
            Map_Close();
            exit(EXIT_FAILURE);
        }
        strcpy(map.listNameMap[map.numberListNameMap - 1], name);
    }
}

SDL_Rect Map_GetSize() {
    SDL_Rect rect = {0, 0, map.size_x, map.size_y};
    return rect;
};

int MapGetX(){
    return map.size_x;
};

int MapGetY(){
    return map.size_y;
};

void Map_Init() {
    map.numberListNameMap = 0;
    map.idUsedMap = -1;

    // Et ouep, notre projet s'adapte à windaube et linux
#ifdef ____WIN32
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(MAP_PATH, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Erreur, le répertoire ne s'ouvre pas");
        exit(EXIT_FAILURE);
    }

    do {
        Map_addListNameMap(findFileData.cFileName);
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);
#else
    DIR *dir;
    struct dirent *entry;
    dir = opendir(MAP_PATH);

    if (dir == NULL) {
        fprintf(stderr, "Erreur, le répertoire ne s'ouvre pas\n");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        Map_addListNameMap(entry->d_name);
    }

    closedir(dir);
#endif
}

void Map_DisplayMap() {
    const double coefZoomW = Graphics_GetCoefZoomW(), coefZoomY = Graphics_GetCoefZoomH();
    SDL_Rect sizeTile = Graphics_GetSizeTile(map.tileMap[0][0]);

    for(int y = 0; y < map.size_y; y++) {
        for(int x = 0; x < map.size_x; x++) {
            sizeTile = Graphics_GetSizeTile(map.tileMap[y][x]);
            SDL_Rect position = {(Sint16)(x * sizeTile.w * coefZoomW), (Sint16)(y * sizeTile.h * coefZoomY)};
            Graphics_DisplayTile(map.tileMap[y][x], position, map.size_x, map.size_y);
        };
    };
};

void Map_CloseMap() {
    for(int i = 0; i < map.size_y; i++) {
        free(map.tileMap[i]);
    }
    free(map.tileMap);
    map.idUsedMap = -1;
    map.size_x = 0;
    map.size_y = 0;
}

void Map_Close() {
    for(int i = 0; i < map.numberListNameMap; i++) {
        free(map.listNameMap[i]);
    }
    free(map.listNameMap);
    Map_CloseMap();
}