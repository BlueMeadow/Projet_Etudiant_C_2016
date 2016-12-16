/*
 La partie commence enfin. Etape importante: Veuillez entrer vos pseudos Première étape: sélection du premier joueur par la fonction QuiCommence.c. L'ordre des joueurs se fera par le
 sens des aiguilles d'une montre. Donc le premier joueur joue. Le suivi des fonctions sera le même pour tous les joueurs de la partie. 
 Tout d'abord, au premier lancer, les joueurs lancent leurs 5 dés. Ensuite ils continuent à lancer leurs dés de leur choix selon la combinaison
 qu'il obtienne jusqu'au troisième lancer. Ils peuvent les lancers quand ils veulent. Pour chaque lancer, une aide sera disponible pour connaître 
 le score qu'il obtienne selon la combinaison des 5 dés.  
*/

/**
* \file Partie.c
* \brief Permet de faire fonctionner notre Yahtzee
* \author Benoit Combasteix, Simon Fernandes et Nathan OUALET
* \version 1.0
*/

/**
* \fn Nettoyer(WINDOW * localwin, int DebutY, int DebutX, int FinY, int FinX)
* \return 
* \fn Garder(WINDOW *localwin, int Garde[5])
* \return FOnction booléenne qui permet de garder le résultat d'un dé ou le changer
* \fn CalculOccurrences()
* \return Pour chaque lancer, calcul le nombre d'occurences d'une valeur sur les 5 dés
* \fn Lancer()
* \return Après utilisation de la fonction Garder(...), on (re)lance les dés qu'on a pas voulu garder.
* \fn ChainePseudo (char pseudos[50])
* \return
* \fn FicheDeScore(WINDOW *localwin, int y, int x)
* \return Affiche le squelette de la fiche de score
*/

/**
* \fn DeUn(WINDOW *localwin, int y, int x)
* \return Affiche la face Un d'un dé
* \fn DeDeux(WINDOW *localwin, int y, int x)
* \return Affiche la face Deux d'un dé
* \fn DeTrois(WINDOW *localwin, int y, int x)
* \return Affiche la face Trois d'un dé
* \fn DeQuatre(WINDOW *localwin, int y, int x)
* \return Affiche la face Quatre d'un dé
* \fn DeCinq(WINDOW *localwin, int y, int x)
* \return Affiche la face Cinq d'un dé
* \fn DeSix(WINDOW *localwin, int y, int x)
* \return Affiche la face Six d'un dé
* \fn DeVide(WINDOW *localwin, int y, int x)
* \return Affiche la face Vide d'un dé ( utiliséé au début de la partie )
*/

/**
* \fn AffichageDe(int De[5], WINDOW *localwin)
* \return Affiche les dés selon le résultat de Lancer()
* \fn MiseEnPlace()
* \return Initialise les zones utilisés par le programme
* \fn ChoixCategorie (int *Categorie, WINDOW *localwin,int joueur)
* \return Permet de choisir entre les différentes catégories ( 1,...,6, Full,...,Chance)
*/

/**
* \fn isBrelan()
* \return Retourne vrai si la série de dé a un Brelan.
* \fn isCarre()
* \return Retourne vrai si la série de dé a un Carre.
* \fn isFull()
* \return Retourne vrai si la série de dé a un Full.
* \fn isPtSuite()
* \return Retourne vrai si la série de dé a une petite suite.
* \fn isGdSuite()
* \return Retourne vrai si la série de dé a une grande suite.
* \fn isYahtzee()
* \return Retourne vrai si la série de dé a un Yahtzee.
*/

/**
* \fn CalculScore(int joueur, int Categorie)
* \return Calcul le score de la catégorie choisi par ChoixCategorie() pour chaque joueur

* \fn EcrireScore(int joueur)
* \return Ecris le score actuelle après chaque tour

* \fn ChangerJoueur(int joueur, int nb_joueur)
* \return retourne le joueur qui suit celui qui a joué.

* \fn Aide(int i)
* \return Affiche l'aide selon l'envie du joueur.

* \fn DetruireFenetre(WINDOW * Fenetre)
* \return Détruis les données d'une fenetre défini en paramêtres.

* \fn Resultat()
* \return Affiche le résultat final d'une partie.

* \fn Partie()
* \return Permet de lancer une nouvelle partie

* \fn Page_Regles(WINDOW *localwin, int y, int x)
* \return Affiche toutes les rêgles.

* \fn Regles()
* \return Permet de faire un déroulement de la page des rêgles.

* \fn EntrerNbJoueur()
* \return Permet de sélectionner le nombre de joueur qui joue à la partie.

* \fn EntrerPseudo()
* \return Permet de sélectionner les pseudos des joueurs selon le nombre de joueurs.

* \fn Menu(WINDOW *localwin, int y, int x)
* \return Affiche la première page qui permet de choisir entre commencer une nouvelle partie, voir le rêgles ou quitter le jeu.
*/


#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>


int Occurrences[6];
int Score[4][13];
int De[5];
int Garde[5];
int NbJoueurs;
char PseudoJ[4][10];
char Pseudos[40];
int Prime[4];
int Joueur;
int NbTours;
int NbLancers;
int isAide[4];
void Aide(int isAide[], int Joueur);

