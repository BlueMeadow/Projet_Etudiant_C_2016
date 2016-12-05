



void FinDePartie()
{	
	WINDOW * ZoneResultat;
	ZoneResultat = CreerFenetre(20, 50,(LINES - 20)/2, (COLS - 50)/2);
	int Prime[nb_joueur];
	int Total[nb_joueur];
	char Vainqueur[4][10];
	int i, j;
	int max;
	


	for (i = 0 ; i < nb_joueur ; i++)
	{
		Total[i] = 0;
		Prime[i] = 0;
		for (j = 0 ; j < 6 ; j++)
		{
			Total[i] + = Score[i][j];
		}
		if (Total[i] > 62) 
		{
			Prime[i] = 1;
			Total[i] + = 35;
		}	
		for (j = 6 ; j < 12 ; j++)
		{
			Total[i] + = Score[i][j];
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
			strcpy(Vainqueur[j], pseudo_j[j]);
		}
	}
	

	wattron(ZoneResultat, A_REVERSE);
	mvwprintw(ZoneResultat, 13, 18, "TABLEAU DE SCORES");
	wattroff(ZoneResultat, A_REVERSE);
	mvwprintw(ZoneResultat, 10, 5, "%s : %i", pseudo_j[0], Total[0]);
	mvwprintw(ZoneResultat, 11, 5, "%s : %i", pseudo_j[1], Total[1]);
	mvwprintw(ZoneResultat, 12, 5, "%s : %i", pseudo_j[2], Total[2]);
	mvwprintw(ZoneResultat, 13, 5, "%s : %i", pseudo_j[3], Total[3]);
	
	wattron(ZoneResultat, A_REVERSE);
	mvwprintw(ZoneResultat, 15, 20, "VAINQUEUR");
	wattroff(ZoneResultat, A_REVERSE);
	for (i = 0 ; i < j ; i++)
	{
		mvwprintw(ZoneResultat, 17+i, (20-strlen(Vainqueur[i])/2, "%s", Vainqueur[i]);
	}
	wrefresh(ZoneResultat);
		
}	
	
