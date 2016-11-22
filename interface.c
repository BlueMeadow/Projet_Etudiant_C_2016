

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int De[5]={1,2,3,4,5};
int Garde[5]={0};
char pseudo_j1[30] = "J1";
char pseudo_j2[30] = "J2;
char pseudo_j3[30] = "J3";
char pseudo_j4[30] = "J4";
int Categorie;
WINDOW *ZoneDe;
WINDOW *ZoneMessage;
WINDOW *ZoneAide;
WINDOW *ZoneScore;
char pseudos[50];


/*

|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

*/



WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *localwin;

	localwin = newwin(height, width, starty, startx);
	wborder(localwin, '|', '|', '-', '-', '+', '+', '+', '+');		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(localwin);		/* Show that box 		*/

	return localwin;
}




WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

void ChainePseudo (char pseudos[50])
{
	int i, esp1, esp2, esp3, esp4;
	esp1 = 10-strlen(pseudo_j1);
	esp2 = 10-strlen(pseudo_j2);
	esp3 = 10-strlen(pseudo_j3);
	esp4 = 10-strlen(pseudo_j4);
	strcat(pseudos, pseudo_j1);
	for(i = 0 ; i <= esp1 ; i++) strcat(pseudos, " ");
	strcat(pseudos, pseudo_j2);
	for(i = 0 ; i < esp2 ; i++) strcat(pseudos, " ");
	strcat(pseudos, pseudo_j3);
	for(i = 0 ; i < esp3 ; i++) strcat(pseudos, " ");
	strcat(pseudos, pseudo_j4);
	for(i = 0 ; i < esp4-1 ; i++) strcat(pseudos, " ");
	
		
}

void FicheDeScore(WINDOW *localwin, int y, int x)
/* Affiche le squelette de la fiche de score */
{
	mvwprintw(localwin, y+1, x,  " PARTIE HAUTE    %s", pseudos);
	mvwprintw(localwin, y+2, x,  "+---+-----------+----------+---------+---------+---------+");
	mvwprintw(localwin, y+3, x,  "|   |     1     |          |         |         |         |");
	mvwprintw(localwin, y+4, x,  "|   |     2     |          |         |         |         |");                                              
	mvwprintw(localwin, y+5, x,  "|   |     3     |          |         |         |         |");                                              
	mvwprintw(localwin, y+6, x,  "|   |     4     |          |         |         |         |");                                             
	mvwprintw(localwin, y+7, x,  "|   |     5     |          |         |         |         |");                                               
	mvwprintw(localwin, y+8, x,  "|   |     6     |          |         |         |         |");                                                 
	mvwprintw(localwin, y+9, x,  "+---+-----------+----------+---------+---------+---------+");
	mvwprintw(localwin, y+10, x, "|PARTIE BASSE    %s|", pseudos);
	mvwprintw(localwin, y+11, x, "+---+-----------+----------+---------+---------+---------+");
	mvwprintw(localwin, y+12, x, "|   | BRELAN    |          |         |         |         |");                                              
	mvwprintw(localwin, y+13, x, "|   | CARRE     |          |         |         |         |");                                               
	mvwprintw(localwin, y+14, x, "|   | FULL      |          |         |         |         |");                                           
	mvwprintw(localwin, y+15, x, "|   | PT SUITE  |          |         |         |         |");                                                
	mvwprintw(localwin, y+16, x, "|   | GD SUITE  |          |         |         |         |");                                               
	mvwprintw(localwin, y+17, x, "|   | YAHTZEE   |          |         |         |         |");                                               
	mvwprintw(localwin, y+18, x, "|   | CHANCE    |          |         |         |         |");                                            
	mvwprintw(localwin, y+19, x, "+---+-----------+----------+---------+---------+---------+");
	wrefresh(localwin);
}




void de_un(WINDOW *localwin, int y, int x){
/* Dessine un de de valeur 1 */ 
	mvwprintw(localwin, y, x, " +-------+"); wrefresh(localwin);
	mvwprintw(localwin, y+1, x, " |       |"); wrefresh(localwin);
	mvwprintw(localwin, y+2, x, " |   O   | [   ]"); wrefresh(localwin);
	mvwprintw(localwin, y+3, x, " |       |"); wrefresh(localwin);
	mvwprintw(localwin, y+4, x, " +-------+"); wrefresh(localwin);
	wrefresh(localwin);
}
						
void de_deux(WINDOW *localwin, int y, int x){
/* Dessine un de de valeur 2 */ 
	mvwprintw(localwin, y, x, " +-------+"); wrefresh(localwin);
	mvwprintw(localwin, y+1, x, " | O     |"); wrefresh(localwin);
	mvwprintw(localwin, y+2, x, " |       | [   ]"); wrefresh(localwin);
	mvwprintw(localwin, y+3, x, " |     O |"); wrefresh(localwin);
	mvwprintw(localwin, y+4, x, " +-------+"); wrefresh(localwin);
}
					
