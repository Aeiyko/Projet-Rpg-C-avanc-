#include "soins.h"
#include <stdio.h>
#include <stdlib.h>

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
