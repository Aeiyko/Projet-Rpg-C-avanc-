#include "affichage.h"
#include "jeu.h"
#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void print_texte(char* texte, int x, int y)
{
    char *ligne = strtok(texte, "\n");

    while (ligne != NULL) {
        gotoxy(x, y);
        printf("%s", ligne);
        ligne = strtok(NULL, "\n");
        y++;
    }
}

void print_show(Jeu* jeu)
{
    /* print le cadre */
    int x, y;
    gotoxy(SHOW_START_X, 0);
    for (y = 0; y < SHOW_END_Y; y++) {
        for (x = SHOW_START_X; x < SHOW_END_X; x++) {
            if (x == SHOW_START_X) {
                if (y == 0) printf("╤");
                else if (y == SHOW_END_Y - 1) printf("╰");
                else printf("│");
            } else if (x == SHOW_END_X - 1) {
                if (y == 0) printf("╤");
                else if (y == SHOW_END_Y - 1) printf("╯");
                else printf("│");
            } else {
                if (y == 0) printf("══");
                else if (y == SHOW_END_Y - 1) printf("──");
                else printf("  ");
            }
        }
        gotoxy(SHOW_START_X, y + 2);
    }

    print_texte(jeu->texte, SHOW_START_X + 4, 2);
}

void maj_affichage(Jeu* jeu)
{
    clear();
    print_support();

    if (!jeu->combat) {
        char* texte = (char*)malloc(sizeof(char*) * L_TEXT);
        strcpy(texte, INSTRUCTIONS);
        free(texte);

        print_show(jeu);
        print_texte(texte, INSTRUCT_X, INSTRUCT_Y);
    }


    gotoxy((SEP_CMD_MESS + 1) * 2, S_HEIGHT - 1);
    printf("%s", jeu->message);
    gotoxy(3, SEP_INPUT_FIELD + 2);
}
