#include "../include/Global.h"

/**
* \file Partie.c
* \brief Rassemble les fonctions principales
* \author Benoit Combasteix, Simon Fernandes et Nathan OUALET
* \version 1.0
*/

void Menu()
/** \fn Menu()
* \brief Permet à l'utilisateur de choisir ce qu'il veut consulter 
*/
{
	int y, x, ch;
	ZoneMenu = CreerFenetre(15,90,(LINES-15)/2,(COLS-90)/2);
	
	keypad(ZoneMenu, TRUE); /**< Permet l'utilisation des touches directionnelles */

	mvwprintw(ZoneMenu, 5, 30,  "[   ] Nouvelle Partie ?");
	mvwprintw(ZoneMenu, 6, 30,  "[   ] Reprendre une partie.");
	mvwprintw(ZoneMenu, 7, 30,  "[   ] Voir les règles.");
	mvwprintw(ZoneMenu, 8, 30,  "[   ] Afficher les Highscores.");
	mvwprintw(ZoneMenu, 9, 30,  "[   ] Quitter le jeu.");
	wmove(ZoneMenu, 5, 32);
	wrefresh(ZoneMenu);
	
	y = 5;
	x = 32;
	do 
	{			
		ch = wgetch(ZoneMenu);
		switch (ch) /**< Permet de se déplacer avec les fleches pour choisir */
		{
			case KEY_DOWN :
				if ( y == 9)
				{
					y = 5;
					wmove(ZoneMenu, y, x);
					wrefresh(ZoneMenu);

				}
				else
				{
					y++;
					wmove(ZoneMenu, y, x);
					wrefresh(ZoneMenu);			
				}
				break;
		
				
			case KEY_UP :
				if ( y > 5)
				{
					y--;
					wmove(ZoneMenu, y, x);
					wrefresh(ZoneMenu);

				}
				else
				{
					y = 9;
					wmove(ZoneMenu, y, x);
					wrefresh(ZoneMenu);			
				}
				break;
		
					
		}
	wrefresh(ZoneMenu);	
	} while ( ch != 10 );	
	/**< Valide la selection avec la touche entree */
	switch(y) /**< exécute l'entrée du menu */
	{
		case 5 :
			EntrerNbJoueur(); 
			EntrerPseudo(); 
			DemandeAide(); 
			DetruireFenetre(ZoneMenu); 
			do 
			{ 
				Initialisation(); 
				Partie(); 
			} while (Resultat());
			 break;
		case 6 :DetruireFenetre(ZoneMenu);
			if (Charger())
			{
				do 
				{ 
					Partie(); 
				} while (Resultat());
			}
				break;
		case 7 : DetruireFenetre(ZoneMenu); Regles(); break;
		case 8 : DetruireFenetre(ZoneMenu); AffichageHS(); break;
		case 9 : DetruireFenetre(ZoneMenu); FinDePartie(); break;
	}
}



int Partie()
/* \fn Partie
* \brief Lance une partie de Yahtzee 
*/
{	
	int ch;
	MiseEnPlace();
	ChargementAffichage();
	while(NbTours < 13*NbJoueurs)
	{
		Aide(isAide, Joueur);
		wattron(ZoneMessage, A_BOLD);
		Nettoyer(ZoneMessage, 1, 2, 8, 87);
		mvwprintw(ZoneMessage,1 ,2 ,"Tour de %s", PseudoJ[Joueur]);
		wattroff(ZoneMessage, A_BOLD);
		Lancer();
		AffichageDe(De);
		Aide(isAide, Joueur);
		do
		{
			if (NbLancers == 3) break; /**< Trois lancers posssibles seulement */
			Nettoyer(ZoneMessage, 2, 2, 8, 87);
			mvwprintw(ZoneMessage,2 ,2 ,"Voulez-vous relancer ? [O/N]");
			wrefresh(ZoneMessage);
			do{
				ch=getch();
			}
			while(tolower(ch) != 'o' && tolower(ch) != 'n');
			if (tolower(ch) == 'n') break; /**< sort de la boucle si on ne relance pas */
			Nettoyer(ZoneMessage, 2, 2, 8, 87);
			mvwprintw(ZoneMessage, 3, 2, "Sélectionnez les dés à garder avec [ESPACE].");
			mvwprintw(ZoneMessage, 4, 2, "Validez avec [ENTREE].");
			wrefresh(ZoneMessage);

			Garder(ZoneDe, Garde); /**< Choix des dés à garder avant de relancer */
			Lancer(); /**< Relance */
			AffichageDe(De);
			Aide(isAide, Joueur);
			NbLancers++;
		
		} while(1); 
		EcrireScore(Joueur); /**< Inscrit le score du joueur */
		NbTours++;
		Joueur = ChangerJoueur(Joueur,NbJoueurs); /**< Passe au joueur suivant */
		NbLancers = 1;
	}
	return 1;
}

