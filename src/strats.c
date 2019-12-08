#include "equipement.h"
#include "jeu.h"
#include "strats.h"
#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void wait(Jeu* jeu);

void replace(char *src, char c, char newc){
    int i;
    for(i = 0; i < strlen(src); i++){
        if(src[i] == c)
            src[i] = newc;
    }
}

char **lireFile(char *filename){
    FILE *file = fopen(filename, "r");
    char *myfile, *mot;
    char **tab;
    int i = 0, fin = 0;
    int taille = TAILLE, taillefile;

    fseek(file, 0, SEEK_END);
    taillefile = ftell(file);
    fseek(file, 0, SEEK_SET);
    myfile = (char *)calloc(sizeof(char), taillefile);
    fread(myfile, taillefile, 1, file);
    myfile[taillefile - 1] = '\0';
    fclose(file);

    tab = (char **)calloc(sizeof(char *), TAILLE);
    mot = strtok(myfile, ESP);

    if(!file) return NULL;

    tab[0] = (char*)calloc(sizeof(char), strlen(mot) + 1);
    strcpy(tab[i++], mot);

    while (!fin){
        mot = strtok(NULL, ESP);
        if (mot != NULL) {
            if (i == taille) {
                taille += TAILLE;
                tab = realloc(tab, sizeof(char *) * taille);
            }
            tab[i] = (char*)calloc(sizeof(char), strlen(mot) + 1);
            strcpy(tab[i++], mot);
        } else
            fin = 1;
    }

    tab = realloc(tab, sizeof(char *) * (i + 1));
    tab[i] = NULL;

    free(myfile);
    return tab;
}

int estNombre(char *tmp, int fin){
    int i;
    for(i = 0;i < fin;i++)
        if(!isdigit(tmp[i]))
            return 0;
    return 1;
}

/**DEBUT VERIFICATION SYNTAXIQUE*/

int verifCommande(char **tmp){
    if(!strcmp(*tmp,motclesprompt[0])){
        tmp++;
        if( !strcmp(*tmp,motcles[7]) || !strcmp(*tmp,motcles[8]) || !strcmp(*tmp,motcles[9]) ){
            tmp++;
            if(estNombre(*tmp,strlen(*tmp)))return 2;
            else return 1;
        }
    }
    else if(!strcmp(*tmp,motclesprompt[1])){
        tmp++;
        if( !strcmp(*tmp,motcles[15]) || !strcmp(*tmp,motcles[16]) ){
            tmp++;
            if(estNombre((*tmp),strlen(*tmp)))return 2;
            else return 1;
        }
    }
    else if( !strcmp(*tmp,motclesprompt[2]) ){
        tmp ++;
        if( !strcmp(*tmp,motcles[5])){
            tmp++;
            if(estNombre((*tmp),strlen(*tmp)))return 2;
            else return 1;
        }
    }
    else if(!strcmp(*tmp,motclesprompt[3]))return 0;
    return -1;
}

int verifIf(char **tmp){
    int inscope = 0,telse = 0,tendif = 0;
    int i,j=0,k=0;
    if( !strcmp(*tmp,motcles[10]) || !strcmp(*tmp,motcles[11]) ){
        tmp++;
        k++;
        for(i = 0; i < NB_MOTS_C_C; i++)if( !strcmp(*tmp,motclescomp[i]) )j=1;
        if(!j){
            printf("ERROR SYNT IF\n");
            return 0;
        }
        tmp++;
        k++;
        if ((*tmp)[strlen(*tmp)-1] == '%' && !estNombre(*tmp,strlen(*tmp)-1))
            return 0;
        else if ((*tmp)[strlen(*tmp)-1] != '%' && !estNombre(*tmp,strlen(*tmp)))
            return 0;
    }
    else if( !strcmp(*tmp,motcles[12]) )inscope = 1;
    else return 0;
    tmp++;
    k++;
    while( (*tmp) && !tendif){
        if(!strcmp(*tmp,motcles[13]))telse++;
        else if(!strcmp(*tmp,motcles[14])){
            tendif++;
            tmp--;
            k--;
        }
        else if(!strcmp(*tmp,motcles[1])){
            tmp++;
            k++;
            if(!(j = verifIf(tmp)))
                return 0;
            else{
                tmp+=j;
                k+=j;
            }
        }
        else{
            if((j = verifCommande(tmp)) == (-1))
                return 0;
            else{
                tmp += j;
                k+=j;
            }
        }
        tmp++;
        k++;
    }
    if( telse > 1 || !tendif || (inscope && !telse))
        return 0;
    return k;
}

