#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int De[5]={0};                                  /* Tableau de dés */
int Garde[5]={0};                               /* Tableau booléen, sert à savoir si on garde les dés ou si on les relance */
int Occurence[6]={0};                           /* Tableau content le nombre d'occurence de chaque valeur de dé */
char pseudo_j1[10] = "J1";                      /* Pseudo du joueur 1 */
char pseudo_j2[10] = "J2";                      /* Pseudo du joueur 2 */
char pseudo_j3[10] = "J3";                      /* Pseudo du joueur 3 */
char pseudo_j4[10] = "J4";                      /* Pseudo du joueur 4 */
char pseudos[40];                               /* Chaine de caractère contenant les pseudos des 4 joueurs avec le nombre d'espace nécesaire à un affichage correct */



int Categorie;                                   /* Permet de savoir quelle catégorie a été sélectionnée pour calculer le score */
WINDOW *ZoneTitre;                               /* Sous fenetre pour l'affichage de YAHTZEE ! */
WINDOW *ZoneMenu;                                /* Sous fenetre pour l'affichage des menus */
WINDOW *ZoneDe;                                  /* Sous fenetre pour l'affichage de la valeur de dés */
WINDOW *ZoneMessage;                             /* Sous fenetre pour l'affichage des messages à l'utilisateur pendant la partie */
WINDOW *ZoneAide;                                /* Sous fenetre pour l'affichage de l'aide au jeu */
WINDOW *ZoneScore;				                 /* Sous fenetre pour l'affichage de la fiche de score */


/* Menu */

void Debut();                                     /* Premier menu, permet de commencer une partie, afficher les règles ou quitter */
void Partie();                                    /* Commence une partie de Yahtzee */
void Regles();                                    /* Affiche les règles */       

/* Initialisation de la partie */


void EntrerPseudo();                                   /* Demande les pseudos des joueurs */
void MiseEnPlace();                                    /* Crée les fenêtres utilisées pour jouer */
void FicheDeScore();								   /* Affiche la fiche de score dans la fenêtre */

/* Fonctions de jeu */

void LancerDe();                                 /* Simule 5 lancers de dés et entre les résultats dans le tableau */
void CalculOccurence();                          /* Entre l'occurence de chaque valeur dans le tableau */
void Garder();                                   /* Permet au joueur de conserver de dés avant de relancer */
int isBrelan();									 /* Fonctions booléennes vérifiant les résultats */
int isCarre();									 /* --- */
int isFull();                                    /* --- */
int isPtSuite();                                 /* --- */
int isGdSuite();                                 /* --- */
int isYahtzee();                                 /* --- */
void ChoixCategorie(int *Categorie);             /* Permet de choisir la catégorie avec les flèches */
void CalculScore();                              /* Calcul le score pour la catégorie choisie */
void EcrireScore();                              /* Ecrie le score sur la ligne et dans la colonne correspondant au joueur */



WINDOW *CreerFenetre(int height, int width, int starty, int startx)
{	WINDOW *localwin;

	localwin = newwin(height, width, starty, startx);
	wborder(localwin, '|', '|', '-', '-', '+', '+', '+', '+');		
	wrefresh(localwin);	

	return localwin;
}



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




void DeUn(WINDOW *localwin, int y, int x){
/* Dessine un de de valeur 1 */ 
	mvwprintw(localwin, y, x, " +-------+");
	mvwprintw(localwin, y+1, x, " |       |");
	mvwprintw(localwin, y+2, x, " |   O   | [   ]");
	mvwprintw(localwin, y+3, x, " |       |");
	mvwprintw(localwin, y+4, x, " +-------+"); 
	wrefresh(localwin);
}
						
void DeDeux(WINDOW *localwin, int y, int x){
/* Dessine un de de valeur 2 */ 
	mvwprintw(localwin, y, x, " +-------+");
	mvwprintw(localwin, y+1, x, " | O     |");
	mvwprintw(localwin, y+2, x, " |       | [   ]");
	mvwprintw(localwin, y+3, x, " |     O |");
	mvwprintw(localwin, y+4, x, " +-------+"); 
	wrefresh(localwin);
}
					
