/*
 * file : Game.h
 *
 * Regroupe tous les prototypes de fonction et structure utilisé pour créer le noyaux du jeu
 */

#ifndef BOMBERMAN_GAME_H
#define BOMBERMAN_GAME_H

#include "Graphics.h"

#define NUMBER_MAX_PLAYER 1

/* Fonction principale du jeu, elle débute par la construction des ressources utilisé par le jeu, leur utilisation pour
 * ensuite finir avec la libération de la mémoire */
void Game_RunGame();

#endif