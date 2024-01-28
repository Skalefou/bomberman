#include "Utils.h"

void Utils_RemoveNewLineAtEnd(char *line) {
    size_t size = strlen(line);
    if (size > 0 && line[size-1] == '\n') {
        line[size-1] = '\000';
    }
}