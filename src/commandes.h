#ifndef COMMANDES_H
#define COMMANDES_H
#include "jeu.h"

void show(Jeu *jeu);
void show_vars(Jeu *jeu,char *arg);
void show_var_i(Jeu *jeu,Type variete,int i);
void show_util(Jeu *jeu,char *util);
void show_util_i(Jeu *jeu,char *util,int i);
int exit_game(Jeu *jeu);
void fight(Jeu *jeu,char *name1,char *name2);
void move(Jeu *jeu,char *dir,int n);
void use_util(Jeu *jeu,char *util);
void use_util_i(Jeu *jeu,char *util,int i);
void end(Jeu *jeu);
#endif
