#include "../include/Global.h"

void ChainePseudo(char Pseudos[40])
{
	int i, esp1, esp2, esp3, esp4;
	strcpy(Pseudos, "");
	/* Vide la chaîne, evite les seg fault si on relance une partie et qu'on a déjà des pseudos dedans*/
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

int Initialisation()
{
	int i, j;
	for (i = 0 ; i < 4 ; i++)
	{
		for (j = 0 ; j < 13 ; j++)
		{
			Score[i][j] = -1;
		}
		Prime[i] = -1;
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
	Joueur = 0;
	NbTours = 0;
	NbLancers = 1;
	return 1;
}

void EntrerNbJoueur()
{
	int y, ch;
	keypad(ZoneMenu, TRUE);
	noecho();
	y = 5;
	NbJoueurs = 0;
	Nettoyer(ZoneMenu, 1, 1 , 13, 88);

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
	int i, j = 0, k, ch;
	char temp[10]="";
	keypad(ZoneMenu, TRUE);
	echo(); 
	/* Remet l'affichage des touches saisies pour faciliter l'entrée du pseudo */
	for ( i = 0; i < NbJoueurs; i++)
	{	
		Nettoyer(ZoneMenu, 1, 1 , 12, 87);
		mvwprintw(ZoneMenu, 2, 6, "Joueur %i : ", i+1);
		mvwprintw(ZoneMenu, 3, 6, "Entrez votre Pseudo (entre 3 et 10 caractères)");
		wmove(ZoneMenu, 4, 6);
		wrefresh(ZoneMenu);

		do	
		{
			ch = wgetch(ZoneMenu);
			mvwprintw(ZoneMenu, 8, 6, "%i", strlen(temp));
			mvwprintw(ZoneMenu, 9,6, "%s", temp);
			wmove(ZoneMenu, 4,7+j);
			wrefresh(ZoneMenu);
			if ( ch == 32 )
				ch = '_';
			if ( ch == 10 )
				break;
			if ( j < 10 )
				temp[j] = ch;
			j++;
		} while (1);			
		

		/* Vérification des conditions d'entrée du pseudo */

		while (strlen(temp) > 10)
		{
			j = 0;
			memset(temp, '\0', 10);
			/* Vide complètement la chaine de catactères */
			mvwprintw(ZoneMenu, 3, 6, "Pseudo de plus de 10 caractères, recommencez la saisie");
			
			Nettoyer(ZoneMenu, 4, 6 , 4, 16);
			wmove(ZoneMenu, 4, 6);
			wrefresh(ZoneMenu);
			do	
			{
				ch = wgetch(ZoneMenu);
				if ( ch == 32 )
					ch = '_';
				if ( ch == 10 )
					break;
				if ( j < 10 )				
					temp[j] = ch;
				j++;
			} while (1);	
		}
		while (strlen(temp) < 3)
		{
			j = 0;
			memset(temp, '\0', 10);
			mvwprintw(ZoneMenu, 3, 6, "Pseudo de moins de 3 caractères, recommencez la saisie");
			Nettoyer(ZoneMenu, 4, 6 , 4, 16);
			wmove(ZoneMenu, 4, 6);
			wrefresh(ZoneMenu);
			do	
			{
				ch = wgetch(ZoneMenu);
				if ( ch == 32 )
					ch = '_';
				if ( ch == 10 )
					break;
				if ( j < 10 )
					temp[j] = ch;
				j++;
			} while (1);	
		}
		while(!strcmp(temp,"AAA") || !strcmp(temp,"BBB") || !strcmp(temp,"CCC") || !strcmp(temp,"DDD") || !strcmp(temp,"EEE"))
		/* Pseudos utilisés par le fichier des Highscores */
		{	
			j = 0;
			memset(temp, '\0', 10);
			mvwprintw(ZoneMenu, 3, 6, "Ce pseudo est utilisé par le programme, recommencez la saisie");
			Nettoyer(ZoneMenu, 4, 6 , 4, 16);
			wmove(ZoneMenu, 4, 6);
			wrefresh(ZoneMenu);
			
			do	
			{
				ch = wgetch(ZoneMenu);
				if ( ch == 32 )
					ch = '_';
				if ( ch == 10 )
					break;
				if ( j < 10 )
					temp[j] = ch;
				j++;
			} while (1);	
		}
		for( k = 0 ; k < i ; k++)
		/* Compare aux pseudos précédents */
		{
			while(!strcmp(temp, PseudoJ[k]))
			{
				j = 0;
				memset(temp, '\0', 10);
				mvwprintw(ZoneMenu, 3, 6, "Ce pseudo est utilisé par un autre joueur, recommencez la saisie");
				Nettoyer(ZoneMenu, 4, 6 , 4, 16);
				wmove(ZoneMenu, 4, 6);
				wrefresh(ZoneMenu);
				do	
				{
					ch = wgetch(ZoneMenu);
					if ( ch == 32 )
						ch = '_';
					if ( ch == 10 )
						break;
					if ( j < 10 )
						temp[j] = ch;
					j++;
				} while (1);	
			}
		}
		strcpy(PseudoJ[i], temp);
		/* Le pseudo remplit les conditions d'entrée */
		j = 0;
		memset(temp, '\0', 10);
		/* temp réinitialisé pour le prochain */
	}
	noecho();
	/* Recache les touches saisies */
}

void DemandeAide()
{
	int i, ch;
	keypad(ZoneMenu, TRUE);
	noecho(); 

	wmove(ZoneMenu, 1, 1);
	for (i = 0 ; i < NbJoueurs ; i++)
	{
		Nettoyer(ZoneMenu, 2, 2, 13, 88);
		mvwprintw(ZoneMenu, 2, 2, "Joueur %s : ", PseudoJ[i]);
		mvwprintw(ZoneMenu, 3, 2, "Voulez-vous afficher l'aide ? [O/N]");
		mvwprintw(ZoneMenu, 4, 2, "(Vous pourrez l'afficher ou la cacher pendant la partie à tout moment)");
		wrefresh(ZoneMenu);
		do
		{
			ch=wgetch(ZoneMenu);
		} while(tolower(ch) != 'o' && tolower(ch) != 'n');

		if (tolower(ch) == 'n') isAide[i] = 0;
		else isAide[i] = 1;

	}
}

void ActiverAide(int i)
{
	if ( tolower(i) == 'h' )
		isAide[Joueur] = (isAide[Joueur]+1)%2;
	Aide();
}
