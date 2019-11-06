#include "prompt.h"
#include "jeu.h"
#include "commandes.h"
#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ma_commande[L_CMD];

void prompt_show(Jeu *jeu) {
    if(ma_commande[1] == NULL)
        show(jeu);
    else {
        int i, fin = 0;
        char *arg1[NB_ARGS] = {"vegetables", "fruits", "weapons", "protections", "cares"};
        char *arg2[NB_ARGS] = {"vegetable", "fruit", "weapon", "protection", "care"};

        for (i = 0; !fin && i < NB_ARGS; i++) {
            if (strcmp(ma_commande[1], arg1[i]) == 0) {
                if (ma_commande[2] == NULL)
                    show_vars(jeu, ma_commande[1]);
                else
                    sprintf(jeu->message, MERROR "Trop de paramètres.");
                fin = 1;
            } else
                sprintf(jeu->message, MERROR "Premier paramètre invalide.");
        }

        for (i = 0; !fin && i < NB_ARGS; i++)
            if (strcmp(ma_commande[1], arg2[i]) == 0) {
                if (ma_commande[2] == NULL)
                    show_var_i(jeu, ma_commande[1], 0);
                else if (( !atoi(ma_commande[2]) && strcmp(ma_commande[2], "0") != 0) || 
                            atoi(ma_commande[2]) < 0 || ma_commande[3] != NULL)
                    sprintf(jeu->message, MERROR "commande invalide.");
                else
                    show_var_i(jeu, ma_commande[1], atoi(ma_commande[2]));
                fin = 1;
            } else
                sprintf(jeu->message, MERROR "Premier paramètre invalide.");
    }
}

void prompt_fight(Jeu* jeu) {
    if (ma_commande[1] != NULL) {
        if (ma_commande[2] != NULL) {
            if (strcmp(ma_commande[2],"versus") == 0) {
                if (ma_commande[4] == NULL) {
                    if (ma_commande[3] != NULL) {
                        sprintf(jeu->message, "Combat lancé entre %s et %s", ma_commande[1], ma_commande[3]);
                    } else
                        sprintf(jeu->message, MERROR "Deuxième combattant manquant.");
                } else
                    sprintf(jeu->message, MERROR "Trop de paramètres.");
            } else
                sprintf(jeu->message, MERROR "Le deuxième paramètre doit être \"versus\"");
        } else
            sprintf(jeu->message, MERROR "Paramètre \"versus\" manquant.");
    } else
        sprintf(jeu->message, MERROR "Paramètres manquants.");
}

void prompt_move(Jeu* jeu) {
    if (ma_commande[1] == NULL)
        sprintf(jeu->message, MERROR "Paramètres manquants");
    else if (strcmp(ma_commande[1], "forward") == 0 || strcmp(ma_commande[1], "backward") == 0) {
        if (ma_commande[3] != NULL)
            sprintf(jeu->message, MERROR "Trop d'arguments.");
        else if (ma_commande[2] == NULL)
            sprintf(jeu->message, "%s %s %d", ma_commande[0], ma_commande[1], 1);
        else if ((!atoi(ma_commande[2]) && strcmp(ma_commande[2], "0") != 0) || atoi(ma_commande[2]) < 0)
            sprintf(jeu->message, MERROR "Nombre positif requis.");
        else
            sprintf(jeu->message, "%s %s %s", ma_commande[0], ma_commande[1], ma_commande[2]);
    } else
        sprintf(jeu->message, MERROR "Premier paramètre invalide.");
}

void prompt_use(Jeu* jeu) {
    if (ma_commande[1] != NULL) {
        if (strcmp(ma_commande[1], "weapon") == 0 || strcmp(ma_commande[1], "care") == 0) {
            if ((ma_commande[2] != NULL && !atoi(ma_commande[2]) && strcmp(ma_commande[2], "0") != 0) ||
                (ma_commande[2] != NULL &&  atoi(ma_commande[2]) < 0) || ma_commande[3] != NULL) {
                sprintf(jeu->message, MERROR "commande invalide.");
            }
            else if (ma_commande[2] == NULL)
                sprintf(jeu->message, "%s %s 0", ma_commande[0], ma_commande[1]);
            else
                sprintf(jeu->message, "%s %s %s", ma_commande[0], ma_commande[1], ma_commande[2]);
        }
        else if (strcmp(ma_commande[1], "protection") == 0) {
            if (ma_commande[2]!=NULL)
                sprintf(jeu->message, MERROR "commande invalide.");
            else
                sprintf(jeu->message, "%s %s", ma_commande[0], ma_commande[1]);
        } else
            sprintf(jeu->message, MERROR "commande invalide.");
    } else
        sprintf(jeu->message, MERROR "Paramètres manquants.");
}

void prompt_end(Jeu* jeu) {
    if (ma_commande[1] != NULL)
        sprintf(jeu->message, MERROR "Cette commande ne prend pas de paramètre.");
    else
        end(jeu);
    /*sprintf(jeu->message, "End of your turn");*/
}

Commande strToCmd() {
    int i;
    char *listecmd[NB_CMD] = {"show", "fight", "move", "use", "end", "exit", "error"};

    for (i = 0; i < NB_CMD - 1; i++) {
        if (strcmp(listecmd[i], ma_commande[0]) == 0)
            return i;
    }
    return i;
}

void prompt(Commande cmd, Jeu* jeu) {
    /*void (*funcs[])(Jeu*) = {prompt_show, prompt_fight, prompt_move, prompt_use, prompt_end};*/

    (jeu->message)[0] = '\0';
    switch (cmd) {
        case SHOW:
            prompt_show(jeu);
            break;
        case FIGHT:
            prompt_fight(jeu);
            break;
        case MOVE:
            prompt_move(jeu);
            break;
        case USE:
            prompt_use(jeu);
            break;
        case END:
            prompt_end(jeu);
            break;
        case EXIT:
            jeu->fin = 1;
            break;
        case ERROR:
        default:
            sprintf(jeu->message, MERROR "commande invalide.");
            break;
    }
}

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

void affichePrompt(Jeu *jeu) {
  char *commande = (char*)malloc(sizeof(char) * L_CMD);
  size_t entier = 10;

  printf("> ");
  getline(&commande, &entier, stdin);

  if (!rangecommand(commande))
      sprintf(jeu->message, MERROR "commande invalide.");
  else
      prompt(strToCmd(), jeu);

  free(commande);
}
