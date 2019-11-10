#include "commandes.h"
#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void show(Jeu *jeu)
{
    if (jeu->combat) {
        Joueur *j = jeu->courant;
        *(jeu->texte) = '\0';
        sprintf(jeu->texte,
                        "\t--- %s ---\n"
                        "Arme : %s\n"
                        "Protection : %s\n"
                        "Soin : %s\n"
                        "Position : %d\n"
                        "\t-------------\n",
                        j->champ->variete,
                        j->equip->arme->nom,
                        j->equip->protect->nom,
                        j->equip->soin->nom,
                        j->pos);
    } else
        sprintf(jeu->message, NOT_FIGHTING);
}

void show_vars(Jeu *jeu, char *arg) 
{
    int i;
    char* temp = (char*)malloc(sizeof(char) * 40);

    *(jeu->texte) = '\0';
    if(strcmp(arg, "vegetables") == 0) {
        strcat(jeu->texte, "\t--- Légumes ---\n");
        for (i = 0; i < NB_CHAMPS / 2; i++) {
            sprintf(temp, "%d -- %s\n", i, jeu->champs[i]->variete);
            strcat(jeu->texte, temp);
        }
        strcat(jeu->texte, "\t---------------\n");
    }
    else if (strcmp(arg, "fruits") == 0){
        strcat(jeu->texte, "\t--- Fruits ---\n");
        for (i = NB_CHAMPS / 2; i < NB_CHAMPS ; i++) {
            sprintf(temp, "%d -- %s\n", i, jeu->champs[i]->variete);
            strcat(jeu->texte, temp);
        }
        strcat(jeu->texte, "\t--------------\n");
    }
    else if (strcmp(arg, "weapons") == 0) {
        strcat(temp, "\t--- Weapons ---\n");
        for (i = 0; i < NB_ARMES; i++) {
            sprintf(temp, "%d -- %s\n", i, jeu->armes[i]->nom);
            strcat(jeu->texte, temp);
        }
        strcat(temp, "\t----------------\n");
    }
    else if (strcmp(arg, "protections") == 0) {
        strcat(temp, "\t--- Protections ---\n");
        for (i = 0; i < NB_PROTECTS; i++) {
            sprintf(temp, "%d -- %s\n", i, jeu->protects[i]->nom);
            strcat(jeu->texte, temp);
        }
        strcat(temp, "\t-------------------\n");
    }
    else {
        strcat(temp, "\t--- Soins ---\n");
        for (i = 0; i < NB_SOINS; i++) {
            sprintf(temp, "%d -- %s\n", i, jeu->soins[i]->nom);
            strcat(jeu->texte, temp);
        }
        strcat(temp, "\t-------------\n");
    }
    free(temp);
}

void show_var_i(Jeu *jeu, char *arg, int i)
{
    if (strcmp(arg, "vegetable") == 0 && i >= 0 && i < NB_CHAMPS / 2) {
        Champion* c = jeu->champs[i];
        sprintf(jeu->texte,
                        "\t%d -- %s\n"
                        "Force : %d\n"
                        "Resistance : %d\n"
                        "PV : %d\n"
                        "Crédit d'équip. : %d\n"
                        "\t-----\n",
                        i, c->variete, c->force, c->resist, c->pv_max, c->ce);
    }
    else if (strcmp(arg, "fruit") == 0 && i >= NB_CHAMPS / 2 && i < NB_CHAMPS) {
        Champion* c = jeu->champs[i];
        sprintf(jeu->texte,
                        "\t%d -- %s\n"
                        "Force : %d\n"
                        "Resistance : %d\n"
                        "PV : %d\n"
                        "Crédit d'équip. : %d\n"
                        "\t-----\n",
                        i, c->variete, c->force, c->resist, c->pv_max, c->ce);
    }
    else if (strcmp(arg, "weapon") == 0 && i >= 0 && i < NB_ARMES) {
        Arme* a = jeu->armes[i];
        sprintf(jeu->texte,
                        "\t%d -- %s\n"
                        "Crédit d'équip. : %d\n"
                        "Crédit d'action : %d\n"
                        "Dégâts : %d - %d\n"
                        "Portée : %d\n"
                        "\t-----\n",
                        i, a->nom, a->ce, a->ca, a->d_min, a->d_max, a->portee);
    }
    else if (strcmp(arg, "protection") == 0 && i >= 0 && i < NB_PROTECTS) {
        Protection* p = jeu->protects[i];
        sprintf(jeu->texte,
                        "\t%d -- %s\n"
                        "Crédit d'équip. : %d\n"
                        "Crédit d'action : %d\n"
                        "Probabilité : %d\n"
                        "\t-----\n",
                        i, p->nom, p->ce, p->ca, p->prob);
    }
    else if (strcmp(arg, "care") == 0 && i >= 0 && i < NB_SOINS) {
        Soin* s = jeu->soins[i];
        sprintf(jeu->texte,
                        "\t%d -- %s\n"
                        "Crédit d'équip. : %d\n"
                        "Crédit d'action : %d\n"
                        "Volume : %d\n"
                        "PV rendus : %d - %d\n"
                        "\t-----\n",
                        i, s->nom, s->ce, s->ca, s->volume, s->hp_min, s->hp_max);
    }
    else
        sprintf(jeu->message, MERROR "Cet identifiant n'existe pas.");
}

