#ifndef STRATS_H
#define STRATS_H

#define ESP " \n,/\t"
#define NB_MOTS_C 15
#define NB_MOTS_C_P 3

#define Maj(c) (('A' <= c && 'Z' >= c)? c : (c-'a'+'A'))

typedef struct{
  char *nom;
  char *filename;
  Equipement *equip;
  int cout;
}Strat;

Strat **mes_strats;
int nbStrats;

char **motcles;
char **motclesprompt;

void initStrats(Jeu *jeu);
#endif
