#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


int tabOccurrences[6]={0}; 
int Score[4][13]={{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}};
int De[5]={0,0,0,0,0};
int Garde[5]={0};
char pseudo_j[4][30];

WINDOW *ZoneDe;
WINDOW *ZoneMessage;
WINDOW *ZoneAide;
WINDOW *ZoneResultat;
WINDOW *ZoneScore;
char pseudos[50];
/*
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

void Garder(WINDOW *localwin, int Garde[5])
{
	int y, x, ch;
	y = 5; //indice d'ordonnée
	x = 14; // indice d'abscisse
	keypad(localwin, TRUE); //Permet l'utilisation des touches directionnelles
	
	wmove(localwin, y, x);
	wrefresh(localwin);
	do 
	{
		ch = wgetch(localwin);
		switch (ch)
		{
			case KEY_UP:  
				if ( y == 5 )
				/* Si on est en haut, on passe en bas */
				{
					y = 25;
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				else 
				/* Sinon on monte d'une case */
				{
					y-=5;
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				break;
			case KEY_DOWN:
				if ( y == 25 )
				/* Si on est en bas, on remonte en haut */
				{
					y = 5;
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				else 
				/* Sinon on descend d'une case */
				{
					y+=5;
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				break;
			case 32: 
				/* La touche espace sert à indiquer si on veut garder le de ou non */
				if ( Garde[y/5-1] == 0 )
				{
					waddch(localwin, 'G');
					Garde[y/5-1] = 1;
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				else
				{
					waddch(localwin, ' ');
					Garde[y/5-1] = 0;
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				break;
		}
	} while ( ch != 10 );	
	/* On valide la selection avec la touche entree */
}
void CalculOccurrences()
{

	//parcourt les 5 dés lancés, on incremente le nombre de valeurs trouvés
	// dans le tableau d'occurrences correspondant à la valeur du dé
	int i;
	for( i = 0; i < 6 ; i++)
		tabOccurrences[i] = 0;

	for( i = 0; i < 5 ; i++){
		
		switch(De[i]){
			case 1: tabOccurrences[0]++; break;
			case 2: tabOccurrences[1]++; break;
			case 3: tabOccurrences[2]++; break;
			case 4: tabOccurrences[3]++; break;
			case 5: tabOccurrences[4]++; break;
			case 6: tabOccurrences[5]++; break;
		}
	}
}
void Lancer()
{
	//initialisation des valeurs aléatoires, à chaque tirage
	srand(time(0));
	int ch;
	mvwprintw(ZoneMessage,2 ,2 ,"                                                                  ");
	mvwprintw(ZoneMessage, 2, 2, "Veuillez appuyer sur [ENTREE] pour lancer les dés.");
	wrefresh(ZoneMessage);
	do
	{
		ch = getch();
	} while (ch != 10);

	for(int i = 0; i < 5; i++){
		if(Garde[i] == 0){	
			//lancement des dés et sélection d'un chiffre entre 1 et 6 avec le hasard
			De[i] = rand()%6+1;
		}
		CalculOccurrences();
		Garde[i]=0;
	}
}

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
	esp1 = 10-strlen(pseudo_j[0]);
	esp2 = 10-strlen(pseudo_j[1]);
	esp3 = 10-strlen(pseudo_j[2]);
	esp4 = 10-strlen(pseudo_j[3]);
	strcat(pseudos, pseudo_j[0]);
	for(i = 0 ; i <= esp1 ; i++) strcat(pseudos, " ");
	strcat(pseudos, pseudo_j[1]);
	for(i = 0 ; i < esp2 ; i++) strcat(pseudos, " ");
	strcat(pseudos, pseudo_j[2]);
	for(i = 0 ; i < esp3 ; i++) strcat(pseudos, " ");
	strcat(pseudos, pseudo_j[3]);
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

void de_un(WINDOW *localwin, int y, int x)
{
/* Dessine un de de valeur 1 */ 
	mvwprintw(localwin, y, x, " +-------+"); wrefresh(localwin);
	mvwprintw(localwin, y+1, x, " |       |"); wrefresh(localwin);
	mvwprintw(localwin, y+2, x, " |   O   | [   ]"); wrefresh(localwin);
	mvwprintw(localwin, y+3, x, " |       |"); wrefresh(localwin);
	mvwprintw(localwin, y+4, x, " +-------+"); wrefresh(localwin);
	wrefresh(localwin);
}
						
void de_deux(WINDOW *localwin, int y, int x)
{
/* Dessine un de de valeur 2 */ 
	mvwprintw(localwin, y, x, " +-------+"); wrefresh(localwin);
	mvwprintw(localwin, y+1, x, " | O     |"); wrefresh(localwin);
	mvwprintw(localwin, y+2, x, " |       | [   ]"); wrefresh(localwin);
	mvwprintw(localwin, y+3, x, " |     O |"); wrefresh(localwin);
	mvwprintw(localwin, y+4, x, " +-------+"); wrefresh(localwin);
}
					
void de_trois(WINDOW *localwin, int y, int x)
{
/* Dessine un de de valeur 3 */ 
	mvwprintw(localwin, y, x, " +-------+"); wrefresh(localwin);
	mvwprintw(localwin, y+1, x, " | O     |"); wrefresh(localwin);
	mvwprintw(localwin, y+2, x, " |   O   | [   ]"); wrefresh(localwin);
	mvwprintw(localwin, y+3, x, " |     O |"); wrefresh(localwin);
	mvwprintw(localwin, y+4, x, " +-------+"); wrefresh(localwin);
}
					
void de_quatre(WINDOW *localwin, int y, int x)
{
/* Dessine un de de valeur 4 */ 
	mvwprintw(localwin, y, x, " +-------+");
	mvwprintw(localwin, y+1, x, " | O   O |"); wrefresh(localwin);
	mvwprintw(localwin, y+2, x, " |       | [   ]"); wrefresh(localwin);
	mvwprintw(localwin, y+3, x, " | O   O |"); wrefresh(localwin);
	mvwprintw(localwin, y+4, x, " +-------+"); wrefresh(localwin);
}	
				
void de_cinq(WINDOW *localwin, int y, int x)
{
/* Dessine un de de valeur 5 */ 
	mvwprintw(localwin, y, x, " +-------+"); wrefresh(localwin); 
	mvwprintw(localwin, y+1, x, " | O   O |"); wrefresh(localwin);
	mvwprintw(localwin, y+2, x, " |   O   | [   ]"); wrefresh(localwin);
	mvwprintw(localwin, y+3, x, " | O   O |"); wrefresh(localwin);
	mvwprintw(localwin, y+4, x, " +-------+"); wrefresh(localwin);
}
					
void de_six(WINDOW *localwin, int y, int x)
{
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
	FicheDeScore(ZoneScore,2,2);
	AffichageDe(De, ZoneDe);
}

void ChoixCategorie (int *Categorie, WINDOW *localwin,int joueur)
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
		if (y < 11) *Categorie = y - 4;
		else *Categorie = y - 7;
		if(Score[joueur][*Categorie-1] != -1){
			mvwprintw(ZoneMessage, 2, 2 ,"                                                                  ");
			mvwprintw(ZoneMessage, 3, 2 ,"                                                                  ");
			mvwprintw(ZoneMessage, 2, 2, "Cette categorie est déja prise.");
			mvwprintw(ZoneMessage, 3, 2, "Choisissez en une autre.");
			wrefresh(ZoneMessage);
			ch = '0';
			wmove(ZoneScore, y, x);
			wrefresh(ZoneScore);		
		}
		else
		{
			mvwprintw(ZoneMessage, 2, 2 ,"                                                                  ");
			mvwprintw(ZoneMessage, 3, 2 ,"                                                                  ");
			wrefresh(ZoneMessage);
			wmove(ZoneScore, y, x);
			wrefresh(ZoneScore);	
		}
			
	} while (ch != 10); 
		/* Entrée valide le choix */
}

int isBrelan()
{
	int i, j, cptvalide = 0;

	int valeuri, valeurj;

	for(i =0; i<5; i++){
		for( j = 4; i<j; j--){
			valeuri = De[i];
			valeurj = De[j];
			
			//s'il trouve trois dés identiques, la condition s'arrete, et retourne le résultat
			if (cptvalide==3) break;

			if (valeuri == valeurj){
				cptvalide++;
			}
		}

	}
	return ( cptvalide == 3);
}

int isCarre()
{
	int i;
	int j;
	
	int total = 0;
	
	for( i = 0; i < 5 ; i++){
		
		for( j=0; j<5; j++){
			
			if(De[i] == De[j] && i != j ){
				//i!=j pour qu'il ne compte pas si les deux sont sur la meme case
				total++;
			}
		}
		if(total > 2){
			return 1;

		}
		total=0;
	}
	return 0;
}

int isFull()
{
	int i, cpt2 = 0, cpt3 = 0;

	for( i = 0 ; i < 6 ; i++)
	{
		if( tabOccurrences[i] == 5 )
			return 1;		
		if( tabOccurrences[i] == 2 )
			cpt2 = 1;
		if( tabOccurrences[i] == 3 )
			cpt3 = 1;
	}
	if (cpt2 == 1 && cpt3 == 1)
		return 1;
	return 0;
}

//Calcul de la petit suite

int isPtSuite()
{
	
	int i;
	int j;

	for(j=0;j<=2;j++){
		if(tabOccurrences[j] > 0 && tabOccurrences[j+1] > 0 && tabOccurrences[j+2] > 0 && tabOccurrences[j+3] > 0)
			return 1;

	}
	return 0;
}

int isGdSuite()
{
	
	int i;
	int j;
	
	for( j=0; j<1; j++){
		if(tabOccurrences[0] == 1){
			//pour trouver si il y a un 1
			if((tabOccurrences[j] > 0) && (tabOccurrences[j+1] > 0) && (tabOccurrences[j+2] > 0) && (tabOccurrences[j+3] > 0) && (tabOccurrences[j+4] > 0)){
				return 1;
			}
		}else{
			if((tabOccurrences[j+1] > 0) && (tabOccurrences[j+2] > 0) && (tabOccurrences[j+3] > 0) && (tabOccurrences[j+4] > 0) && (tabOccurrences[j+5] > 0)){
				//pour trouver si il y a un six
				return 1;
			}
		}
	}
	return 0;
}

int isYahtzee()
{

	//on parcourt la tab Occurrences, si on trouve 5 dans tabOccu, on trouve un Yahtzee donc 5 dés de même valeur.

	for (int i=0; i < 6; i++){
		if ( tabOccurrences[i] == 5){
			return 1;
		}
	}
	return 0;
}

void CalculScore(int joueur, int Categorie)
{
	switch(Categorie){
	/* choix score a utiliser */		
		case 1 :
		case 2 :
		case 3 :
		case 4 :
		case 5 :
		case 6 :
		/* fonction qui calcule le score pour les dés de un a six */
			Score[joueur][Categorie-1] = (Categorie) * tabOccurrences[Categorie-1];
			break;			
		case 7:
			if(isBrelan())
				Score[joueur][Categorie-1] = De[0]+De[1]+De[2]+De[3]+De[4];
			else
				Score[joueur][Categorie-1] = 0;
			break;
			
		case 8:
			if(isCarre())
				Score[joueur][Categorie-1] = De[0]+De[1]+De[2]+De[3]+De[4];
			else
				Score[joueur][Categorie-1] = 0;
			break;
			
		case 9:
			if(isFull())
				Score[joueur][Categorie-1] = 25;
			else
				Score[joueur][Categorie-1] = 0;
			break;
			
		case 10:
			if(isPtSuite())
				Score[joueur][Categorie-1] = 30;
			else
				Score[joueur][Categorie-1] = 0;
			break;
			
		case 11:
			if(isGdSuite())
				Score[joueur][Categorie-1] = 40;
			else
				Score[joueur][Categorie-1] = 0;
			break;
			
		case 12:
			if(isYahtzee())
				Score[joueur][Categorie-1] = 50;
			else
				Score[joueur][Categorie-1] = 0;
			break;
			
		case 13:
			Score[joueur][Categorie-1] = De[0]+De[1]+De[2]+De[3]+De[4];
			break;
	}
}	

void EcrireScore(int joueur)
{
	int categorie;
	int x = 2;
	int y = 2;
	int i;
	int j;
	
	mvwprintw(ZoneMessage ,y ,x ,"Veuillez choisir la categorie");
	wrefresh(ZoneMessage);
	ChoixCategorie(&categorie ,ZoneScore,joueur); 
	CalculScore(joueur, categorie);
	
	/* choix de la colonne */
	x = 24 + 10 * joueur;
	/* choix de la ligne */
	
	

	if(categorie < 7)
		y = categorie + 4;
	else
		y = categorie + 7;
	
	/*affiche le score */
	mvwprintw(ZoneScore ,y ,x ,"%i" ,Score[joueur][categorie-1]);
	wrefresh(ZoneScore);
}
int ChangerJoueur(int joueur, int nb_joueur){
	return ((joueur+1)%nb_joueur);
}

void Aide(int i){//demande d'entrer 1 si on veut l'aide
	int y=2;
	int x=2;
	int temp1=0, temp2=0;
	attron(A_BOLD);
	mvwprintw(ZoneAide, 2, 13, "AIDE");
	attroff(A_BOLD);
	wrefresh(ZoneAide);
	y+=2;
	if( i==1 ){
		if(isBrelan()){
			mvwprintw(ZoneAide, y, x, "Brelan de %i", temp1);
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isCarre()){
			mvwprintw(ZoneAide, y, x, "Carre de %i", temp1);
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isFull()){
			mvwprintw(ZoneAide, y, x, "Full : %i - %i", temp1, temp2);
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isPtSuite()){
			mvwprintw(ZoneAide, y, x, "Petite suite");
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isGdSuite()){
			mvwprintw(ZoneAide, y, x, "Grande suite");
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isYahtzee()){
			mvwprintw(ZoneAide, y, x, "YAHTZEE !");
			wrefresh(ZoneAide);
			y+=2;
		}
	}
	else{
		mvwprintw(ZoneAide, y, x, "L'aide n'est pas activée");
		wrefresh(ZoneAide);
	}
}

void DetruireFenetre(WINDOW * Fenetre)
{
	wclear(Fenetre);
	wrefresh(Fenetre);
	delwin(Fenetre);
}

void Resultat(int nb_joueur)
{	

	
	int Total[nb_joueur];
	int ch;
	char Vainqueur[4][10];
	int i, j;
	int max;
	DetruireFenetre(ZoneMessage);
	DetruireFenetre(ZoneDe);
	DetruireFenetre(ZoneScore);
	DetruireFenetre(ZoneAide);
	ZoneResultat = create_newwin(20,60,(LINES-20)/2, (COLS-60)/2);

	for (i = 0 ; i < nb_joueur ; i++)
	{
		Total[i] = 0;
		for (j = 0 ; j < 6 ; j++)
		{
			Total[i] += Score[i][j];
			
		}
		if (Total[i] > 62) 
		{
			Total[i] += 35;
		}	
		for (j = 6 ; j < 13 ; j++)
		{
			Total[i] += Score[i][j];
		}
	}
	max = Total[0];
	strcpy(Vainqueur[0], pseudo_j[0]);
	j = 0;
	for( i = 1 ; i < 4 ; i++)
	{
		if ( max < Total[i] )
		{
			max = Total[i];
			strcpy(Vainqueur[j], pseudo_j[j]);
		}
		else if ( max == Total[i] )
		{
			j++;
			strcpy(Vainqueur[j], pseudo_j[i]);
		}
	}
	

	wattron(ZoneResultat, A_REVERSE);
	mvwprintw(ZoneResultat, 2, 16, "TABLEAU DE SCORES");
	wattroff(ZoneResultat, A_REVERSE);

	for (i = 0 ; i < nb_joueur ; i++)
	{
		mvwprintw(ZoneResultat, 5+i, 10, "%s : %i", pseudo_j[i], Total[i]);
	}
	
	wattron(ZoneResultat, A_REVERSE);
	mvwprintw(ZoneResultat, 11, 20, "VAINQUEUR");
	wattroff(ZoneResultat, A_REVERSE);

	for (i = 0 ; i <= j ; i++)
	{
		mvwprintw(ZoneResultat, 14+i, (50-strlen(Vainqueur[i]))/2 , "%s", Vainqueur[i] ) ;
	}
	mvwprintw(ZoneResultat, 15+j, 6, "Appuyez sur [ENTREE] pour relancer une partie");
	mvwprintw(ZoneResultat, 16+j, 6, "Appuyez sur [Q] pour quitter");
	do
	{
		ch = wgetch(ZoneResultat);
	} while ( ch != 10 || tolower(ch) != 'q');
	/*switch (ch)
	{
		case 10 : Partie(); break;
		case 'q' :
		case 'Q' : Menu(); break;
	}	*/
	wrefresh(ZoneResultat);
		
} 

int main(){
	
	int joueur=0;
	int nb_joueur=2;
	char ch;
	int nb_tour=0;
	int nb_lancers=1;
	strcpy(pseudo_j[0], "J1");
	strcpy(pseudo_j[1], "J2");
	strcpy(pseudo_j[2], "J3");
	strcpy(pseudo_j[3], "J4");
	MiseEnPlace();
	while(nb_tour < 13*nb_joueur){
		attron(A_BOLD);
		mvwprintw(ZoneMessage,1 ,2 ,"                                                                  ");
		mvwprintw(ZoneMessage,3 ,2 ,"                                                                  ");
		mvwprintw(ZoneMessage,1 ,2 ,"Tour de %s", pseudo_j[joueur]);
		attroff(A_BOLD);
		for(int i=3;i<20;i++)
		mvwprintw(ZoneAide,i,2,"                           "); 
		Lancer();
		AffichageDe(De ,ZoneDe);
		Aide(1);
		do
		{
			if (nb_lancers == 3) break;
			mvwprintw(ZoneMessage,2 ,2 ,"                                                                  ");
			mvwprintw(ZoneMessage,2 ,2 ,"Voulez-vous relancer ? [O/N]");
			wrefresh(ZoneMessage);
			do{
				ch=getch();
			}
			while(tolower(ch) != 'o' && tolower(ch) != 'n');
			if (tolower(ch) == 'n') break;
			mvwprintw(ZoneMessage, 2, 2, "                                                                  ");
			mvwprintw(ZoneMessage, 2, 2, "Sélectionnez les dés à garder avec [ESPACE].");
			mvwprintw(ZoneMessage, 2, 2, "Validez avec [ENTREE].");
			wrefresh(ZoneMessage);
			Garder(ZoneDe, Garde);
			Lancer();
			AffichageDe(De ,ZoneDe);
			Aide(1);
			nb_lancers++;
		
		}while(1);
		EcrireScore(joueur);
		nb_tour++;
		joueur=ChangerJoueur(joueur,nb_joueur);
		nb_lancers = 1;
	}
	Resultat(nb_joueur);
	do
	{
		ch = getch();
	} while (ch != 'j');
	endwin();
}	
