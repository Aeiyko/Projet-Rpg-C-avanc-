#ifndef PROMPT_H
#define PROMPT_H

#include "jeu.h"

#define _POSIX_C_SOURCE 200809L

#define L_CMD 7
#define NB_CMD 9
#define NB_ARGS 5

typedef enum {SHOW, FIGHT, EQUIP, MOVE, USE, ADD, END, EXIT, ERROR} Commande;

void affichePrompt(Jeu* jeu);
void prompt(Commande cmd, Jeu* jeu);

#endif
