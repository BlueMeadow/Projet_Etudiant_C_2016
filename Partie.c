#include <stdio.h>
#include<stdlib.h>
#include "fonction.h"

/*
 La partie commence enfin. Etape importante: Veuillez entrer vos pseudos Première étape: sélection du premier joueur par la fonction QuiCommence.c. L'ordre des joueurs se fera par le
 sens des aiguilles d'une montre. Donc le premier joueur joue. Le suivi des fonctions sera le même pour tous les joueurs de la partie. 
 Tout d'abord, au premier lancer, les joueurs lancent leurs 5 dés. Ensuite ils continuent à lancer leurs dés de leur choix selon la combinaison
 qu'il obtienne jusqu'au troisième lancer. Ils peuvent les lancers quand ils veulent. Pour chaque lancer, une aide sera disponible pour connaître 
 le score qu'il obtienne selon la combinaison des 5 dés.  
*/

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
