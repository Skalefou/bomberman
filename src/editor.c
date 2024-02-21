#include "Map.h"

void saveMap() {
    printf("saving..\n");

    int LINE = MapGetX();
    int COL = MapGetY();

    // Create a string for saving the characters
    char save[LINE * COL * 2];  // Assuming a single digit per element

    // Loop through the 2D array and concatenate values to the string
    int index = 0;
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COL; j++) {
            index += sprintf(save + index, "%d,", GetTileFromMap(j, i));
        }
        index += sprintf(save + index, "\n");
    }

    // Remove the trailing comma and newline character
    save[index - 2] = '\0';

    // Create and open the save file
    FILE *file = fopen("media/map/save.map", "w+");
    
    if (file != NULL) {
        // Write the map to the file
        fprintf(file, "%s", save);
        
        // Close the file
        fclose(file);

        printf("saved!\n");
    } else {
        printf("Error opening the file!\n");
    }
}