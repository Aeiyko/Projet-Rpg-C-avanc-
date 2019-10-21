#ifndef PROTECTION_H
#define PROTECTION_H

#include <stdio.h>
#include <stdlib.h>

#define NB_PROTECTIONS 4

typedef struct{
    char *nom;
    int ce;
    int ca;
    float probabilite;
}Protection;

Protection initProtection(char *nom,int ce,int ca,float probabilite);

#endif