int ChangerJoueur(int Joueur, int NbJoueurs)
/* \fn ChangerJoueur(int Joueur, int NbJoueur)
*\ brief Passe au joueur suivant
*/
{
	return ((Joueur+1)%NbJoueurs);
}

void Aide()
/* \fn Aide()
* \brief Affiche (ou non) les combinaisons 
*/
{
	int y=2;
	int x=2;
	int i;
	int temp1=0;
	Nettoyer(ZoneAide, 2, 2, 28, 28);
	attron(A_BOLD);
	mvwprintw(ZoneAide, 2, 13, "AIDE");
	attroff(A_BOLD);
	wrefresh(ZoneAide);
	y+=2;
	
	if( isAide[Joueur] )/**< Affiche l'aide selon le choix de l'utilisateur */
	{ 
		mvwprintw(ZoneAide, y, x, "Pas de combinaison"); /**< Pas de combinaison */
		wrefresh(ZoneAide);
		if(isBrelan()) /**< Si brelan */
		{ 
			for (i = 0 ; i < 6 ; i++)
			{
				if (Occurrences[i] > 2)
				{
					temp1 = i;
					break;
				}
			}
			mvwprintw(ZoneAide, y, x, "Brelan de %i       ", temp1+1); /**< Affiche la valeur des dés formant le brelan */
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isCarre())  /**< Si carré */
		{
			for (i = 0 ; i < 6 ; i++)
			{
				if (Occurrences[i] > 3)
				{
					temp1 = i;
					break;
				}
			}
			mvwprintw(ZoneAide, y, x, "Carre de %i", temp1+1); /**< Affiche la valeur des dés formant le carré */
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isFull()) /**< Si full */
		{
			mvwprintw(ZoneAide, y, x, "Full");
			wrefresh(ZoneAide);
			y+=2;
		} 
		if(isPtSuite()) /**< Si petite suite*/
		{
			mvwprintw(ZoneAide, y, x, "Petite suite     ");
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isGdSuite()) /**< Si grande suite */
		{
			mvwprintw(ZoneAide, y, x, "Grande suite");
			wrefresh(ZoneAide);
			y+=2;
		} 
		if(isYahtzee()) /**< si yahtzee */
		{
			mvwprintw(ZoneAide, y, x, "YAHTZEE !");
			wrefresh(ZoneAide);
			y+=2;
		}
	}
	else
	{
		mvwprintw(ZoneAide, y, x, "L'aide n'est pas activée"); /**< Affiche que l'aide n'est pas activée si c'est le cas */
		wrefresh(ZoneAide);
	}
}


