#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *ma_commande[L_CMD];

void prompt_show(){
  if(ma_commande[1] == NULL){
    printf("%s\n",ma_commande[0]);
  }
  else{
    int i;
    char *arg1[NB_ARGS]={"vegetables","fruits","weapons","protections","cares"};
    char *arg2[NB_ARGS]={"vegetable","fruit","weapon","protection","care"};
      for(i=0;i<NB_ARGS;i++){
        if(strcmp(ma_commande[1],arg1[i])==0){
          if(ma_commande[2] == NULL)printf("%s %s\n",ma_commande[0],ma_commande[1]);
          else printf("ERROR : invalid command\n");
        }
      }
      for(i=0;i<NB_ARGS;i++)
        if(strcmp(ma_commande[1],arg2[i])==0){
          if(ma_commande[2] == NULL)printf("%s %s 0\n",ma_commande[0],ma_commande[1]);
          else if((!atoi(ma_commande[2]) && strcmp(ma_commande[2],"0")!=0)||atoi(ma_commande[2])<0)printf("ERROR : invalid command\n");
          else printf("%s %s %s\n",ma_commande[0],ma_commande[1],ma_commande[2]);
        }
    }
  }

void prompt_fight(){
  if(ma_commande[1]!=NULL && strcmp(ma_commande[2],"versus")==0 && ma_commande[3]!=NULL) {
    printf("Combat lancé entre %s et %s\n",ma_commande[1],ma_commande[3]);
  }
  else printf("ERROR : invalid command\n");
}

void prompt_move(){
  if(ma_commande[1]==NULL) printf("Error : invalid command\n");
  else if((strcmp(ma_commande[1],"forward")==0 ||strcmp(ma_commande[1],"backward")==0)){
      if(ma_commande[2] == NULL) printf("%s %s %d\n",ma_commande[0],ma_commande[1],1);
      else if(ma_commande[2]==NULL ||(!atoi(ma_commande[2]) && strcmp(ma_commande[2],"0")!=0)||(ma_commande[2]!=NULL && atoi(ma_commande[2])<0)) printf("Error : invalid command\n");
      else printf("%s %s %s\n",ma_commande[0],ma_commande[1],ma_commande[2]);
    }
}

void prompt_use(){
  if(ma_commande[1]!=NULL &&(strcmp(ma_commande[1],"weapon")==0||strcmp(ma_commande[1],"care")==0)){
      if((ma_commande[2] !=NULL && !atoi(ma_commande[2]) && strcmp(ma_commande[2],"0")!=0)||(ma_commande[2]!=NULL&&atoi(ma_commande[2])<0)){
        printf("ERROR : invalid command\n");
      }
      else if(ma_commande[2] == NULL){
        printf("%s %s 0\n",ma_commande[0],ma_commande[1]);
      }
      else printf("%s %s %s\n",ma_commande[0],ma_commande[1],ma_commande[2]);
  }
  else if(ma_commande[1]!=NULL &&(strcmp(ma_commande[1],"protection")==0)){
    if(ma_commande[2]!=NULL)printf("ERROR : invalid command\n");
    else printf("%s %s\n",ma_commande[0],ma_commande[1]);
  }
  else printf("ERROR : invalid command\n");
}

void prompt_end(){
  printf("End of your turn\n");
}


Commande strToCmd(){
  int i;
  char *listecmd[NB_CMD]={"show","fight","move","use","end","exit","error"};
  for(i=0;i<NB_CMD-1;i++){
    if(strcmp(listecmd[i],ma_commande[0])==0)return i;
  }
  return i;
}

void prompt(Commande cmd){
  char *tmp;
  switch (cmd) {
    case SHOW:
      prompt_show();
      break;
    case FIGHT:
      prompt_fight();
      break;
    case MOVE:
      prompt_move();
      break;
    case USE:
      prompt_use();
      break;
    case END:
      prompt_end();
      break;
    case EXIT:
      exit(0);
      break;
    case ERROR:
    default:
      printf("Error : invalid command\n");
      break;

  }
}

int rangecommand(char *cmd){
  int i=1,fin=0;
  ma_commande[0]=strtok(cmd," \n");
  if(ma_commande[0] == NULL)return 0;
  while(!fin){
    ma_commande[i]=strtok(NULL," \n");
    if(ma_commande[i] == NULL)fin=1;
    if(i >= L_CMD && ma_commande[i] != NULL)return 0;
    i++;
  }
  return 1;
}

void affichePrompt(){
  char *commande = (char *)malloc(sizeof(char)*L_CMD);
  printf("> ");
  size_t entier=10;
  getline(&commande,&entier,stdin);
  if(!rangecommand(commande))printf("ERROR : invalid command\n");
  else prompt(strToCmd());
  free(commande);
}
