#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int debut(WINDOW *localwin, int y, int x){	

	
/* Affichage du menu et saisie du choix */
		
		
	mvwprintw(localwin, y,   x,  " Bonjour Joueurs de Yahtzee !");
	mvwprintw(localwin, y+1, x,  " 1 - Nouvelle Partie ?");
	mvwprintw(localwin, y+2, x,  " 2 - Voir les Regles.");
	mvwprintw(localwin, y+3, x,  " 3 - Quitter le jeu.");
	
}

void ChoixCategorie (int *Categorie, WINDOW *localwin)
{
	
	
	int y, x;
	y = 1; //indice d'ordonnée
	x = 1; // indice d'abscisse
	int ch; 
	keypad(localwin, TRUE); //Permet l'utilisation des touches directionnelles
	
	wmove(localwin, y, x);
	wrefresh(localwin);

	
	do 
	{
		wclear(localwin);
		/* Copier Les règles ici */
		debut(localwin, y, x);
		wrefresh(localwin);
		
		ch = wgetch(localwin);
		switch (ch)
		{
			case KEY_UP:  
				
				y--;
				/* On remonte d'une case */
				wmove(localwin, y, x);
				wrefresh(localwin);
				break;
				
				
			
			case KEY_DOWN:
				/* Fleche du bas entree */
				y++;
				/* On descend d'une case */
				wmove(localwin, y, x);
				wrefresh(localwin);
				
				break;
		}
		if (y < 11) *Categorie = y - 4;
		else *Categorie = y - 7;
	} while (ch != 10); 
		/* Entrée valide le choix */
}

int main(void){

	int x, y, ch;
	WINDOW * ZoneDebut;
	ZoneDebut =  newwin(30, 67, 1, 1);	
	
	ChoixCategorie (1, ZoneDebut);




}





