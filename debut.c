#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int debut(WINDOW *localwin, int y, int x){	

	
/* Affichage du menu et saisie du choix */
		
		
	mvwprintw(localwin, y,   x,  "Bonjour Joueurs de Yahtzee !");
	mvwprintw(localwin, y+1, x,  "  | Nouvelle Partie ?");
	mvwprintw(localwin, y+2, x,  "  | Voir les Regles.");
	mvwprintw(localwin, y+3, x,  " | Quitter le jeu.");
	
}

void ChoixCategorie ( WINDOW *localwin)
{
	int y, x;
	y = 5; //indice d'ordonnée
	x = 4; // indice d'abscisse
	int ch; 
	keypad(localwin, TRUE); //Permet l'utilisation des touches directionnelles
	
	wmove(localwin, y, x);
	wrefresh(localwin);

	
	do 
	{
		ch = wgetch(localwin);
		switch (ch)
		{
			case KEY_UP:  
				/* Fleche du haut entree */
				if (y == 5)
				{
					y = 20; 
					/* Si on est en haut du tableau, on passe en bas */
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				else if (y == 14)
				{
					/* On remet un vide car on change de catégorie */
					y = 10; 
					/* On passe les 3 lignes centrales du tableau de score */
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				else 
				{
					y--;
					/* On remonte d'une case */
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				break;
			
			case KEY_DOWN:
				/* Fleche du bas entree */
				if (y == 20)
				{
					y = 5; 
					/* Si on est en bas du tableau, on passe en haut */
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				else if (y == 10)
				{
					y = 14; 
					/* On passe les 3 lignes centrales du tableau de score */
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				else 
				{

					y++;
					/* On descend d'une case */
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				break;
		}
		
			
	} while (ch != 10); 
		/* Entrée valide le choix */
}

int main(void){
	
	int ch;
	WINDOW * ZoneDebut;
	ZoneDebut =  newwin(20, 40, 1, 1);
	initscr();
	cbreak();
	noecho(); /* Les trois lignes au dessus sont dans MiseEnPlace() */
	ChoixCategorie(ZoneDebut);
	endwin();



}