int verifChoose(char **tmp){
    int i;
    if(!strcmp(*tmp,motcles[7]) || !strcmp(*tmp,motcles[8]) || !strcmp(*tmp,motcles[9])){
        tmp++;
        for(i = 0;i < NB_MOTS_C;i++)if(!strcmp(*tmp,motcles[i]))return 0;
        return 1;
    }
    return 0;
}

int verifSyntaxe(char** tmp){
    int i, j, chooseweapon = 0;

    if (!strcmp(*tmp, motcles[0])) {
        tmp++;
        for(i = 0; i < NB_MOTS_C; i++) {
            if (!strcmp(*tmp, motcles[i]))
                return 0;
        }
        tmp++;

        while (!strcmp(*tmp, motcles[6])) {
            if (!(j = verifChoose(++tmp)))
                return 0;
            else {
                if (!strcmp(*tmp, motcles[7]))
                    chooseweapon=1;
                tmp += j;
            }
            tmp++;
        }

        if (!chooseweapon)
            return 0;

        while (*tmp) {
            if (!strcmp(*tmp, motcles[1])) {
                tmp++;
                if ((j = verifIf(tmp)))
                    tmp += j;
                else return 0;
            } else{
                if ((j = verifCommande(tmp)) != -1)
                    tmp+=j;
                else return 0;
            }
            tmp++;
        }
        return 1;
    }
    return 0;
}

/**FIN VERIFICATION SYNTAXIQUE*/

/*DEBUT EXEC STRAT*/

void prompt_exec(Jeu* jeu, char** machaine, int j)
{
    if (j == 0) {
        /*sprintf(jeu->message, "Commande executé : %s\n", *machaine);*/
        ma_commande[0] = *machaine;
    }
    else if (j == 1) {
        /*sprintf(jeu->message, "Commande executé : %s %s\n", *machaine, machaine[1]);*/
        ma_commande[0] = *machaine;
        ma_commande[1] = machaine[1];
    } else if (j == 2) {
        /*sprintf(jeu->message, "Commande executé : %s %s %s\n", *machaine, machaine[1], machaine[2]);*/
        ma_commande[0] = *machaine;
        ma_commande[1] = machaine[1];
        ma_commande[2] = machaine[2];
    }

    prompt(strToCmd(), jeu);
    wait(jeu);
}

char** exec_condition(Jeu* jeu, char **machaine)
{
    int i;
    if( !strcmp(motcles[1], *machaine) ){
        execif(jeu, machaine);
        machaine++;
        i = verifIf(machaine);
    } else {
        i = verifCommande(machaine);

        if (strcmp(*machaine, "end") == 0)
            while (*(++machaine) != NULL);
        else
            prompt_exec(jeu, machaine, i);
    }
    if (*machaine != NULL) machaine += i + 1;
    return machaine;
}

char** exec_else(char **machaine)
{
    int i;
    if( !strcmp(*machaine,motcles[1]) ){
        machaine++;
        i = verifIf(machaine);
        machaine += i;
    }
    machaine++;
    return machaine;
}

char **execif(Jeu *jeu, char **machaine){
    int condition = -1, test, test2;
    Joueur *lifetest;
    machaine++;

    if( !strcmp(*machaine,motcles[10]) || !strcmp(*machaine,motcles[11]) ){
        if (!strcmp(*machaine, motcles[10]))
            lifetest = jeu->courant;
        else {
            if (jeu->courant == jeu->legume)
                lifetest = jeu->fruit;
            else
                lifetest = jeu->legume;
        }
        test = lifetest->champ->pv;
        /*verif du comparateurs*/
        machaine++;
        if (machaine[1][strlen(machaine[1]) - 1] == '%')
            test = (test * 100) / lifetest->champ->pv_max;
        test2 = atoi(machaine[1]);

        /*Verif de la condition*/
        if (!strcmp(motclescomp[0], *machaine))
            condition = !(test < test2);
        else if (!strcmp(motclescomp[1], *machaine))
            condition = !(test <= test2);
        else if (!strcmp(motclescomp[2], *machaine))
            condition = !(test == test2);
        else if (!strcmp(motclescomp[3], *machaine))
            condition = !(test != test2);
        else if (!strcmp(motclescomp[4], *machaine))
            condition = !(test >= test2);
        else if (!strcmp(motclescomp[5],*machaine))
            condition = !(test > test2);
        /* 0 : < - 1 : <= - 2 : = - 3 : != - 4 : >= - 5 : >*/
        machaine++;
    }
    else
        condition = !(fabs((float)(jeu->legume->pos - jeu->fruit->pos)) <= jeu->courant->equip->arme->portee);

    /*je traite le if*/
    machaine++;
    if(!condition){
        /*Exec jusqu'au else*/
        while(*machaine != NULL && strcmp(motcles[13], *machaine) && strcmp(motcles[14], *machaine) )
            machaine = exec_condition(jeu, machaine);

        /*machaine++;*/
        while(*machaine != NULL && strcmp(motcles[14],*machaine) )
            machaine = exec_else(machaine);
        /*Fin premier cas*/
    }
    else{
        /*Traverser la premiere partie de if*/
        while( strcmp(motcles[13],*machaine) && strcmp(motcles[14],*machaine) )
            machaine = exec_else(machaine);

        if( !strcmp(*machaine,motcles[13]) ) machaine++;
        /*faire l exec*/

        while(*machaine != NULL && strcmp(motcles[14],*machaine) )
            machaine = exec_condition(jeu, machaine);
    }

    return machaine;
}

