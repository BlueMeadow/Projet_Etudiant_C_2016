#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int tabOccurences[6]={0}; 
int Score[4][13]={{0}};
int De[5]={0,0,0,0,0};
int Garde[5]={0};
char pseudo_j1[30] = "J1";
char pseudo_j2[30] = "J2";
char pseudo_j3[30] = "J3";
char pseudo_j4[30] = "J4";
WINDOW *ZoneDe;
WINDOW *ZoneMessage;
WINDOW *ZoneAide;
WINDOW *ZoneScore;
char pseudos[50];
/*
|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

void Garder (WINDOW *localwin, int Garde[5])
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

void Lancer()
{
	//initialisation des valeurs aléatoires, à chaque tirage
	srand(time(0));
	int ch;
	do
	{
		ch = getch();
	} while (ch != 10);
	for(int i = 0; i < 5; i++){
		if(Garde[i] == 0){	
			//lancement des dés et sélection d'un chiffre entre 1 et 6 avec le hasard
			De[i] = rand()%6+1;
		}
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

void ChoixCategorie (int *Categorie, WINDOW *localwin)
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
	} while (ch != 10); 
		/* Entrée valide le choix */
}

void CalculOccurences()
{

	//parcourt les 5 dés lancés, on incremente le nombre de valeurs trouvés
	// dans le tableau d'occurences correspondant à la valeur du dé

	for( int i = 0; i < 5; i++){
		switch(De[i]){
			case 1: tabOccurences[0]++; break;
			case 2: tabOccurences[1]++; break;
			case 3: tabOccurences[2]++; break;
			case 4: tabOccurences[3]++; break;
			case 5: tabOccurences[4]++; break;
			case 6: tabOccurences[5]++; break;
		}
	}
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
		if(total == 3){
			return 1;

		}
		total=0;
	}
	return 0;
}

int isFull()
{
	
	int tabOccurences[6] = {0,0,0,0,0,0};

	CalculOccurences();

	int cpt3 = 0 , cpt2 = 0;

	//On a notre tableau d'occurences, maintenant on va circuler dans le tab d'occurences, pour voir s'il y a un full.

	for (int j = 0; j < 6; j++){

		if ( tabOccurences[j]==3){
			cpt3++;
		}
		else if( tabOccurences[j] == 2){
			cpt2++;
		}
	}

	if ( (cpt3 == 1) && (cpt2 == 1) ){
		return 1;
	}
	else{
		return 0;
	}

}

//Calcul de la petit suite

int isPtSuite()
{
	
	int i;
	int j;
	
	int tabOccurences[6] = {0,0,0,0,0,0};

	CalculOccurences();

	for(i=0;i<5;i++){
		tabOccurences[De[i]-1]++;
	}

	for(j=0;j<=2;j++){
		if(tabOccurences[j] > 0 && tabOccurences[j+1] > 0 && tabOccurences[j+2] > 0 && tabOccurences[j+3] > 0)
			return 1;

	}
	return 0;
}

int isGdSuite()
{
	
	int i;
	int j;
	
	int tabOccurences[6] = {0,0,0,0,0,0};

	CalculOccurences();

	for( i = 0;i < 5; i++){
		//compte le nombre d'occurence
		tabOccurences[De[i]-1]++;
	}
	for( j=0; j<1; j++){
		if(tabOccurences[0] == 1){
			//pour trouver si il y a un 1
			if((tabOccurences[j] > 0) && (tabOccurences[j+1] > 0) && (tabOccurences[j+2] > 0) && (tabOccurences[j+3] > 0) && (tabOccurences[j+4] > 0)){
				return 1;
			}
		}else{
			if((tabOccurences[j+1] > 0) && (tabOccurences[j+2] > 0) && (tabOccurences[j+3] > 0) && (tabOccurences[j+4] > 0) && (tabOccurences[j+5] > 0)){
				//pour trouver si il y a un six
				return 1;
			}
		}
	}
	return 0;
}

int isYahtzee()
{
	

	CalculOccurences();

	//on parcourt la tab Occurences, si on trouve 5 dans tabOccu, on trouve un Yahtzee donc 5 dés de même valeur.

	for (int i=0; i < 6; i++){
		if ( tabOccurences[i] == 5){
			return 1;
		}
	}
	return 0;
}

void CalculScore(int joueur, int * Categorie)
{
	switch(*Categorie){
	/* choix score a utiliser */		
		case 1 :
		case 2 :
		case 3 :
		case 4 :
		case 5 :
		case 6 :
		/* fonction qui calcule le score pour les dés de un a six */
			Score[joueur][*Categorie] = (*Categorie) * tabOccurences[*Categorie-1];
			break;			
		case 7:
			if(isBrelan())
				Score[joueur][*Categorie] = De[0]+De[1]+De[2]+De[3]+De[4];
			break;
			
		case 8:
			if(isCarre())
				Score[joueur][*Categorie] = De[0]+De[1]+De[2]+De[3]+De[4];
			break;
			
		case 9:
			if(isFull())
				Score[joueur][*Categorie] = 25;
			break;
			
		case 10:
			if(isPtSuite())
				Score[joueur][*Categorie] = 30;
			break;
			
		case 11:
			if(isGdSuite())
				Score[joueur][*Categorie] = 40;
			break;
			
		case 12:
			if(isYahtzee())
				Score[joueur][*Categorie] = 50;
			break;
			
		case 13:
			Score[joueur][*Categorie] = De[0]+De[1]+De[2]+De[3]+De[4];
			break;
	}
}	

void EcrireScore(int joueur)
{
	int categorie;
	int x = 2;
	int y = 2;
	
	mvwprintw(ZoneMessage ,y ,x ,"veuillez désigner la categorie choisie");
	wrefresh(ZoneMessage);
	ChoixCategorie(&categorie ,ZoneScore); 
	CalculScore(joueur, &categorie);
	
	/* choix de la colonne */
	x = 24 + 10 * joueur;
	/* choix de la ligne */
	
	if(categorie < 7)
		y = categorie + 4;
	else
		y = categorie + 7;
	
	/*affiche le score */
	mvwprintw(ZoneScore ,y ,x ,"%i" ,Score[joueur][categorie]);
	wrefresh(ZoneScore);
}

int main(){
	
	char ch;
	MiseEnPlace();
	int i;
	for(i = 0; i < 2 ;i++){
		Lancer();
		AffichageDe(De ,ZoneDe);
		Garder(ZoneDe, Garde);
		mvwprintw(ZoneMessage,2 ,2 ,"voulez vous relancer ? [O/N]");
		do{
			ch=getch();
		}
		while(tolower(ch) != 'o' && tolower(ch) != 'n');
		if (tolower(ch) == 'n') break;
	}
	CalculOccurences();
	EcrireScore(3);
	do
	{
		ch = getch();
	} while (ch != 'j');
	endwin();
}
	
	
