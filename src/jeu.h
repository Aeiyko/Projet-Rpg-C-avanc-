#ifndef __JEU__
#define __JEU__

#include "equipement.h"

#define NB_CHAMPS 12

typedef enum { LEGUME, FRUIT } Type;

/*
 * Structures
 */

typedef struct {
    Arme *arme;
    Protection *protect;
    Soin *soin;
} Equipement;

typedef struct {
    char* variete;
    Type type;
    int force;
    int resist;
    int pv_max;
    int ce;
} Champion;

typedef struct {
    int ce_max;
    int ce;
    int ca_max;
    int ca;
    Champion *champ;
    Equipement* equip;
} Joueur;

typedef struct {
    Joueur* fruit;
    Joueur* legume;

    Champion** champs;
    Arme** armes;
    Protection** protects;
    Soin** soins;
} Jeu;

/*
 * Headers
 */

Equipement* initEquipement(Arme* arme, Protection* protect, Soin* soin);
Champion* initChamp(char* variete, Type type, int force, int resist, int pv_max, int ce);
Joueur* initJoueur(int ce_start, int c_max);
Jeu* initJeu();
Champion** initChamps();

void freeChamps(Champion*** champs);
void freeJeu(Jeu** jeu);

#endif
