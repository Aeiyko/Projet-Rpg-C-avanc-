#ifndef ARMES_H
#define ARMES_H

#include <stdio.h>
#include <stdlib.h>

#define NB_ARMES 5

typedef struct{
    char *nom;
    int ce;
    int ca;
    int d_min;
    int d_max;
    int portee;
}Arme;

Arme initArme(char *nom,int ce,int ca,int d_min,int d_max,int portee);

#endif
