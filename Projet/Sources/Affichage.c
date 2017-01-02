#include "../include/Global.h"

/**
* \file Affichage.c
* \brief Fonctions graphiques, gèrent les éléments statiques 
* \author Benoit Combasteix, Simon Fernandes et Nathan OUALET
* \version 1.0
*/


void EcranTitre()
/* \fn EcranTitre()
* \brief Affiche le titre du jeu 
*/
{
	WINDOW * ZoneTitre;
	ZoneTitre = newwin(LINES,COLS, 1, 1); /**< Crée une fenetre ncurses de la taille de la fenetre du terminal */
	mvwprintw(ZoneTitre, (LINES-11)/2-5, (COLS-140)/2, " .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------. ");
	mvwprintw(ZoneTitre, (LINES-11)/2-4, (COLS-140)/2, "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |");
	mvwprintw(ZoneTitre, (LINES-11)/2-3, (COLS-140)/2, "| |  ____  ____  | || |      __      | || |  ____  ____  | || |  _________   | || |   ________   | || |  _________   | || |  _________   | |");
	mvwprintw(ZoneTitre, (LINES-11)/2-2, (COLS-140)/2, "| | |_  _||_  _| | || |     /  \\     | || | |_   ||   _| | || | |  _   _  |  | || |  |  __   _|  | || | |_   ___  |  | || | |_   ___  |  | |");
	mvwprintw(ZoneTitre, (LINES-11)/2-1, (COLS-140)/2, "| |   \\ \\  / /   | || |    / /\\ \\    | || |   | |__| |   | || | |_/ | | \\_|  | || |  |_/  / /    | || |   | |_  \\_|  | || |   | |_  \\_|  | |");
	mvwprintw(ZoneTitre, (LINES-11)/2, (COLS-140)/2,   "| |    \\ \\/ /    | || |   / ____ \\   | || |   |  __  |   | || |     | |      | || |     .'.' _   | || |   |  _|  _   | || |   |  _|  _   | |");
	mvwprintw(ZoneTitre, (LINES-11)/2+1, (COLS-140)/2, "| |    _|  |_    | || | _/ /    \\ \\_ | || |  _| |  | |_  | || |    _| |_     | || |   _/ /__/ |  | || |  _| |___/ |  | || |  _| |___/ |  | |");
	mvwprintw(ZoneTitre,(LINES-11)/2+2, (COLS-140)/2,  "| |   |______|   | || ||____|  |____|| || | |____||____| | || |   |_____|    | || |  |________|  | || | |_________|  | || | |_________|  | |");
	mvwprintw(ZoneTitre,(LINES-11)/2+3, (COLS-140)/2,  "| |              | || |              | || |              | || |              | || |              | || |              | || |              | |");
	mvwprintw(ZoneTitre,(LINES-11)/2+4, (COLS-140)/2,  "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |");
	mvwprintw(ZoneTitre, (LINES-11)/2+5, (COLS-140)/2, " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' ");
	
	mvwprintw(ZoneTitre, (LINES-11)/2+12, (COLS-23)/2, "Appuyez sur une touche !");
	wrefresh(ZoneTitre);	
	wgetch(ZoneTitre);
	DetruireFenetre(ZoneTitre); /**< Supprime la fentre et libère la mémoire */

}


