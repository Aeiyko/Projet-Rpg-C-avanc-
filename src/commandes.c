#include "commandes.h"
#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

void show(Jeu *jeu) {
    if (jeu->combat) {
        Joueur *j = jeu->courant;
        gotoxy(0, S_HEIGHT + 1);

        printf("\t--- %s ---\n", j->champ->variete);
        printf("Arme : %s\n", j->equip->arme->nom);
        printf("Protection : %s\n", j->equip->protect->nom);
        printf("Soin : %s\n", j->equip->soin->nom);
        printf("Position : %d\n", j->pos);
        printf("\t-------------\n");
    } else
        sprintf(jeu->message, NOT_FIGHTING);
}

void show_vars(Jeu *jeu,char *arg){
    int i;
    gotoxy(0, S_HEIGHT + 1);

    if(strcmp(arg, "vegetables") == 0) {
        printf("\t--- Légumes ---\n");
        for (i = 0; i < NB_CHAMPS / 2; i++)
            printf("%d -- %s\n", i, jeu->champs[i]->variete);
        printf("\t---------------\n");
    }
    else if (strcmp(arg, "fruits") == 0){
        printf("\t--- Fruits ---\n");
        for (i = NB_CHAMPS / 2; i < NB_CHAMPS ; i++)
            printf("%d -- %s\n", i, jeu->champs[i]->variete);
        printf("\t--------------\n");
    }
    else if (strcmp(arg, "weapons") == 0) {
        printf("\t--- Weapons ---\n");
        for (i = 0; i < NB_ARMES; i++)
            printf("%d -- %s\n", i, jeu->armes[i]->nom);
        printf("\t----------------\n");
    }
    else if (strcmp(arg, "protections") == 0) {
        printf("\t--- Protections ---\n");
        for (i = 0; i < NB_PROTECTS; i++)
            printf("%d -- %s\n", i, jeu->protects[i]->nom);
        printf("\t-------------------\n");
    }
    else {
        printf("\t--- Soins ---\n");
        for (i = 0; i < NB_SOINS; i++)
            printf("%d -- %s\n", i, jeu->soins[i]->nom);
        printf("\t-------------\n");
    }
}

void show_var_i(Jeu *jeu,char *arg,int i) {
    gotoxy(0, S_HEIGHT + 1);

    if (strcmp(arg, "vegetable") == 0 && i >= 0 && i < NB_CHAMPS / 2) {
        printf("\t%d -- %s\n", i, jeu->champs[i]->variete);
        printf("Force : %d\n", jeu->champs[i]->force);
        printf("Resistance : %d\n", jeu->champs[i]->resist);
        printf("PV_max : %d\n", jeu->champs[i]->pv_max);
        printf("ce : %d\n", jeu->champs[i]->ce);
        printf("\t-----\n");
    }
    else if (strcmp(arg, "fruit") == 0 && i >= NB_CHAMPS / 2 && i < NB_CHAMPS) {
        printf("\t%d -- %s\n", i, jeu->champs[i]->variete);
        printf("Force : %d\n", jeu->champs[i]->force);
        printf("Resistance : %d\n", jeu->champs[i]->resist);
        printf("Pv_max : %d\n", jeu->champs[i]->pv_max);
        printf("ce : %d\n", jeu->champs[i]->ce);
        printf("\t-----\n");
    }
    else if (strcmp(arg, "weapon") == 0 && i >= 0 && i < NB_ARMES) {
        printf("\t%d -- %s\n", i, jeu->armes[i]->nom);
        printf("Ce : %d\n", jeu->armes[i]->ce);
        printf("Ca : %d\n", jeu->armes[i]->ca);
        printf("D_min : %d\n", jeu->armes[i]->d_min);
        printf("D_max : %d\n", jeu->armes[i]->d_max);
        printf("Portée : %d\n", jeu->armes[i]->portee);
        printf("\t-----\n");
    }
    else if (strcmp(arg, "protection") == 0 && i >= 0 && i < NB_PROTECTS) {
        printf("\t%d -- %s\n", i, jeu->protects[i]->nom);
        printf("Ce : %d\n", jeu->protects[i]->ce);
        printf("Ca : %d\n", jeu->protects[i]->ca);
        printf("Prob : %d\n", jeu->protects[i]->prob);
        printf("\t-----\n");
    }
    else if (strcmp(arg, "care") == 0 && i >= 0 && i < NB_SOINS) {
        printf("\t%d -- %s\n", i, jeu->soins[i]->nom);
        printf("Ce : %d\n", jeu->soins[i]->ce);
        printf("Ca : %d\n", jeu->soins[i]->ca);
        printf("Volume : %d\n", jeu->soins[i]->volume);
        printf("HP_min : %d\n", jeu->soins[i]->hp_min);
        printf("HP_max : %d\n", jeu->soins[i]->hp_max);
        printf("\t-----\n");
    }
    else
        sprintf(jeu->message, MERROR "Cet identifiant n'existe pas.");
}

