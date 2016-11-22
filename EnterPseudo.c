#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void EnterPseudo(){

	FILE *fic1;
	//FILE *fic2;
	
	char nom[10];
	//char pseudo[10];
	int nbre_joueurs = 4;
	int compteur = 1;
	
	fic1 = fopen("fichierPseudo.txt","w");
	
	do{
		// On demande l'âge
		printf("Quel est votre pseudo (10 caractères maximum) ? ");
		scanf("%s", nom);
		
		if ( strlen(nom) <= 10){
			// On l'écrit dans le fichier
			fprintf(fic1, "Le joueur numéro %i s'appelle %s.\n", compteur, nom);
			compteur++;
	 	}
	 	else{
	 		printf("Veuillez respecter les conditions d'écriture, s'il vous plaît.\n");
	 	}
	 			
		
	
	}while(compteur <= nbre_joueurs);
	
	fclose(fic1);
	
	/*fic2 = fopen("fichierpseudo.txt","r");
	
	if(fic2 == NULL){
		printf("Le fichier pseudo est vide.\n");
	}
	else{
		while(!feof(fic2)){
		
			fscanf(fic2,"%s", pseudo); // On lit le caractère
            		fprintf("%s", pseudo); // On l'affiche
		
		}
		fclose(fic2);
	
	
	}*/
	

}


int main(){
	
	EnterPseudo();

}
