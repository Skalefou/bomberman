#include "Map.h"

//TODO: Traduire tous les textes dans les chaines en anglais

static Map map;

int Map_OpenMap(const int id) {
    if (id >= map.numberListNameMap || id < 0) {
        return 1;
    }
    FILE *file = fopen(map.listNameMap[id], "r");

    fclose(file);
    return 0;
}

void Map_addListNameMap(char *name) {
    if (Utils_VerifyExtensionFile(name, ".map") == 1) {
        map.numberListNameMap++;
        char **tmpMap = realloc(map.listNameMap, map.numberListNameMap * sizeof(char*));

        if (tmpMap == NULL) {
            fprintf(stderr, "Erreur allocation memoire map");
            Map_Close();
            exit(EXIT_FAILURE);
        }
        map.listNameMap = tmpMap;
        map.listNameMap[map.numberListNameMap - 1] = malloc((strlen(name) + 1) * sizeof(char));
        if(map.listNameMap[map.numberListNameMap - 1] == NULL) {
            fprintf(stderr, "Erreur allocation memoire map");
            Map_Close();
            exit(EXIT_FAILURE);
        }
        strcpy(map.listNameMap[map.numberListNameMap - 1], name);
    }
}

void Map_Init() {
    map.numberListNameMap = 0;
    map.idUsedMap = -1;

#ifdef _WIN32
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(MAP_PATH, &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Erreur, le directoire ne s'ouvre pas");
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
        fprintf(stderr, "Erreur, le directoire ne s'ouvre pas");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        Map_addListNameMap(entry->d_name);
    }

    closedir(dir);
#endif
}

void Map_Close() {
    for(int i = 0; i < map.numberListNameMap; i++) {
        free(map.listNameMap[i]);
    }
    free(map.listNameMap);
}