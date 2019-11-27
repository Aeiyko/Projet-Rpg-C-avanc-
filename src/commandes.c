#include "commandes.h"
#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/** Permet d'afficher les détails du joueur courant
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void show(Jeu *jeu)
{
    if (jeu->combat) {
        Joueur *j = jeu->courant;
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

/** Permet d'afficher les détails d'un certain camp
  * Args :
  *   Jeu *jeu : instance du Jeu
  *   char *arg : nom du camp
  * Return:
  *   NONE
  */
void show_vars(Jeu *jeu, char *arg)
{
    int i;
    char* temp = (char*)calloc(100, sizeof(char));

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

    if (BETA_TESTING) printf(BOLD "\nOUT :" NORMAL " \n%s\n", jeu->texte);
    sprintf(jeu->message, "Voici en haut tous les %s", arg);

    free(temp);
}

/** Permet d'afficher les détails d'un champion i
  * Args :
  *   Jeu *jeu : intance du Jeu
  *   char *arg : nom du camp
  *   int i : numéro du champion
  * Return:
  *   NONE
  */
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
        if (BETA_TESTING) printf(BOLD "\nOUT :" NORMAL " \n%s\n", jeu->texte);
        sprintf(jeu->message, "Voici en haut ses caractéristiques.");
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
        if (BETA_TESTING) printf(BOLD "\nOUT :" NORMAL " \n%s\n", jeu->texte);
        sprintf(jeu->message, "Voici en haut ses caractéristiques.");
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
        if (BETA_TESTING) printf(BOLD "\nOUT :" NORMAL " \n%s\n", jeu->texte);
        sprintf(jeu->message, "Voici en haut ses caractéristiques.");
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
        if (BETA_TESTING) printf(BOLD "\nOUT :" NORMAL " \n%s\n", jeu->texte);
        sprintf(jeu->message, "Voici en haut ses caractéristiques.");
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
        if (BETA_TESTING) printf(BOLD "\nOUT :" NORMAL " \n%s\n", jeu->texte);
        sprintf(jeu->message, "Voici en haut ses caractéristiques.");
    }
    else
        sprintf(jeu->message, MERROR "Cet identifiant n'existe pas.");
}

/** Permet de lancer le combat
  * Args :
  *   Jeu *jeu : intance du Jeu
  *   int v : numéro du champion légume
  *   int f : numéro du champion fruit
  * Return:
  *   NONE
  */
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

/** Permet d'équiper un champion
  * Args :
  *   Jeu *jeu : intance du Jeu
  *   int arme : numéro de l'arme
  *   int protect : numéro de la protection
  *   int soin : numéro du soin
  * Return:
  *   NONE
  */
void equip(Jeu* jeu, int arme, int protect, int soin)
{
    if (arme >= NB_ARMES)
        sprintf(jeu->message, MERROR "L'identifiant " BOLD "%d" NORMAL " n'appartient à aucune Arme.", arme);
    else if (protect >= NB_PROTECTS)
        sprintf(jeu->message, MERROR "L'identifiant " BOLD "%d" NORMAL " n'appartient à aucune Protection.", protect);
    else if (soin >= NB_SOINS)
        sprintf(jeu->message, MERROR "L'identifiant " BOLD "%d" NORMAL " n'appartient à aucun Soin.", soin);
    else {
        Arme* a = jeu->armes[arme];
        Protection* p = jeu->protects[protect];
        Soin* s = jeu->soins[soin];

        jeu->courant->equip = initEquipement(a, p, s);
        jeu->courant->ce_used = a->ce + p->ce + s->ce;

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

/** Permet de déplacer son champion
  * Args :
  *   Jeu *jeu : intance du Jeu
  *   char *dir : direction du déplacement
  *   int n : nombre de case
  * Return:
  *   NONE
  */
void move(Jeu *jeu, char *dir, int n) {
    if (jeu->legume == jeu->courant){
        if (strcmp(dir, "forward") == 0 && jeu->courant->ca - n >= 0 &&
                jeu->courant->pos + n < jeu->fruit->pos) {
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
                jeu->courant->pos - n > jeu->legume->pos) {
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

/** Termine le combat et affecte les gains.
  * Args :
  *     Jeu* jeu : instance du Jeu
  * Return :
  *     NONE
  */
void termine_combat(Jeu* jeu)
{
    int diff = jeu->legume->ce_used - (jeu->courant == jeu->fruit ? jeu->fruit->ce_used : jeu->legume->ce_used);
    jeu->combat = 0;

    jeu->courant->ce += 5 * (diff > 1 ? diff : 1);

    jeu->legume->ce_used = 0;
    jeu->fruit->ce_used = 0;

    jeu->legume->champ->pv = jeu->legume->champ->pv_max;
    jeu->legume->pos = jeu->legume->pos_init;
    jeu->legume->ca = jeu->legume->ca_max;

    jeu->fruit->champ->pv = jeu->fruit->champ->pv_max;
    jeu->fruit->pos = jeu->fruit->pos_init;
    jeu->fruit->ca = jeu->fruit->ca_max;

    jeu->courant = jeu->legume;

    jeu->legume->champ = NULL;
    jeu->fruit->champ = NULL;

    free(jeu->legume->equip);
    free(jeu->fruit->equip);
}

/** Permet d'utiliser son arme
  * Args :
  *   Jeu *jeu : intance du Jeu
  *   int n : nombre de tirs
  * Return:
  *   NONE
  */
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

        if (jeu->courant->equip->arme->portee >= jeu->fruit->pos - jeu->legume->pos) {
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
            
            adversaire->champ->pv -= somme;

            if (adversaire->champ->pv <= 0)
                termine_combat(jeu);

            sprintf(jeu->message, "Vous infligez %d !", somme);
        }
        else sprintf(jeu->message, "Oh non ! L'ennemi était trop loin !");
    }
}

/** Permet d'utiliser sa protection
  * Args :
  *   Jeu *jeu : intance du Jeu
  * Return:
  *   NONE
  */
void use_protection(Jeu *jeu)
{
    if (jeu->combat) {
        jeu->courant->bouclier = 1;
    } else
        sprintf(jeu->message, NOT_FIGHTING);
}

/** Permet d'utiliser son soin
  * Args :
  *   Jeu *jeu : intance du Jeu
  *   int n : nombre d'utilisation
  * Return:
  *   NONE
  */
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

/** Permet de finir son tour
  * Args :
  *   Jeu *jeu : intance du Jeu
  * Return:
  *   NONE
  */
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
        jeu->courant->ca = jeu->courant->ca_max;
    } else
        sprintf(jeu->message, NOT_FIGHTING);
}