WINDOW *ZoneDe;
WINDOW *ZoneMessage;
WINDOW *ZoneAide;
WINDOW *ZoneResultat;
WINDOW *ZoneScore;
WINDOW *ZoneMenu;

void Debut();                                     /* Premier menu, permet de commencer une partie, afficher les règles ou quitter */
int Partie();                                    /* Commence une partie de Yahtzee */
int Regles();                                    /* Affiche les règles */  
void Page_Regles(WINDOW *Fenetre, int y, int x);
void Menu();
void Sauvegarder();
void FinDePartie();
void ChargementAffichage();
WINDOW *CreerFenetre(int height, int width, int starty, int startx);

int Initialisation()
{
	int i, j;
	for (i = 0 ; i < 4 ; i++)
	{
		for (j = 0 ; j < 13 ; j++)
		{
			Score[i][j] = -1;
		}
	}
	
	for (i = 0 ; i < 6 ; i++)
	{
		Occurrences[i] = 0;
	}
	for (i = 0 ; i < 5 ; i++)
	{
		Garde[i] = 0;
		De[i] = 0;
	}
	for (i = 0 ; i < 4 ; i++)
	{
		Prime[i] = 0;
	}
	Joueur = 0;
	NbTours = 0;
	NbLancers = 1;
	return 1;
}

void Nettoyer(WINDOW * Fenetre, int DebutY, int DebutX, int FinY, int FinX)
{
	int i, j;
	for (i = DebutY ; i < FinY ; i++)
		for (j = DebutX ; j < FinX ; j++)
			mvwprintw(Fenetre, i, j, " ");
}


