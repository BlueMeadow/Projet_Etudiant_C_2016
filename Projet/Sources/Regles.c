#include "../include/Global.h"

/**
* \file Regles.c
* \brief Rassemble les fonctions principales
* \author Benoit Combasteix, Simon Fernandes et Nathan OUALET
* \version 1.0
*/

void PageRegles(WINDOW *Fenetre, int y, int x)
/* \fn PageRegles(WINDOW *Fenetre, int y, int x)
* \brief affiche toutes les règles du jeu
*/ 
{	
	mvwprintw(Fenetre, y,    x, "                        Règles du Yahtzee                                              ");
	mvwprintw(Fenetre, y+1,  x, "+------------+------------------------------------------------+");
	mvwprintw(Fenetre, y+2,  x, "|  As à Six  | Vous multipliez le nombre d'occurrences d une  |");
	mvwprintw(Fenetre, y+3,  x, "|            | valeur par cette valeur et l'écrivez dans la   |");
	mvwprintw(Fenetre, y+4,  x, "|            | case correspondante. i.e.                      |");                                              
	mvwprintw(Fenetre, y+5,  x, "|            | vous inscrivez 10 dans la case.                |");                                             
	mvwprintw(Fenetre, y+6,  x, "|            |                                                |");                                               
	mvwprintw(Fenetre, y+7,  x, "+------------+------------------------------------------------+");                                          
	mvwprintw(Fenetre, y+8,  x, "+------------+------------------------------------------------+");
	mvwprintw(Fenetre, y+9,  x, "|  Brelan    | Vous obtenez trois fois le même chiffre et deux|");
	mvwprintw(Fenetre, y+10, x, "|            | autres chiffres. Vous additionnez le total des |");
	mvwprintw(Fenetre, y+11, x, "|            | dés et l'écrivez dans la case Brelan         |");                                              
	mvwprintw(Fenetre, y+12, x, "|            |                                                |");                                               
	mvwprintw(Fenetre, y+13, x, "+------------+------------------------------------------------+");
	mvwprintw(Fenetre, y+14, x, "+------------+------------------------------------------------+");
	mvwprintw(Fenetre, y+15, x, "| Pt Suite   | Vous obtenez une suite de quatre chiffre.      |");                                                
	mvwprintw(Fenetre, y+16, x, "|            | Vous gagnez 30 points.                         |");                                               
	mvwprintw(Fenetre, y+17, x, "|            |                                                |");                                               
	mvwprintw(Fenetre, y+18, x, "+------------+------------------------------------------------+");                                     
	mvwprintw(Fenetre, y+19, x, "+------------+------------------------------------------------+");
	mvwprintw(Fenetre, y+20, x, "| Gd Suite   | Vous obtenez une suite de cinq chiffres.       |");  
	mvwprintw(Fenetre, y+21, x, "|            |  Vous gagnez 40 points.                        |"); 
	mvwprintw(Fenetre, y+22, x, "|            |                                                |"); 
	mvwprintw(Fenetre, y+23, x, "+------------+------------------------------------------------+");
	mvwprintw(Fenetre, y+24, x, "+------------+------------------------------------------------+");
	mvwprintw(Fenetre, y+25, x, "|   Carré    | Vous obtenez quatre fois le même chiffre et un |"); 
	mvwprintw(Fenetre, y+26, x, "|            | autre. Vous additionnez le total des dés et    |"); 
	mvwprintw(Fenetre, y+27, x, "|            | l'écrivez dans la case Carré.                |"); 
	mvwprintw(Fenetre, y+28, x, "|            |                                                |");
	mvwprintw(Fenetre, y+29, x, "+------------+------------------------------------------------+");
	mvwprintw(Fenetre, y+30, x, "+------------+------------------------------------------------+");
	mvwprintw(Fenetre, y+31, x, "|   Full     | Vous obtenez trois dés identiques et 2 dés     |"); 
	mvwprintw(Fenetre, y+32, x, "|            | identiques entre eux. Vous additionnez le total|"); 
	mvwprintw(Fenetre, y+33, x, "|            | des dés et l'écrivez dans la case Full,      |"); 
	mvwprintw(Fenetre, y+34, x, "|            | vous gagnez 25 points bonus.                   |");
	mvwprintw(Fenetre, y+35, x, "|            |                                                |");
	mvwprintw(Fenetre, y+36, x, "+------------+------------------------------------------------+");
	mvwprintw(Fenetre, y+37, x, "+------------+------------------------------------------------+");
	mvwprintw(Fenetre, y+38, x, "|  Yahtzee   | Vous obtenez 5 dés identiques.                |"); 
	mvwprintw(Fenetre, y+39, x, "|            | Vous marquez 50 points.                        |"); 
	mvwprintw(Fenetre, y+40, x, "|            |                                                |");
	mvwprintw(Fenetre, y+41, x, "+------------+------------------------------------------------+");
	mvwprintw(Fenetre, y+42, x, "+------------+------------------------------------------------+");
	mvwprintw(Fenetre, y+43, x, "|  Chance    | Vous additionnez la valeur de chaque dé et     |"); 
	mvwprintw(Fenetre, y+44, x, "|            | l'écrivez dans la case.                       |"); 
	mvwprintw(Fenetre, y+45, x, "|            |                                                |");
	mvwprintw(Fenetre, y+46, x, "+------------+------------------------------------------------+");
	mvwprintw(Fenetre, y+47, x, "+-------------------------------------------------------------+");
	mvwprintw(Fenetre, y+48, x, "| Attention ! Plusieurs résultats peuvent correspondre à      |");
	mvwprintw(Fenetre, y+49, x, "| plusieurs catégories mais vous ne pouvez remplir une case   |");
	mvwprintw(Fenetre, y+50, x, "| qu'une seule fois, soyez stratégiques !                    |");
	mvwprintw(Fenetre, y+51, x, "+-------------------------------------------------------------+");
} 
	


int Regles()
/* \fn Regles()
* \brief Affiche les règles dans un menu défilant
*/
{

	int x, y, ch;

	WINDOW * ZoneRegles;
	ZoneRegles = newwin(30, 120, (LINES-30)/2, (COLS-67)/2);
	ZoneMessage = CreerFenetre(5,120, (LINES-30)/2+35, (COLS-120)/2);

	keypad(ZoneRegles, TRUE);/**< Permet d'utiliser les fleches directionnelles */
	curs_set(0);/**< Rend le curseur invisible */

	mvwprintw(ZoneMessage, 2, 38, "Faites défiler avec les flèches ou la molette");
	mvwprintw(ZoneMessage, 3, 38, "Appuyez sur [ENTREE] pour retourner au menu");
	wrefresh(ZoneMessage);

	y = 1;
	x = 2;
	
	do
	{

		Nettoyer(ZoneRegles, 0, 0, LINES, COLS);
		PageRegles(ZoneRegles, y, x);
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
		}

	} while (ch != 10); 
	DetruireFenetre(ZoneRegles);
	DetruireFenetre(ZoneMessage);
	return 0;
}
