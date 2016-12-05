/**
* \file debut.c
* \author Nathan OUALET
* \brief Permet via un menu, de choisir entre un enouvelle partie, voir les rêgles ou quitter le jeu.
* \date 05 décembre 2016
* \verson 1.0
*/

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void Page_Regles(WINDOW *localwin, int y, int x){
	

	
	mvwprintw(localwin, y,   x,  "                        Rêgles du Yahtzee ");
	mvwprintw(localwin, y+1, x,  "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+2, x,  "|  As à Six  | Vous multipliez le nombre d occurrences d une  |");
	mvwprintw(localwin, y+3, x,  "|            | valeur par cette valeur et l écrivez dans la   |");                                              
	mvwprintw(localwin, y+4, x,  "|            | case correspondante. i.e. Vous obtenez 5 Deux, |");                                              
	mvwprintw(localwin, y+5, x,  "|            | vous inscrivez 10 dans la case.                |");                                             
	mvwprintw(localwin, y+6, x,  "|            |                                                |");                                               
	mvwprintw(localwin, y+7, x,  "+------------+------------------------------------------------+");                                          
	mvwprintw(localwin, y+8, x,  "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+9, x,  "|  Brelan    | Vous obtenez trois fois le même chiffre et deux|");
	mvwprintw(localwin, y+10, x, "|            | autres chiffres. Vous additionnez le total des |");
	mvwprintw(localwin, y+11, x, "|            | dés et l'écrivez dans la case « Brelan »       |");                                              
	mvwprintw(localwin, y+12, x, "|            |                                                |");                                               
	mvwprintw(localwin, y+13, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+14, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+15, x, "| Pt Suite   | Vous obtenez une suite de quatre chiffre.      |");                                                
	mvwprintw(localwin, y+16, x, "|            | Vous gagnez 30 points.                         |");                                               
	mvwprintw(localwin, y+17, x, "|            |                                                |");                                               
	mvwprintw(localwin, y+18, x, "+------------+------------------------------------------------+");                                     
	mvwprintw(localwin, y+19, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+20, x, "| Gd Suite   | Vous obtenez une suite de cinq chiffres.       |");  
	mvwprintw(localwin, y+21, x, "|            |  Vous gagnez 40 points.                        |"); 
	mvwprintw(localwin, y+22, x, "|            |                                                |"); 
	mvwprintw(localwin, y+23, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+24, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+25, x, "|   Carré    | Vous obtenez quatre fois le même chiffre et un |"); 
	mvwprintw(localwin, y+26, x, "|            | autre. Vous additionnez le total des dés et    |"); 
	mvwprintw(localwin, y+27, x, "|            | l'écrivez dans la case « Carré ».              |"); 
	mvwprintw(localwin, y+28, x, "|            |                                                |");
	mvwprintw(localwin, y+29, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+30, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+31, x, "|   Full     | Vous obtenez trois dés identiques et 2 dés     |"); 
	mvwprintw(localwin, y+32, x, "|            | identiques entre eux. Vous additionnez le total|"); 
	mvwprintw(localwin, y+33, x, "|            | des dés et l'écrivez dans la case « Full »,    |"); 
	mvwprintw(localwin, y+34, x, "|            | vous gagnez 25 points bonus.                   |");
	mvwprintw(localwin, y+35, x, "|            |                                                |");
	mvwprintw(localwin, y+36, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+37, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+38, x, "|  Yahtzee   | Vous obtenez 5 dés identiques.                 |"); 
	mvwprintw(localwin, y+39, x, "|            | Vous marquez 50 points.                        |"); 
	mvwprintw(localwin, y+40, x, "|            |                                                |");
	mvwprintw(localwin, y+41, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+42, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+43, x, "|  Chance    | Vous additionnez la valeur de chaque dé et     |"); 
	mvwprintw(localwin, y+44, x, "|            | l'écrivez dans la case.                        |"); 
	mvwprintw(localwin, y+45, x, "|            |                                                |");
	mvwprintw(localwin, y+46, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+47, x, "+-------------------------------------------------------------+");
	mvwprintw(localwin, y+48, x, "| Attention ! Plusieurs résultats peuvent correspondre à      |");
	mvwprintw(localwin, y+49, x, "| plusieurs catégories mais vous ne pouvez remplir une case   |");
	mvwprintw(localwin, y+50, x, "| qu'une seule fois, soyez stratégiques !                     |");
	mvwprintw(localwin, y+51, x, "+-------------------------------------------------------------+");
	
		

} 
	


void Regles(){
/* A faire dans une fenetre ayant moins de lignes que le texte que l'on veut afficher */
	int x, y, ch;
	WINDOW * ZoneRegles;
	ZoneRegles =  newwin(30, 67, 1, 1);	
	wrefresh(ZoneRegles);
	keypad(ZoneRegles, TRUE);
	y = 1;
	x = 1;
	
	do
	{

		wclear(ZoneRegles);
		/* Copier Les règles ici */
		Page_Regles(ZoneRegles, y, x);
		wrefresh(ZoneRegles);
		ch = wgetch(ZoneRegles);
		switch (ch)
		{
			case KEY_DOWN:  
				if ( y > -24 )
				{
					y = y-1;
				}
				break;
			case KEY_UP:
				if ( y < 1)
				{
					y = y + 1;

				}
				break;
			case 'q' : Debut(); break;
		}

	} while (ch != 10); /* Entrée fait sortir de l'affichage des règles */
	/* Retour au menu ici */
}


int debut(WINDOW *localwin, int y, int x){	

	
/* Affichage du menu et saisie du choix */
		
		
	mvwprintw(localwin, y,   x,  "  |Bonjour Joueurs de Yahtzee !");
	mvwprintw(localwin, y+1, x,  "  |Nouvelle Partie ?");
	mvwprintw(localwin, y+2, x,  "  |Voir les Regles.");
	mvwprintw(localwin, y+3, x,  "  |Quitter le jeu.");
	
}



void SelectDebut()
{
	int y, x, ch;
	
	y = 1; //indice d'ordonnée
	x = 1; // indice d'abscisse
	WINDOW * ZoneDebut;
	ZoneDebut =  newwin(30, 67, 1, 1);
	
	keypad(ZoneDebut, TRUE); //Permet l'utilisation des touches directionnelles
	
	debut(ZoneDebut, y, x);
	wmove(ZoneDebut, 2, 2);
	wrefresh(ZoneDebut);
	do 
	{	
		
		ch = wgetch(ZoneDebut);
		switch (ch)
		{
			case KEY_DOWN:  
				if ( y < 4 )
				{
					y = y + 1;
					wmove(ZoneDebut, y, x);
					wrefresh(ZoneDebut);
				}
				else{
					y = 2;
					wmove(ZoneDebut, y, x);
					wrefresh(ZoneDebut);			
				}
				
			case KEY_UP:
				if ( y > 2)
				{
					y = y - 1;
					wmove(ZoneDebut, y, x);
					wrefresh(ZoneDebut);

				}
				else{
					y = 4;
					wmove(ZoneDebut, y, x);
					wrefresh(ZoneDebut);			
				}
				
			
		}
	wrefresh(ZoneDebut);	
	} while ( ch != 10 );	
	/* On valide la selection avec la touche entree */
	
	/*if ( y == 3 ) {
			Partie();
		}*/
		if ( y == 3){			
			
			Regles();
		}
		else{
			
			
		}
}

int Debut(){
	
	
	initscr();
	cbreak();
	noecho(); /* Les trois lignes au dessus sont dans MiseEnPlace() */
	SelectMenu();
	endwin();

}

















