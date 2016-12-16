
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
		DetruireFenetre(ZoneChargement);
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
}
