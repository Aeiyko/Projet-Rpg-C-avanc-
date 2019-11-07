#include "jeu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Equipement* initEquipement(Arme* arme, Protection* protect, Soin* soin)
{
    Equipement* equip = (Equipement*)malloc(sizeof(Equipement));

    equip->arme = arme;
    equip->protect = protect;
    equip->soin = soin;

    return equip;
}

Champion* initChamp(char* variete, Type type, int force, int resist, int pv_max, int ce)
{
    Champion* champ = (Champion*)malloc(sizeof(Champion));

    champ->variete = (char*)malloc(sizeof(char) * (strlen(variete) + 1));
    strcpy(champ->variete, variete);

    champ->type = type;
    champ->force = force;
    champ->resist = resist;
    champ->pv_max = pv_max;
    champ->pv = pv_max;
    champ->ce = ce;

    return champ;
}

Joueur* initJoueur(int ce_start, int c_max, int pos)
{
    Joueur* joueur = (Joueur*)malloc(sizeof(Joueur));
    joueur->ce_max = c_max;
    joueur->ce = ce_start;
    joueur->ca_max = c_max;
    joueur->ca = c_max;
    joueur->champ = NULL;
    joueur->equip = NULL;
    joueur->pos = pos;
    joueur->bouclier = 0;

    return joueur;
}

Jeu* initJeu(int ce_start, int c_max)
{
    Jeu* jeu = (Jeu*)malloc(sizeof(Jeu));

    jeu->fruit = initJoueur(ce_start, c_max,0);
    jeu->legume = initJoueur(ce_start, c_max,42);
    jeu->courant = jeu->legume;

    jeu->message = (char*)malloc(sizeof(char) * L_MESSAGE);

    jeu->champs = initChamps();
    jeu->armes = initArmes();
    jeu->protects = initProtections();
    jeu->soins = initSoins();

    jeu->combat = 0;
    jeu->equiping = 0;
    jeu->equiped = 0;
    jeu->fin = 0;

    return jeu;
}

/* Initialisation en brut */

Champion** initChamps()
{
    Champion **champs = (Champion**)malloc(sizeof(Champion*) * NB_CHAMPS);

    champs[0] = initChamp("Haricot", LEGUME, 10, 10, 40, 5);
    champs[1] = initChamp("Fenouil", LEGUME, 12, 15, 40, 7);
    champs[2] = initChamp("Poireau", LEGUME, 15, 20, 60, 10);
    champs[3] = initChamp("Aubergine", LEGUME, 20, 20, 60, 15);
    champs[4] = initChamp("Courgette", LEGUME, 20, 25, 80, 20);
    champs[5] = initChamp("Carotte", LEGUME, 25, 25, 80, 25);

    champs[6] = initChamp("Banane", FRUIT, 10, 10, 40, 5);
    champs[7] = initChamp("Kiwi", FRUIT, 12, 15, 40, 7);
    champs[8] = initChamp("Poire", FRUIT, 15, 20, 60, 10);
    champs[9] = initChamp("Pomme", FRUIT, 20, 20, 60, 15);
    champs[10] = initChamp("Ananas", FRUIT, 20, 25, 80, 20);
    champs[11] = initChamp("Durian", FRUIT, 25, 25, 80, 25);

    return champs;
}

/*                                                */
/**************************************************/
/*                                                */



/*                                                */
/**************************************************/
/*                                                */

/* Free de la mémoire */

void freeChamps(Champion*** champs)
{
    int i;
    for (i = 0; i < NB_CHAMPS; i++) {
        free((*champs)[i]->variete);
        free((*champs)[i]);
    }
    free(*champs);
}

void freeJeu(Jeu** jeu)
{
    free((*jeu)->fruit);
    free((*jeu)->legume);
    free((*jeu)->message);
    freeChamps(&((*jeu)->champs));
    freeArmes(&((*jeu)->armes));
    freeProtections(&((*jeu)->protects));
    freeSoins(&((*jeu)->soins));
    free(*jeu);
}
