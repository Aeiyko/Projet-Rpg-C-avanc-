#include "protections.h"
#include <stdio.h>
#include <stdlib.h>

Protection initProtection(char *nom,int ce,int ca,float probabilite){
    Protection new_protec;
    new_protec.nom = nom;
    new_protec.ce = ce;
    new_protec.ca = ca;
    new_protec.probabilite = probabilite;
    return new_protec;
}
