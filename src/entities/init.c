#include "champions.h"
#include "armes.h"
#include "protections.h"
#include "soins.h"
#include <stdio.h>
#include <stdlib.h>

void initAll(){
    Champion *champions = (Champion *)malloc(sizeof(Champion)*NB_CHAMPIONS);
    champions[0] = initChamp("Haricot",LEGUME,10,10,40,5);
    champions[1] = initChamp("Fenouil",LEGUME,12,15,40,7);
    champions[2] = initChamp("Poireau",LEGUME,15,20,60,10);
    champions[3] = initChamp("Aubergine",LEGUME,20,20,60,15);
    champions[4] = initChamp("Courgette",LEGUME,20,25,80,20);
    champions[5] = initChamp("Carotte",LEGUME,25,25,80,25);
    champions[6] = initChamp("Bannane",FRUIT,10,10,40,5);
    champions[7] = initChamp("Kiwi",FRUIT,12,15,40,7);
    champions[8] = initChamp("Poire",FRUIT,15,20,60,10);
    champions[9] = initChamp("Pomme",FRUIT,20,20,60,15);
    champions[10] = initChamp("Ananas",FRUIT,20,25,80,20);
    champions[11] = initChamp("Durian",FRUIT,25,25,80,25);

    Arme *armes = (Arme *)malloc(sizeof(Arme)*NB_ARMES);
    armes[0] = initArme("Eplucheur Laser",2,1,1,2,2);
    armes[1] = initArme("Mandoline Sonique",5,3,1,3,3);
    armes[2] = initArme("Couperet Laser",10,5,2,6,5);
    armes[3] = initArme("Hachoir Neuronique",20,7,4,9,7);
    armes[4] = initArme("Mixeur Blaster",30,10,7,12,11);

    Protection *protections = (Protection *)malloc(sizeof(Protection)*NB_PROTECTIONS);
    protections[0] = initProtection("Casque-Egouttoir",1,2,0.25);
    protections[1] = initProtection("Casque-Entonnoir",3,4,0.40);
    protections[2] = initProtection("Woklier",5,6,0.60);
    protections[3] = initProtection("Tableur-Armure",10,8,0.80);

    Soin *soins = (Soin *)malloc(sizeof(Soin)*NB_SOINS);
    soins[0] = initSoin("Humus-Neutronique",1,5,4,2,4);
    soins[1] = initSoin("Compost-Protonique",5,10,3,5,8);
    soins[2] = initSoin("Engrais-Ionique",7,15,2,8,12);
}

int main(void){
    initAll();
    return 0;
}
