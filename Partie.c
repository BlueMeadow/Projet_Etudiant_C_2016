#include <stdio.h>
#include<stdlib.h>
#include "fonction.h"

int De[5] /* stock les résultats des 5 dés */
int Garder[5] /* tableau de booléens, permet de savoir si on veut relancer les dés */
int Score[13][4] /* Garde le score de chaque joueur */

int Partie (int nb){
	int repjoueur;
	int nb_joueur=0;
	int reptour;
	Debut();
	for(repjoueur=0;repjoueur<nb_joueur;repjoueur++){
		for(reptour=0;rep<13;rep++){
			Lancer();
			Calcul();
			Garde();
		}
		ChangerJoueur();
	}
}
