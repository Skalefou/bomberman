#include "Map.h"

void saveMap() {
    printf("saving..\n");

    
    int COL = MapGetX();
    int LINE = MapGetY();

    printf("dim %d %d\n", MapGetX(), MapGetY());

    // Example terrain grid
    int terrain_grid[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        // Add more rows as needed
    };


    char save[LINE * COL * 2];

    int index = 0;
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COL; j++) {
            index += sprintf(save + index, "%d,", GetTileFromMap(j, i)); //GetTileFromMap(j, i));
        };
        index += sprintf(save + index, "\n");
    };

    printf("save :\n%s", save);

    save[index - 2] = '\0';

    FILE *file = fopen("media/map/save.map", "w+");
    
    if (file != NULL) {
        fprintf(file, "%s", save);
        
        fclose(file);

        printf("saved!\n");
    } else {
        printf("Error opening the file!\n");
    };
};