void de_trois(WINDOW *localwin, int y, int x){
/* Dessine un de de valeur 3 */ 
	mvwprintw(localwin, y, x, " +-------+"); wrefresh(localwin);
	mvwprintw(localwin, y+1, x, " | O     |"); wrefresh(localwin);
	mvwprintw(localwin, y+2, x, " |   O   | [   ]"); wrefresh(localwin);
	mvwprintw(localwin, y+3, x, " |     O |"); wrefresh(localwin);
	mvwprintw(localwin, y+4, x, " +-------+"); wrefresh(localwin);
}
					
void de_quatre(WINDOW *localwin, int y, int x){
/* Dessine un de de valeur 4 */ 
	mvwprintw(localwin, y, x, " +-------+");
	mvwprintw(localwin, y+1, x, " | O   O |"); wrefresh(localwin);
	mvwprintw(localwin, y+2, x, " |       | [   ]"); wrefresh(localwin);
	mvwprintw(localwin, y+3, x, " | O   O |"); wrefresh(localwin);
	mvwprintw(localwin, y+4, x, " +-------+"); wrefresh(localwin);
}					
void de_cinq(WINDOW *localwin, int y, int x){
/* Dessine un de de valeur 5 */ 
	mvwprintw(localwin, y, x, " +-------+"); wrefresh(localwin); 
	mvwprintw(localwin, y+1, x, " | O   O |"); wrefresh(localwin);
	mvwprintw(localwin, y+2, x, " |   O   | [   ]"); wrefresh(localwin);
	mvwprintw(localwin, y+3, x, " | O   O |"); wrefresh(localwin);
	mvwprintw(localwin, y+4, x, " +-------+"); wrefresh(localwin);
}
					
void de_six(WINDOW *localwin, int y, int x){
/* Dessine un de de valeur 6 */ 
	mvwprintw(localwin, y, x, " +-------+"); wrefresh(localwin);
	mvwprintw(localwin, y+1, x, " | O   O |"); wrefresh(localwin);
	mvwprintw(localwin, y+2, x, " | O   O | [   ]"); wrefresh(localwin);
	mvwprintw(localwin, y+3, x, " | O   O |"); wrefresh(localwin);
	mvwprintw(localwin, y+4, x, " +-------+"); wrefresh(localwin);
}

void de_vide(WINDOW *localwin, int y, int x)
/* Dessine un de si on a pas encore de valeur */
{
mvwprintw(localwin, y, x, " +-------+"); wrefresh(localwin);
	mvwprintw(localwin, y+1, x, " |       |"); wrefresh(localwin);
	mvwprintw(localwin, y+2, x, " |   ?   | [   ]"); wrefresh(localwin);
	mvwprintw(localwin, y+3, x, " |       |"); wrefresh(localwin);
	mvwprintw(localwin, y+4, x, " +-------+"); wrefresh(localwin);
	wrefresh(localwin);
}

void AffichageDe(int De[5], WINDOW *localwin)
/* Choisit quel de afficher et dessine les cinq obtenus après un lancer*/
{
	int x = 1;
	int y = 3;
	for(int i = 0 ; i < 5 ; i++)
	{
		switch(De[i])
		{
			case 0 : de_vide(localwin, y, x); break;
			case 1 : de_un(localwin, y, x); break;
			case 2 : de_deux(localwin, y, x); break;
			case 3 : de_trois(localwin, y, x); break;
			case 4 : de_quatre(localwin, y, x); break;
			case 5 : de_cinq(localwin, y, x); break;
			case 6 : de_six(localwin, y, x); break;
		}
		y+=5;
	}
}


void MiseEnPlace()
{	
	initscr();
	cbreak();
	noecho();
	refresh();
	ChainePseudo(pseudos);
	ZoneAide = create_newwin(30,30,3,92);
	ZoneDe = create_newwin(31, 19, 3, 3);
	ZoneScore = create_newwin(25,70,3,22);
	ZoneMessage = create_newwin(10,70,28,22);
	FicheDeScore(ZoneScore,1,2);
	AffichageDe(De, ZoneDe);
}


/*int main ()
{
	int ch = 68;
	MiseEnPlace();
	AffichageDe(De, ZoneDe);
	while (ch != 10)
		ch = getch();
	De[3] = 6;
	AffichageDe(De, ZoneDe);
	ch = 68;
	while (ch != 10)
		ch = getch();
	endwin();
}*/
