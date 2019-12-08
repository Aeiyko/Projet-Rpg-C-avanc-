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

void wait(Jeu* jeu);
void replace(char *src, char c, char newc);
char **lireFile(char *filename);
int estNombre(char *tmp, int fin);
int verifCommande(char **tmp);
int verifIf(char **tmp);
int verifChoose(char **tmp);
int verifSyntaxe(char** tmp);
void prompt_exec(Jeu* jeu, char** machaine, int j);
char** exec_condition(Jeu* jeu, char **machaine);
char** exec_else(char **machaine);
char **execif(Jeu *jeu, char **machaine);
void exec(Jeu* jeu, Strat* mastrat);
Strat *creerStrat(char *nom, char *filename, char **tab);
Strat **creerListeStrats(char **listenoms,int n);
Arme *findWeapon(Jeu *jeu,char *nom);
Protection *findProtec(Jeu *jeu, char *nom);
Soin *findHeal(Jeu *jeu,char *nom);
void equipementStrats(Jeu *jeu);
void printAllStrats();
void printStrat(int i);
void remplirTab();
void free_strats();
void initStrats(Jeu *jeu);

#endif
