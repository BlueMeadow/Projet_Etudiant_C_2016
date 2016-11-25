#ifndef _yahtzee.h
#def _yahtzee.h

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int De[5]={0};                                  /* Tableau de dés */
int Garde[5]={0};                               /* Tableau booléen, sert à savoir si on garde les dés ou si on les relance */
int Score[4][13];                               /* Tableau conservant les scores de chaque joueur */
int Occurence[6]={0};                           /* Tableau content le nombre d'occurences de chaque valeur de dé */
char pseudo_j1[10] = "J1";                      /* Pseudo du joueur 1 */
char pseudo_j2[10] = "J2";                      /* Pseudo du joueur 2 */
char pseudo_j3[10] = "J3";                      /* Pseudo du joueur 3 */
char pseudo_j4[10] = "J4";                      /* Pseudo du joueur 4 */
char pseudos[40];                               /* Chaine de caractère contenant les pseudos des 4 joueurs avec le nombre d'espace nécesaire à un affichage correct */

int Categorie;                                   /* Permet de savoir quelle catégorie a été sélectionnée pour calcuelr le score */
WINDOW *ZoneTitre;                               /* Sous fenetre pour l'affichage de YAHTZEE ! */
WINDOW *ZoneMenu;                                /* Sous fenetre pour l'affichage des menus */
WINDOW *ZoneDe;                                  /* Sous fenetre pour l'affichage de la valeur de dés */
WINDOW *ZoneMessage;                             /* Sous fenetre pour l'affichage des messages à l'utilisateur pendant la partie */
WINDOW *ZoneAide;                                /* Sous fenetre pour l'affichage de l'aide au jeu */
WINDOW *ZoneScore;				 /* Sous fenetre pour l'affichage de la fiche de score */			



#endif
