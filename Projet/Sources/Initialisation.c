#include "../lib/Global.h"

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
		isAide[i] = 0;
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
	y = 5;
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
	int i;
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
		while(!strcmp(PseudoJ[i],"AAA") || !strcmp(PseudoJ[i],"BBB") || !strcmp(PseudoJ[i],"CCC") || !strcmp(PseudoJ[i],"DDD") || !strcmp(PseudoJ[i],"EEE"))
		{
			mvwprintw(ZoneMenu, 3, 6, "Ce pseudo est utilisé par le système, recommencez la saisie");
			wmove(ZoneMenu, 4, 6);
			wrefresh(ZoneMenu);
			wscanw(ZoneMenu, "%s", PseudoJ[i]);
		}
	}
	noecho();
	/* On recache les touches saisies */
}

void DemandeAide()
{
	int i, ch;
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


