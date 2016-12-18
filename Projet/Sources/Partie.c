#include "../include/Global.h"

void Menu()
{
	int y, x, ch;
	int isRelancer;
	ZoneMenu = CreerFenetre(15,90,(LINES-15)/2,(COLS-90)/2);
	
	keypad(ZoneMenu, TRUE); 
	/* Permet l'utilisation des touches directionnelles */

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
		switch (ch)
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
	/* On valide la selection avec la touche entree */
	switch(y)
	{
		case 5 :
			EntrerNbJoueur(); 
			EntrerPseudo(); 
			DemandeAide(); DetruireFenetre(ZoneMenu); 
			do 
			{ 
				Initialisation(); 
				Partie(); 
				Resultat(&isRelancer); 
			} while (isRelancer);
			 break;
		case 6 :DetruireFenetre(ZoneMenu);
			if (Charger())
			{
				do 
				{ 
					Partie(); 
					Resultat(&isRelancer);
				} while ( isRelancer == 1);
			}
				break;
		case 7 : DetruireFenetre(ZoneMenu); Regles(); break;
		case 8 : DetruireFenetre(ZoneMenu); AffichageHS(); break;
		case 9 : DetruireFenetre(ZoneMenu); FinDePartie(); break;
	}
}



int Partie()
{	
	int i;
	MiseEnPlace();
	ChargementAffichage();
	while(NbTours < 13*NbJoueurs)
	{
		Aide(isAide, Joueur);
		attron(A_BOLD);
		mvwprintw(ZoneMessage,1 ,2 ,"                                                                  ");
		mvwprintw(ZoneMessage,3 ,2 ,"                                                                  ");
		mvwprintw(ZoneMessage,1 ,2 ,"Tour de %s", PseudoJ[Joueur]);
		attroff(A_BOLD);
		for( i = 3 ; i < 20 ; i++)
		mvwprintw(ZoneAide,i,2,"                           "); 
		Lancer();
		AffichageDe(De ,ZoneDe);
		Aide(isAide, Joueur);
		/*do
		{
			if (NbLancers == 3) break;
			mvwprintw(ZoneMessage,2 ,2 ,"                                                                  ");
			mvwprintw(ZoneMessage,2 ,2 ,"Voulez-vous relancer ? [O/N]");
			wrefresh(ZoneMessage);
			do{
				ch=getch();
			}
			while(tolower(ch) != 'o' && tolower(ch) != 'n');
			if (tolower(ch) == 'n') break;
			mvwprintw(ZoneMessage, 2, 2, "                                                                  ");
			mvwprintw(ZoneMessage, 2, 2, "Sélectionnez les dés à garder avec [ESPACE].");
			mvwprintw(ZoneMessage, 2, 2, "Validez avec [ENTREE].");
			wrefresh(ZoneMessage);

			Garder(ZoneDe, Garde);
			Lancer();
			AffichageDe(De ,ZoneDe);
			Aide(isAide, Joueur);
			NbLancers++;
		
		} while(1);*/
		EcrireScore(Joueur);
		NbTours++;
		Joueur = ChangerJoueur(Joueur,NbJoueurs);
		NbLancers = 1;
	}
	return 1;
}

int ChangerJoueur(int Joueur, int NbJoueur)
{
	return ((Joueur+1)%NbJoueur);
}

void Aide()
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
	
	if( isAide[Joueur] ){
		mvwprintw(ZoneAide, y, x, "Pas de combinaison");
		wrefresh(ZoneAide);
		if(isBrelan()){
			for (i = 0 ; i < 6 ; i++)
			{
				if (Occurrences[i] > 2)
				{
					temp1 = i;
					break;
				}
			}
			mvwprintw(ZoneAide, y, x, "Brelan de %i", temp1+1);
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isCarre()){
			for (i = 0 ; i < 6 ; i++)
			{
				if (Occurrences[i] > 3)
				{
					temp1 = i;
					break;
				}
			}
			mvwprintw(ZoneAide, y, x, "Carre de %i", temp1+1);
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isFull()){
			mvwprintw(ZoneAide, y, x, "Full");
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isPtSuite()){
			mvwprintw(ZoneAide, y, x, "Petite suite");
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isGdSuite()){
			mvwprintw(ZoneAide, y, x, "Grande suite");
			wrefresh(ZoneAide);
			y+=2;
		}
		if(isYahtzee()){
			mvwprintw(ZoneAide, y, x, "YAHTZEE !");
			wrefresh(ZoneAide);
			y+=2;
		}
	}
	else{
		mvwprintw(ZoneAide, y, x, "L'aide n'est pas activée");
		wrefresh(ZoneAide);
	}
}


