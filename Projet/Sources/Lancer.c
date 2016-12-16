#include "../lib/Global.h"

void Lancer(int De[5], int Garde[5])
{
	int i, ch;
	/* initialisation des valeurs aléatoires, à chaque tirage */
	srand(time(0));
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

	for( i = 0; i < 5; i++)
	{
		if(Garde[i] == 0)
		{	
			/* lancement des dés et sélection d'un chiffre entre 1 et 6 avec le hasard */
			De[i] = rand()%6+1;
		}
		CalculOccurrences();
		Garde[i]=0;	
	}
	Aide(isAide, Joueur);
}

void Garder(WINDOW *Fenetre, int Garde[5])
{
	int y, x, ch;
	y = 5; /* indice d'ordonnée */
	x = 14; /* indice d'abscisse */
	keypad(Fenetre, TRUE); /* Permet l'utilisation des touches directionnelles */
	
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
	/* parcourt les 5 dés lancés, on incremente le nombre de valeurs trouvés */
	/* dans le tableau d'occurrences correspondant à la valeur du dé */
	int i;
	for( i = 0; i < 6 ; i++)
		Occurrences[i] = 0;

	for( i = 0; i < 5 ; i++){
		Occurrences[De[i]-1]++;
	}
}

