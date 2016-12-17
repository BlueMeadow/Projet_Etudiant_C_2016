/* Bibliothèques standards */
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
/* -------------------- */

/* HEADERS */
#include "Affichage.h"
#include "Chargement.h"
#include "Fenetre.h"
#include "Highscore.h"
#include "Initialisation.h"
#include "Lancer.h"
#include "Partie.h"
#include "Regles.h"
#include "Score.h"
/* -------------------- */


#ifndef H_Global
#define H_Global

WINDOW *ZoneDe;
WINDOW *ZoneMessage;
WINDOW *ZoneAide;
WINDOW *ZoneResultat;
WINDOW *ZoneScore;
WINDOW *ZoneMenu;
WINDOW *ZoneHighScore;
WINDOW *ZoneChargement;

int Occurrences[6];
int Score[4][13];
int De[5];
int Garde[5];
int NbJoueurs;
char PseudoJ[4][10];
char Pseudos[40];
int Joueur;
int NbTours;
int NbLancers;
int isAide[4];

#endif


