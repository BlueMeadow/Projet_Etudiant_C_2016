#include "../include/Global.h"

void Lancer()
{
	noecho();
	srand(time(0));
	int ch;
	do
	{
	Nettoyer(ZoneMessage, 4, 2, 6, 68);
	mvwprintw(ZoneMessage, 2, 2, "Appuyez sur [ENTREE] pour lancer les dés.");
	mvwprintw(ZoneMessage, 5, 2, "Vous pouvez sauvegarder et quitter en appuyant sur [S]");
	wrefresh(ZoneMessage);
	
		ch = getch();
		ActiverAide(ch);
	
		if (ch == 10)
		Nettoyer(ZoneMessage, 5, 2, 5, 68);

		if ( ch == 's' )
		{
			Sauvegarder();
			Nettoyer(ZoneMessage, 5, 2, 5, 68);
			mvwprintw(ZoneMessage, 5, 2, "Appuyez sur [Q] pour quitter ou sur une autre touche pour continuer");
			ch = wgetch(ZoneMessage);
			if ( tolower(ch) == 'q' )			
				FinDePartie();	
		}


	} while (ch != 10 && tolower(ch) != 's');

	for(int i = 0; i < 5; i++)
	{
		if(Garde[i] == 0)
		{	
			De[i] = rand()%6+1;			
		}
		CalculOccurrences();
		Garde[i]=0;	
	}
	Aide(isAide, Joueur);
	wrefresh(ZoneMessage);
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
		ActiverAide(ch);
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