void DeTrois(WINDOW *localwin, int y, int x){
/* Dessine un de de valeur 3 */ 
	mvwprintw(localwin, y, x, " +-------+");
	mvwprintw(localwin, y+1, x, " | O     |");
	mvwprintw(localwin, y+2, x, " |   O   | [   ]");
	mvwprintw(localwin, y+3, x, " |     O |");
	mvwprintw(localwin, y+4, x, " +-------+");
	wrefresh(localwin);
}
					
void DeQuatre(WINDOW *localwin, int y, int x){
/* Dessine un de de valeur 4 */ 
	mvwprintw(localwin, y, x, " +-------+");
	mvwprintw(localwin, y+1, x, " | O   O |");
	mvwprintw(localwin, y+2, x, " |       | [   ]");
	mvwprintw(localwin, y+3, x, " | O   O |");
	mvwprintw(localwin, y+4, x, " +-------+"); 
	wrefresh(localwin);
}					
void DeCinq(WINDOW *localwin, int y, int x){
/* Dessine un de de valeur 5 */ 
	mvwprintw(localwin, y, x, " +-------+");
	mvwprintw(localwin, y+1, x, " | O   O |");
	mvwprintw(localwin, y+2, x, " |   O   | [   ]");
	mvwprintw(localwin, y+3, x, " | O   O |");
	mvwprintw(localwin, y+4, x, " +-------+"); 
	wrefresh(localwin);
}
					
void DeSix(WINDOW *localwin, int y, int x){
/* Dessine un de de valeur 6 */ 
	mvwprintw(localwin, y, x, " +-------+");
	mvwprintw(localwin, y+1, x, " | O   O |");
	mvwprintw(localwin, y+2, x, " | O   O | [   ]");
	mvwprintw(localwin, y+3, x, " | O   O |");
	mvwprintw(localwin, y+4, x, " +-------+"); 
	wrefresh(localwin);
}

void DeVide(WINDOW *localwin, int y, int x)
/* Dessine un de si on a pas encore de valeur */
{
	mvwprintw(localwin, y, x, " +-------+");
	mvwprintw(localwin, y+1, x, " |       |");
	mvwprintw(localwin, y+2, x, " |   ?   | [   ]");
	mvwprintw(localwin, y+3, x, " |       |");
	mvwprintw(localwin, y+4, x, " +-------+");
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
			case 0 : DeVide(localwin, y, x); break;
			case 1 : DeUn(localwin, y, x); break;
			case 2 : DeDeux(localwin, y, x); break;
			case 3 : DeTrois(localwin, y, x); break;
			case 4 : DeQuatre(localwin, y, x); break;
			case 5 : DeCinq(localwin, y, x); break;
			case 6 : DeSix(localwin, y, x); break;
		}
		y+=5;
	}
}


void InterfaceJeu()
{	
	initscr();
	cbreak();
	noecho();
	refresh();
	ChainePseudo(pseudos);
	ZoneAide = CreerFenetre(31,30,3,(COLS-70)/2+70);
	ZoneDe = CreerFenetre(31, 19, 3, (COLS-70)/2-19);
	ZoneScore = CreerFenetre(25,70,3, (COLS-70)/2);
	ZoneMessage = CreerFenetre(10,70,28,(COLS-70)/2);
	FicheDeScore(ZoneScore,1,6);
	AffichageDe(De, ZoneDe);
	wmove(ZoneDe, 100, 67); /* Sort le curseur de la fenetre, purement cosmétique */
	wrefresh(ZoneDe);
}


int main ()
{
	int ch = 68;
	InterfaceJeu();
	//AffichageDe(De, ZoneDe);
	while (ch != 10)
		ch = getch();
	De[3] = 6;
	AffichageDe(De, ZoneDe);
	ch = 68;
	while (ch != 10)
		ch = getch();
	endwin();
}