int Resultat(int * isRelancer)
{		
	int Total[NbJoueurs];
	int ch;
	int i, j, y = 0;
	int max;
	DetruireFenetre(ZoneMessage);
	DetruireFenetre(ZoneDe);
	DetruireFenetre(ZoneScore);
	DetruireFenetre(ZoneAide);
	ZoneResultat = CreerFenetre(28,60,(LINES-28)/2, (COLS-60)/2);
	
		/* Calcul du Total des points */

	for (i = 0 ; i < NbJoueurs ; i++)
	{
		Total[i] = 0;
		for (j = 0 ; j < 6 ; j++)
		{
			Total[i] += Score[i][j];
			
		}
		if (Total[i] > 62) 
		/* Prime de 35 si le score de la partie haute est de 63 ou plus */
		{
			Total[i] += 35;
		}	
		for (j = 6 ; j < 13 ; j++)
		{
			Total[i] += Score[i][j];
		}
		if ( Prime[i] > 0 )
			Total[i] = Total[i] + 100 * (Prime[i]-1);
		/* Prime pour chaque Yahtzee supplémentaire */
	}

	/* Mise en place de l'interface */

	wattron(ZoneResultat, A_REVERSE);
	mvwprintw(ZoneResultat, 2, 16, "TABLEAU DE SCORES");
	wattroff(ZoneResultat, A_REVERSE);
	
	wattron(ZoneResultat, A_REVERSE);
	mvwprintw(ZoneResultat, 11, 20, "VAINQUEUR");
	wattroff(ZoneResultat, A_REVERSE);

	/* Affichage des points de chaque joueur */
	
	for (i = 0 ; i < NbJoueurs ; i++)
	{
		mvwprintw(ZoneResultat, 5+i, 10, "%s : %i", PseudoJ[i], Total[i]);
	}

	/* Ecriture du nom des vainqueurs */

	mvwprintw(ZoneResultat, y+14, (50-strlen(PseudoJ[0]))/2 , "%s", PseudoJ[0] );
	max = Total[0];
	for (i = 1 ; i < NbJoueurs ; i++)
	{
		if ( Total[i] > max )
		{
			max = Total[i];
			y = 0;
			/* Place sur la première ligne */
			Nettoyer(ZoneResultat, y+14, 2, y+17, 58);
			/* Efface les 3 potentiels joueurs écrits en dessous */
			mvwprintw(ZoneResultat, y+14, (50-strlen(PseudoJ[i]))/2 , "%s", PseudoJ[i] );
			/* Ecrit le nom du vainqueur */

		}
		else if ( max == Total[i] )
		{
			y++;
			/* Passe à la ligne suivante */
			mvwprintw(ZoneResultat, y+14, (50-strlen(PseudoJ[i]))/2 , "%s", PseudoJ[i] );
			/* Ecrit le nom du joueur sous le précédent */
		}
	}
	wrefresh(ZoneResultat);

	

	/* Options de sortie */

	y = 0;
	if ( VerifHS() )
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
		if ( !VerifHS() )
			ch = 0;
		/* Empeche de sortir du menu avec [H] si il n'y a pas de nouveau highscore */
		switch (tolower(ch))
		{
			case 'h' : EcritureHS(); break;
			case 10 : *isRelancer = 1; Initialisation(); DetruireFenetre(ZoneResultat); return 1;
			case 'q' : *isRelancer = 0; FinDePartie(); break;
			case 'm' : *isRelancer = 0; DetruireFenetre(ZoneResultat); return 1;		
		}
		
	} while (ch != 'h');
	/* Affiche un nouveau menu si les highscores sont entrés */

	mvwprintw(ZoneResultat, 20+y, 6, "Highscores enregistrés ! Consultez la page depuis le menu !");
	mvwprintw(ZoneResultat, 21+y, 6, "Appuyez sur [ENTREE] pour relancer une partie");
	mvwprintw(ZoneResultat, 22+y, 6, "Appuyez sur [M] pour revenir au menu");
	mvwprintw(ZoneResultat, 23+y, 6, "Appuyez sur [Q] pour quitter");
	wrefresh(ZoneResultat);

	do
	{
		switch (tolower(ch))
		{
			case 10 : *isRelancer = 1; Initialisation(); DetruireFenetre(ZoneResultat); return 1;
			case 'q' : *isRelancer = 0; FinDePartie(); break;
			case 'm' : *isRelancer = 0; DetruireFenetre(ZoneResultat); return 1;		
		}
	} while (1);
	return 0;			
} 

void FinDePartie()
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
















