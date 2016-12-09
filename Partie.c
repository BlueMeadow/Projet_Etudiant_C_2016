/*
 La partie commence enfin. Etape importante: Veuillez entrer vos pseudos Première étape: sélection du premier joueur par la fonction QuiCommence.c. L'ordre des joueurs se fera par le
 sens des aiguilles d'une montre. Donc le premier joueur joue. Le suivi des fonctions sera le même pour tous les joueurs de la partie. 
 Tout d'abord, au premier lancer, les joueurs lancent leurs 5 dés. Ensuite ils continuent à lancer leurs dés de leur choix selon la combinaison
 qu'il obtienne jusqu'au troisième lancer. Ils peuvent les lancers quand ils veulent. Pour chaque lancer, une aide sera disponible pour connaître 
 le score qu'il obtienne selon la combinaison des 5 dés.  
*/


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

void Partie();
void Menu();
void Regles();
void Debut();
void SelectDebut();
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
	int compt; 	
	int x=2;
	int temp1=0, temp2=0;
	attron(A_BOLD);
	mvwprintw(ZoneAide, 2, 13, "AIDE");
	attroff(A_BOLD);
	wrefresh(ZoneAide);
	y+=2;
	if( i==1 ){
		if(isBrelan()){
			for(compt = 0; compt <= 5; compt++){
				if(tabOccurrences[compt] >= 3){
					 temp1 = compt+1;
				}
			}
			mvwprintw(ZoneAide, y, x, "Brelan de %i", temp1);
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isCarre()){
			for(compt = 0; compt <= 5; compt++){
				if(tabOccurrences[compt] >= 4){
					 temp1 = compt+1;
				}
			}
			mvwprintw(ZoneAide, y, x, "Carre de %i", temp1);
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isFull()){
			for(compt = 0; compt <= 5; compt++){
				if(tabOccurrences[compt] == 3){
					 temp1 = compt+1;
				}
				if(tabOccurrences[compt] == 2){
					 temp2 = compt+1;
				}
			}
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
	//permet de detruire une fenetre defini en parametres
{
	wclear(Fenetre);
	wrefresh(Fenetre);
	delwin(Fenetre);
}

void Resultat(int nb_joueur)
	//affiche le resultat et la possibilites de recommencer
{	

	
	int Total[nb_joueur];
	int ch;
	char Vainqueur[4][10];
	int i, j;
	int max;
	//supprime toute les fenetres de la partie pour ne laisser que la fenetre de score
	DetruireFenetre(ZoneMessage);
	DetruireFenetre(ZoneDe);
	DetruireFenetre(ZoneScore);
	DetruireFenetre(ZoneAide);
	ZoneResultat = create_newwin(20,60,(LINES-20)/2, (COLS-60)/2);
	
	//calcule le score des joueurs
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
	//calcule le meilleur score
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
	
	//affiche les score
	for (i = 0 ; i < nb_joueur ; i++)
	{
		mvwprintw(ZoneResultat, 5+i, 10, "%s : %i", pseudo_j[i], Total[i]);
	}
	
	wattron(ZoneResultat, A_REVERSE);
	mvwprintw(ZoneResultat, 11, 20, "VAINQUEUR");
	wattroff(ZoneResultat, A_REVERSE);
	
	//affiche le vainqueur
	for (i = 0 ; i <= j ; i++)
	{
		mvwprintw(ZoneResultat, 14+i, (50-strlen(Vainqueur[i]))/2 , "%s", Vainqueur[i] ) ;
	}
	mvwprintw(ZoneResultat, 16+j, 6, "Appuyez sur [ENTREE] pour relancer une partie");
	mvwprintw(ZoneResultat, 17+j, 6, "Appuyez sur [Q] pour quitter");
	do
	{
		ch = wgetch(ZoneResultat);
	//donne la possibilites de recommencer
	} while ( ch != 10 || tolower(ch) != 'q');
	switch (ch)
	{
		case 10 : DetruireFenetre(ZoneResultat);
			  Partie();
			  break;
		case 'q' :
		case 'Q' : DetruireFenetre(ZoneResultat);
			   Debut();
			   break;
	}	
	wrefresh(ZoneResultat);
		
} 


void Partie(){ 
	//lance la partie de yathzee
	int joueur=0;
	int nb_joueur=2;
	char ch;
	int a;
	int nb_tour=0;
	int nb_lancers=1;
	strcpy(pseudo_j[0], "J1");
	strcpy(pseudo_j[1], "J2");
	strcpy(pseudo_j[2], "J3");
	strcpy(pseudo_j[3], "J4");
	MiseEnPlace();
	mvwprintw(ZoneMessage,1 ,2 ,"taper [o] pour avoir l'aide et [n] pour ne pas l'avoir");
	wrefresh(ZoneMessage);
	do{
		ch=getch();
	}
	while(tolower(ch) != 'o' && tolower(ch) != 'n');
	if (tolower(ch) == 'n') a=0;
	if(tolower(ch) == 'o') a=1;
	//tant que toute les case ne sont pas remplie
	while(nb_tour < 13*nb_joueur){
		attron(A_BOLD);
		mvwprintw(ZoneMessage,1 ,2 ,"                                                                  ");
		mvwprintw(ZoneMessage,3 ,2 ,"                                                                  ");
		mvwprintw(ZoneMessage,1 ,2 ,"Tour de %s", pseudo_j[joueur]);
		attroff(A_BOLD);
		//vide la ZoneAide de ses caractere
		for(int i=3;i<20;i++)
		mvwprintw(ZoneAide,i,2,"                        "); 
		Lancer();
		AffichageDe(De ,ZoneDe);
		Aide(a);
		//do while pour la relance entre chaque entrée
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
			for(int i=3;i<20;i++)
			mvwprintw(ZoneAide,i,2,"                        "); 
			Aide(a);
			nb_lancers++;
		
		}while(1);
		EcrireScore(joueur);
		nb_tour++;
		joueur=ChangerJoueur(joueur,nb_joueur);
		nb_lancers = 1;
	}
	//une fois la partie terminé affiche le resultat
	Resultat(nb_joueur);
	do
	{
		ch = getch();
	} while (ch != 'j');
	endwin();
}

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
	Debut();
}


void Menu(WINDOW *localwin, int y, int x){	

	
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
	
	Menu(ZoneDebut, y, x);
	wmove(ZoneDebut, 2, 2);
	wrefresh(ZoneDebut);
	y = 2;
	do 
	{			
		ch = wgetch(ZoneDebut);
		switch (ch)
		{
			case KEY_DOWN :
				if ( y == 4)
				{
					y=2;
					wmove(ZoneDebut, y, x);
					wrefresh(ZoneDebut);

				}
				else{
					y++;
					wmove(ZoneDebut, y, x);
					wrefresh(ZoneDebut);			
				}
				break;
		
				
			case KEY_UP :
				if ( y > 2)
				{
					y--;
					wmove(ZoneDebut, y, x);
					wrefresh(ZoneDebut);

				}
				else{
					y = 4;
					wmove(ZoneDebut, y, x);
					wrefresh(ZoneDebut);			
				}
				break;
		
					
		}
	mvwprintw(ZoneDebut, 7, 3, "%i", y);
	wrefresh(ZoneDebut);	
	} while ( ch != 10 );	
	/* On valide la selection avec la touche entree */
	switch(y)
	{
		case 2 : Partie();
		case 3 : Regles();
		case 4 : endwin();
	}
}

void Debut(){
	
	initscr();
	cbreak();
	noecho(); /* Les trois lignes au dessus sont dans MiseEnPlace() */
	SelectDebut();

}

int main(){	
	Debut();
}
