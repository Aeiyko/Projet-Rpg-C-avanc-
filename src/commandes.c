#include "commandes.h"
#include <stdio.h>
#include <string.h>

void show(Jeu *jeu){
  printf("\t--- %s ---\n",jeu->courant->champ->variete);
  printf("%s\n",jeu->courant->equip->arme->nom);
  printf("%s\n",jeu->courant->equip->protect->nom);
  printf("%s\n",jeu->courant->equip->soin->nom);
  printf("\t-------------\n");
}

void show_vars(Jeu *jeu,char *arg){
    int i;
    if(strcmp(arg,"vegetables")==0){
      printf("\t--- Légumes ---\n");
      for(i=0;i<NB_CHAMPS/2;i++)
        printf("%d -- %s\n",i,jeu->champs[i]->variete);
      printf("\t---------------\n");
    }
    else if(strcmp(arg,"fruits")==0){
      printf("\t--- Fruits ---\n");
      for(i=NB_CHAMPS/2;i<NB_CHAMPS;i++)
        printf("%d -- %s\n",i,jeu->champs[i]->variete);
      printf("\t--------------\n");
    }
    else if(strcmp(arg,"weapons")==0){
      printf("\t--- Weapons ---\n");
      for(i=0;i<NB_ARMES;i++)
        printf("%d -- %s\n",i,jeu->armes[i]->nom);
      printf("\t----------------\n");
    }
    else if(strcmp(arg,"protections")==0){
      printf("\t--- Protections ---\n");
      for(i=0;i<NB_PROTECTS;i++)
        printf("%d -- %s\n",i,jeu->protects[i]->nom);
      printf("\t-------------------\n");
    }
    else{
      printf("\t--- Soins ---\n");
      for(i=0;i<NB_SOINS;i++)
        printf("%d -- %s\n",i,jeu->soins[i]->nom);
      printf("\t-------------\n");
    }
}
