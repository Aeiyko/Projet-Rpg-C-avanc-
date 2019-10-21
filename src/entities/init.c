#include <stdio.h>
#include <stdlib.h>

#define NB_CHAMPIONS 12
#define NB_ARMES 5
#define NB_PROTECTIONS 4
#define NB_SOINS 3

typedef enum{LEGUME,FRUIT}Type;

typedef struct{
    char *variete;
    Type type;
    int force;
    int resistance;
    int pv_max;
    int ce;
}Champion;

typedef struct{
    char *nom;
    int ce;
    int ca;
    int d_min;
    int d_max;
    int portee;
}Arme;

typedef struct{
    char *nom;
    int ce;
    int ca;
    float probabilite;
}Protection;

typedef struct{
    char *nom;
    int ce;
    int ca;
    int volumes;
    int e_min;
    int e_max;
}Soin;

Champion initChamp(char *variete,Type type,int force,int resistance,int pv_max,int ce){
    Champion new_champ;
    new_champ.variete = variete;
    new_champ.type = type;
    new_champ.force = force;
    new_champ.resistance = resistance;
    new_champ.pv_max = pv_max;
    new_champ.ce = ce;
    return new_champ;
}

Arme initArme(char *nom,int ce,int ca,int d_min,int d_max,int portee){
    Arme new_arme;
    new_arme.nom = nom;
    new_arme.ce = ce;
    new_arme.ca = ca;
    new_arme.d_min = d_min;
    new_arme.d_max = d_max;
    new_arme.portee = portee;
    return new_arme;
}

Protection initProtection(char *nom,int ce,int ca,float probabilite){
    Protection new_protec;
    new_protec.nom = nom;
    new_protec.ce = ce;
    new_protec.ca = ca;
    new_protec.probabilite = probabilite;
    return new_protec;
}

Soin initSoin(char *nom,int ce,int ca,int volumes,int e_min,int e_max){
    Soin new_soin;
    new_soin.nom = nom;
    new_soin.ce = ce;
    new_soin.ca = ca;
    new_soin.volumes = volumes;
    new_soin.e_min = e_min;
    new_soin.e_max = e_max;
    return new_soin;
}

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