void exec(Jeu *jeu,Strat *mastrat){
    char **machaine = mastrat->tab;
    int j;

    while( strcmp(*machaine,motcles[1]) && strcmp(*machaine,motcles[2]) && \
            strcmp(*machaine,motcles[3]) && strcmp(*machaine, motcles[4]) && strcmp(*machaine,motcles[17]) )
        machaine++;

    while(*machaine != NULL){
        if (!strcmp(motcles[1], *machaine))
            machaine = execif(jeu, machaine);
        else {
            j = verifCommande(machaine);
            prompt_exec(jeu, machaine, j);
            machaine += j;
        }
        machaine++;
    }
}

/*FIN DE L EXECUTION DE LA STRAT*/

Strat *creerStrat(char *nom, char *filename, char **tab){
    Strat *newStrat = (Strat*)calloc(sizeof(Strat), 1);
    newStrat->tab = tab;
    newStrat->nom = (char*)calloc(sizeof(char), strlen(nom) + 1);
    newStrat->filename = (char*)calloc(sizeof(char), strlen(filename) + 1);

    strcpy(newStrat->filename, filename);
    strcpy(newStrat->nom, nom);

    return newStrat;
}

Strat **creerListeStrats(char **listenoms,int n){
    Strat **listesStrats = calloc(sizeof(Strat), n);
    char **tmp;
    int i, j = 0;
    listesNomsStrats = calloc(sizeof(char *),n);
    for(i = 0;i < n; i++){
        tmp = lireFile(listenoms[i]);
        if( !strcmp(tmp[0],motcles[0]) ){
            if(verifSyntaxe(tmp)){
                listesNomsStrats[j] = tmp[1];
                listesStrats[j] = creerStrat(listesNomsStrats[j],listenoms[i],tmp);
                j++;
            }
            else nbStrats--;
        }
        else printf("ERROR\n");
    }
    return listesStrats;
}

Arme *findWeapon(Jeu *jeu,char *nom){
    char* test;
    int i,j;
    for(i = 0; nom[i] != '\0'; i++)
        nom[i] = toupper(nom[i]);
    for(i = 0;i < NB_ARMES;i++){
        test = calloc(sizeof(char), strlen(jeu->armes[i]->nom) + 1);
        strcpy(test,jeu->armes[i]->nom);
        replace(test,' ','_');
        replace(test,'-','_');
        for(j = 0;j < strlen(test);j++)
            test[j] = toupper(test[j]);
        if(!strcmp(test,nom)){
            free(test);
            return jeu->armes[i];
        }
        free(test);
    }
    return NULL;
}

Protection *findProtec(Jeu *jeu, char *nom){
    char* test;
    int i,j;
    for(i = 0; nom[i] != '\0'; i++)
        nom[i] = toupper(nom[i]);
    for(i = 0;i < NB_PROTECTS;i++){
        test = calloc(sizeof(char), strlen(jeu->protects[i]->nom) + 1);
        strcpy(test, jeu->protects[i]->nom);
        replace(test,' ','_');
        replace(test,'-','_');
        for(j = 0;j < strlen(test);j++)
            test[j] = toupper(test[j]);
        if(!strcmp(test,nom)){
            free(test);
            return jeu->protects[i];
        }
        free(test);
    }
    return NULL;
}

Soin *findHeal(Jeu *jeu,char *nom){
    char *test;
    int i,j;
    for(i = 0; nom[i] != '\0'; i++)
        nom[i] = toupper(nom[i]);
    for(i = 0;i < NB_ARMES;i++){
        test = calloc(sizeof(char), strlen(jeu->soins[i]->nom) + 1);
        strcpy(test,jeu->soins[i]->nom);
        replace(test,' ','_');
        replace(test,'-','_');
        for(j = 0;j < strlen(test);j++)
            test[j] = toupper(test[j]);
        if(!strcmp(test,nom)){
            free(test);
            return jeu->soins[i];
        }
        free(test);
    }
    return NULL;
}

