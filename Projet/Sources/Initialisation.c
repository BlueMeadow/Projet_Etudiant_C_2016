#include "../include/Global.h"

/**
* \file Initialisation.c
* \brief Permet de sauvegarder et charger une partie
* \author Benoit Combasteix, Simon Fernandes et Nathan OUALET
* \version 1.0
*/



void ChainePseudo(char Pseudos[40])
/* \fn ChainePseudo(char Pseudos[40])
* \brief Concatène chaque pseudo avec des espace pour former chaine de 40 caractères
*	Facilite l'affichage
*/
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
/* \fn Initialisation()
* \brief Initialise les données avant chaque partie 
*/
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
/* \fn EntrerNbJoueur()
* \brief Demande d'entrer le nombre de participants à la partie
*/
{
	int y, ch;
	keypad(ZoneMenu, TRUE);
	noecho();
	curs_set(1);
	y = 5;
	NbJoueurs = 0;
	Nettoyer(ZoneMenu, 1, 1 , 13, 88);

	mvwprintw(ZoneMenu, 2, (90-57)/2, "Choisissez le nombre de joueurs (max. 4) avec les flèches");
	mvwprintw(ZoneMenu, 5, 38, "  |1 Joueur");
	mvwprintw(ZoneMenu, 6, 38, "  |2 Joueurs");
	mvwprintw(ZoneMenu, 7, 38, "  |3 Joueurs");
	mvwprintw(ZoneMenu, 8, 38, "  |4 Joueurs");
	mvwprintw(ZoneMenu, 10, (90-37)/2, "%i Joueur(s) ? Confirmer avec [ENTREE]", y-4);
	
	wrefresh(ZoneMenu);
	
	wmove(ZoneMenu, y, 38);
	wrefresh(ZoneMenu);
	
	/** Selection du nombre de joueurs */
	do
	{
		ch = wgetch(ZoneMenu);
		
		switch(ch) /**< Choisir avec les fleches directionnelles */
		{
			case KEY_UP : 
						if (y > 5)
						{
							y--;
							mvwprintw(ZoneMenu, 10, (90-37)/2, "%i Joueur(s) ? Confirmer avec [ENTREE]", y-4);
							wmove(ZoneMenu, y, 38);
							wrefresh(ZoneMenu);
						}
						else
						{
							y = 8;
							mvwprintw(ZoneMenu, 10, (90-37)/2, "%i Joueur(s) ? Confirmer avec [ENTREE]", y-4);
							wmove(ZoneMenu, y, 38);
							wrefresh(ZoneMenu);
						}
						break;	
			case KEY_DOWN : 
						if (y < 8)
						{
							y++;
							mvwprintw(ZoneMenu, 10, (90-37)/2, "%i Joueur(s) ? Confirmer avec [ENTREE]", y-4);
							wmove(ZoneMenu, y, 38);
							wrefresh(ZoneMenu);
						}
						else
						{
							y = 5;
							mvwprintw(ZoneMenu, 10, (90-37)/2, "%i Joueur(s) ? Confirmer avec [ENTREE]", y-4);
							wmove(ZoneMenu, y, 38);
							wrefresh(ZoneMenu);
						}
						break;	
		} 
	} while (ch != 10); /**< Valider le choix avec [ENTREE] */
	if (NbJoueurs == 0)
		NbJoueurs = y - 4;	
}


 	
void EntrerPseudo()
/* \fn EntrerPseudo()
* \brief Demande d'entrer le pseudo de chaque participant
*/
{
	int i, j = 0, k, ch;
	char temp[10]="";
	keypad(ZoneMenu, TRUE);
	echo(); /**< Affiche les touches saisies pour faciliter l'entrée du pseudo */
	curs_set(0);
	for ( i = 0; i < NbJoueurs; i++) /**< Pour chaque joueur */
	{	
		Nettoyer(ZoneMenu, 1, 1 , 12, 87);
		mvwprintw(ZoneMenu, 2, 40, "Joueur %i : ", i+1);
		mvwprintw(ZoneMenu, 3, (90-43)/2, "Entrez votre Pseudo (entre 3 et 10 caractères)");
		mvwprintw(ZoneMenu, 4, 33, "-> ");
		wrefresh(ZoneMenu);

		do	
		{
			ch = wgetch(ZoneMenu);
			if ( ch == 32 )
				ch = '_'; /**< Remplace les ' ' par des '_' pour l'écriture dans les fichiers Highscore et sauvegarde*/
			if ( ch == 10 )
				break;
			if ( j < 10 )
				temp[j] = ch;
			j++;
		} while (1);			
		

		/** Vérification des conditions d'entrée du pseudo */

		while (strlen(temp) > 10) /**< Empeche d'écrire un pseudo de plus de 10 caractères */
		{
			j = 0;
			memset(temp, '\0', 10);	/**< Vide complètement la chaine de catactères */
			Nettoyer(ZoneMenu, 3, 2 , 5, 88);
			mvwprintw(ZoneMenu, 3, (90-53)/2, "Pseudo de plus de 10 caractères, recommencez la saisie");
			mvwprintw(ZoneMenu, 4, 33, "-> ");
			wrefresh(ZoneMenu);

			do	/**< Recommence la saisie */
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
		while (strlen(temp) < 3) /**< Empeche d'écrire un pseudo de moins de 3 caractères */
		{
			j = 0;
			memset(temp, '\0', 10); /**< Vide complètement la chaine de catactères */
			Nettoyer(ZoneMenu, 3, 2 , 5, 88);
			mvwprintw(ZoneMenu, 3, (90-53)/2, "Pseudo de moins de 3 caractères, recommencez la saisie");
			mvwprintw(ZoneMenu, 4, 33, "-> ");
			wrefresh(ZoneMenu);
			
			do	/**< Recommence la saisie */
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
		while(!strcmp(temp,"AAA") || !strcmp(temp,"BBB") || !strcmp(temp,"CCC") || !strcmp(temp,"DDD") || !strcmp(temp,"EEE")) /**< Empeche d'utiliser un pseudo placeholder, utilisé par le fichier des Highscores */
		{	
			j = 0;
			memset(temp, '\0', 10); /**< Vide complètement la chaine de catactères */
			Nettoyer(ZoneMenu, 3, 2 , 5, 88);
			mvwprintw(ZoneMenu, 3, (90-53)/2, "Pseudo utilisé par le programme, recommencez la saisie");
			mvwprintw(ZoneMenu, 4, 33, "-> ");
			wrefresh(ZoneMenu);
			
			do	/**< Recommence la saisie */
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
		for( k = 0 ; k < i ; k++)/**< Empeche deux joueurs de prende le même pseudo */
		{
			while(!strcmp(temp, PseudoJ[k]))
			{
				j = 0;
				memset(temp, '\0', 10); /**< Vide complètement la chaine de catactères */
				mvwprintw(ZoneMenu, 3, (90-64)/2, "Ce pseudo est utilisé par un autre joueur, recommencez la saisie");
				Nettoyer(ZoneMenu, 4, 6 , 4, 16);
				wmove(ZoneMenu, 4, 6);
				wrefresh(ZoneMenu);
				do	/**< Recommence la saisie */
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
		strcpy(PseudoJ[i], temp); /**< Le pseudo remplissant toutes les conditions d'entrée est sauvegardé*/
		j = 0;
		memset(temp, '\0', 10);	/**< Vide complètement la chaine de catactères pour le prochain joueur*/
	}
	noecho(); /**< Recache les touches saisies */
}

void MiseEnPlace()
/* \fn MiseEnPlace()
* \brief Génère les fenetres nécéssaires au déroulement de la fonction Partie() 
*/
{	
	ChainePseudo(Pseudos); /**< Concatène les pseudos avec des espaces pour améliorer l'affichage */
	ZoneScore = CreerFenetre(25,70,(LINES-35)/2,(COLS-70)/2); /**< Genere la fenetre principale au centre du terminal */
	ZoneDe = CreerFenetre(31, 19, (LINES-35)/2, (COLS-70)/2-19); /**< Génère la fenetre d'affichage des dés à la gauche de la fenetre de score */
	ZoneAide = CreerFenetre(30,30,(LINES-35)/2,(COLS+70)/2); /**< Genere la fenetre d'Aide à droite de la fenetre score */
	ZoneMessage = CreerFenetre(10,70,(LINES+15)/2,(COLS-70)/2); /**< Genere la fentre par laquelle le systeme s'adresse à l'utilisateur pendant la partie */
	FicheDeScore(ZoneScore,2,2); /**< Affiche le squelette de la fiche de score */
	AffichageDe(De); /**< Affiche les dés */
}


void DemandeAide()
/* \fn DemandeAide()
* \brief Demande à chaque joueur s'il veut afficher l'aide pendant la partie
*/
{
		int i, ch;
	keypad(ZoneMenu, TRUE);
	noecho(); 

	wmove(ZoneMenu, 1, 1);
	for (i = 0 ; i < NbJoueurs ; i++)
	{
		Nettoyer(ZoneMenu, 2, 2, 13, 88);
		mvwprintw(ZoneMenu, 2, (90-13)/2, "Joueur %s : ", PseudoJ[i]);
		mvwprintw(ZoneMenu, 4, (90-35)/2, "Voulez-vous afficher l'aide ? [O/N]");
		mvwprintw(ZoneMenu, 6, 10, "(Vous pourrez l'afficher ou la cacher pendant la partie à tout moment)");
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
/* \fn ActiverAide(int i) 
* \brief Permet à chaque joueur d'activer ou désactiver l'aide pendant la pertie 
*/
{
	if ( tolower(i) == 'h' )
		isAide[Joueur] = (isAide[Joueur]+1)%2;
	Aide();
}