void fight(Jeu *jeu, int v, int f)
{
    if (!jeu->combat) {
        if (v >= 0 && v < NB_CHAMPS / 2) {
            if (f >= NB_CHAMPS / 2 && f < NB_CHAMPS) {
                jeu->legume->champ = jeu->champs[v];
                jeu->fruit->champ = jeu->champs[f];
                jeu->equiping = 1;

                sprintf(jeu->message, BOLD "%s " NORMAL RED "< VERSUS >" NORMAL BOLD " %s" NORMAL,
                        jeu->champs[v]->variete, jeu->champs[f]->variete);
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
        sprintf(jeu->message, MERROR "L'identifiant " BOLD "%d" NORMAL " n'appartient à aucune Arme.", arme);
    else if (protect >= NB_PROTECTS)
        sprintf(jeu->message, MERROR "L'identifiant " BOLD "%d" NORMAL " n'appartient à aucune Protection.", protect);
    else if (soin >= NB_SOINS)
        sprintf(jeu->message, MERROR "L'identifiant " BOLD "%d" NORMAL " n'appartient à aucun Soin.", soin);
    else {
        jeu->courant->equip = initEquipement(jeu->armes[arme], jeu->protects[protect], jeu->soins[soin]);

        if (jeu->equiping && jeu->courant == jeu->legume) {
            jeu->courant = jeu->fruit;
            sprintf(jeu->message, GREEN "Bien ! Au tour du fruit." NORMAL);
        } else {
            jeu->courant = jeu->legume;
            jeu->equiping = 0;
            jeu->combat = 1;

            sprintf(jeu->message, RED "Combat lancé ! " NORMAL BOLD "%s "
                    NORMAL RED "< VERSUS >" NORMAL BOLD " %s" NORMAL,
                    jeu->legume->champ->variete, jeu->fruit->champ->variete);
        }
    }
}

void move(Jeu *jeu, char *dir, int n) {
    if (jeu->legume == jeu->courant){
        if (strcmp(dir, "forward") == 0 && jeu->courant->ca - n >= 0 &&
                jeu->courant->pos + n <= jeu->fruit->pos) {
            jeu->courant->ca -= n;
            jeu->courant->pos += n;
        }
        else if (strcmp(dir, "backward") == 0 && jeu->courant->ca - (n * 2) >= 0 && jeu->courant->pos - n >= 0) {
            jeu->courant->ca = jeu->courant->ca - (n * 2);
            jeu->courant->pos -= n;
        }
        else
            sprintf(jeu->message, MERROR "Déplacement impossible.");
    }
    else {
        if (strcmp(dir, "forward") == 0 && jeu->courant->ca - n >= 0 &&
                jeu->courant->pos - n >= jeu->legume->pos) {
            jeu->courant->ca -= n;
            jeu->courant->pos -= n;
        }
        else if (strcmp(dir, "backward") == 0 && jeu->courant->ca - (n * 2) >= 0 && jeu->courant->pos + n <= TERRAIN_WIDTH) {
            jeu->courant->ca = jeu->courant->ca - (n * 2);
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

        if (jeu->courant->equip->arme->portee <= jeu->legume->pos - jeu->fruit->pos) {
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