void DetruireFenetre(WINDOW * Fenetre)
{
	wclear(Fenetre);
	wrefresh(Fenetre);
	delwin(Fenetre);
}
void Garder(WINDOW *Fenetre, int Garde[5])
{
	int y, x, ch;
	y = 5; //indice d'ordonnée
	x = 14; // indice d'abscisse
	keypad(Fenetre, TRUE); //Permet l'utilisation des touches directionnelles
	
	wmove(Fenetre, y, x);
	wrefresh(Fenetre);
	do 
	{
		ch = wgetch(Fenetre);
		switch (ch)
		{
			case KEY_UP:  
				if ( y == 5 )
				/* Si on est en haut, on passe en bas */
				{
					y = 25;
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else 
				/* Sinon on monte d'une case */
				{
					y-=5;
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				break;
			case KEY_DOWN:
				if ( y == 25 )
				/* Si on est en bas, on remonte en haut */
				{
					y = 5;
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else 
				/* Sinon on descend d'une case */
				{
					y+=5;
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				break;
			case 32: 
				/* La touche espace sert à indiquer si on veut garder le de ou non */
				if ( Garde[y/5-1] == 0 )
				{
					waddch(Fenetre, 'G');
					Garde[y/5-1] = 1;
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else
				{
					waddch(Fenetre, ' ');
					Garde[y/5-1] = 0;
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
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
		Occurrences[i] = 0;

	for( i = 0; i < 5 ; i++){
		Occurrences[De[i]-1]++;
	}
}


void Lancer()
{
	//initialisation des valeurs aléatoires, à chaque tirage
	srand(time(0));
	int ch;
	mvwprintw(ZoneMessage,2 ,2 ,"                                                                  ");
	mvwprintw(ZoneMessage, 2, 2, "Appuyez sur [ENTREE] pour lancer les dés.");
	mvwprintw(ZoneMessage, 4, 2, "Vous pouvez sauvegarder et quitter en appuyant sur [S]");
	wrefresh(ZoneMessage);
	do
	{
		ch = getch();
	} while (ch != 10 && tolower(ch) != 's');
	
	if ( ch == 's' )
	{
		mvwprintw(ZoneMessage, 4, 2, "                                                          ");
		mvwprintw(ZoneMessage, 4, 2, "Vous-vous vraiment sauvegarder et quitter ? [O/N]");
		wrefresh(ZoneMessage);
		do
		{
			ch = getch();
		} while (tolower(ch) != 'o' && tolower(ch) != 'n');
		if ( tolower(ch) == 'o')
		{
			Sauvegarder();
			
			FinDePartie();
		}
	}
	if (ch == 10)
		mvwprintw(ZoneMessage, 4, 2, "                                                          ");

	for(int i = 0; i < 5; i++)
	{
		if(Garde[i] == 0)
		{	
			//lancement des dés et sélection d'un chiffre entre 1 et 6 avec le hasard
			De[i] = rand()%6+1;
		}
		CalculOccurrences();
		Garde[i]=0;	
	}
	Aide(isAide, Joueur);
}

WINDOW *CreerFenetre(int height, int width, int starty, int startx)
{	WINDOW *Fenetre;
	Fenetre = newwin(height, width, starty, startx);
	wborder(Fenetre, '|', '|', '-', '-', '+', '+', '+', '+');		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(Fenetre);		/* Show that box 		*/
	return Fenetre;
}

void FinDePartie()
{
	WINDOW * ZoneFin;
	ZoneFin = CreerFenetre(12, 80, (LINES-12)/2, (COLS-80)/2);

	mvwprintw(ZoneFin, 3, 30, "Merci d'avoir joué !");
	mvwprintw(ZoneFin, 6, 21, "Le programme quittera dans 3 secondes");
	wrefresh(ZoneFin);
	sleep(3);
	endwin();
	exit(1);
}

void ChainePseudo (char Pseudos[40])
{
	strcpy(Pseudos, "");
	/* Vide la chaîne, evite les seg fault si on relance une partie et qu'on a déjà des pseudos dedans*/
	int i, esp1, esp2, esp3, esp4;
	esp1 = 10-strlen(PseudoJ[0]);
	esp2 = 10-strlen(PseudoJ[1]);
	esp3 = 10-strlen(PseudoJ[2]);
	esp4 = 10-strlen(PseudoJ[3]);
	strcat(Pseudos, PseudoJ[0]);
	for(i = 0 ; i <= esp1 ; i++) strcat(Pseudos, " ");
	strcat(Pseudos, PseudoJ[1]);
	for(i = 0 ; i < esp2 ; i++) strcat(Pseudos, " ");
	strcat(Pseudos, PseudoJ[2]);
	for(i = 0 ; i < esp3 ; i++) strcat(Pseudos, " ");
	strcat(Pseudos, PseudoJ[3]);
	for(i = 0 ; i < esp4-1 ; i++) strcat(Pseudos, " ");
	
		
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
	int x = 1;
	int y = 3;
	for(int i = 0 ; i < 5 ; i++)
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

void MiseEnPlace()
{	
	initscr();
	cbreak();
	noecho();
	refresh();
	ChainePseudo(Pseudos);
	ZoneAide = CreerFenetre(30,30,3,92);
	ZoneDe = CreerFenetre(31, 19, 3, 3);
	ZoneScore = CreerFenetre(25,70,3,22);
	ZoneMessage = CreerFenetre(10,70,28,22);
	FicheDeScore(ZoneScore,2,2);
	AffichageDe(De, ZoneDe);
}



void Sauvegarder()
{
	FILE * Sauvegarde = NULL;
	int i;
	int j;
	char NomFichier[7] = "sav_";
	char temp[4]; // Garde le début du nom de fichier après modifcation
	char NumSav[3]; // Jusqu'à 99 sauvegardes

	strcpy(temp, NomFichier);
	NumSav[2] = '\0';
	NumSav[1] = '1'; 
	NumSav[0] = '0'; 
	strcat(NomFichier, NumSav);

	/* Vérification du numéro de sauvegarde à attribuer */
	for (i = 0; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
			Sauvegarde = fopen(NomFichier, "r");
			if (Sauvegarde != NULL)
			{
				fclose(Sauvegarde);
				strcpy(NomFichier, temp);
				NumSav[1]++;
				if (NumSav[1] > '9')
				{
					NumSav[1] = '0';
					NumSav[0]++;
				}
				strcat(NomFichier, NumSav);
			}
			else break; 
			/* Si le fichier n'existe pas, on sort des boucles de vérification */
		}
		if (Sauvegarde == NULL) break; 
		/* Si le fichier n'existe pas, on sort des boucles de vérification */
	}
	Sauvegarde = fopen(NomFichier, "w");
	/* On rentre les données importantes dans le fichier */
	fprintf(Sauvegarde, "%i %i %i %i", NbJoueurs, Joueur, NbTours, NbLancers);
	for (i = 0; i < NbJoueurs; i++)
	{
		fprintf(Sauvegarde, " %s %i", PseudoJ[i], isAide[i]);
		for (j = 0; j < 13; j++)
		{
			fprintf(Sauvegarde, " %i", Score[i][j]);
		}
	}

	fclose(Sauvegarde);
	mvwprintw(ZoneMessage, 4, 2, "Votre sauvegarde est la numéro %c%c", NumSav[0],NumSav[1]);
	mvwprintw(ZoneMessage, 5, 2, "Appuyez sur une touche pour quitter");
	wgetch(ZoneMessage);
}		


int Charger()
{
	FILE * Sauvegarde = NULL;
	int i;
	int j;
	int y = 1, x = 0, ch;
	int NbFichier = 0;
	char NomFichier[10] = "sav_";
	char temp[4]; // Garde le début du nom de fichier après modifcation
	char NumSav[3]; // Jusqu'à 99 sauvegardes

	strcpy(temp, NomFichier);
	NumSav[2] = '\0';
	NumSav[1] = '1'; 
	NumSav[0] = '0'; 
	strcat(NomFichier, NumSav);

	/* Vérification du numéro de sauvegarde à attribuer */
	for (i = 0; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
			Sauvegarde = fopen(NomFichier, "r");
			if (Sauvegarde != NULL)
			{
				fclose(Sauvegarde);
				strcpy(NomFichier, temp);
				NumSav[1]++;
				NbFichier++;
				if (NumSav[1] > '9')
				{
					NumSav[1] = '0';
					NumSav[0]++;
				}
				strcat(NomFichier, NumSav);
			}
			else break; 
			/* Si le fichier n'existe pas, on sort des boucles de vérification */
		}
		if (Sauvegarde == NULL) break; 
		/* Si le fichier n'existe pas, on sort des boucles de vérification */
	}

	/* Affichage Ncurses */
	
	WINDOW * ZoneChargement;
	
	int Hauteur = (LINES-40)/2;
	int Longueur = (COLS-85)/2;
	ZoneChargement = CreerFenetre(48, 85, Hauteur, Longueur);
	
	keypad(ZoneChargement, TRUE);
	mvwprintw(ZoneChargement, 2, (Longueur-17)/2, "Sélectionnez la sauvegarde à charger");
	if (!NbFichier) 
	{
		mvwprintw(ZoneChargement, 2, (Longueur-34)/2, "Il n'y a pas de sauvegarde à charger");
		mvwprintw(ZoneChargement, 4, 16, "Appuyez sur une touche pour revenir au menu");
		wgetch(ZoneChargement);
		return 0;
	}
		
	for (i = 1; i < 100 ; i++)
	{ 
		y++;
		if (i == 34)
		{
			x = 1;
			/* Passe à la colonne suivante */
			y-=33;
			/* Retourne à la première ligne */
		}
		if ( i == 67 )
		{
			x = 2;
			/* Revient à la colonne précédente */
			y-=33;
			/* Retourne à la première ligne */
		}
		if ( i < (NbFichier+1) )
			mvwprintw(ZoneChargement, y+5, 4+x*23, "[   ] Sauvegarde n°%i", i);
		/*else 
			
			mvwprintw(ZoneChargement, y+5, 4+x*23, "[   ] Sauvegarde vide");*/
	}
	
	/* Sélection de la sauvegarde */
	
	y = 1;
	x = 0;

	wmove(ZoneChargement, y+6, 6+x*23);
	wrefresh(ZoneChargement);
	

	do
	{
		ch = wgetch(ZoneChargement);
		
		switch(ch)
		{
			case KEY_DOWN : if ((y+33*x) < NbFichier) 
					/* Empeche d'aller se potitionner sur des sauvegardes vides */
					{
						y++;
						if (y > 33 && x < 2)
						{
							x++;
							/* Passe à la colonne suivante */
							y-=33;
							/* Repart à la première ligne */					
						}
						mvwprintw(ZoneChargement, 2,2, "  %i  %i   ", y, x);
						wmove(ZoneChargement, y+6, 6+x*22);
						wrefresh(ZoneChargement);
					}
					break;
			case KEY_UP : if (y > 0)
					{
						y--;
						if (y < 1 && x > 0)
						{
							x--;
							/* Revient à la colonne précédente */
							y+=33; 
							/* Repart à la dernière ligne */
						}
						mvwprintw(ZoneChargement, 2,2, "  %i  %i   ", y, x);
						wmove(ZoneChargement, y+6, 6+x*22);
						wrefresh(ZoneChargement);
					}
					break;
		}
	} while(ch != 10);


	/* Chargement */	

	y = (y + 33 * x); /* Donne le numéro de sauvegarde */

	x = y%10; /* Donne le nombre des unités */
	y = y / 10;  /* Donne le nombre des dizaines */

	NumSav[2] = '\0';
	NumSav[1] = x + 48; /* Code ASCII du chiffre x */
	NumSav[0] = y + 48; /* Code ASCII du chiffre y */

	strcpy(NomFichier, temp);
	strcat(NomFichier, NumSav);
	
	Sauvegarde = fopen(NomFichier, "r");
	fscanf(Sauvegarde, "%i %i %i %i", &NbJoueurs, &Joueur, &NbTours, &NbLancers);
	for (i = 0; i < NbJoueurs; i++)
	{
		fscanf(Sauvegarde, " %s %i", PseudoJ[i], &isAide[i]);
		for (j = 0; j < 13; j++)
		{
			fscanf(Sauvegarde, " %i", &Score[i][j]);
		}
	}

	fclose(Sauvegarde);
	DetruireFenetre(ZoneChargement);
	return 1;
}



void ChoixCategorie (int *Categorie, WINDOW *Fenetre, int Joueur)
{
	int y, x;
	y = 5; //indice d'ordonnée
	x = 4; // indice d'abscisse
	int ch; 
	keypad(Fenetre, TRUE); //Permet l'utilisation des touches directionnelles
	
	wmove(Fenetre, y, x);
	wrefresh(Fenetre);

	
	do 
	{
		ch = wgetch(Fenetre);
		switch (ch)
		{
			case KEY_UP:  
				/* Fleche du haut entree */
				if (y == 5)
				{
					y = 20; 
					/* Si on est en haut du tableau, on passe en bas */
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else if (y == 14)
				{
					/* On remet un vide car on change de catégorie */
					y = 10; 
					/* On passe les 3 lignes centrales du tableau de score */
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else 
				{
					y--;
					/* On remonte d'une case */
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				break;
			
			case KEY_DOWN:
				/* Fleche du bas entree */
				if (y == 20)
				{
					y = 5; 
					/* Si on est en bas du tableau, on passe en haut */
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else if (y == 10)
				{
					y = 14; 
					/* On passe les 3 lignes centrales du tableau de score */
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else 
				{

					y++;
					/* On descend d'une case */
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				break;
		}
		if (y < 11) *Categorie = y - 4;
		else *Categorie = y - 7;
		if(Score[Joueur][*Categorie-1] != -1){
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
	/* VRAI si 3 dés ont la même valeur */
	int i;
	for( i = 0; i < 6 ; i++)
	{
		if (Occurrences[i] > 2)
			return 1;
	}
	return 0;
}

int isCarre()
{
	/* VRAI si 4 dés ont la même valeur */
	int i;
	
	for( i = 0; i < 6 ; i++)
	{
		if (Occurrences[i] > 3)
			return 1;
	}
	return 0;		
}

int isYahtzee()
{

	/* VRAI si les 5 dés ont la même valeur */

	for (int i=0; i < 6; i++){
		if ( Occurrences[i] == 5){
			return 1;
		}
	}
	return 0;
}

int isFull()
{
	/* VRAI si on a un brelan et une paire */
	int i, cpt2 = 0, cpt3 = 0;

	for( i = 0 ; i < 6 ; i++)
	{		
		if( Occurrences[i] == 2 )
			cpt2 = 1;
		else if( Occurrences[i] == 3 )
			cpt3 = 1;
	}
	if (cpt2 == 1 && cpt3 == 1)
		return 1;
	return (isYahtzee());
	/* Un Yahtzee est condéré comme un Full */
}



int isPtSuite()
{
	/* VRAI si 4 dés se suivent */
	int i;
	int j;

	for(j=0;j<=2;j++){
		if(Occurrences[j] > 0 && Occurrences[j+1] > 0 && Occurrences[j+2] > 0 && Occurrences[j+3] > 0)
			return 1;

	}
	return 0;
}

int isGdSuite()
{
	/* VRAI si 5 dés se suivent */
	int i;
	
	for(i = 0; i < 1; i++)
	{
		if ((Occurrences[i] > 0) && (Occurrences[i+1] > 0) && (Occurrences[i+2] > 0) && (Occurrences[i+3] > 0) && (Occurrences[i+4] > 0))
			return 1;
	}
	return 0;
}



void CalculScore(int Joueur, int Categorie)
{
	if(Score[Joueur][11]>0){
		if(isYahtzee()){
			Prime[Joueur]++;
		}
	}
	switch(Categorie){	
		case 1 :
		case 2 :
		case 3 :
		case 4 :
		case 5 :
		case 6 :
		/* Calcule le score pour les dés de un à six */
			Score[Joueur][Categorie-1] = (Categorie) * Occurrences[Categorie-1];
			break;			
		case 7:
			if(isBrelan())
				Score[Joueur][Categorie-1] = De[0]+De[1]+De[2]+De[3]+De[4];
			else
				Score[Joueur][Categorie-1] = 0;
			break;
			
		case 8:
			if(isCarre())
				Score[Joueur][Categorie-1] = De[0]+De[1]+De[2]+De[3]+De[4];
			else
				Score[Joueur][Categorie-1] = 0;
			break;
			
		case 9:
			if(isFull())
				Score[Joueur][Categorie-1] = 25;
			else
				Score[Joueur][Categorie-1] = 0;
			break;
			
		case 10:
			if(isPtSuite())
				Score[Joueur][Categorie-1] = 30;
			else
				Score[Joueur][Categorie-1] = 0;
			break;
			
		case 11:
			if(isGdSuite())
				Score[Joueur][Categorie-1] = 40;
			else
				Score[Joueur][Categorie-1] = 0;
			break;

		case 12:
			if(isYahtzee())
				Score[Joueur][Categorie-1] = 50;
			else
				Score[Joueur][Categorie-1] = 0;
			break;
			
		case 13:
			Score[Joueur][Categorie-1] = De[0]+De[1]+De[2]+De[3]+De[4];
			break;
	}	
}	

void EcrireScore(int Joueur)
{
	int categorie;
	int x = 2;
	int y = 2;
	int i;
	int j;
	
	mvwprintw(ZoneMessage ,y ,x ,"Veuillez choisir la catégorie");
	wrefresh(ZoneMessage);
	ChoixCategorie(&categorie ,ZoneScore,Joueur); 
	CalculScore(Joueur, categorie);
	
	/* choix de la colonne */
	x = 24 + 10 * Joueur;
	/* choix de la ligne */
	
	

	if(categorie < 7)
		y = categorie + 4;
	else
		y = categorie + 7;
	
	/*affiche le score */
	mvwprintw(ZoneScore, y, x,"%i", Score[Joueur][categorie-1]);
	wrefresh(ZoneScore);
}
int ChangerJoueur(int Joueur, int NbJoueurs){
	return ((Joueur+1)%NbJoueurs);
}

void Aide(int isAide[4], int Joueur){
	int y=2;
	int x=2;
	int i;
	int temp1=0, temp2=0;
	Nettoyer(ZoneAide, 2, 2, 29, 29);
	attron(A_BOLD);
	mvwprintw(ZoneAide, 2, 13, "AIDE");
	attroff(A_BOLD);
	wrefresh(ZoneAide);
	y+=2;
	
	if( isAide[Joueur] ){
		mvwprintw(ZoneAide, y, x, "Pas de combinaison");
		wrefresh(ZoneAide);
		if(isBrelan())
		{
			for (i = 0 ; i < 6 ; i++)
			{
				if (Occurrences[i] > 2)
				{
					temp1 = i;
					break;
				}
			}
			mvwprintw(ZoneAide, y, x, "                         ", temp1+1);
			/* Efface la ligne"Pas de combinaison */
			mvwprintw(ZoneAide, y, x, "Brelan de %i", temp1+1);
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isCarre())
		{
			for (i = 0 ; i < 6 ; i++)
			{
				if (Occurrences[i] > 3)
				{
					temp1 = i;
					break;
				}
			}
			mvwprintw(ZoneAide, y, x, "Carre de %i", temp1+1);
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isFull())
		{
			mvwprintw(ZoneAide, y, x, "Full");
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isPtSuite())
		{
			mvwprintw(ZoneAide, y, x, "                         ", temp1+1);
			/* Efface la ligne"Pas de combinaison */
			mvwprintw(ZoneAide, y, x, "Petite suite");
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isGdSuite())
		{
			mvwprintw(ZoneAide, y, x, "                         ", temp1+1);
			/* Efface la ligne"Pas de combinaison */
			mvwprintw(ZoneAide, y, x, "Grande suite");
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isYahtzee())
		{
			mvwprintw(ZoneAide, y, x, "YAHTZEE !");
			wrefresh(ZoneAide);
			y+=2;
		}
	}
	else
	{
		mvwprintw(ZoneAide, y, x, "L'aide n'est pas activée");
		wrefresh(ZoneAide);
	}
}



int Resultat(int * isRelancer)
{		
	int Total[NbJoueurs];
	int ch;
	char Vainqueur[4][10];
	int i, j;
	int max;
	DetruireFenetre(ZoneMessage);
	DetruireFenetre(ZoneDe);
	DetruireFenetre(ZoneScore);
	DetruireFenetre(ZoneAide);
	ZoneResultat = CreerFenetre(28,60,(LINES-28)/2, (COLS-60)/2);

	for (i = 0 ; i < NbJoueurs ; i++)
	{
		Total[i] = 0;
		for (j = 0 ; j < 6 ; j++)
		{
			Total[i] += Score[i][j];
			
		}
		if (Total[i] > 62) 
		/* La prime de 35 si le score de la partie haute est de 63 ou plus */
		{
			Total[i] += 35;
		}	
		for (j = 6 ; j < 13 ; j++)
		{
			Total[i] += Score[i][j];
		}
		if(Prime[i] > 0)
		{
			Total[i] += 100*Prime[i];
		}
	}
	max = Total[0];
	strcpy(Vainqueur[0], PseudoJ[0]);		
	j = 0;
	for( i = 1 ; i < 4 ; i++)
	{
		if ( max < Total[i] )
		/* Si le joueur i n'a pas le meilleur score */
		{
			max = Total[i];
			strcpy(Vainqueur[j], PseudoJ[i]);		
		
		}
		else if ( max == Total[i] )
		/* En cas d'égalité */
		{
			j++;
			strcpy(Vainqueur[j], PseudoJ[i]);
		}
	}
	wattron(ZoneResultat, A_REVERSE);
	mvwprintw(ZoneResultat, 2, 16, "TABLEAU DE SCORES");
	wattroff(ZoneResultat, A_REVERSE);
	for (i = 0 ; i < NbJoueurs ; i++)
	{
		mvwprintw(ZoneResultat, 5+i, 10, "%s : %i", PseudoJ[i], Total[i]);
	}
	
	wattron(ZoneResultat, A_REVERSE);
	mvwprintw(ZoneResultat, 11, 20, "VAINQUEUR");
	wattroff(ZoneResultat, A_REVERSE);

	for (i = 0 ; i <= j ; i++)
	{
		mvwprintw(ZoneResultat, 14+i, (50-strlen(Vainqueur[i+1]))/2 , "%s", Vainqueur[i] ) ;
	}
	mvwprintw(ZoneResultat, 20+j, 6, "Appuyez sur [ENTREE] pour relancer une partie");
	mvwprintw(ZoneResultat, 21+j, 6, "Appuyez sur [M] pour revenir au menu");
	mvwprintw(ZoneResultat, 22+j, 6, "Appuyez sur [Q] pour quitter");
	wrefresh(ZoneResultat);
	do
	{
		ch = wgetch(ZoneResultat);
	} while ( ch != 10 && tolower(ch) != 'q' && tolower(ch) != 'm');

	switch (ch)
	{
		case 10 :  DetruireFenetre(ZoneResultat); *isRelancer = 1;  break;
		case 'q' :
		case 'Q' : *isRelancer = 0; FinDePartie(); break;
		case 'm' :
		case 'M' : *isRelancer = 0; DetruireFenetre(ZoneResultat); return 1;		
	}			
} 

void DemandeAide()
{
	int i, j, ch;
	keypad(ZoneMenu, TRUE);
	echo(); 

	wmove(ZoneMenu, 1, 1);
	for (i = 0 ; i < NbJoueurs ; i++)
	{
		Nettoyer(ZoneMenu, 2, 2, 14, 89);
		mvwprintw(ZoneMenu, 2, 2, "Joueur %s : ", PseudoJ[i]);
		mvwprintw(ZoneMenu, 3, 2, "Voulez-vous afficher l'aide ? [O/N]");
		wrefresh(ZoneMenu);
		do
		{
			ch=wgetch(ZoneMenu);
		} while(tolower(ch) != 'o' && tolower(ch) != 'n');

		if (tolower(ch) == 'n') isAide[i] = 0;
		else isAide[i] = 1;

	}
	
}

int Partie()
{	
	char ch;
	int i;
	MiseEnPlace();
	ChargementAffichage();
	while(NbTours < 13*NbJoueurs)
	{
		Aide(isAide, Joueur);
		attron(A_BOLD);
		mvwprintw(ZoneMessage,1 ,2 ,"                                                                  ");
		mvwprintw(ZoneMessage,3 ,2 ,"                                                                  ");
		mvwprintw(ZoneMessage,1 ,2 ,"Tour de %s", PseudoJ[Joueur]);
		attroff(A_BOLD);
		for(int i=3;i<20;i++)
		mvwprintw(ZoneAide,i,2,"                           "); 
		Lancer();
		AffichageDe(De ,ZoneDe);
		Aide(isAide, Joueur);
		do
		{
			if (NbLancers == 3) break;
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
			Aide(isAide, Joueur);
			NbLancers++;
		
		} while(1);
		EcrireScore(Joueur);
		NbTours++;
		Joueur = ChangerJoueur(Joueur,NbJoueurs);
		NbLancers = 1;
	}
	return 1;
}

void Page_Regles(WINDOW *Fenetre, int y, int x)
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
{

	int x, y, ch;

	WINDOW * ZoneRegles;
	ZoneRegles = newwin(30, 120, (LINES-30)/2, (COLS-67)/2);
	ZoneMessage = CreerFenetre(5,120, (LINES-30)/2+35, (COLS-120)/2);

	mvwprintw(ZoneMessage, 2, 38, "Faites défiler avec les flèches ou la molette");
	mvwprintw(ZoneMessage, 3, 38, "Appuyez sur [ENTREE] pour retourner au menu");
	wrefresh(ZoneMessage);

	keypad(ZoneRegles, TRUE);

	y = 1;
	x = 2;
	
	do
	{

		Nettoyer(ZoneRegles, 0, 0, LINES, COLS);
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
		}

	} while (ch != 10); 
	DetruireFenetre(ZoneRegles);
	DetruireFenetre(ZoneMessage);
	return 0;
	/* Entrée fait sortir de l'affichage des règles */
	/* Retour au menu */
}



void EntrerNbJoueur()
{
	keypad(ZoneMenu, TRUE);

	int y = 5, ch;
	NbJoueurs = 0;
	wclear(ZoneMenu);

	mvwprintw(ZoneMenu, 2, 2, "Choisissez le nombre de joueurs (max. 4) avec les flèches.");
	mvwprintw(ZoneMenu, 5, 2, "  |1 Joueur.");
	mvwprintw(ZoneMenu, 6, 2, "  |2 Joueurs.");
	mvwprintw(ZoneMenu, 7, 2, "  |3 Joueurs.");
	mvwprintw(ZoneMenu, 8, 2, "  |4 Joueurs.");
	mvwprintw(ZoneMenu, 9, 1, "%i Joueur(s) ? Confirmer avec [ENTREE]", y-4);
	
	wrefresh(ZoneMenu);
	
	wmove(ZoneMenu, y, 2);
	wrefresh(ZoneMenu);
	

	do
	{
		ch = wgetch(ZoneMenu);
		
		switch(ch)
		{
			case KEY_UP : 
						if (y > 5)
						{
							y--;

							mvwprintw(ZoneMenu, 9, 1, "                                                             ");
							mvwprintw(ZoneMenu, 9, 1, "%i Joueur(s) ? Confirmer avec [ENTREE]", y-4);
							wmove(ZoneMenu, y, 2);
							wrefresh(ZoneMenu);
						}
						else
						{
							y = 8;
							mvwprintw(ZoneMenu, 9, 1, "                                                             ");
							mvwprintw(ZoneMenu, 9, 1, "%i Joueur(s) ? Confirmer avec [ENTREE]", y-4);
							wmove(ZoneMenu, y, 2);
							wrefresh(ZoneMenu);
						}
						break;	
			case KEY_DOWN : 
						if (y < 8)
						{
							y++;
							mvwprintw(ZoneMenu, 9, 1, "                                                             ");
							mvwprintw(ZoneMenu, 9, 1, "%i Joueur(s) ? Confirmer avec [ENTREE]", y-4);
							wmove(ZoneMenu, y, 2);
							wrefresh(ZoneMenu);
						}
						else
						{
							y = 5;
							mvwprintw(ZoneMenu, 9, 1, "                                                             ");
							mvwprintw(ZoneMenu, 9, 1, "%i Joueur(s) ? Confirmer avec [ENTREE]", y-4);
							wmove(ZoneMenu, y, 2);
							wrefresh(ZoneMenu);
						}
						break;	
		} 
	} while (ch != 10);
	if (NbJoueurs == 0)
		NbJoueurs = y - 4;	
}


 	
void EntrerPseudo()
{
	int i, j;
	keypad(ZoneMenu, TRUE);
	echo(); 
	/* On remet l'affichage des touches saisies piur facilite l'entrée du pseudo */
	for ( i = 0; i < NbJoueurs; i++)
	{	
		wclear(ZoneMenu);
		mvwprintw(ZoneMenu, 2, 6, "Joueur %i : ", i+1);
		mvwprintw(ZoneMenu, 3, 6, "Entrez votre Pseudo (moins de 10 caractères)");
		wmove(ZoneMenu, 4, 6);
		wrefresh(ZoneMenu);
		wscanw(ZoneMenu, "%s", PseudoJ[i]);
		while (strlen(PseudoJ[i]) > 10)
		{
			mvwprintw(ZoneMenu, 3, 6, "Pseudo de plus de 10 caractères, recommencez la saisie");
			wmove(ZoneMenu, 4, 6);
			wrefresh(ZoneMenu);
			wscanw(ZoneMenu, "%s", PseudoJ[i]);
		}
		while (strlen(PseudoJ[i]) < 1)
		{
			mvwprintw(ZoneMenu, 3, 6, "Un pseudo contient au moins un caractère, recommencez la saisie");
			wmove(ZoneMenu, 4, 6);
			wrefresh(ZoneMenu);
			wscanw(ZoneMenu, "%s", PseudoJ[i]);
		}
		for( j = 0; j < i; j++)
		{
			while(!strcmp(PseudoJ[i],PseudoJ[j]))
			{
				mvwprintw(ZoneMenu, 3, 6, "Vous ne pouvez pas choisir le même pseudo qu'un autre utilisateur");
				mvwprintw(ZoneMenu, 4, 6,"          "); 
				wmove(ZoneMenu, 4, 6);
				wrefresh(ZoneMenu);
				wscanw(ZoneMenu, "%s", PseudoJ[i]);
			}
		}
		
	}
	noecho();
	/* On recache les touches saisies */
}

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

void Menu()
{
	int y, x, ch;
	int isRelancer;
	ZoneMenu = CreerFenetre(15,90,(LINES-15)/2,(COLS-90)/2);
	
	keypad(ZoneMenu, TRUE); //Permet l'utilisation des touches directionnelles

	mvwprintw(ZoneMenu, 5, 30,  "[   ] Nouvelle Partie ?");
	mvwprintw(ZoneMenu, 6, 30,  "[   ] Reprendre une partie.");
	mvwprintw(ZoneMenu, 7, 30,  "[   ] Voir les règles.");
	mvwprintw(ZoneMenu, 8, 30,  "[   ] Afficher les Highscores.");
	mvwprintw(ZoneMenu, 9, 30,  "[   ] Quitter le jeu.");
	wmove(ZoneMenu, 5, 32);
	wrefresh(ZoneMenu);
	
	y = 5;
	x = 32;
	do 
	{			
		ch = wgetch(ZoneMenu);
		switch (ch)
		{
			case KEY_DOWN :
				if ( y == 9)
				{
					y = 5;
					wmove(ZoneMenu, y, x);
					wrefresh(ZoneMenu);

				}
				else
				{
					y++;
					wmove(ZoneMenu, y, x);
					wrefresh(ZoneMenu);			
				}
				break;
		
				
			case KEY_UP :
				if ( y > 5)
				{
					y--;
					wmove(ZoneMenu, y, x);
					wrefresh(ZoneMenu);

				}
				else
				{
					y = 9;
					wmove(ZoneMenu, y, x);
					wrefresh(ZoneMenu);			
				}
				break;
		
					
		}
	wrefresh(ZoneMenu);	
	} while ( ch != 10 );	
	/* On valide la selection avec la touche entree */
	switch(y)
	{
		case 5 :
			EntrerNbJoueur(); 
			EntrerPseudo(); 
			DemandeAide(); DetruireFenetre(ZoneMenu); 
			do 
			{ 
				Initialisation(); 
				Partie(); 
				Resultat(&isRelancer); 
			} while (isRelancer);
			 break;
		case 6 : DetruireFenetre(ZoneMenu);
			if (Charger())
			{
				do 
				{ 
					Partie(); 
					Resultat(&isRelancer);
				} while ( isRelancer );
			}
				break;
		case 7 : DetruireFenetre(ZoneMenu); Regles(); break;
		case 8 : break;
		case 9 : DetruireFenetre(ZoneMenu); FinDePartie(); break;
	}
}

void ChargementAffichage()
/* Met à jour l'affichage du tableau des scores */
/* Ne fait rien si la partie n'a pas été chargée à partir d'un fichier */
{
	int i;
	int j;
	int x, y, ch;	
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
	mvwprintw(ZoneMessage, 2,2 ,"WESH JE SUIS DANS LE CHARGEMENT FRERO");
	wrefresh(ZoneMessage);
}

int main(){	
	int ch;
	initscr();
	cbreak();
	noecho();
	refresh();
	EcranTitre();
	do
	{
		Menu();
	} while (1);
	
}
