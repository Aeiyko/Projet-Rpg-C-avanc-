#ifndef JOUEUR_H
#define JOUEUR_H

typedef enum{TEAM1,TEAM2}Team;

typedef struct{
  char *nom;
  Team team;
  int ce;
  int ca;
  Champion champ;
}

#endif