void equipementStrats(Jeu *jeu){
    char **tmp;
    Equipement *equip;
    int i,arme,prot,heal;
    for(i = 0; i < nbStrats; i++){
        arme = 0;
        prot = 0;
        heal = 0;
        equip = calloc(sizeof(Equipement),1);
        tmp = mes_strats[i]->tab;
        tmp++;
        while( !strcmp(*(++tmp),motcles[6]) ){
            tmp++;
            if(!strcmp(*tmp,motcles[7]) && !arme){ /*Si une arme*/
                equip->arme = findWeapon(jeu,*(++tmp));
                mes_strats[i]->cout += equip->arme->ce;
                arme = 1;
            }
            else if(!strcmp(*tmp,motcles[8]) && !prot){
                equip->protect = findProtec(jeu, *(++tmp));
                mes_strats[i]->cout += equip->protect->ce;
                prot = 1;
            }
            else if(!strcmp(*tmp,motcles[9]) && !heal){
                equip->soin = findHeal(jeu,*(++tmp));
                mes_strats[i]->cout += equip->soin->ce;
                heal = 1;
            }
            else printf("ERROR\n");
        }
        mes_strats[i]->equip = equip;
        if(!mes_strats[i]->equip->arme)printf("ERROR\n");
    }
}

void printAllStrats(){
    int i = 0;
    printf("\t--- Strats ---\n");
    for(i = 0;i < nbStrats;i++)
        printf("\t/ %d / %s\n", i, mes_strats[i]->nom);
    printf("\t-------------\n\n");
}

void printStrat(int i){
    printf("\t--- %s ---\n", mes_strats[i]->filename);
    printf("\tNom : %s\n", mes_strats[i]->nom);
    printf("\tArme : %s\n", mes_strats[i]->equip->arme->nom);
    printf("\tProtection : %s\n", mes_strats[i]->equip->protect->nom);
    printf("\tSoin : %s\n", mes_strats[i]->equip->soin->nom);
    printf("\tCout en Ce : %d\n", mes_strats[i]->cout);
    printf("\t----%.*s----\n\n",(int)strlen(mes_strats[i]->filename),
            "-----------------------------------------------");
}

void remplirTab(){
    int i;
    char *tab[] = {"use","move","add","end"};
    /* 0 : use - 1 : move - 2 : add - 3 : end*/
    char *tab2[] = {"strategy","if","use","move","add","action","choose","weapon","protection",\
        "care","life","enemyLife","enemyInScope","else","endif","forward","backward","end"};

    /* 0 : strategy - 1 : if - 2 : use - 3 : move - 4 : add - 5 : action
6 : choose - 7 : weapon - 8 : protection - 9 : care - 10 : life
11 : enemyLife - 12 : enemyInScope - 13 : else - 14 : endif
15 : forward - 16 : backward - 17 : end*/
    char *tab3[] = {"<","<=","=","!=",">=",">"};
    /* 0 : < - 1 : <= - 2 : = - 3 : != - 4 : >= - 5 : >*/
    motclesprompt = calloc(sizeof(char *),NB_MOTS_C_P);
    motclescomp = calloc(sizeof(char *),NB_MOTS_C_C);
    motcles = calloc(sizeof(char *),NB_MOTS_C);
    for(i = 0;i < NB_MOTS_C_P;i++)motclesprompt[i]=tab[i];
    for(i = 0;i < NB_MOTS_C;i++)motcles[i]=tab2[i];
    for(i = 0;i < NB_MOTS_C_C;i++)motclescomp[i]=tab3[i];
}

void free_strats()
{
    int i;
    for(i = 0;i < nbStrats;i++){
        char** tab = mes_strats[i]->tab;
        while (*tab != NULL)
            free(*tab++);
        free(mes_strats[i]->tab);
        free(mes_strats[i]->equip);
        free(mes_strats[i]->nom);
        free(mes_strats[i]->filename);
        free(mes_strats[i]);
    }
    free(mes_strats);
    free(motcles);
    free(motclesprompt);
    free(motclescomp);
    free(listesNomsStrats);
}

void initStrats(Jeu *jeu) {
    char *pouet[]={"./build/Strats/1.strat","./build/Strats/2.strat","./build/Strats/3.strat"};
    /*int i;*/
    nbStrats=3;
    remplirTab();
    mes_strats = creerListeStrats(pouet, nbStrats);
    equipementStrats(jeu);
    /*for (i = 0; i < nbStrats; i++)*/
        /*printStrat(i);*/
    /*printAllStrats();*/
}
