#include "../lib/Global.h"


void EcranTitre()
{
	WINDOW * ZoneTitre;
	ZoneTitre = newwin(LINES,COLS, 1, 1);
	mvwprintw(ZoneTitre, (LINES-11)/2-5, (COLS-140)/2, " .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------.  .----------------. ");
	mvwprintw(ZoneTitre, (LINES-11)/2-4, (COLS-140)/2, "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |");
	mvwprintw(ZoneTitre, (LINES-11)/2-3, (COLS-140)/2, "| |  ____  ____  | || |      __      | || |  ____  ____  | || |  _________   | || |   ________   | || |  _________   | || |  _________   | |");
	mvwprintw(ZoneTitre, (LINES-11)/2-2, (COLS-140)/2, "| | |_  _||_  _| | || |     /  \\     | || | |_   ||   _| | || | |  _   _  |  | || |  |  __   _|  | || | |_   ___  |  | || | |_   ___  |  | |");
	mvwprintw(ZoneTitre, (LINES-11)/2-1, (COLS-140)/2, "| |   \\ \\  / /   | || |    / /\\ \\    | || |   | |__| |   | || | |_/ | | \\_|  | || |  |_/  / /    | || |   | |_  \\_|  | || |   | |_  \\_|  | |");
	mvwprintw(ZoneTitre, (LINES-11)/2, (COLS-140)/2, "| |    \\ \\/ /    | || |   / ____ \\   | || |   |  __  |   | || |     | |      | || |     .'.' _   | || |   |  _|  _   | || |   |  _|  _   | |");
	mvwprintw(ZoneTitre, (LINES-11)/2+1, (COLS-140)/2, "| |    _|  |_    | || | _/ /    \\ \\_ | || |  _| |  | |_  | || |    _| |_     | || |   _/ /__/ |  | || |  _| |___/ |  | || |  _| |___/ |  | |");
	mvwprintw(ZoneTitre,(LINES-11)/2+2, (COLS-140)/2, "| |   |______|   | || ||____|  |____|| || | |____||____| | || |   |_____|    | || |  |________|  | || | |_________|  | || | |_________|  | |");
	mvwprintw(ZoneTitre,(LINES-11)/2+3, (COLS-140)/2, "| |              | || |              | || |              | || |              | || |              | || |              | || |              | |");
	mvwprintw(ZoneTitre,(LINES-11)/2+4, (COLS-140)/2, "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |");
	mvwprintw(ZoneTitre, (LINES-11)/2+5, (COLS-140)/2, " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' ");
	
	mvwprintw(ZoneTitre, (LINES-11)/2+12, (COLS-23)/2, "Appuyez sur une touche !");
	wrefresh(ZoneTitre);	
	wgetch(ZoneTitre);
	DetruireFenetre(ZoneTitre);

}


void MiseEnPlace()
{	
	refresh();
	ChainePseudo(Pseudos);
	ZoneAide = CreerFenetre(30,30,(LINES-35)/2,(COLS+70)/2);
	ZoneDe = CreerFenetre(31, 19, (LINES-35)/2, (COLS-70)/2-19);
	ZoneScore = CreerFenetre(25,70,(LINES-35)/2,(COLS-70)/2);
	ZoneMessage = CreerFenetre(10,70,(LINES+15)/2,(COLS-70)/2);
	FicheDeScore(ZoneScore,2,2);
	AffichageDe(De, ZoneDe);
}


void FicheDeScore(WINDOW *Fenetre, int y, int x)
/* Affiche le squelette de la fiche de score */
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

void DeUn(WINDOW *Fenetre, int y, int x)
{
/* Dessine un de de valeur 1 */ 
	mvwprintw(Fenetre, y, x,   " +-------+"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+1, x, " |       |"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+2, x, " |   O   | [   ]"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+3, x, " |       |"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+4, x, " +-------+"); wrefresh(Fenetre);
	wrefresh(Fenetre);
}
						
void DeDeux(WINDOW *Fenetre, int y, int x)
{
/* Dessine un de de valeur 2 */ 
	mvwprintw(Fenetre, y, x,   " +-------+"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+1, x, " | O     |"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+2, x, " |       | [   ]"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+3, x, " |     O |"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+4, x, " +-------+"); wrefresh(Fenetre);
}
					
void DeTrois(WINDOW *Fenetre, int y, int x)
{
/* Dessine un de de valeur 3 */ 
	mvwprintw(Fenetre, y, x, " +-------+"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+1, x, " | O     |"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+2, x, " |   O   | [   ]"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+3, x, " |     O |"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+4, x, " +-------+"); wrefresh(Fenetre);
}
					
void DeQuatre(WINDOW *Fenetre, int y, int x)
{
/* Dessine un de de valeur 4 */ 
	mvwprintw(Fenetre, y, x,   " +-------+");
	mvwprintw(Fenetre, y+1, x, " | O   O |"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+2, x, " |       | [   ]"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+3, x, " | O   O |"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+4, x, " +-------+"); wrefresh(Fenetre);
}	
				
void DeCinq(WINDOW *Fenetre, int y, int x)
{
/* Dessine un de de valeur 5 */ 
	mvwprintw(Fenetre, y, x,   " +-------+"); wrefresh(Fenetre); 
	mvwprintw(Fenetre, y+1, x, " | O   O |"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+2, x, " |   O   | [   ]"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+3, x, " | O   O |"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+4, x, " +-------+"); wrefresh(Fenetre);
}
					
void DeSix(WINDOW *Fenetre, int y, int x)
{
/* Dessine un de de valeur 6 */ 
	mvwprintw(Fenetre, y, x,   " +-------+"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+1, x, " | O   O |"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+2, x, " | O   O | [   ]"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+3, x, " | O   O |"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+4, x, " +-------+"); wrefresh(Fenetre);
}

void DeVide(WINDOW *Fenetre, int y, int x)
/* Dessine un de si on a pas encore de valeur */
{
	mvwprintw(Fenetre, y, x,   " +-------+"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+1, x, " |       |"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+2, x, " |   ?   | [   ]"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+3, x, " |       |"); wrefresh(Fenetre);
	mvwprintw(Fenetre, y+4, x, " +-------+"); wrefresh(Fenetre);
	wrefresh(Fenetre);
}

void AffichageDe(int De[5], WINDOW *Fenetre)
/* Choisit quel de afficher et dessine les cinq obtenus après un lancer*/
{
	int i;
	int x = 1;
	int y = 3;
	for(i = 0 ; i < 5 ; i++)
	{
		switch(De[i])
		{
			case 0 : DeVide(Fenetre, y, x); break;
			case 1 : DeUn(Fenetre, y, x); break;
			case 2 : DeDeux(Fenetre, y, x); break;
			case 3 : DeTrois(Fenetre, y, x); break;
			case 4 : DeQuatre(Fenetre, y, x); break;
			case 5 : DeCinq(Fenetre, y, x); break;
			case 6 : DeSix(Fenetre, y, x); break;
		}
		y+=5;
	}
}

