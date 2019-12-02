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

char **lireFile(char *filename){
  FILE *file = fopen(filename,"r");
  char *myfile;
  char **tab;
  int i = 0;
  int bool=1;
  int taille = TAILLE;
  int taillefile;
  fseek(file,0,SEEK_END);
  taillefile = ftell(file);
  fseek(file,0,SEEK_SET);
  myfile = (char *)calloc(sizeof(char),taillefile);
  fread(myfile,taillefile,taillefile,file);
  fclose(file);
  tab = (char **)calloc(sizeof(char *),TAILLE);
  myfile = strtok(myfile,ESP);
  if(!file)return NULL;
  tab[i++] = myfile;
  while( bool ){
    myfile = strtok(NULL,ESP);
    if(i == taille){
      taille += TAILLE;
      tab = realloc(tab,sizeof(char *)*taille);
    }
    tab[i++] = myfile;
    if(!myfile)bool=0;
  }
  tab = realloc(tab,sizeof(char *)*i);
  return tab;
}

int estNombre(char *tmp,int fin){
  int i;
  for(i = 0;i < fin;i++)if(!isdigit(tmp[i]))return 0;
  return 1;
}

int verifCommande(char **tmp){
  if(!strcmp(*tmp,motclesprompt[0])){
    tmp++;
    if( !strcmp(*tmp,motcles[7]) || !strcmp(*tmp,motcles[8]) || !strcmp(*tmp,motcles[9]) ){
      tmp++;
      if(estNombre(*tmp,strlen(*tmp)))return 2;
      else return 1;
    }
  }
  else if(!strcmp(*tmp,motclesprompt[1])){
    tmp++;
    if( !strcmp(*tmp,motcles[15]) || !strcmp(*tmp,motcles[16]) ){
      tmp++;
      if(estNombre((*tmp),strlen(*tmp)))return 2;
      else return 1;
    }
  }
  else if( !strcmp(*tmp,motclesprompt[2]) ){
    tmp ++;
    if( !strcmp(*tmp,motcles[5])){
      tmp++;
      if(estNombre((*tmp),strlen(*tmp)))return 2;
      else return 1;
    }
  }
  else if(!strcmp(*tmp,motclesprompt[3]))return 0;
  return -1;
}

int verifIf(char **tmp){
  int inscope = 0,telse = 0,tendif = 0;
  int i,j=0,k=0;
  if( !strcmp(*tmp,motcles[10]) || !strcmp(*tmp,motcles[11]) ){
    tmp++;
    k++;
    for(i = 0; i < NB_MOTS_C_C; i++)if( !strcmp(*tmp,motclescomp[i]) )j=1;
    if(!j){
      printf("ERROR SYNT IF\n");
      return 0;
    }
    tmp++;
    k++;
    if((*tmp)[strlen(*tmp)-1] == '%' && !estNombre(*tmp,strlen(*tmp)-1))return 0;
    else if((*tmp)[strlen(*tmp)-1] != '%' && !estNombre(*tmp,strlen(*tmp)))return 0;
  }
  else if( !strcmp(*tmp,motcles[12]) )inscope = 1;
  else return 0;
  tmp++;
  k++;
  while( (*tmp) && !tendif){
    if(!strcmp(*tmp,motcles[13]))telse++;
    else if(!strcmp(*tmp,motcles[14])){
      tendif++;
      tmp--;
      k--;
    }
    else if(!strcmp(*tmp,motcles[1])){
      tmp++;
      k++;
      if(!(j=verifIf(tmp)))return 0;
      else{
        tmp+=j;
        k+=j;
      }
    }
    else{
      if((j = verifCommande(tmp)) == (-1))return 0;
      else{
        tmp += j;
        k+=j;
      }
    }
    tmp++;
    k++;
  }
  if( telse > 1 || !tendif || (inscope && !telse))return 0;
  return k;
}

int verifChoose(char **tmp){
  int i;
  if(!strcmp(*tmp,motcles[7]) || !strcmp(*tmp,motcles[8]) || !strcmp(*tmp,motcles[9])){
    tmp++;
    for(i = 0;i < NB_MOTS_C;i++)if(!strcmp(*tmp,motcles[i]))return 0;
    return 1;
  }
  return 0;
}