void fight(Jeu *jeu, int v, int f)
{
    if (!jeu->combat) {
        if (v >= 0 && v < NB_CHAMPS / 2) {
            if (f >= NB_CHAMPS / 2 && f < NB_CHAMPS) {
                jeu->combat = 1;
                jeu->legume->champ = jeu->champs[v];
                jeu->fruit->champ = jeu->champs[f];
                jeu->equiping = 1;

                sprintf(jeu->message, GREEN "Equipez vos champions ! Le légume d'abord." NORMAL);
            } else
                sprintf(jeu->message, MERROR "L'identifiant" BOLD " %d"
                        NORMAL " n'appartient à aucun " BOLD "Fruit." NORMAL, f);
        } else
            sprintf(jeu->message, MERROR "L'identifiant" BOLD " %d"
                    NORMAL " n'appartient à aucun " BOLD "Légume." NORMAL, v);
    } else
        sprintf(jeu->message, MERROR "Vous êtes déjà en combat.");
}

void equip(Jeu* jeu, int arme, int protect, int soin)
{
    if (arme >= NB_ARMES)
        sprintf(jeu->message, "L'identifiant " BOLD "%d" NORMAL " n'appartient à aucune Arme.", arme);
    else if (protect >= NB_PROTECTS)
        sprintf(jeu->message, "L'identifiant " BOLD "%d" NORMAL " n'appartient à aucune Protection.", protect);
    else if (soin >= NB_SOINS)
        sprintf(jeu->message, "L'identifiant " BOLD "%d" NORMAL " n'appartient à aucun Soin.", soin);
    else {
        jeu->courant->equip = initEquipement(jeu->armes[arme], jeu->protects[protect], jeu->soins[soin]);

        if (jeu->equiping && jeu->courant == jeu->legume) {
            jeu->courant = jeu->fruit;
            sprintf(jeu->message, GREEN "Bien ! Au tour du fruit." NORMAL);
        } else {
            jeu->courant = jeu->legume;
            jeu->equiping = 0;
            jeu->equiped = 1;

            sprintf(jeu->message, BOLD "%s " NORMAL RED "< VERSUS >" NORMAL BOLD " %s" NORMAL,
                    jeu->legume->champ->variete, jeu->fruit->champ->variete);
        }
    }
}

