#include "champions.h"
#include <stdio.h>
#include <stdlib.h>

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
