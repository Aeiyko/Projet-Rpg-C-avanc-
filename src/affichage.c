#include "affichage.h"
#include "jeu.h"
#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>

void print_support()
{
    int i, j;
    for (i = 0; i < S_HEIGHT; i++) {
        for (j = 0; j < S_WIDTH; j++) {
            if (j == 0 || j == S_WIDTH - 1) {
                if (i == 0 || i == S_HEIGHT - 1)
                    putchar(' ');
                else
                    putchar('|');
            } else {
                if (i == 0 || i == S_HEIGHT - 1)
                    printf("--");
                else
                    printf("##");
            }

        }
        putchar('\n');
    }
}

void clear_console()
{
    for (int i = 0; i < 100; i++)
        putchar('\n');
}

void maj_affichage(Jeu* jeu)
{
    clear_console();
    print_support();
}
