#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void Regles(WINDOW *localwin, int y, int x){

	int page1, page2, page3;
	
	int x = 2;
	int y = 2;
	
	mvwprintw(localwin, y 1, x,  "                     Rêgles du Yahtzee   %s", pseudos);
	mvwprintw(localwin, y+2, x,  "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+3, x,  "|  As à Six  | Vous multipliez le nombre d’occurrences d’une  |");
	mvwprintw(localwin, y+4, x,  "|            | valeur par cette valeur et l’écrivez dans la   |");                                              
	mvwprintw(localwin, y+5, x,  "|            | case correspondante. i.e. Vous obtenez 5 Deux,	|");                                              
	mvwprintw(localwin, y+6, x,  "|            | vous inscrivez 10 dans la case.                |");                                             
	mvwprintw(localwin, y+7, x,  "|            |                                                |");                                               
	mvwprintw(localwin, y+8, x,  "+------------+------------------------------------------------+");                                          
	mvwprintw(localwin, y+9, x,  "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+10, x, "|  Brelan    | Vous obtenez trois fois le même chiffre et deux|");
	mvwprintw(localwin, y+11, x, "|            | autres chiffres. Vous additionnez le total des |");
	mvwprintw(localwin, y+12, x, "|            | dés et l'écrivez dans la case « Brelan »       |");                                              
	mvwprintw(localwin, y+13, x, "|            |                                                |");                                               
	mvwprintw(localwin, y+14, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+15, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+16, x, "| Pt Suite   | Vous obtenez une suite de quatre chiffre.      |");                                                
	mvwprintw(localwin, y+17, x, "|            | Vous gagnez 30 points.                         |");                                               
	mvwprintw(localwin, y+18, x, "|            |                                                |");                                               
	mvwprintw(localwin, y+19, x, "+------------+------------------------------------------------+");                                     
	mvwprintw(localwin, y+20, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+21, x, "| Gd Suite   | Vous obtenez une suite de cinq chiffres.       |");  
	mvwprintw(localwin, y+22, x, "|            |  Vous gagnez 40 points.                        |"); 
	mvwprintw(localwin, y+23, x, "|            |                                                |"); 
	mvwprintw(localwin, y+24, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+25, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+26, x, "|   Carré    | Vous obtenez quatre fois le même chiffre et un |"); 
	mvwprintw(localwin, y+27, x, "|            | autre. Vous additionnez le total des dés et    |"); 
	mvwprintw(localwin, y+28, x, "|            | l'écrivez dans la case « Carré ».              |"); 
	mvwprintw(localwin, y+29, x, "|            |                                                |");
	mvwprintw(localwin, y+30, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+31, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+32, x, "|   Full     | Vous obtenez trois dés identiques et 2 dés     |"); 
	mvwprintw(localwin, y+33, x, "|            | identiques entre eux. Vous additionnez le total|"); 
	mvwprintw(localwin, y+34, x, "|            | des dés et l'écrivez dans la case « Full »,    |"); 
	mvwprintw(localwin, y+35, x, "|            | vous gagnez 25 points bonus.                   |");
	mvwprintw(localwin, y+36, x, "|            |                                                |");
	mvwprintw(localwin, y+37, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+38, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+39, x, "|  Yahtzee   | Vous obtenez 5 dés identiques.                 |"); 
	mvwprintw(localwin, y+40, x, "|            | Vous marquez 50 points.                        |"); 
	mvwprintw(localwin, y+41, x, "|            |                                                |");
	mvwprintw(localwin, y+42, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+43, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+44, x, "|  Chance    | Vous additionnez la valeur de chaque dé et     |"); 
	mvwprintw(localwin, y+45, x, "|            | l'écrivez dans la case.                        |"); 
	mvwprintw(localwin, y+46, x, "|            |                                                |");
	mvwprintw(localwin, y+47, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+48, x, "+-------------------------------------------------------------+");
	mvwprintw(localwin, y+49, x, "| Attention ! Plusieurs résultats peuvent correspondre à      |");
	mvwprintw(localwin, y+50, x, "| plusieurs catégories mais vous ne pouvez remplir une case   |");
	mvwprintw(localwin, y+51, x, "| qu'une seule fois, soyez stratégiques !                     |");
	mvwprintw(localwin, y+52, x, "+-------------------------------------------------------------+");
	
	
	
	wrefresh(localwin);





}