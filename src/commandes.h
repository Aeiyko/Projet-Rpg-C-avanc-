#ifndef COMMANDES_H
#define COMMANDES_H

#include "jeu.h"

void show(Jeu *jeu);
void show_vars(Jeu *jeu, char *arg);
void show_var_i(Jeu *jeu, char *arg, int i);
int exit_game(Jeu *jeu);
void fight(Jeu *jeu, char *name1, char *name2);
void move(Jeu *jeu, char *dir, int n);
void use_weapon(Jeu *jeu, int n);
void use_protection(Jeu *jeu);
void use_care(Jeu *jeu, int n);
void end(Jeu *jeu);

#endif
