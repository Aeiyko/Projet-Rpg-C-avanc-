#ifndef SOINS_H
#define SOINS_H

#include <stdio.h>
#include <stdlib.h>

#define NB_SOINS 3

typedef struct{
    char *nom;
    int ce;
    int ca;
    int volumes;
    int e_min;
    int e_max;
}Soin;

Soin initSoin(char *nom,int ce,int ca,int volumes,int e_min,int e_max);

#endif
