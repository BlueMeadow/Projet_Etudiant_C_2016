#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void ReglesPage1(WINDOW *localwin, int y, int x){
	
	
	int x = 2;
	int y = 2;
	
	mvwprintw(localwin, y  , x,  "                  Rêgles du Yahtzee - Page 1   %s");
	mvwprintw(localwin, y+1, x,  "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+2, x,  "|  As à Six  | Vous multipliez le nombre d’occurrences d’une  |");
	mvwprintw(localwin, y+3, x,  "|            | valeur par cette valeur et l’écrivez dans la   |");                                              
	mvwprintw(localwin, y+4, x,  "|            | case correspondante. i.e. Vous obtenez 5 Deux,	|");                                              
	mvwprintw(localwin, y+5, x,  "|            | vous inscrivez 10 dans la case.                |");                                             
	mvwprintw(localwin, y+6, x,  "|            |                                                |");                                               
	mvwprintw(localwin, y+7, x,  "+------------+------------------------------------------------+");                                          
	mvwprintw(localwin, y+8, x,  "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+9,  x, "|  Brelan    | Vous obtenez trois fois le même chiffre et deux|");
	mvwprintw(localwin, y+10, x, "|            | autres chiffres. Vous additionnez le total des |");
	mvwprintw(localwin, y+11, x, "|            | dés et l'écrivez dans la case « Brelan »       |");                                              
	mvwprintw(localwin, y+12, x, "|            |                                                |");                                               
	mvwprintw(localwin, y+13, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+14, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+15, x, "| Pt Suite   | Vous obtenez une suite de quatre chiffre.      |");                                                
	mvwprintw(localwin, y+16, x, "|            | Vous gagnez 30 points.                         |");                                               
	mvwprintw(localwin, y+17, x, "|            |                                                |");                                               
	mvwprintw(localwin, y+18, x, "+------------+------------------------------------------------+");   


}

void ReglesPage2(WINDOW *localwin, int y, int x){
	
	
	int x = 2;
	int y = 2;
	
	mvwprintw(localwin, y  , x,  "          	Rêgles du Yahtzee - Page 2   %s");	
	mvwprintw(localwin, y+1 , x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+2 , x, "| Gd Suite   | Vous obtenez une suite de cinq chiffres.       |");  
	mvwprintw(localwin, y+3 , x, "|            |  Vous gagnez 40 points.                        |"); 
	mvwprintw(localwin, y+4 , x, "|            |                                                |"); 
	mvwprintw(localwin, y+5 , x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+6 , x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+7 , x, "|   Carré    | Vous obtenez quatre fois le même chiffre et un |"); 
	mvwprintw(localwin, y+8 , x, "|            | autre. Vous additionnez le total des dés et    |"); 
	mvwprintw(localwin, y+9 , x, "|            | l'écrivez dans la case « Carré ».              |"); 
	mvwprintw(localwin, y+10, x, "|            |                                                |");
	mvwprintw(localwin, y+11, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+12, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+13, x, "|   Full     | Vous obtenez trois dés identiques et 2 dés     |"); 
	mvwprintw(localwin, y+14, x, "|            | identiques entre eux. Vous additionnez le total|"); 
	mvwprintw(localwin, y+15, x, "|            | des dés et l'écrivez dans la case « Full »,    |"); 
	mvwprintw(localwin, y+16, x, "|            | vous gagnez 25 points bonus.                   |");
	mvwprintw(localwin, y+17, x, "|            |                                                |");
	mvwprintw(localwin, y+18, x, "+------------+------------------------------------------------+");


}

void ReglesPage3(WINDOW *localwin, int y, int x){
	
	
	int x = 2;
	int y = 2;
	
	
	mvwprintw(localwin, y  , x,  "          	Rêgles du Yahtzee - Page 3   %s");	
	mvwprintw(localwin, y+1 , x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+2 , x, "|  Yahtzee   | Vous obtenez 5 dés identiques.                 |"); 
	mvwprintw(localwin, y+3 , x, "|            | Vous marquez 50 points.                        |"); 
	mvwprintw(localwin, y+4 , x, "|            |                                                |");
	mvwprintw(localwin, y+5 , x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+6 , x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+7 , x, "|  Chance    | Vous additionnez la valeur de chaque dé et     |"); 
	mvwprintw(localwin, y+8 , x, "|            | l'écrivez dans la case.                        |"); 
	mvwprintw(localwin, y+9 , x, "|            |                                                |");
	mvwprintw(localwin, y+10, x, "+------------+------------------------------------------------+");
	mvwprintw(localwin, y+11, x, "+-------------------------------------------------------------+");
	mvwprintw(localwin, y+12, x, "| Attention ! Plusieurs résultats peuvent correspondre à      |");
	mvwprintw(localwin, y+13, x, "| plusieurs catégories mais vous ne pouvez remplir une case   |");
	mvwprintw(localwin, y+14, x, "| qu'une seule fois, soyez stratégiques !                     |");
	mvwprintw(localwin, y+15, x, "+-------------------------------------------------------------+");
	mvwprintw(localwin, y+16, x, "+-------------------------------------------------------------+");
	mvwprintw(localwin, y+17, x, "| 1994 Hasbro International lnc. Tous droits réservés.        |");
	mvwprintw(localwin, y+18, x, "+-------------------------------------------------------------+");
		



}

void Regles(){

	int choix;
	int x = 2;
	int y = 2;
	
	do
/* Affichage du menu et saisie du choix */
	{	
		mvwprintw(localwin, y  , x,  "\nVoici les rêgles du Jeu\n");
		mvwprintw(localwin, y+1, x,  " 1) Consulter la page 1\n");
		mvwprintw(localwin, y+2, x,  " 2) Consulter la page 2\n");
		mvwprintw(localwin, y+3, x,  " 3) Consulter la page 3\n");
		mvwprintw(localwin, y+4, x,  " 4) Quitter le menu des rêgles\n");
		mvwprintw(localwin, y+5, x,  " Votre choix : ");
		scanf("%i",&choix);

/* Traitement du choix de l'utilisateur */
		switch(choix)
		{	case 1: mvwprintw(localwin, y  , x, ReglesPage1(); break;
			case 2: mvwprintw(localwin, y  , x, ReglesPage2(); break;
			case 3: mvwprintw(localwin, y  , x, ReglesPage3(); break;
			case 4: break;
			default: mvwprintw(localwin, y  , x, "Erreur: votre choix doit etre compris entre 1 et 3 inclus.\n");
		}
		
	}
	while(joueur != 5);

	mvwprintw(localwin, y  , x, "Vous pouvez consulter les rêgles à tout moment via le menu Aides. Nous vous souhaitons une bonne partie !\n");
	return EXIT_SUCCESS;
}
	                                
	
	
	
	
	wrefresh(localwin);





}
