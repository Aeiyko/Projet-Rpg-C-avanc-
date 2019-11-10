#include "prompt.h"
#include "jeu.h"
#include "commandes.h"
#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ma_commande[L_CMD];

/** Permet de lancer tous les cas de la commande show
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void prompt_show(Jeu *jeu) {
    if(ma_commande[1] == NULL && jeu->combat)
        show(jeu);
    else if(ma_commande[1] == NULL)
      sprintf(jeu->message, NOT_FIGHTING);
    else {
        int i, fin = 0;
        char *arg1[NB_ARGS] = {"vegetables", "fruits", "weapons", "protections", "cares"};
        char *arg2[NB_ARGS] = {"vegetable", "fruit", "weapon", "protection", "care"};

        for (i = 0; !fin && i < NB_ARGS; i++) {
            if (strcmp(ma_commande[1], arg1[i]) == 0) {
                if (ma_commande[2] == NULL)
                    show_vars(jeu, ma_commande[1]);
                else
                    sprintf(jeu->message, TOO_MUCH_ARGS);
                fin = 1;
            }
        }

        for (i = 0; !fin && i < NB_ARGS; i++) {
            if (strcmp(ma_commande[1], arg2[i]) == 0) {
                if (ma_commande[2] == NULL)
                    show_var_i(jeu, ma_commande[1], 0);
                else if ((!atoi(ma_commande[2]) && strcmp(ma_commande[2], "0") != 0) ||
                        atoi(ma_commande[2]) < 0 || ma_commande[3] != NULL)
                    sprintf(jeu->message, INVALID_CMD);
                else
                    show_var_i(jeu, ma_commande[1], atoi(ma_commande[2]));
                fin = 1;
            }
        }

        if (!fin) sprintf(jeu->message, WRONG_FIRST_ARG);
    }
}

/** Permet de lancer tous les cas de la commande equip
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void prompt_equip(Jeu* jeu)
{
    if (ma_commande[1] == NULL || ma_commande[2] == NULL || ma_commande[3] == NULL || ma_commande[4] != NULL)
        sprintf(jeu->message, MERROR "Vous devez entrer " BOLD "3" NORMAL " identifiants.");
    else {
        int a = atoi(ma_commande[1]);
        int p = atoi(ma_commande[2]);
        int s = atoi(ma_commande[3]);

        if ((a == 0 && strcmp(ma_commande[1], "0") != 0) || a < 0)
            sprintf(jeu->message, MERROR "Le premier identifiant est incorrect.");
        else if ((p == 0 && strcmp(ma_commande[2], "0") != 0) || p < 0)
            sprintf(jeu->message, MERROR "Le deuxième identifiant est incorrect.");
        else if ((s == 0 && strcmp(ma_commande[3], "0") != 0) || s < -1)
            sprintf(jeu->message, MERROR "Le troisième identifiant est incorrect.");
        else
            equip(jeu, a, p, s);
    }
}

/** Permet de lancer tous les cas de la commande fight
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void prompt_fight(Jeu* jeu)
{
    if (ma_commande[1] == NULL)
        sprintf(jeu->message, ARGS_MISSING);
    else if (ma_commande[2] == NULL)
        sprintf(jeu->message, MERROR "Paramètre \"versus\" manquant.");
    else if (strcmp(ma_commande[2],"versus") != 0)
        sprintf(jeu->message, MERROR "Le deuxième paramètre doit être \"versus\"");
    else if (ma_commande[4] != NULL)
        sprintf(jeu->message, TOO_MUCH_ARGS);
    else if (ma_commande[3] == NULL)
        sprintf(jeu->message, MERROR "Deuxième combattant manquant.");
    else {
        int v = atoi(ma_commande[1]);
        int f = atoi(ma_commande[3]);

        if ((v == 0 && strcmp(ma_commande[1], "0") != 0) || v < 0)
            sprintf(jeu->message, MERROR "Le premier identifiant est incorrect.");
        else if ((f == 0 && strcmp(ma_commande[3], "0") != 0) || f < 0)
            sprintf(jeu->message, MERROR "Le deuxième identifiant est incorrect.");
        else
            fight(jeu, v, f);
    }
}

/** Permet de lancer tous les cas de la commande move
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void prompt_move(Jeu* jeu) {
    if (ma_commande[1] == NULL)
        sprintf(jeu->message, ARGS_MISSING);
    else if (strcmp(ma_commande[1], "forward") == 0 || strcmp(ma_commande[1], "backward") == 0) {
        if (ma_commande[3] != NULL)
            sprintf(jeu->message, TOO_MUCH_ARGS);
        else if (ma_commande[2] == NULL)
            move(jeu, ma_commande[1], 1);
        else if ((!atoi(ma_commande[2]) && strcmp(ma_commande[2], "0") != 0) || atoi(ma_commande[2]) < 0)
            sprintf(jeu->message, POS_NUMBER_NEEDED);
        else
            move(jeu, ma_commande[1], atoi(ma_commande[2]));
    } else
        sprintf(jeu->message, WRONG_FIRST_ARG);
}

/** Permet de lancer tous les cas de la commande use
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void prompt_use(Jeu* jeu) {
    if (ma_commande[1] != NULL) {
        if (strcmp(ma_commande[1], "weapon") == 0 || strcmp(ma_commande[1], "care") == 0) {
            if ((ma_commande[2] != NULL && !atoi(ma_commande[2]) && strcmp(ma_commande[2], "0") != 0) ||
                    (ma_commande[2] != NULL &&  atoi(ma_commande[2]) < 0) || ma_commande[3] != NULL) {
                sprintf(jeu->message, INVALID_CMD);
            }
            else if (ma_commande[2] == NULL){
                if(strcmp(ma_commande[1], "weapon") == 0)
                    use_weapon(jeu, 1);
                else
                    use_care(jeu, 1);
            }
            else{
                if(strcmp(ma_commande[1], "weapon") == 0)
                    use_weapon(jeu, atoi(ma_commande[2]));
                else
                    use_care(jeu, atoi(ma_commande[2]));
            }
        }
        else if (strcmp(ma_commande[1], "protection") == 0) {
            if (ma_commande[2]!=NULL)
                sprintf(jeu->message, INVALID_CMD);
            else
                use_protection(jeu);
        } else
            sprintf(jeu->message, INVALID_CMD);
    } else
        sprintf(jeu->message, ARGS_MISSING);
}

/** Permet de lancer tous les cas de la commande end
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void prompt_end(Jeu* jeu) {
    if (ma_commande[1] != NULL)
        sprintf(jeu->message, MERROR "Cette commande ne prend pas de paramètre.");
    else
        end(jeu);
}

/** Permet de transformer une chaine en commande
  * Args :
  *   NONE
  * Return:
  *   NONE
  */
