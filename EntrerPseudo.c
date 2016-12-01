/**
* \file EnterPseudo.c
* \version 2.0
* \date 28 novembre 2016
* \fn EnterPseudo()
* \return Enregistre et affiche le pseudo des joueurs
*/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char pseudos[40];


void EnterPseudo(){

	//char pseudo_j[0][10];                      /* Pseudo du joueur 1 */
	//char pseudo_j[1][10];                      /* Pseudo du joueur 2 */
	//char pseudo_j[2][10];                      /* Pseudo du joueur 3 */
	//char pseudo_j[3][10];                      /* Pseudo du joueur 4 */
	
	char pseudo_j[4][10];
	
	//char pseudos[40];                        /* Chaine de caractère contenant les pseudos des 4 joueurs avec le nombre d'espace nécesaire à un affichage correct */


	
	int nbjoueurs = 4;
	int compteur = 1;
	

		for ( int i=0; i < nbjoueurs; i++){
	
			// On demande le pseudo 
			mvwprintw(localwin, y, x, "Quel est votre pseudo (moins de 10 caractères) ? ");
			scanf("%s", pseudo_j[i]);
		
			if ( strlen(pseudo_j[i]) < 10){
				// On l'écrit dans le fichier
				
				mvwprintw(localwin, y, x, "%s", pseudo_j[i]);
				mvwprintw(localwin, y, x, "Bonne insertion. Bonjour %s !\n", pseudo_j[i]);
				mvwprintw(localwin, y, x, "%s ", pseudos);
				
		 	}
		 	else{
		 		printf("Veuillez respecter les conditions d'écriture, s'il vous plaît.\n");
		 	}
		 }



}


int main(){

	//char pseudos[40]; 
	
	EnterPseudo();
	
	printf("%s", pseudos); 
	
	printf("Affichage\n");
	
	

}