int Resultat()
/* \fn Resultat()
* \brief Calcule et affiche les résultats de chaque joueur, désigne le vainqueur 
* \return VRAI pour relancer une partie
*/
{		
	int Total[4];
	int ch;
	int i, j, y = 0;
	int max;
	DetruireFenetre(ZoneMessage);
	DetruireFenetre(ZoneDe);
	DetruireFenetre(ZoneScore);
	DetruireFenetre(ZoneAide);
	ZoneResultat = CreerFenetre(28,60,(LINES-28)/2, (COLS-60)/2);
	
		/** Calcul du Total des points */

	for (i = 0 ; i < NbJoueurs ; i++)
	{
		Total[i] = 0;
		for (j = 0 ; j < 6 ; j++)
		{
			Total[i] += Score[i][j]; /**< Somme partie haute */
			
		}
		if (Total[i] > 62) /**< Prime de 35 si le score de la partie haute est de 63 ou plus */
		{
			Total[i] += 35;
		}	
		for (j = 6 ; j < 13 ; j++)
		{
			Total[i] += Score[i][j]; /**< Somme partie basse */
		}
		if ( Prime[i] > 0 )
			Total[i] = Total[i] + 100 * (Prime[i]-1); /**< Prime pour chaque Yahtzee supplémentaire */
	}

	/** Affichage ncurses */

	wattron(ZoneResultat, A_REVERSE);
	mvwprintw(ZoneResultat, 2, 16, "TABLEAU DE SCORES");
	wattroff(ZoneResultat, A_REVERSE);
	
	wattron(ZoneResultat, A_REVERSE);
	mvwprintw(ZoneResultat, 11, 20, "VAINQUEUR");
	wattroff(ZoneResultat, A_REVERSE);

	/** Affichage des points de chaque joueur */
	
	for (i = 0 ; i < NbJoueurs ; i++)
	{
		mvwprintw(ZoneResultat, 5+i, 10, "%s : %i", PseudoJ[i], Total[i]);
	}

	/** Ecriture du nom des vainqueurs */

	mvwprintw(ZoneResultat, y+14, (50-strlen(PseudoJ[0]))/2 , "%s", PseudoJ[0] );
	max = Total[0];
	for (i = 1 ; i < NbJoueurs ; i++)
	{
		if ( Total[i] > max ) /**< Si le joueur actuel a un meilleur score que le précédent */
		{
			max = Total[i];
			y = 0;	/**< Place sur la première ligne */
			Nettoyer(ZoneResultat, y+14, 2, y+17, 58); /**< Efface les 3 potentiels joueurs écrits en dessous */			
			mvwprintw(ZoneResultat, y+14, (50-strlen(PseudoJ[i]))/2 , "%s", PseudoJ[i] );/**< Ecrit le nom du "nouveau" vainqueur */		

		}
		else if ( max == Total[i] ) /**< Si le joueur actuel a le même score que le précédent */
		{
			y++; /**< Passe à la ligne suivante */
			mvwprintw(ZoneResultat, y+14, (50-strlen(PseudoJ[i]))/2 , "%s", PseudoJ[i] ); /**< Ecrit le nom du joueur sous le précédent */
		}
	}
	wrefresh(ZoneResultat);

	/** Options de sortie */

	y = 0;
	if ( VerifHS(Total) )
		mvwprintw(ZoneResultat, 20+y, 6, "Appuyez sur [H] pour enregistrer vos Highscores");
	else 
		mvwprintw(ZoneResultat, 20+y, 6, "Dommage, pas de Highscore cette fois");
	mvwprintw(ZoneResultat, 21+y, 6, "Appuyez sur [ENTREE] pour relancer une partie");
	mvwprintw(ZoneResultat, 22+y, 6, "Appuyez sur [M] pour revenir au menu");
	mvwprintw(ZoneResultat, 23+y, 6, "Appuyez sur [Q] pour quitter");
	wrefresh(ZoneResultat);

	do
	{
		ch = wgetch(ZoneResultat);
		if ( tolower(ch) == 'h' && !VerifHS(Total) ) /**< Empeche d'écrire les highscores s'il n'y en a pas de nouveau */
			ch = 48;		
		switch (tolower(ch))
		{
			case 'h' : EcritureHS(PseudoJ, Total); break;
			case 10 :Initialisation(); DetruireFenetre(ZoneResultat); return 1;
			case 'q' : FinDePartie(); break;
			case 'm' : DetruireFenetre(ZoneResultat); return 0;		
		}
	} while (ch != 'h');
	
	Nettoyer(ZoneResultat, 20+y, 5, 20+y, 57);
	mvwprintw(ZoneResultat, 20+y, 6, "Consultez vos highscores depuis le menu !");/**< Affiche un nouveau menu si les highscores sont entrés */
	wrefresh(ZoneResultat);

	do
	{
		ch = wgetch(ZoneResultat);
		switch (tolower(ch))
		{
			case 10 : Initialisation(); DetruireFenetre(ZoneResultat); return 1;
			case 'q' : FinDePartie(); break;
			case 'm' : DetruireFenetre(ZoneResultat); return 0;				
		}
	wrefresh(ZoneResultat);
	} while (1);
	return 0;			
} 

void FinDePartie()
/* \fn FinDePartie()
* \brief Remercie les joueurs et clos le programme 
*/
{
	WINDOW * ZoneFin;
	ZoneFin = CreerFenetre(12, 80, (LINES-12)/2, (COLS-80)/2);

	mvwprintw(ZoneFin, 3, 30, "Merci d'avoir joué !");
	mvwprintw(ZoneFin, 6, 21, "Le programme quittera dans 3 secondes");
	wrefresh(ZoneFin);
	sleep(3);
	endwin();
	exit(1);
}
















