void Resultat()
{	

	
	int nb_joueur = 4;
	int Total[nb_joueur];
	int ch;
	char Vainqueur[4][10];
	int i, j;
	int max;

	for (i = 0 ; i < nb_joueur ; i++)
	{
		Total[i] = 0;
		Prime[i] = 0;
		for (j = 0 ; j < 6 ; j++)
		{
			Total[i] += Score[i][j];
		}
		if (Total[i] > 62) 
		{
			Total[i] += 35;
		}	
		for (j = 6 ; j < 12 ; j++)
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
	mvwprintw(ZoneResultat, 15+j, 6, "Appuyez sur [ENTREE] pour relancer une partie ou sur Q pour revenir au menu");
	do
	{
		ch = wgetch(ZoneResultat);
	} while ( ch != 10 || tolower(ch) != 'q');
	switch (ch)
	{
		case 10 : Partie(); break;
		case q :
		case Q : Menu();
	}	
	wrefresh(ZoneResultat);
		
}	
