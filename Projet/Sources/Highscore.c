#include "../include/Global.h"



void Tri(int iTab[5], char cTab[5][10])
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
{
	int i = 1;
	HighScore = fopen("Highscore", "r");
	
	if (HighScore == NULL)
	{
		HighScore = fopen("Highscore", "w+");
		fprintf(HighScore, "AAA 0 BBB 0 CCC 0 DDD 0 EEE 0 ");
		/* Etat de base du fichier Highscore */
		/* Pseudos bloqués dans EntrerPseudo() */
		fclose(HighScore);
		HighScore = fopen("Highscore", "r");
	}

	rewind(HighScore);
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

int VerifHS(int NbJoueurs, int Total[NbJoueurs])
{
	FILE * HighScore = NULL;
	int i, j, ch;
	char PseudoHS[5][10];
	int HS[5];

	mvwprintw(ZoneResultat, 1,1, "Avant la lecture");
	wrefresh(ZoneResultat);
	ch = wgetch(ZoneResultat);

	LectureHS(HighScore, PseudoHS, HS);

	mvwprintw(ZoneResultat, 1,1, "Après la lecture");
	wrefresh(ZoneResultat);
	ch = wgetch(ZoneResultat);

	for ( i = 0 ; i < NbJoueurs ; i++)
	{
		mvwprintw(ZoneResultat, 1,1, "Dans le for : i = %i", i);
		wrefresh(ZoneResultat);
		ch = wgetch(ZoneResultat);

		for ( j = 0 ; j < 5 ; j++)
		{
			mvwprintw(ZoneResultat, 1,1, "Dans le for : j = %i", j);
			wrefresh(ZoneResultat);
			ch = wgetch(ZoneResultat);
			mvwprintw(ZoneResultat, 1,1, "HS[0] =  %i", HS[0]);
			wrefresh(ZoneResultat);
			ch = wgetch(ZoneResultat);
			mvwprintw(ZoneResultat, 1,1, "Total[0] = %i", Total[0]);
			wrefresh(ZoneResultat);
			ch = wgetch(ZoneResultat);

			wrefresh(ZoneResultat);
			ch = wgetch(ZoneResultat);
			
			if ( HS[j] < Total[i] )
			{
				mvwprintw(ZoneResultat, 1,1, "Dans le if");
				wrefresh(ZoneResultat);
				ch = wgetch(ZoneResultat);
				mvwprintw(ZoneResultat, 1,1, "HS[%i] =  %i",j,  HS[j]);
				wrefresh(ZoneResultat);
				ch = wgetch(ZoneResultat);
				mvwprintw(ZoneResultat, 1,1, "Total[%i] = %i", i, Total[i]);
				wrefresh(ZoneResultat);
				ch = wgetch(ZoneResultat);
				return 1;
			}
		}
	}
	
	return 0;
}


int AffichageHS()
{
	FILE * HighScore = NULL;
	WINDOW * ZoneHighScore;
	ZoneHighScore = CreerFenetre(28,60,(LINES-28)/2, (COLS-60)/2);
	keypad(ZoneHighScore, TRUE);

	int i, ch;
	char PseudoHS[5][10];
	int HS[5];
	wattron(ZoneHighScore, A_REVERSE);
	mvwprintw(ZoneHighScore, 4, (60-9)/2, "HIGHSCORE");
	wattroff(ZoneHighScore, A_REVERSE);
	mvwprintw(ZoneHighScore, 7, (60-31)/2, "Bienvenue au panthéon des héros");

	LectureHS(HighScore, PseudoHS, HS);

	for (i = 0 ; i < 5 ; i++)
	{
		/*if (!strcmp(PseudoHS[i], "AAA"))
			break;*/
		/* Empeche d'afficher les placeholders */ 
		mvwprintw(ZoneHighScore, 12+2*i, 18, "%s", PseudoHS[i]);
		mvwprintw(ZoneHighScore, 12+2*i, 29, "|");
		mvwprintw(ZoneHighScore, 12+2*i, 32, "%i",HS[i]);
		
	}
	mvwprintw(ZoneHighScore, 26, 8, "Appuyez sur une touche pour revenir au menu");
	wrefresh(ZoneHighScore);
	ch = wgetch(ZoneHighScore);
	DetruireFenetre(ZoneHighScore);
	return 1;
}

void EcritureHS(char PseudoJ[4][10], int Total[4])
{
	FILE * HighScore = NULL;
	int i, j;
	char PseudoHS[5][10];
	int HS[5];
	
	LectureHS(HighScore, PseudoHS, HS);
	
	for ( j = 0 ; j < 4 ; j++)
	{
		if (Total[j] > HS[4])
		/* Remplace le dernier élément du tableau */
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

