#include "affichage.h"
#include "jeu.h"
#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_bienvenu()
{
    print_texte(BIENVENU, 25, 10);
    gotoxy(0, 0);
    getchar();
}

void print_support()
{
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
}

void print_texte(char* texte, int x, int y)
{
    char *ligne, *str = (char*)malloc(sizeof(char) * L_TEXT);
    strcpy(str, texte);

    ligne = strtok(str, "\n");
    while (ligne != NULL) {
        gotoxy(x, y);
        printf("%s", ligne);
        ligne = strtok(NULL, "\n");
        y++;
    }
    free(str);
}

void print_show(Jeu* jeu)
{
    int x, y;
    gotoxy(SHOW_START_X, 0);
    for (y = 0; /*!jeu->combat &&*/ y < SHOW_END_Y; y++) {
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

    print_texte(jeu->texte, SHOW_START_X + 8, 2);
}

void maj_affichage(Jeu* jeu)
{
    clear();
    print_support();
    print_show(jeu);

    if (!jeu->equiping && !jeu->combat) print_texte(INSTRUCTIONS_F, INSTRUCT_X, INSTRUCT_Y);
    if (jeu->combat) {
        int x1 = (S_WIDTH - TERRAIN_WIDTH - SPRITE_WIDTH - 1) + jeu->legume->pos * S_MULT;
        int x2 = (S_WIDTH - TERRAIN_WIDTH) + jeu->fruit->pos * S_MULT;
        print_texte(LEG_SPRITE, x1, SPRITE_Y);
        print_texte(FRU_SPRITE, x2, SPRITE_Y);
    }

    gotoxy((SEP_CMD_MESS + 1) * 2, S_HEIGHT - 1);
    printf("%s", jeu->message);
}