void move(Jeu *jeu, char *dir, int n) {
    if (jeu->fruit == jeu->courant){
        if (strcmp(dir, "forward") == 0 && jeu->courant->ca - n >= 0 &&
                jeu->courant->pos + n <= jeu->legume->pos) {
            jeu->courant->ca -= n;
            jeu->courant->pos += n;
        }
        else if (strcmp(dir, "backward") == 0 && jeu->courant->ca - n >= 0 && jeu->courant->pos - n > 0) {
            jeu->courant->ca = jeu->courant->ca - (n * 2);
            jeu->courant->pos -= n;
        }
        else
            sprintf(jeu->message, MERROR "Déplacement impossible.");
    }
    else {
        if (strcmp(dir, "forward") == 0 && jeu->courant->ca - n >= 0 &&
                jeu->courant->pos - n >= jeu->fruit->pos) {
            jeu->courant->ca -= n;
            jeu->courant->pos -= n;
        }
        else if (strcmp(dir, "backward") == 0 && jeu->courant->ca - n >= 0 && jeu->courant->pos + n > 42) {
            jeu->courant->ca = jeu->courant->ca - (n*2);
            jeu->courant->pos += n;
        }
        else
            sprintf(jeu->message, MERROR "Déplacement impossible.");
    }
}

void use_weapon(Jeu *jeu, int n)
{
    int cout = n * jeu->courant->equip->arme->ca;
    int somme = 0, random;

    srand(time(NULL));

    if (cout > jeu->courant->ca)
        sprintf(jeu->message, MERROR "Vous n'avez pas assez de" BOLD " crédit d'action" NORMAL);
    else {
        Joueur *adversaire;
        jeu->courant->ca -= cout;

        if (jeu->courant == jeu->fruit)
            adversaire = jeu->legume;
        else
            adversaire = jeu->fruit;

        if (jeu->courant->equip->arme->portee <= fabs(adversaire->pos - jeu->courant->pos)) {
            while (n > 0) {
                int blocked = (rand() % 100) + 1 <= adversaire->equip->protect->prob;
                if (adversaire->bouclier == 0 || (adversaire->bouclier == 1 && !blocked)) {
                    int a = jeu->courant->equip->arme->d_max + 1 - jeu->courant->equip->arme->d_min;
                    int b = jeu->courant->equip->arme->d_min;
                    random = rand() % a + b;
                    somme += random;
                    somme += jeu->courant->champ->force;
                    somme -= adversaire->champ->resist;
                }
                n--;
            }
            sprintf(jeu->message, "Vous infligez %d !", somme);
        }
        else sprintf(jeu->message, "Oh non ! L'ennemi était trop loin !");
    }
}

void use_protection(Jeu *jeu)
{
    if (jeu->combat) {
        jeu->courant->bouclier = 1;
    } else
        sprintf(jeu->message, NOT_FIGHTING);
}

void use_care(Jeu *jeu, int n)
{
    if (jeu->combat) {
        int cout = n * jeu->courant->equip->soin->ca;
        int somme = 0, random;

        if (cout > jeu->courant->ca)
            sprintf(jeu->message, MERROR "Vous n'avez pas assez de" BOLD " crédit d'action" NORMAL);
        else{
            jeu->courant->ca -= cout;
            while (n > 0) {
                int a = jeu->courant->equip->soin->hp_max + 1 - jeu->courant->equip->soin->hp_min;
                int b = jeu->courant->equip->soin->hp_min;
                random = rand() % a + b;
                somme += random;
                n--;
            }
            jeu->courant->champ->pv += somme;

            if(jeu->courant->champ->pv > jeu->courant->champ->pv_max)
                jeu->courant->champ->pv = jeu->courant->champ->pv_max;

            sprintf(jeu->message, GREEN "Vous vous êtes soigné ! Vos PV sont maintenant a "
                    BOLD "%d", jeu->courant->champ->pv);
        }
    } else
        sprintf(jeu->message, NOT_FIGHTING);
}

void end(Jeu *jeu) {
    if (jeu->combat == 1) {
        if (jeu->courant == jeu->fruit) {
            sprintf(jeu->message, "Fin du tour du " BOLD "Fruit" NORMAL);
            jeu->courant = jeu->legume;
            jeu->legume->bouclier = 0;
        } else {
            sprintf(jeu->message, "Fin du tour du " BOLD "Légume" NORMAL);
            jeu->courant = jeu->fruit;
            jeu->fruit->bouclier = 0;
        }
    } else
        sprintf(jeu->message, NOT_FIGHTING);
}
