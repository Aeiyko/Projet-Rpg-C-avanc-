#include "jeu.h"
#include "prompt.h"
#include "affichage.h"
#include <stdio.h>
#include <stdlib.h>

#define CE_START 1000
#define C_MAX 50

int main(int argc, char **argv)
{
    Jeu* jeu = initJeu(CE_START, C_MAX);
    int fini = 0;

    while (!fini) {
<<<<<<< HEAD
        affichePrompt(jeu);
=======
        maj_affichage(jeu);
        affichePrompt(&fini);
>>>>>>> 5157fe395d80cb85a28adced85c1a332bb8242a2
    }

    freeJeu(&jeu);
    return (0);
}
