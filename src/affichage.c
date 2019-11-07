#include "affichage.h"
#include "jeu.h"
#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>

void print_support()
{
    /*printf("\033[7m\033[]");*/
    int x, y;
    gotoxy(0, 0);
    for (y = 0; y < S_HEIGHT; y++) {
        for (x = 0; x < S_WIDTH; x++) {
            if (x == 0) {
                if (y == 0) printf("╔");
                else if (y == SEP_INPUT_FIELD) printf("╠");
                else if (y == S_HEIGHT - 1) printf("╚");
                else printf("║");
            } else if (x == SEP_CMD_MESS) {
                if (y == SEP_INPUT_FIELD) printf("╤");
                else if (y == S_HEIGHT - 1) printf("╧");
                else if (y > SEP_INPUT_FIELD) printf("│");
                else if (y == 0) printf("═");
                else printf(" ");
            } else if (x == S_WIDTH - 1) {
                if (y == 0) printf("╗");
                else if (y == SEP_INPUT_FIELD) printf("╣");
                else if (y == S_HEIGHT - 1) printf("╝");
                else printf("║");
            } else {
                if (y == 0 || y == SEP_INPUT_FIELD || y == S_HEIGHT - 1) printf("══");
                else printf("  ");
            }
        }
        putchar('\n');
    }
    /*printf("\033[0m");*/
}

void print_show()
{
    /* print le cadre */
    int x, y;
    gotoxy(31, 0);
    for (y = 0; y < 16; y++) {
        for (x = 31; x < 55; x++) {
            if (x == 31) {
                if (y == 0) printf("╤");
                else if (y == 16 - 1) printf("╰");
                else printf("│");
            } else if (x == 55 - 1) {
                if (y == 0) printf("╤");
                else if (y == 16 - 1) printf("╯");
                else printf("│");
            } else {
                if (y == 0) printf("══");
                else if (y == 16 - 1) printf("──");
                else printf("  ");
            }
        }
        gotoxy(31, y + 2);
    }

    /* print le show */
}

void print_instruct()
{
    /*utiliser strtok et un define du texte.*/
}

void maj_affichage(Jeu* jeu)
{
    /*clear();*/
    print_support();

    if (!jeu->combat) print_show();
    /*print des commandes*/
    /*print des instructions*/

    gotoxy((SEP_CMD_MESS + 1)* 2, S_HEIGHT - 1);
    printf("%s", jeu->message);
    gotoxy(3, SEP_INPUT_FIELD + 2);
}
