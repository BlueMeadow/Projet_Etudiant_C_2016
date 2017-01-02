#include "../include/Global.h"

/**
* \file Chargement.c
* \brief Permet de sauvegarder et charger une partie
* \author Benoit Combasteix, Simon Fernandes et Nathan OUALET
* \version 1.0
*/


void Sauvegarder()
/* \fn Sauvegarder()
* \brief Sauvegarde l'état de la partie dans un ficheir pour pouvoir reprendre
*/
{
	FILE * Sauvegarde = NULL; /**< Fichier de sauvegarde */
	int i;
	int j;
	char NomFichier[7] = "sav_";
	char temp[4]; /**< Garde le début du nom de fichier après modifcation */
	char NumSav[3]; /**< Jusqu'à 99 sauvegardes */

	strcpy(temp, NomFichier);
	NumSav[2] = '\0';
	NumSav[1] = '1'; 
	NumSav[0] = '0'; 
	strcat(NomFichier, NumSav);

	/** Vérification du numéro de sauvegarde à attribuer */

	for (i = 0; i < 10; i++)
	{
		for (j = 1; j < 10; j++)
		{
			Sauvegarde = fopen(NomFichier, "r");
			if (Sauvegarde != NULL)
			{
				fclose(Sauvegarde);/**< si le fichier existe, ferme et passe au suivant */
				strcpy(NomFichier, temp);
				NumSav[1]++;
				if (NumSav[1] > '9')
				{
					NumSav[1] = '0';
					NumSav[0]++;
				}
				strcat(NomFichier, NumSav); 
			}
			else break; /**< Si le fichier n'existe pas, sort des boucles de vérification */
		}
		if (Sauvegarde == NULL) break;/**< Si le fichier n'existe pas, sort des boucles de vérification */
	}
	
	/** Rentre les données importantes dans le fichier */

	Sauvegarde = fopen(NomFichier, "w");
	fprintf(Sauvegarde, "%i %i %i %i", NbJoueurs, Joueur, NbTours, NbLancers); 
	for (i = 0; i < NbJoueurs; i++)
	{
		fprintf(Sauvegarde, " %s %i %i", PseudoJ[i], isAide[i], Prime[i]);
		for (j = 0; j < 13; j++)
		{
			fprintf(Sauvegarde, " %i", Score[i][j]);
		}
	}

	fclose(Sauvegarde);
	mvwprintw(ZoneMessage, 4, 2, "Votre sauvegarde est la numéro %c%c", NumSav[0],NumSav[1]); /**< Affiche à l'utilisateur le numéro de la sauvegarde à charger pour reprendre cette partie */ 
}

int Charger()
/* \fn Charger
* \brief Permet de reprendre une partie préalablement sauvegardée 
*/
{
	FILE * Sauvegarde = NULL;
	int i;
	int j;
	int y = 1, x = 0, ch;
	int NbSav = 0;
	char SavTable[100][3];
	char NomFichier[10] = "sav_"; /**< Début de nom ommun à toutes les sauvegardes */
	char temp[4];  	/**< Garde le début du nom de fichier après modifcation */
	char NumSav[3]; /**< Jusqu'à 99 sauvegardes */	
	WINDOW * ZoneChargement;	
	ZoneChargement = CreerFenetre(48, 85, (LINES-40)/2, (COLS-85)/2);
	strcpy(temp, NomFichier);
	NumSav[2] = '\0';	

	/** Recherche des sauvegardes */

	for ( i = 1 ; i < 100 ; i++ )
	{
		NumSav[1] = i%10+48; /**< Code ASCII du chiffre des unités */
		NumSav[0] = i/10+48; /**< Code ASCII du chiffre des dizaines */

		strcat(NomFichier, NumSav); /**< Donne le nom du fichier à rechercher */
		Sauvegarde = fopen(NomFichier, "r");/**< Vérification de l'existence */
		if ( Sauvegarde != NULL ) /**< Si le fichier existe */
		{	
			strcpy(SavTable[NbSav], NumSav); /**< Garde le numéro en mémoire */
			wrefresh(ZoneChargement);
			NbSav++;
			fclose(Sauvegarde); /**< Passe au suivant */
		}
		strcpy(NomFichier, temp);
	}
			
	/** Affichage Ncurses */	


	keypad(ZoneChargement, TRUE);
	mvwprintw(ZoneChargement, 2, (85-36)/2, "Sélectionnez la sauvegarde à charger");
	if (!NbSav) /**< Si aucune sauvegarde n'a été trouvée */
	{
		Nettoyer(ZoneChargement, 2, 2, 5, 83);
		mvwprintw(ZoneChargement, 2, (85-36)/2, "Il n'y a pas de sauvegarde à charger"); /**< Affiche un message d'erreur */
		mvwprintw(ZoneChargement, 4, (85-43)/2, "Appuyez sur une touche pour revenir au menu");
		wgetch(ZoneChargement);
		DetruireFenetre(ZoneChargement);
		return 0;
	}
	else
	{	
		y = 0;
		x = 0;
		for ( i = 0 ; i < NbSav ; i++)
		{

			mvwprintw(ZoneChargement, 7+y, 4+28*x, "[   ] Sauvegarde n°%s", SavTable[i]); /**< Affiche chaque fichier de sauvegarde trouvé */
			y++;
			if ( y > 32 )
			{
				y-=33;
				x++;
			}
		}
	}
	wrefresh(ZoneChargement);

		/** Sélection de la sauvegarde */

	y = 0;
	x = 0;
	wmove(ZoneChargement, 7+y, 6+28*x);
	wrefresh(ZoneChargement);
	do
	{
		ch = wgetch(ZoneChargement);

		switch(ch)
		{
			case KEY_DOWN : if ( ((y+1)+x*33) < NbSav )/**< Empeche de se placer sur des sauvegardes inexistantes */
					{
						y++;
						if ( y > 32 )
						{
							y-=33;
							x++;
						}
					}
					break;
			case KEY_UP : if ( y > 0 ) /**< Empeche de se placer sur des sauvegardes inexistantes */
					{
						y--;
						if ( y < 1 && x > 0)
						{
							y+=33;
							x--;
						}
					}
					break;
		}		
		wmove(ZoneChargement, 7+y, 6+28*x);
		wrefresh(ZoneChargement);
			

	} while (ch != 10);
		
		/** Chargement de la sauvegarde */
	
	strcpy(NomFichier, temp);
	
	strcat(NomFichier, SavTable[y]); 
	
	Sauvegarde = fopen(NomFichier, "r"); /**< Ouvre le fichier de sauvegarde choisi par l'utilisateur */
	fscanf(Sauvegarde, "%i %i %i %i", &NbJoueurs, &Joueur, &NbTours, &NbLancers);
	for (i = 0; i < NbJoueurs; i++)
	{
		fscanf(Sauvegarde, " %s %i %i", PseudoJ[i], &isAide[i], &Prime[i]);
		for (j = 0; j < 13; j++)
		{
			fscanf(Sauvegarde, " %i", &Score[i][j]);
		}
	} /**< Initilialise les différentes données pour la partie à venir */

	fclose(Sauvegarde);
	DetruireFenetre(ZoneChargement);	
		
		return 1;
}



