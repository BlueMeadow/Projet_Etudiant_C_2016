#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void EntrerPseudo(){

	FILE *fic1;
	
	char nom[10];
	
	int nbre_joueurs = 4;
	int compteur = 1;
	int x=2;
	int y=2;
	
	fic1 = fopen("fichierPseudo.txt","w");
	
	do{
		wclear(ZoneMessage);
		// On demande le pseudo du joueur
		mvwprintw(ZoneMessage, y, x,"Quel est votre pseudo (10 caractères maximum) ? ");
		scanf("%s", nom);
		
		if ( strlen(nom) <= 10){
			// Si les conditions d'écriture sont respectés, on écrit le pseudo dans le fichier
			wclear(ZoneMessage);
			fprintf(fic1, "Le joueur numéro %i s'appelle %s.\n", compteur, nom);
			compteur++;
	 	}
	 	else{
			//si les conditions ne sont pas respectés, on affiche un message d'erreur
	 		mvwprintw(ZoneMessage, y, x, "Veuillez respecter les conditions d'écriture, s'il vous plaît.\n");
	 	}
	
	}while(compteur <= nbre_joueurs);
	//la demande de aisie de pseudo s'arrete lorsque tous les joueurs les ont.
	
	fclose(fic1);	
}


int main(){
	
	EnterPseudo();

}
