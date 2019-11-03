#ifndef PROMPT_H
#define PROMPT_H

#define L_CMD 5
#define NB_CMD 7
#define NB_ARGS 5

#define L_MESSAGE 200

typedef enum{SHOW,FIGHT,MOVE,USE,END,EXIT,ERROR}Commande;

typedef struct {
    char* stand;
    char* error;
} Messages;

Messages* initMessages();
void freeMessages(Messages** m);
void affichePrompt(int* term);
void prompt(Commande cmd, int* term);


#endif