int verifSyntaxe(char **tmp){
  int i,j,chooseweapon=0;
  if( !strcmp(*tmp,motcles[0]) ){
    tmp++;
    for(i = 0;i < NB_MOTS_C;i++)if( !strcmp(*tmp,motcles[i]) )return 0;
    tmp++;
    while( !strcmp(*tmp,motcles[6]) ){
      if(!(j = verifChoose(++tmp) ))return 0;
      else{
        if( !strcmp(*tmp,motcles[7]) ) chooseweapon=1;
        tmp+=j;
      }
      tmp++;
    }
    if(!chooseweapon)return 0;
    while(*tmp){
      if( !strcmp(*tmp,motcles[1]) ){
        tmp++;
        if( (j=verifIf(tmp)) )tmp+=j;
        else return 0;
      }
      else{
        if( (j=verifCommande(tmp)) != (-1) )tmp+=j;
        else return 0;
      }
      tmp++;
    }
    return 1;
  }
  return 0;
}

Strat *creerStrat(char *nom,char *filename,char **tab){
  Strat *newStrat = calloc(sizeof(Strat),1);
  newStrat->nom = nom;
  newStrat->filename = filename;
  newStrat->tab = tab;
  return newStrat;
}

Strat **creerListeStrats(char **listenoms,int n){
  char **listesNomsStrats = calloc(sizeof(char),n);
  Strat **listesStrats = calloc(sizeof(Strat),n);
  char **tmp;
  int i,j=0;
  for(i = 0;i < n; i++){
    tmp = lireFile(listenoms[i]);
    if( !strcmp(tmp[0],motcles[0]) ){
      if(verifSyntaxe(tmp)){
        listesNomsStrats[j] = tmp[1];
        listesStrats[j] = creerStrat(listesNomsStrats[j],listenoms[i],tmp);
        j++;
      }
      else nbStrats--;
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
  char **tmp;
  Equipement *equip;
  int i,arme,prot,heal;
  for(i = 0; i < nbStrats; i++){
    arme = 0;
    prot = 0;
    heal = 0;
    equip = calloc(sizeof(Equipement),1);
    tmp = mes_strats[i]->tab;
    tmp++;
    while( !strcmp(*(++tmp),motcles[6]) ){
      tmp++;
      if(!strcmp(*tmp,motcles[7]) && !arme){ /*Si une arme*/
        equip->arme = findWeapon(jeu,*(++tmp));
        arme = 1;
      }
      else if(!strcmp(*tmp,motcles[8]) && !prot){
        equip->protect = findProtec(jeu,*(++tmp));
        prot = 1;
      }
      else if(!strcmp(*tmp,motcles[9]) && !heal){
        equip->soin = findHeal(jeu,*(++tmp));
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

void remplirTab(){
  int i;
  char *tab[] = {"use","move","add","end"};
  /* 0 : use - 1 : move - 2 : add - 3 : end*/
  char *tab2[] = {"strategy","if","use","move","add","action","choose","weapon","protection",\
  "care","life","enemyLife","enemyInScope","else","endif","forward","backward","end"};

  /* 0 : strategy - 1 : if - 2 : use - 3 : move - 4 : add - 5 : action
     6 : choose - 7 : weapon - 8 : protection - 9 : care - 10 : life
     11 : enemyLife - 12 : enemyInScope - 13 : else - 14 : endif
     15 : forward - 16 : backward - 17 : end*/
  char *tab3[] = {"<","<=","=","!=",">=",">"};
  /* 0 : < - 1 : <= - 2 : = - 3 : != - 4 : >= - 5 : >*/
  motclesprompt = calloc(sizeof(char *),NB_MOTS_C_P);
  motclescomp = calloc(sizeof(char *),NB_MOTS_C_C);
  motcles = calloc(sizeof(char *),NB_MOTS_C);
  for(i = 0;i < NB_MOTS_C_P;i++)motclesprompt[i]=tab[i];
  for(i = 0;i < NB_MOTS_C;i++)motcles[i]=tab2[i];
  for(i = 0;i < NB_MOTS_C_C;i++)motclescomp[i]=tab3[i];
}

void initStrats(Jeu *jeu) {
  char *pouet[]={"./build/Strats/1.strat","./build/Strats/2.strat","./build/Strats/3.strat"};
  int i;
  nbStrats=3;
  remplirTab();
  mes_strats = creerListeStrats(pouet,nbStrats);
  equipementStrats(jeu);
  for(i=0;i<nbStrats;i++)printStrat(i);
  printAllStrats();
}

/*
int main(){
  Jeu *jeu = initJeu(1000,50);
  initStrats(jeu);
  return 0;
}
*/
