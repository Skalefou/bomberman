#include "Utils.h"

void Utils_RemoveNewLineAtEnd(char *line) {
    size_t size = strlen(line);
    if (size > 0 && line[size-1] == '\n') {
        line[size-1] = '\000';
    }
}

int Utils_VerifyExtensionFile(char *path, char *ext) {
    const char *dot = strrchr(path, '.');
    return (dot != NULL && strcmp(dot, ext) == 0);
}

void Utils_splitChar(char *line, char splitChar) {
    int i, j;
    size_t size = strlen(line);

    for (i = 0, j = 0; i < size; i++) {
        if(line[i] != splitChar && line[i] != '\n') {
            line[j] = line[i];
            j++;
        }
    }
    line[j] = '\000';
}