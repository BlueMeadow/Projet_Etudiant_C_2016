#include "../include/Global.h"

/**
* \file Highscore.c
* \brief Gère la lecture, l'affichage et la lecture des Highscores
* \author Benoit Combasteix, Simon Fernandes et Nathan OUALET
* \version 1.0
*/

void Tri(int iTab[5], char cTab[5][10])
/* \fn Tri(int iTab[5], char cTab[5][10])
* \brief Trie un tableau d'entier dans l'ordre décroissant et effectue les même permutation sur le tableau de caratères correspondant 
* \param iTab Tableau de 5 entiers
* \param cTab Tableau de 5 chaines de caractères
*/
{
	int i, j, iTemp, ok;
	char cTemp[10];	
	for ( i = 1 ; i < 5 ; i++)
	{
		j = i;
		ok = 0;
		while (j>0 && !ok)
		{
			ok = (iTab[j] <= iTab[j-1]); 
			if(!ok)            
			{                   
				iTemp = iTab[j];
				strcpy(cTemp, cTab[j]) ;
				iTab[j] = iTab[j-1];
				strcpy(cTab[j], cTab[j-1]); 
				iTab[j-1] = iTemp;
				strcpy(cTab[j-1], cTemp);				    
				j--; 
			} 
		} 
	}
}


int LectureHS(FILE * HighScore, char PseudoHS[5][10], int HS[5])
/* \fn LectureHS(FILE * HighScore, char PseudoHS[5][10], int HS[5])
* \brief Ouvre le fichier des Highscores et récupère leur valeur 
* \param HighScore Un fichier 
* \param PseudoHS Un tableau de 5 chaines de caractères contenant les pseudos des highscorers
* \param HS Un tableau de 5 entiers contenant les highscores 
*/
{
	int i = 1;

	/** Ouverture du fichier */

	HighScore = fopen("Highscore", "r");
	
	if (HighScore == NULL) /**< Création du fichier s'il n'existe pas */
	{
		HighScore = fopen("Highscore", "w+");
		fprintf(HighScore, "AAA 0 BBB 0 CCC 0 DDD 0 EEE 0 ");/**< Etat de base du fichier Highscore. Pseudos bloqués dans EntrerPseudo() */
		fclose(HighScore);
		HighScore = fopen("Highscore", "r");
	}

	/** Récupération des données */

	fscanf(HighScore, "%s ", PseudoHS[0]); 
	fscanf(HighScore, "%i ", &HS[0]);
	while (!feof(HighScore))
	{

		fscanf(HighScore, "%s ", PseudoHS[i]);
		fscanf(HighScore, "%i ", &HS[i]);
		i++;		
	}
	fclose(HighScore);
	return 1;
}

int VerifHS(int Total[4])
/* \fn VerifHS(int Total[4])
* \brief Vérifie si les résultats de fin de partie peuvent être entrés comme highscores
* \param Total Le tableau des scores de la fin de la partie
* \return VRAI s'il y a un nouveau highscore dans Total, 0 sinon
*/
{
	FILE * HighScore = NULL;
	int i, j;
	char PseudoHS[5][10];
	int HS[5];

	LectureHS(HighScore, PseudoHS, HS);
	
	for ( i = 0 ; i < NbJoueurs ; i++)
	{
		for ( j = 0 ; j < 5 ; j++)
		{			
			if ( HS[j] < Total[i] )				
				return 1;
		}
			
	}
	
	return 0;
}


int AffichageHS()
/* \fn AffichageHS()
* \brief Vérifie si les résultats de fin de partie peuvent être entrés comme highscores
* \param Total Le tableau des scores de la fin de la partie
* \return VRAI s'il y a un nouveau highscore dans Total, 0 sinon
*/
{
	FILE * HighScore = NULL;
	WINDOW * ZoneHighScore;
	ZoneHighScore = CreerFenetre(28,60,(LINES-28)/2, (COLS-60)/2);
	keypad(ZoneHighScore, TRUE);

	int i;
	char PseudoHS[5][10];
	int HS[5];

	/** Affichage ncurses */
	wattron(ZoneHighScore, A_REVERSE);
	mvwprintw(ZoneHighScore, 4, (60-9)/2, "HIGHSCORE");
	wattroff(ZoneHighScore, A_REVERSE);
	mvwprintw(ZoneHighScore, 7, (60-31)/2, "Bienvenue au panthéon des héros");

	/** Lecture des highscores */
	LectureHS(HighScore, PseudoHS, HS);


	/** Ecriture des highscores à l'écran */
	for (i = 0 ; i < 5 ; i++)
	{
		if (!strcmp(PseudoHS[i], "AAA"))/**< Empeche d'afficher les placeholders */ 
			break;
		
		mvwprintw(ZoneHighScore, 12+2*i, 18, "%s", PseudoHS[i]);
		mvwprintw(ZoneHighScore, 12+2*i, 29, "|");
		mvwprintw(ZoneHighScore, 12+2*i, 32, "%i",HS[i]);
		
	}
	mvwprintw(ZoneHighScore, 26, 8, "Appuyez sur une touche pour revenir au menu");
	wrefresh(ZoneHighScore);
	wgetch(ZoneHighScore);
	DetruireFenetre(ZoneHighScore);
	return 1;
}

void EcritureHS(char PseudoJ[4][10], int Total[4])
/* \fn EcritureHS(char PseudoJ[4][10], int Total[4])
* \brief Modifie le fichier avec les nouveaux highscores
* \param PseudoJ Le tableau contenant les pseudos des joueurs de cette partie
* \param Total Le tableau des scores de la fin de la partie
* \return VRAI s'il y a un nouveau highscore dans Total, 0 sinon
*/
{
	FILE * HighScore = NULL;
	int i, j;
	char PseudoHS[5][10];
	int HS[5];

	LectureHS(HighScore, PseudoHS, HS);
	
	/** Vérifie chaque score */
	for ( j = 0 ; j < 4 ; j++) 
	{
		if (Total[j] > HS[4]) /**< Remplace le plus petit highscore */
		{
			HS[4] = Total[j];
			strcpy(PseudoHS[4], PseudoJ[j]);
			Tri(HS, PseudoHS);
		}		
	}
	HighScore = fopen("Highscore", "w+");
	for(i = 0 ; i < 5 ; i++)
	{
		fprintf(HighScore, "%s %i ", PseudoHS[i], HS[i]);
	}
	fclose(HighScore);
}

