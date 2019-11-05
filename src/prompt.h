#ifndef PROMPT_H
#define PROMPT_H

#include "jeu.h"

#define _GNU_SOURCE

#define L_CMD 5
#define NB_CMD 7
#define NB_ARGS 5

typedef enum{SHOW,FIGHT,MOVE,USE,END,EXIT,ERROR}Commande;

void affichePrompt(Jeu* jeu);
void prompt(Commande cmd, Jeu* jeu);


#endif
