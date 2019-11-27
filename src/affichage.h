#ifndef __AFFICHAGE__
#define __AFFICHAGE__

#include "jeu.h"
#include "prompt.h"

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

#define BETA_TESTING 0

/*
 *  Caractères d'échappement.
 */

#define NORMAL "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLINK "\033[5m"
#define MERROR BOLD RED "ERROR :\033[0m "

/*
 *  Messages d'erreur.
 */

#define INVALID_CMD MERROR "Commande invalide."
#define TOO_MUCH_ARGS MERROR "Trop de paramètres."
#define WRONG_FIRST_ARG MERROR "Premier paramètre invalide."
#define ARGS_MISSING MERROR "Paramètres manquants."
#define POS_NUMBER_NEEDED MERROR "Nombre positif requis."
#define NOT_FIGHTING MERROR "Vous n'êtes pas en combat."

/*
 *  Constantes de positionnement.
 */

#define S_MULT 2
#define S_WIDTH (28 * S_MULT)
#define S_HEIGHT (16 * S_MULT)

#define SEP_INPUT_FIELD ((S_HEIGHT) - 3)
#define SEP_CMD_MESS ((S_WIDTH) / 2 - 1)

#define SHOW_START_X (15 * S_MULT)
#define SHOW_END_X (28 * S_MULT)
#define SHOW_END_Y (8 * S_MULT)

#define INSTRUCT_X (2 * S_MULT)
#define INSTRUCT_Y (11 * S_MULT)

#define TERRAIN_WIDTH (15 * S_MULT)
#define SPRITE_Y (S_HEIGHT - 10)
#define SPRITE_WIDTH 14

/*
 *  Textes.
 */

#define L_TEXT 512

#define BETA_TEXT RED BOLD\
    BLINK "****************************\n"\
    " " NORMAL RED BOLD " BETA-TEST MODE ACTIVATED " BLINK " \n"\
    BLINK "****************************\n"\
    NORMAL

#define BIENVENU \
    " _     _____ _____ _  ____        ___    ____  ____\n"\
    "| |   | ____| ____| |/ /\\ \\      / / \\  |  _ \\/ ___|\n"\
    "| |   |  _| |  _| | ' /  \\ \\ /\\ / / _ \\ | |_) \\___ \\\n"\
    "| |___| |___| |___| . \\   \\ V  V / ___ \\|  _ < ___) |\n"\
    "|_____|_____|_____|_|\\_\\   \\_/\\_/_/   \\_\\_| \\_\\____/\n"\
    " \n \n \n"\
    "\t\t  " BLINK ">" NORMAL " Press [ENTER] " BLINK "<" NORMAL


#define INSTRUCTIONS_F \
    "                           INSTRUCTIONS DE DEBUT DE PARTIE\n"\
    "                           ===============================\n"\
    " \n"\
    "           Vous vous apprêtez à lancer un combat entre un Légume et un Fruit.\n"\
    "                        Veillez à bien choisir votre champion !\n"\
    "                                          ---\n"


/*#define INSTRUCTIONS_E*/

#define SHOW_START \
    " ▏CARACTERISTIQUES DES CHAMPIONS▕\n"\
    " ▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔\n"\
    " \n \n"\
    "\t           Ici\n"\
    "\t           sont\n"\
    "\t         affichés\n"\
    "\t           les\n"\
    "\t     caractéristiques\n"\
    "\t           des\n"\
    "\t        champions"

/*
 *  Sprites.
 */

#define LEG_SPRITE \
    "╭ ╌ ╌ ╌ ╌ ╌ ╌ ╮\n"\
    "╎ L E G U M E ╎\n"\
    "╎ L E G U M E ╎\n"\
    "╎ L E G U M E ╎\n"\
    "╰ ╌ ╌ ╌ ╌ ╌ ╌ ╯"
                            /* TEMPORAIRE */
#define FRU_SPRITE \
    "╭ ╌ ╌ ╌ ╌ ╌ ╌ ╮\n"\
    "╎  F R U I T  ╎\n"\
    "╎  F R U I T  ╎\n"\
    "╎  F R U I T  ╎\n"\
    "╰ ╌ ╌ ╌ ╌ ╌ ╌ ╯"

/*
 *  Headers.
 */

void print_bienvenu();
void maj_affichage(Jeu* jeu);
void print_texte(char* str, int x, int y);

#endif