void FicheDeScore(WINDOW *Fenetre, int y, int x)
/* \fn FicheDeScore()
* \brief Génère les fenetres nécéssaires au déroulement de la fonction Partie() 
* \param Fenetre Pointeur de type WINDOW de ncurses, doit être initialisé et non NULL
*/
{
	mvwprintw(Fenetre, y+1, x,  " PARTIE HAUTE    %s", Pseudos);
	mvwprintw(Fenetre, y+2, x,  "+---+-----------+----------+---------+---------+---------+");
	mvwprintw(Fenetre, y+3, x,  "|   |     1     |          |         |         |         |");
	mvwprintw(Fenetre, y+4, x,  "|   |     2     |          |         |         |         |");                                              
	mvwprintw(Fenetre, y+5, x,  "|   |     3     |          |         |         |         |");                                              
	mvwprintw(Fenetre, y+6, x,  "|   |     4     |          |         |         |         |");                                             
	mvwprintw(Fenetre, y+7, x,  "|   |     5     |          |         |         |         |");                                               
	mvwprintw(Fenetre, y+8, x,  "|   |     6     |          |         |         |         |");                                                 
	mvwprintw(Fenetre, y+9, x,  "+---+-----------+----------+---------+---------+---------+");
	mvwprintw(Fenetre, y+10, x, "|PARTIE BASSE    %s|", Pseudos);
	mvwprintw(Fenetre, y+11, x, "+---+-----------+----------+---------+---------+---------+");
	mvwprintw(Fenetre, y+12, x, "|   | BRELAN    |          |         |         |         |");                                              
	mvwprintw(Fenetre, y+13, x, "|   | CARRE     |          |         |         |         |");                                               
	mvwprintw(Fenetre, y+14, x, "|   | FULL      |          |         |         |         |");                                           
	mvwprintw(Fenetre, y+15, x, "|   | PT SUITE  |          |         |         |         |");                                                
	mvwprintw(Fenetre, y+16, x, "|   | GD SUITE  |          |         |         |         |");                                               
	mvwprintw(Fenetre, y+17, x, "|   | YAHTZEE   |          |         |         |         |");                                               
	mvwprintw(Fenetre, y+18, x, "|   | CHANCE    |          |         |         |         |");                                            
	mvwprintw(Fenetre, y+19, x, "+---+-----------+----------+---------+---------+---------+");
	wrefresh(Fenetre);
}

void DeUn(int y, int x)
{
/* \fn DeUn()
* \brief Dessine un dé de valeur 1  
* \param Fenetre Pointeur de type WINDOW de ncurses, doit être initialisé et non NULL
* \param y Première ligne de l'affichage
* \param x Première colonne de l'affichage
*/ 
	mvwprintw(ZoneDe, y, x,   " +-------+");
	mvwprintw(ZoneDe, y+1, x, " |       |");
	mvwprintw(ZoneDe, y+2, x, " |   O   | [   ]");
	mvwprintw(ZoneDe, y+3, x, " |       |");
	mvwprintw(ZoneDe, y+4, x, " +-------+");
}
						
void DeDeux(int y, int x)
{
/* \fn DeDeux()
* \brief Dessine un de de valeur 2  
* \param Fenetre Pointeur de type WINDOW de ncurses, doit être initialisé et non NULL
* \param y Première ligne de l'affichage
* \param x Première colonne de l'affichage
*/
	mvwprintw(ZoneDe, y, x,   " +-------+");
	mvwprintw(ZoneDe, y+1, x, " | O     |");
	mvwprintw(ZoneDe, y+2, x, " |       | [   ]");
	mvwprintw(ZoneDe, y+3, x, " |     O |");
	mvwprintw(ZoneDe, y+4, x, " +-------+");
}
					
void DeTrois(int y, int x)
{
/* \fn DeTrois()
* \brief Dessine un de de valeur 3  
* \param Fenetre Pointeur de type WINDOW de ncurses, doit être initialisé et non NULL
* \param y Première ligne de l'affichage
* \param x Première colonne de l'affichage
*/ 
	mvwprintw(ZoneDe, y, x, " +-------+");
	mvwprintw(ZoneDe, y+1, x, " | O     |");
	mvwprintw(ZoneDe, y+2, x, " |   O   | [   ]");
	mvwprintw(ZoneDe, y+3, x, " |     O |");
	mvwprintw(ZoneDe, y+4, x, " +-------+");
}
					
