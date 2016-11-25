#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "Yahtzee.h"

void EcrireScore(int joueur){
	int categorie = 0;
	int x = 2;
	int y = 2;
	
	mvwprintw(ZoneMessage ,y ,x ,"veuillez désigner la categorie choisie");
	ChoixCategorie(categorie ,ZoneMessage); 
	Calcul_Score();
	
	/* choix de la colonne */
	x = 9 + 10 * joueur;
	/* choix de la ligne */
	
	if(categorie < 7)
		y = categorie + 2;
	else
		y = categorie + 5;
	
	/*affiche le score */
	mvwprintw(ZoneScore ,x ,y ,"%i" ,Score[joueur][categorie]);
}

int main(){
	EcrireScore(1);
}
	
	
