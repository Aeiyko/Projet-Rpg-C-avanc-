#ifndef __AFFICHAGE__
#define __AFFICHAGE__

#include "jeu.h"
#include "prompt.h"

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

#define NORMAL "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define MERROR BOLD RED "ERROR :\033[0m "

/*
 *  Messages d'erreur.
 */

#define INVALID_CMD MERROR "Commande invalide."
#define TOO_MUCH_ARGS MERROR "Trop de paramètres."
#define WRONG_FIRST_ARG MERROR "Premier paramètre invalide."
#define ARGS_MISSING MERROR "Paramètres manquants."
#define POS_NUMBER_NEEDED MERROR "Nombre positif requis."
#define NOT_FIGHTING MERROR "Vous n'êtes pas en combat."

#define S_MULT 2
#define S_WIDTH (28 * S_MULT)
#define S_HEIGHT (16 * S_MULT)

#define SEP_INPUT_FIELD ((S_HEIGHT) - 3)
#define SEP_CMD_MESS ((S_WIDTH) / 2 - 1)

void maj_affichage(Jeu* jeu);

#endif
