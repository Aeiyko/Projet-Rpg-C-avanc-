#ifndef __AFFICHAGE__
#define __AFFICHAGE__

#include "jeu.h"
#include "prompt.h"

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

#define BOLD "\033[1m"
#define RED "\033[31m"
#define MERROR BOLD RED "ERROR : \033[0m"

#define S_MULT 2
#define S_WIDTH (28 * S_MULT)
#define S_HEIGHT (16 * S_MULT)

#define SEP_INPUT_FIELD ((S_HEIGHT) - 3)
#define SEP_CMD_MESS ((S_WIDTH) / 2 - 1)

void maj_affichage(Jeu* jeu);

#endif
