#ifndef CHAMPIONS_H
#define CHAMPIONS_H

#include "armes.h"
#include "protections.h"
#include "soins.h"
#include <stdio.h>
#include <stdlib.h>

#define NB_CHAMPIONS 12

typedef enum{LEGUME,FRUIT}Type;

typedef struct{
    char *variete;
    Type type;
    int force;
    int resistance;
    int pv_max;
    int ce;
    Arme arme;
    Protection protec;
    Soin heal;
}Champion;

Champion initChamp(char *variete,Type type,int force,int resistance,int pv_max,int ce);

#endif
