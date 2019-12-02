#include "jeu.h"
#include "affichage.h"
#include "strats.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CE_START 1000
#define C_MAX 50

int main(int argc, char **argv)
{
    Jeu* jeu = initJeu(CE_START, C_MAX);

    if (!BETA_TESTING) {
        clear();
        print_bienvenu();
    } else {
        printf(BETA_TEXT);
        /*initStrats(jeu);*/
    }

    while (!(jeu->fin)) {
        maj_affichage(jeu);
        affichePrompt(jeu);
    }

    if (!BETA_TESTING) clear();
    freeJeu(&jeu);

    printf("\nCrédits : Alexis SALVETTI && Jordan HERENG\n\n");
    /*printf("\033[33m▟\n" NORMAL);*/

    return (0);
}
