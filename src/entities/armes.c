#include "armes.h"
#include <stdio.h>
#include <stdlib.h>

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
