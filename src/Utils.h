#ifndef BOMBERMAN_UTILS_H
#define BOMBERMAN_UTILS_H

#include <string.h>

void Utils_RemoveNewLineAtEnd(char *line);
int Utils_VerifyExtensionFile(char *path, char *ext);
void Utils_splitChar(char *line, char splitChar);

#endif