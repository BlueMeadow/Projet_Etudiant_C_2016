#include "../include/Global.h"

/**
* \file Lancer.c
* \brief Gère les lancers de dés
* \author Benoit Combasteix, Simon Fernandes et Nathan OUALET
* \version 1.0
*/


void Lancer()
/* \fn Lancer()
* \Brief Simule un lancer aléatoire de 5 dés à six faces
*/
{
	noecho();
	srand(time(0));
	int ch;

	/** Sélection */

	do
	{
	Nettoyer(ZoneMessage, 4, 2, 6, 68);
	mvwprintw(ZoneMessage, 2, 2, "Appuyez sur [ENTREE] pour lancer les dés.");
	mvwprintw(ZoneMessage, 5, 2, "Vous pouvez sauvegarder et quitter en appuyant sur [S]");
	wrefresh(ZoneMessage);
	
		ch = getch();
		ActiverAide(ch); /**< Permet d'activer/désactiver l'aide avant de lancer le dé */
	
		if ( ch == 's' ) /**< Permet sauvegarder la partie avant de lancer le dé */
		{
			Sauvegarder();
			Nettoyer(ZoneMessage, 5, 2, 5, 68);
			mvwprintw(ZoneMessage, 5, 2, "Appuyez sur [Q] pour quitter ou sur une autre touche pour continuer");
			ch = wgetch(ZoneMessage);
			if ( tolower(ch) == 'q' )			
				FinDePartie();	
		}

		if (ch == 10)  /**< Appuyer sur [ENTREE] lance les dés */
		Nettoyer(ZoneMessage, 5, 2, 5, 68);

	} while (ch != 10 && tolower(ch) != 's');

	/** Lancement des dés */

	for(int i = 0; i < 5; i++)
	{
		if(Garde[i] == 0) /**< Empeche de lancer un dé gardé, sert lors des seconds et troisièmes lancers */
		{	
			De[i] = rand()%6+1;			
		}
		CalculOccurrences(); /**< Calcul le nombre d'occurrences de chaque valeur */
		Garde[i]=0; /**< Libère les dés */
	}
	Aide(isAide, Joueur); /**< Affiche l'aide ( ou non ) en focntion des combinaisons de dés */
	wrefresh(ZoneMessage);
}


void Garder(WINDOW *Fenetre, int Garde[5])
/* \fn Lancer()
* \Brief Simule un lancer aléatoire de 5 dés à six faces
*/
{
	int y, x, ch;
	y = 5; 
	x = 14;
	keypad(Fenetre, TRUE); 
	
	wmove(Fenetre, y, x);
	wrefresh(Fenetre);
	do 
	{
		ch = wgetch(Fenetre);
		ActiverAide(ch);
		switch (ch)
		{
			case KEY_UP:  
				if ( y == 5 ) /**< Si on est en haut, on passe en bas */
				{
					y = 25;
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else /**< Sinon on monte d'une case */
				{
					y-=5;
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				break;
			case KEY_DOWN:
				if ( y == 25 )/**< Si on est en bas, on remonte en haut */
				{
					y = 5;
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else /**< Sinon on descend d'une case */
				{
					y+=5;
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				break;
			case 32: /**< [ESPACE] indique si on veut garder le de ou non */
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
	} while ( ch != 10 );	/**<  [ENTREE] valide la sélection avec la touche entrée */
}

void CalculOccurrences()
/* \fn CalculOccurrences()
* \brief Calcule le nombre d'occurrences de chaque valeur de dé
*/
{

	int i;
	for( i = 0; i < 6 ; i++)
		Occurrences[i] = 0;

	for( i = 0; i < 5 ; i++)
	{
		Occurrences[De[i]-1]++;
	}
}

