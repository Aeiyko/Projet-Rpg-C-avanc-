#include "jeu.h"
#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>

#define CE_START 1000
#define C_MAX 50

int main(int argc, char **argv)
{
    Jeu* jeu = initJeu(CE_START, C_MAX);
    int fini = 0;

    while (!fini) {
        affichePrompt();
    }

    freeJeu(&jeu);
    return (0);
}
