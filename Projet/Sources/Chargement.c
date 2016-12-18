#include "../include/Global.h"


void Sauvegarder()
{
	FILE * Sauvegarde = NULL;
	int i;
	int j;
	char NomFichier[7] = "sav_";
	char temp[4]; /* Garde le début du nom de fichier après modifcation */
	char NumSav[3]; /* Jusqu'à 99 sauvegardes */

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
		fprintf(Sauvegarde, " %s %i %i", PseudoJ[i], isAide[i], Prime[i]);
		for (j = 0; j < 13; j++)
		{
			fprintf(Sauvegarde, " %i", Score[i][j]);
		}
	}

	fclose(Sauvegarde);
	mvwprintw(ZoneMessage, 4, 2, "Votre sauvegarde est la numéro %c%c", NumSav[0],NumSav[1]);
}

int Charger()
{
	FILE * Sauvegarde = NULL;
	int i;
	int j;
	int y = 1, x = 0, ch;
	int NbSav = 0;
	char SavTable[100][3];
	char NomFichier[10] = "sav_";
	char temp[4]; 
	/* Garde le début du nom de fichier après modifcation */
	char NumSav[3]; 
	/* Jusqu'à 99 sauvegardes */	

	strcpy(temp, NomFichier);
	NumSav[2] = '\0';

	WINDOW * ZoneChargement;
	
	int Hauteur = (LINES-40)/2;
	int Longueur = (COLS-85)/2;
	ZoneChargement = CreerFenetre(48, 85, Hauteur, Longueur);

	/* Recherche des sauvegardes */

	for ( i = 1 ; i < 100 ; i++ )
	{
		NumSav[1] = i%10+48; 
		/* Code ASCII du chiffre des unités */
		NumSav[0] = i/10+48; 	
		/* Code ASCII du chiffre des dizaines */

		strcat(NomFichier, NumSav);
		/* Donne le nom du fichier à rechercher */
		Sauvegarde = fopen(NomFichier, "r");
		/* Vérification de l'existence */
		if ( Sauvegarde != NULL )
		{	
			strcpy(SavTable[NbSav], NumSav);
			wrefresh(ZoneChargement);
			NbSav++;
			fclose(Sauvegarde);
		}
		strcpy(NomFichier, temp);
	}
			

	/* Affichage Ncurses */
	
	
	
	keypad(ZoneChargement, TRUE);
	mvwprintw(ZoneChargement, 2, (Longueur-17)/2, "Sélectionnez la sauvegarde à charger");
	if (!NbSav) 
	{
		mvwprintw(ZoneChargement, 2, (Longueur-34)/2, "Il n'y a pas de sauvegarde à charger");
		mvwprintw(ZoneChargement, 4, 16, "Appuyez sur une touche pour revenir au menu");
		wgetch(ZoneChargement);
		DetruireFenetre(ZoneChargement);
		return 0;
	}
	else
	{	
		y = 0;
		x = 0;
		for ( i = 0 ; i < NbSav ; i++)
		{

			mvwprintw(ZoneChargement, 7+y, 4+28*x, "[   ] Sauvegarde n°%s", SavTable[i]);
			y++;
			if ( y > 32 )
			{
				y-=33;
				x++;
			}
		}
	}
	wrefresh(ZoneChargement);

		/* Sélection de la sauvegarde */
	y = 0;
	x = 0;
	wmove(ZoneChargement, 7+y, 6+28*x);
	wrefresh(ZoneChargement);
	do
	{
		ch = wgetch(ZoneChargement);

		switch(ch)
		{
			case KEY_DOWN : if ( ((y+1)+x*33) < NbSav )
					/* Empeche de se placer sur des sauvegardes inexistantes */
					{
						y++;
						if ( y > 32 )
						{
							y-=33;
							x++;
						}
					}
					break;
			case KEY_UP : if ( y > 0 )
					/* Empeche de se placer sur des sauvegardes inexistantes */
					{
						y--;
						if ( y < 1 && x > 0)
						{
							y+=33;
							x--;
						}
					}
					break;
		}		
		wmove(ZoneChargement, 7+y, 6+28*x);
		wrefresh(ZoneChargement);
			

	} while (ch != 10);
		
		/* Selection de la sauvegarde */
	
	strcpy(NomFichier, temp);
	
	strcat(NomFichier, SavTable[y]);
	
	Sauvegarde = fopen(NomFichier, "r");
	fscanf(Sauvegarde, "%i %i %i %i", &NbJoueurs, &Joueur, &NbTours, &NbLancers);
	for (i = 0; i < NbJoueurs; i++)
	{
		fscanf(Sauvegarde, " %s %i %i", PseudoJ[i], &isAide[i], &Prime[i]);
		for (j = 0; j < 13; j++)
		{
			fscanf(Sauvegarde, " %i", &Score[i][j]);
		}
	}

	fclose(Sauvegarde);
	DetruireFenetre(ZoneChargement);	
		
		return 1;
}




void ChargementAffichage()
/* Met à jour l'affichage du tableau des scores */
/* Ne fait rien si la partie n'a pas été chargée à partir d'un fichier */
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
