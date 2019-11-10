# Projet-Rpg-C-avanc-
Rpg Fruit vs Légumes (LeekWars)
Projet créé par Alexis SALVETTI et JORDAN HERENG

Pour compiler utiliser la commande :
  make
Cela a pour effet de créer un dossier build contenant le fichier éxécutable
pour supprimer le dossier build ainsi que l'éxécutable :
  make clean

affichage.c/affichage.h :
  Création de l'affichage

commande.c/commande.h :
  Toutes les commandes liés au jeu et utilisable par le joueur

  - show(Jeu) : Permet d'afficher les détails du personnage courant
  (commande utilisable seulement en combat)
  - show_vars(Jeu,Char*) : Permet d'afficher la liste des personnages d'un certain camp
  (commande utilisable a n'importe quel moment)
  - show_vars_i(Jeu,Char*,int) : Permet d'afficher les détails du personnage a l'indice i
  (commande utilisable a n'importe quel moment)
  - exit_game(Jeu) : Permet de fermer le Jeu
  (commande utilisable a n'importe quel moment)
  - equip(Jeu,int,int,int) : Permet d'équiper les personnages
  (commande utilisable quand le match vient d'être lancé et que les personnages ne sont pas encore équipés)
  - move(Jeu,char*,int) : Permet de bouger son personnage
  (commande utilisable seulement en combat)
  use_weapon(Jeu,int)/use_protection(Jeu)/use_care(Jeu,int) : Permet d'utiliser son arme/protection/soin
  (commande utilisable seulement en combat)

equipement.c/equipement.h :
  Gère les equipements

  - initArme(char*,int,int,int,int,int)/
    initProtection(char*,int,int,int)/
    initSoin(char*,int,int,int,int,int) : Initialise une arme/protection/soin
  - initArmes(Arme***)/initProtections(Protection***)/initSoins(Soin***) : Permet d'initialiser la liste des armes/protections/soins
  - freeArmes(Arme***)/freeProtections(Protection***)/freeSoins(Soin***)

jeu.c/jeu.h :
 - initEquipement(Arme*,Protection*,Soin*)/
   initChamp(char*,Type,int,int,int,int)/
   initJoueur(int,int,int)/
   initJeu() : Initialise l'Equipement/Champion/Joueur/Jeu
 - initChamps() : initialise la liste des champions
 - boucle_combat(Jeu*) : Gère la boucle de combat
 - freeJoueur(Joueur**)/
   freeChamps(Champion**)/
   freeJeu(Jeu**) : Free tous les Joueurs/Champions/Jeu

prompt.c/prompt.h :
 - prompt_show(Jeu*)/
   prompt_equip(Jeu*)/
   prompt_fight(Jeu*)/
   prompt_move(Jeu*)/
   prompt_use(Jeu*)/
   prompt_end(Jeu*) : Permet de lancer les commandes
 - strToCmd() : Permet de transformer une chaine en une commande de base
 - vider_ma_commande() : Permet de vider la chaine de caractère qui sert de buffer
 - prompt(Commande,Jeu*) : Prompt général
 - rangecommand(char*) : range la commande dans la chaine de caractère buffer
 - affichePrompt(Jeu*) : affiche le prompt et demande une commande
