#include "equipement.h"
#include "jeu.h"
#include "strats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char *replace(char *src,char c,char newc){
  int i;
  for(i = 0;i < strlen(src);i++){
    if(src[i] == c)src[i] = newc;
  }
  return src;
}

char *lireFile(char *filename){
  FILE *file = fopen(filename,"r");
  char *myfile;
  int taillefile;
  fseek(file,0,SEEK_END);
  taillefile = ftell(file);
  fseek(file,0,SEEK_SET);
  myfile = (char *)calloc(sizeof(char),taillefile);
  fread(myfile,taillefile,taillefile,file);
  fclose(file);
  return myfile;
}

Strat *creerStrat(char *nom,char *filename){
  Strat *newStrat = calloc(sizeof(Strat),1);
  newStrat->nom = nom;
  newStrat->filename = filename;
  return newStrat;
}

Strat **creerListeStrats(char **listenoms,int n){
  char **listesNomsStrats = calloc(sizeof(char),n);
  Strat **listesStrats = calloc(sizeof(Strat),n);
  char *tmp,*tmp2;
  int i;
  for(i = 0;i < n; i++){
    tmp = lireFile(listenoms[i]);
    tmp2 = strtok(tmp,ESP);
    if( !strcmp(tmp2,motcles[0]) ){
      listesNomsStrats[i] = strtok(NULL,ESP);
      listesStrats[i] = creerStrat(listesNomsStrats[i],listenoms[i]);
    }
    else printf("ERROR\n");
  }
  return listesStrats;
}

Arme *findWeapon(Jeu *jeu,char *nom){
  char *test = calloc(sizeof(char),strlen(nom));
  int i,j;
  for(i = 0;i < strlen(nom);i++)
    nom[i] = toupper(nom[i]);
  for(i = 0;i < NB_ARMES;i++){
    test = strcpy(test,jeu->armes[i]->nom);
    test = replace(test,' ','_');
    test = replace(test,'-','_');
    for(j = 0;j < strlen(test);j++){
      test[j] = toupper(test[j]);
    }
    if(!strcmp(test,nom))return jeu->armes[i];
  }
  return NULL;
}

Protection *findProtec(Jeu *jeu,char *nom){
  char *test = calloc(sizeof(char),strlen(nom));
  int i,j;
  for(i = 0;i < strlen(nom);i++)
    nom[i] = toupper(nom[i]);
  for(i = 0;i < NB_PROTECTS;i++){
    test = strcpy(test,jeu->protects[i]->nom);
    test = replace(test,' ','_');
    test = replace(test,'-','_');
    for(j = 0;j < strlen(test);j++)
      test[j] = toupper(test[j]);
    if(!strcmp(test,nom))return jeu->protects[i];
  }
  return NULL;
}

Soin *findHeal(Jeu *jeu,char *nom){
  char *test = calloc(sizeof(char),strlen(nom));
  int i,j;
  for(i = 0;i < strlen(nom);i++)
    nom[i] = toupper(nom[i]);
  for(i = 0;i < NB_ARMES;i++){
    test = strcpy(test,jeu->soins[i]->nom);
    test = replace(test,' ','_');
    test = replace(test,'-','_');
    for(j = 0;j < strlen(test);j++)
      test[j] = toupper(test[j]);
    if(!strcmp(test,nom))return jeu->soins[i];
  }
  return NULL;
}

void equipementStrats(Jeu *jeu){
  char *tmp;
  Equipement *equip;
  int i,arme,prot,heal;
  for(i = 0; i < nbStrats; i++){
    arme = 0;
    prot = 0;
    heal = 0;
    equip = calloc(sizeof(Equipement),1);
    tmp = lireFile(mes_strats[i]->filename);
    tmp = strtok(tmp,ESP);
    tmp = strtok(NULL,ESP);
    while( !strcmp(tmp=strtok(NULL,ESP),motcles[6]) ){
      tmp=strtok(NULL,ESP);
      if(!strcmp(tmp,motcles[7]) && !arme){ /*Si une arme*/
        equip->arme = findWeapon(jeu,tmp=strtok(NULL,ESP));
        arme = 1;
      }
      else if(!strcmp(tmp,motcles[8]) && !prot){
        equip->protect = findProtec(jeu,tmp=strtok(NULL,ESP));
        prot = 1;
      }
      else if(!strcmp(tmp,motcles[9]) && !heal){
        equip->soin = findHeal(jeu,tmp=strtok(NULL,ESP));
        heal = 1;
      }
      else printf("ERROR\n");
    }
    mes_strats[i]->equip = equip;
    if(!mes_strats[i]->equip->arme)printf("ERROR\n");
  }
}

void printAllStrats(){
  int i = 0;
  printf("\t--- Strats ---\n");
  for(i = 0;i < nbStrats;i++)
    printf("\t/ %d / %s\n", i, mes_strats[i]->nom);
  printf("\t-------------\n\n");
}

void printStrat(int i){
  printf("\t--- %s ---\n", mes_strats[i]->filename);
  printf("\tNom : %s\n", mes_strats[i]->nom);
  printf("\tArme : %s\n", mes_strats[i]->equip->arme->nom);
  printf("\tProtection : %s\n", mes_strats[i]->equip->protect->nom);
  printf("\tSoin : %s\n", mes_strats[i]->equip->soin->nom);
  printf("\tCout en Ce : %d\n", mes_strats[i]->cout);
  printf("\t----%.*s----\n\n",(int)strlen(mes_strats[i]->filename),"-----------------------------------------------");
}

void remplirtab(){
  int i;
  char *tab[NB_MOTS_C_P] = {"use","move","add"};
  char *tab2[NB_MOTS_C] = {"strategy","if","use","move","add","action","choose","weapon","protection",\
  "care","life","enemyLife","enemyInScope","else","endif"};
  motclesprompt = calloc(sizeof(char *),NB_MOTS_C_P);
  motcles = calloc(sizeof(char *),NB_MOTS_C);
  for(i = 0;i < NB_MOTS_C_P;i++)motclesprompt[i]=tab[i];
  for(i = 0;i < NB_MOTS_C;i++)motcles[i]=tab2[i];
}

void initStrats(Jeu *jeu) {
  char *pouet[]={"./build/Strats/1.strat","./build/Strats/2.strat","./build/Strats/3.strat"};
  int i;
  nbStrats=3;
  remplirtab();
  mes_strats = creerListeStrats(pouet,nbStrats);
  equipementStrats(jeu);
  for(i=0;i<3;i++)printStrat(i);
  printAllStrats();
}

/*
int main(){
  Jeu *jeu = initJeu(1000,50);
  initStrats(jeu);
  return 0;
}
*/
