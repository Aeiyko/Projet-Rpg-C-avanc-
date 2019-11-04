#include "affichage.h"
#include "jeu.h"
#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>

void print_support()
{
    int x, y;
    for (y = 0; y < S_HEIGHT; y++) {
        for (x = 0; x < S_WIDTH; x++) {
            if (x == 0) {
                if (y == 0) printf("╔");
                else if (y == SEP_INPUT_FIELD) printf("╠");
                else if (y == S_HEIGHT - 1) printf("╚");
                else printf("║");
            /*} else if (x == SEP_INPUT_FIELD) {*/
                /*if (y == SEP_INPUT_FIELD) printf("T");*/
                /*else if (y == S_HEIGHT - 1) printf("T");*/
                /*else if (y > SEP_INPUT_FIELD) printf("│");*/
            } else if (x == S_WIDTH - 1) {
                if (y == 0) printf("╗");
                else if (y == SEP_INPUT_FIELD) printf("╣");
                else if (y == S_HEIGHT - 1) printf("╝");
                else printf("║");
            } else {
                if (y == 0 || y == SEP_INPUT_FIELD || y == S_HEIGHT - 1) printf("═");
                else printf(" ");
            }
        }
        putchar('\n');
    }
}

void maj_affichage(Jeu* jeu)
{
    clear();
    print_support();

    gotoxy(3, S_HEIGHT - 1);
}