Commande strToCmd() {
    int i;
    char *listecmd[NB_CMD] = {"show", "fight", "equip", "move", "use", "end", "exit", "error"};

    for (i = 0; i < NB_CMD - 1; i++) {
        if (strcmp(listecmd[i], ma_commande[0]) == 0)
            return i;
    }

    return i;
}

/** Permet de vider le buffer de la chaine de carac qui reçoit la commande
  * Args :
  *   NONE
  * Return:
  *   NONE
  */
void vider_ma_commande()
{
    int i;
    for (i = 0; i < L_CMD; i++)
        ma_commande[i] = NULL;
}

/** Permet de choisir quelle fonction lancer selon l'entrée de l'utilisateur
  * Args :
  *   Commande cmd : Commande de l'utilisateur
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void prompt(Commande cmd, Jeu* jeu) {
    /*void (*funcs[])(Jeu*) = {prompt_show, prompt_fight, prompt_move, prompt_use, prompt_end};*/

    (jeu->message)[0] = '\0';
    switch (cmd) {
        case SHOW:
            prompt_show(jeu);
            break;
        case FIGHT:
            if(!jeu->combat && !jeu->equiping) prompt_fight(jeu);
            else sprintf(jeu->message, NOT_FIGHTING);
            break;
        case EQUIP:
            if(jeu->equiping) prompt_equip(jeu);
            else if (jeu->combat) sprintf(jeu->message, MERROR "Votre champion est déjà équipé.");
            else sprintf(jeu->message, NOT_FIGHTING);
            break;
        case MOVE:
            if(jeu->combat) prompt_move(jeu);
            else sprintf(jeu->message, NOT_FIGHTING);
            break;
        case USE:
            if(jeu->combat) prompt_use(jeu);
            else sprintf(jeu->message, NOT_FIGHTING);
            break;
        case END:
            if(jeu->combat) prompt_end(jeu);
            else sprintf(jeu->message, NOT_FIGHTING);
            break;
        case EXIT:
            if(!jeu->equiping && !jeu->combat){
              jeu->fin = 1;
              vider_ma_commande();
            }
            else sprintf(jeu->message,"Un guerrier ne quitte pas le champ de bataille!");
            break;
        case ERROR:
        default:
            sprintf(jeu->message, INVALID_CMD);
            break;
    }
}

/** Place dans le buffer l'entrée de l'utilisateur
  * Args :
  *   char *cmd : l'entrée de l'utilisateur
  * Return:
  *   bool
  */
int rangecommand(char *cmd) {
    int i = 1, fin = 0;
    ma_commande[0] = strtok(cmd, " \n");

    if (ma_commande[0] == NULL)
        return 0;

    while (!fin) {
        ma_commande[i] = strtok(NULL, " \n");
        if (ma_commande[i] == NULL)
            fin=1;
        if (i >= L_CMD && ma_commande[i] != NULL)
            return 0;
        i++;
    }

    return 1;
}

/** Permet de récuperer ce qu'a écrit l'utilisateur et de lancer l'analyse
  * Args :
  *   Jeu *jeu : instance du Jeu
  * Return:
  *   NONE
  */
void affichePrompt(Jeu *jeu) {
    char *commande = NULL;
    size_t entier = 0;

    gotoxy(3, S_HEIGHT - 1);
    if (jeu->combat)
        printf(BOLD "%s (%d)" NORMAL " > ", jeu->courant->champ->variete, jeu->courant->ca);
    else if (jeu->equiping)
        printf("Equipez votre " BOLD "%s" NORMAL " ! > ", jeu->courant->champ->variete);
    else
        printf("> ");

    getline(&commande, &entier, stdin);

    if (!rangecommand(commande))
        sprintf(jeu->message, INVALID_CMD);
    else
        prompt(strToCmd(), jeu);

    free(commande);
}
