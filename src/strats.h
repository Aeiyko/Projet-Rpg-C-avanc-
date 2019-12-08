#ifndef STRATS_H
#define STRATS_H

#define TAILLE 256
#define ESP " \n,/\t"
#define NB_MOTS_C 18
#define NB_MOTS_C_C 6
#define NB_MOTS_C_P 4

#define Maj(c) (('A' <= c && 'Z' >= c)? c : (c-'a'+'A'))

typedef struct {
  char *nom;
  char *filename;
  char **tab;
  Equipement *equip;
  int cout;
} Strat;

Strat **mes_strats;
int nbStrats;
char **listesNomsStrats;

char **motcles;
char **motclescomp;
char **motclesprompt;

void initStrats(Jeu *jeu);
void exec(Jeu* jeu, Strat* mastrat);
char **execif(Jeu *jeu, char **machaine);
void free_strats();

#endif
