#include "commandes.h"
#include "affichage.h"
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

void show_var_i(Jeu *jeu,char *arg,int i){
    if(strcmp(arg,"vegetable")==0 && i>=0 && i<NB_CHAMPS/2){
      printf("\t%d -- %s\n",i,jeu->champs[i]->variete);
      printf("Force : %d\n",jeu->champs[i]->force);
      printf("Resistance : %d\n",jeu->champs[i]->resist);
      printf("Pv_max : %d\n",jeu->champs[i]->pv_max);
      printf("ce : %d\n",jeu->champs[i]->ce);
      printf("\t-----\n");
    }
    else if(strcmp(arg,"fruit")==0 && i>=NB_CHAMPS/2 && i<NB_CHAMPS){
      printf("\t%d -- %s\n",i,jeu->champs[i]->variete);
      printf("Force : %d\n",jeu->champs[i]->force);
      printf("Resistance : %d\n",jeu->champs[i]->resist);
      printf("Pv_max : %d\n",jeu->champs[i]->pv_max);
      printf("ce : %d\n",jeu->champs[i]->ce);
      printf("\t-----\n");
    }
    else if(strcmp(arg,"weapon")==0 && i>=0 && i<NB_ARMES){
      printf("\t%d -- %s\n",i,jeu->armes[i]->nom);
      printf("Ce : %d\n",jeu->armes[i]->ce);
      printf("Ca : %d\n",jeu->armes[i]->ca);
      printf("D_min : %d\n",jeu->armes[i]->d_min);
      printf("D_max : %d\n",jeu->armes[i]->d_max);
      printf("Portée : %d\n",jeu->armes[i]->portee);
      printf("\t-----\n");
    }
    else if(strcmp(arg,"protection")==0 && i>=0 && i<NB_PROTECTS){
      printf("\t%d -- %s\n",i,jeu->protects[i]->nom);
      printf("Ce : %d\n",jeu->protects[i]->ce);
      printf("Ca : %d\n",jeu->protects[i]->ca);
      printf("Prob : %d\n",jeu->protects[i]->prob);
      printf("\t-----\n");
    }
    else if(strcmp(arg,"care")==0 && i>=0 && i<NB_SOINS){
      printf("\t%d -- %s\n",i,jeu->soins[i]->nom);
      printf("Ce : %d\n",jeu->soins[i]->ce);
      printf("Ca : %d\n",jeu->soins[i]->ca);
      printf("Volume : %d\n",jeu->soins[i]->volume);
      printf("Hp_min : %d\n",jeu->soins[i]->hp_min);
      printf("Hp_max : %d\n",jeu->soins[i]->hp_max);
      printf("\t-----\n");
    }
    else{
      sprintf(jeu->message, MERROR "Cet identifiant n'existe pas.");
    }
}

/*void fight(Jeu *jeu){*/
/*}*/

void move(Jeu *jeu,char *dir,int n){
  if(jeu->fruit == jeu->courant){
    if(strcmp(dir,"forward") == 0 && jeu->courant->ca - n >= 0){
      jeu->courant->ca -= n;
      jeu->courant->pos += n;
    }
    else if(strcmp(dir,"backward") == 0 && jeu->courant->ca - n >= 0){
      jeu->courant->ca-=n;
      jeu->courant->pos-=n;
    }
    else sprintf(jeu->message, MERROR "Déplacement impossible.");
  }
  else{
    if(strcmp(dir,"forward")==0 && jeu->courant->ca-n >=0){
      jeu->courant->ca-=n;
      jeu->courant->pos-=n;
    }
    else if(strcmp(dir,"backward")==0 && jeu->courant->ca-n >=0){
      jeu->courant->ca -= n;
      jeu->courant->pos += n;
    }
    else sprintf(jeu->message, MERROR "Déplacement impossible.");
  }
}