void DeQuatre(int y, int x)
{
/* \fn DeQuatre()
* \brief Dessine un de de valeur 4  
* \param Fenetre Pointeur de type WINDOW de ncurses, doit être initialisé et non NULL
* \param y Première ligne de l'affichage
* \param x Première colonne de l'affichage
*/ 
	mvwprintw(ZoneDe, y, x,   " +-------+");
	mvwprintw(ZoneDe, y+1, x, " | O   O |");
	mvwprintw(ZoneDe, y+2, x, " |       | [   ]");
	mvwprintw(ZoneDe, y+3, x, " | O   O |");
	mvwprintw(ZoneDe, y+4, x, " +-------+");
}	
				
void DeCinq(int y, int x)
{
/* \fn DeCinq()
* \brief Dessine un de de valeur 5  
* \param Fenetre Pointeur de type WINDOW de ncurses, doit être initialisé et non NULL
* \param y Première ligne de l'affichage
* \param x Première colonne de l'affichage
*/ 
	mvwprintw(ZoneDe, y, x,   " +-------+");
	mvwprintw(ZoneDe, y+1, x, " | O   O |");
	mvwprintw(ZoneDe, y+2, x, " |   O   | [   ]");
	mvwprintw(ZoneDe, y+3, x, " | O   O |");
	mvwprintw(ZoneDe, y+4, x, " +-------+");
}
					
void DeSix(int y, int x)
{
/* \fn DeSix()
* \brief Dessine un de de valeur 6  
* \param Fenetre Pointeur de type WINDOW de ncurses, doit être initialisé et non NULL
* \param y Première ligne de l'affichage
* \param x Première colonne de l'affichage
*/ 
	mvwprintw(ZoneDe, y, x,   " +-------+");
	mvwprintw(ZoneDe, y+1, x, " | O   O |");
	mvwprintw(ZoneDe, y+2, x, " | O   O | [   ]");
	mvwprintw(ZoneDe, y+3, x, " | O   O |");
	mvwprintw(ZoneDe, y+4, x, " +-------+");
}

void DeVide(int y, int x)
/* \fn DeVide()
* \brief Dessine un de si on a pas encore de valeur 
* \param Fenetre Pointeur de type WINDOW de ncurses, doit être initialisé et non NULL
* \param y Première ligne de l'affichage
* \param x Première colonne de l'affichage
*/
{
	mvwprintw(ZoneDe, y, x,   " +-------+");
	mvwprintw(ZoneDe, y+1, x, " |       |");
	mvwprintw(ZoneDe, y+2, x, " |   ?   | [   ]");
	mvwprintw(ZoneDe, y+3, x, " |       |");
	mvwprintw(ZoneDe, y+4, x, " +-------+");
}

void AffichageDe(int De[5])
/* \fn DeDeux()
* \brief Choisit quel de afficher et dessine les cinq obtenus après un lancer 
*/
{
	int i;
	int x = 1;
	int y = 3;
	for(i = 0 ; i < 5 ; i++)
	{
		switch(De[i])
		{
			case 0 : DeVide(ZoneDe, y, x); break;
			case 1 : DeUn(ZoneDe, y, x); break;
			case 2 : DeDeux(ZoneDe, y, x); break;
			case 3 : DeTrois(ZoneDe, y, x); break;
			case 4 : DeQuatre(ZoneDe, y, x); break;
			case 5 : DeCinq(ZoneDe, y, x); break;
			case 6 : DeSix(ZoneDe, y, x); break;
		}
		y+=5;
	}
}

void ChargementAffichage()
/* \fn ChargementAffichage()
* \brief Met à jour l'affichage du tableau des scores
*        Ne fait rien si la partie n'a pas été chargée à partir d'un fichier 
*/
{
	int i;
	int j;
	int x, y;	
	for (i = 0 ; i < NbJoueurs ; i++)
	{
		for ( j = 0 ; j < 13 ; j ++)
		{
			if(j < 6)
				y = j + 5;
			else
				y = j + 8;
			x = 24 + 10 * i;
			if (Score[i][j] != -1)
				mvwprintw(ZoneScore, y, x, "%i", Score[i][j]);		
		}

	}
	wrefresh(ZoneScore);
}
