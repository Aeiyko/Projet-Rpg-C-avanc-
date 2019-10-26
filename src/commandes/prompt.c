#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int viderbuffer(){
  int c;
  int cpt = -1;
  do{
    c = getchar();
    cpt++;
  }while(c != '\n' && c!= EOF);
  return cpt>0;
}

void prompt_show(){
  char tmp = getchar();
  char *type = malloc(sizeof(char)*L_CMD);
  char *arg1[NB_ARGS]={"vegetables","fruits","weapons","protections","cares"};
  char *arg2[NB_ARGS]={"vegetable","fruit","weapon","protection","care"};
  int ind,i;
  if(tmp == ' '){
    scanf("%s",type);
    for(i=0;i<NB_ARGS;i++)if(strcmp(type,arg1[i])==0)printf("%s %s\n","show",type);
    for(i=0;i<NB_ARGS;i++)
      if(strcmp(type,arg2[i])==0){
        scanf("%d",&ind);
        printf("%s %s %d\n","show",type,ind);
      }
  }
  else if(tmp == '\n'){
    printf("Show\n");
  }
  else printf("Error\n");
  /*if(ind < 0)show(commande);
  else show(commande,ind);*/
}

void prompt_fight(){
  char *v = (char*)malloc(sizeof(char)*L_CMD);
  char *f = (char*)malloc(sizeof(char)*L_CMD);
  char *tmp = (char*)malloc(sizeof(char)*L_CMD);
  scanf("%s",v);
  scanf("%s",tmp);
  if(strcmp(tmp,"versus")==0 && getchar()==' '){
    scanf("%s",f);
    printf("Combat lancé entre %s et %s\n",v,f);
  }
  else printf("Erreur ! commande erronée\n");
}

void prompt_move(){
  char *sens = (char*)malloc(sizeof(char)*L_CMD);
  int n = -1;
  scanf("%s",sens);
  if((strcmp(sens,"forward")==0 ||strcmp(sens,"backward")==0) && getchar()!='\n'){
    scanf("%d",&n);
    if(viderbuffer())printf("Error : move <forward/backward> <case number>\n");
    else{
      if(n<0) printf("%s 1\n",sens);
      else printf("%s %d\n",sens,n);
    }
  }
  else printf("Error : move <forward/backward> <case number>\n");
}

void prompt_use(){
  char *object=(char*)malloc(sizeof(char)*L_CMD);
  int n = -1;
  scanf("%s",object);
  if(strcmp(object,"weapon")==0||strcmp(object,"protection")==0||strcmp(object,"care")==0){
      scanf("%d",&n);
      if(n<0 && viderbuffer()){
        printf("Erreur\n");
      }
      else{
        if(n<0){
          if(strcmp(object,"protection")!=0) printf("%s\n",object,0);
          else printf("%s equipée\n",object);
        }
        else printf("%s %d\n",object,n);
      }
  }
  else printf("Use weapon,protection or care after the command use\n");
}

void prompt_end(){
  printf("End of your turn\n");
}


Commande strToCmd(char *c){
  int i;
  char *listecmd[NB_CMD]={"show","fight","move","use","end","exit","error"};
  for(i=0;i<NB_CMD-1;i++){
    if(strcmp(listecmd[i],c)==0)return i;
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
      printf("Error");
      break;

  }
}

void affichePrompt(){
  char *commande = (char *)malloc(sizeof(char)*L_CMD);
  int entier;
  printf("> ");
  scanf("%s",commande);
  prompt(strToCmd(commande));
}
