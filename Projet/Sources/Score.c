#include "../include/Global.h"

/**
* \file Score.c
* \brief Permet de calculer les combinaisons de dés et les scores
* \author Benoit Combasteix, Simon Fernandes et Nathan OUALET
* \version 1.0
*/

int isBrelan()
/* \fn isBrelan()
* \brief Fonction booléenne calculant la présence d'un brelan dans les dés
* \return VRAI s'il y a un brelan
*/
{
	int i;
	for( i = 0; i < 6 ; i++)
	{
		if (Occurrences[i] > 2)
			return 1;
	}
	return 0;
}

int isCarre()
/* \fn isCarre()
* \brief Fonction booléenne calculant la présence d'un carré dans les dés
* \return VRAI s'il y a un carré
*/
{
	int i;
	
	for( i = 0; i < 6 ; i++)
	{
		if (Occurrences[i] > 3)
			return 1;
	}
	return 0;		
}

int isYahtzee()
/* \fn isYahtzee
* \brief Fonction booléenne calculant la présence d'un brelan dans les dés
* \return VRAI s'il y a un brelan
*/
{
	for (int i=0; i < 6; i++){
		if ( Occurrences[i] == 5){
			return 1;
		}
	}
	return 0;
}

int isFull()
/* \fn isFull()
* \brief Fonction booléenne calculant la présence d'un full dans les dés
* \return VRAI s'il y a un brelan et une paire ( pas nécessairement de valeurs différentes )
*/
{

	int i, cpt2 = 0, cpt3 = 0;

	for( i = 0 ; i < 6 ; i++)
	{		
		if( Occurrences[i] == 2 )
			cpt2 = 1;
		else if( Occurrences[i] == 3 )
			cpt3 = 1;
	}
	if (cpt2 == 1 && cpt3 == 1)
		return 1;
	return (isYahtzee());	/**< Un Yahtzee est considéré comme un Full */
}



int isPtSuite()
/* \fn isPtSuite()
* \brief Fonction booléenne calculant la présence d'une petite suite dans les dés
* \return VRAI si les valeurs de quatre dés se suivent
*/
{

	int i;
	for( i = 0 ; i <= 2 ; i++){
		if(Occurrences[i] > 0 && Occurrences[i+1] > 0 && Occurrences[i+2] > 0 && Occurrences[i+3] > 0)
			return 1;
	}
	return 0;
}

int isGdSuite()
/* \fn isGdSuite()
* \brief Fonction booléenne calculant la présence d'une grande suite dans les dés
* \return VRAI si les valeurs de cinq dés se suivent
*/
{
	int i;
	
	for(i = 0; i < 1; i++)
	{
		if ((Occurrences[i] > 0) && (Occurrences[i+1] > 0) && (Occurrences[i+2] > 0) && (Occurrences[i+3] > 0) && (Occurrences[i+4] > 0))
			return 1;
	}
	return 0;
}

void CalculScore(int Joueur, int Categorie)
/* \fn CalculScore(int Joueur, int Categorie)
* \brief Calcul le score selon la catégorie
* \param Joueur Permet d'insérer le score dans la bonne ligne du tableau Score
* \param Categorie Permet de choisir seulement une catégorie pour ne pas faire 13 calculs
*/
{
	switch(Categorie){	
		case 1 :
		case 2 :
		case 3 :
		case 4 :
		case 5 :
		case 6 :
		/* Calcule le score pour les dés de un à six */
			Score[Joueur][Categorie-1] = (Categorie) * Occurrences[Categorie-1];
			break;			
		case 7:
			if(isBrelan())
				Score[Joueur][Categorie-1] = De[0]+De[1]+De[2]+De[3]+De[4];
			else
				Score[Joueur][Categorie-1] = 0;
			break;
			
		case 8:
			if(isCarre())
				Score[Joueur][Categorie-1] = De[0]+De[1]+De[2]+De[3]+De[4];
			else
				Score[Joueur][Categorie-1] = 0;
			break;
			
		case 9:
			if(isFull())
				Score[Joueur][Categorie-1] = 25;
			else
				Score[Joueur][Categorie-1] = 0;
			break;
			
		case 10:
			if(isPtSuite())
				Score[Joueur][Categorie-1] = 30;
			else
				Score[Joueur][Categorie-1] = 0;
			break;
			
		case 11:
			if(isGdSuite())
				Score[Joueur][Categorie-1] = 40;
			else
				Score[Joueur][Categorie-1] = 0;
			break;
			
		case 12:
			if(isYahtzee())
			{
				Score[Joueur][Categorie-1] = 50;
				Prime[Joueur]++;
				/* Débloque les primes de Yahtzee */
			}
			else
				Score[Joueur][Categorie-1] = 0;
			break;
			
		case 13:
			Score[Joueur][Categorie-1] = De[0]+De[1]+De[2]+De[3]+De[4];
			break;
	}
}	

void ChoixCategorie (int *Categorie, WINDOW *Fenetre, int Joueur)
/* \fn ChoixCategorie (int *Categorie, WINDOW *Fenetre, int Joueur)
* \brief permet au joueur de choisir dans quel catégorie il veut entrer le résultat de son lancer de dés
*/
{
	int y, x;
	y = 5; /**< indice d'ordonnée */
	x = 4; /**< indice d'abscisse */
	int ch; 
	noecho();
	curs_set(1);
	keypad(Fenetre, TRUE); /**< Permet l'utilisation des touches directionnelles */
	
	wmove(Fenetre, y, x);
	wrefresh(Fenetre);

	
	do 
	{
		ch = wgetch(Fenetre);
		ActiverAide(ch);
		switch (ch)
		{
			case KEY_UP:  /**< Fleche du haut entrée */
				if (y == 5)
				{
					y = 20; /**< Si on est en haut du tableau, on passe en bas */
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else if (y == 14) /**< Passe les 3 lignes centrales du tableau de score */
				{
					y = 10; 
					
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else 
				{
					y--;/**< Sinon, remonte d'une case */ 					
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				break;
			
			case KEY_DOWN:/**< Fleche du bas entrée */
				
				if (y == 20)
				{
					y = 5; /**< Si on est en bas du tableau, on passe en haut */					
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else if (y == 10)
				{
					y = 14; /**< On passe les 3 lignes centrales du tableau de score */					
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else 
				{

					y++;/**< Sinon, descend d'une case */					
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				break;
		}
		if (y < 11) *Categorie = y - 4;
		else *Categorie = y - 7;
		if(Score[Joueur][*Categorie-1] != -1) /**< Empeche de choisir une catégorie déjà remplie */
		{
			Nettoyer(ZoneMessage, 2, 2, 8, 68);
			mvwprintw(ZoneMessage, 3, 2, "Cette categorie est déja prise.");
			mvwprintw(ZoneMessage, 4, 2, "Choisissez en une autre.");
			wrefresh(ZoneMessage);
			ch = '0';
			wmove(ZoneScore, y, x);
			wrefresh(ZoneScore);		
		}
		else
		{
			Nettoyer(ZoneMessage, 2, 2, 8, 68);
			wmove(ZoneScore, y, x);
			wrefresh(ZoneScore);	
		}
			
	} while (ch != 10); 
		/**< Entrée valide le choix */
}

void EcrireScore(int Joueur)
/* \fn EcrireScore
* \brief Rassemble toutes les fonctions pour choisir la catégorie, calculer le score et l'écrire au bon endroit
*/
{
	int categorie;
	int x, y;
	Nettoyer(ZoneMessage, 2, 2, 8, 68);
	mvwprintw(ZoneMessage ,3 ,2 ,"Veuillez choisir la catégorie");
	wrefresh(ZoneMessage);
	ChoixCategorie(&categorie ,ZoneScore,Joueur); 
	CalculScore(Joueur, categorie);	

	if( isYahtzee() && (Prime[Joueur] >=0) ) /**< Comptabilise les Yahtzee supplémentaires */
		Prime[Joueur]++;

	/** choix de la colonne */

	x = 24 + 10 * Joueur; 		
	
	/** Choix de la ligne */

	if(categorie < 7) 
		y = categorie + 4;
	else
		y = categorie + 7;	

	/** Ecriture du score */

	mvwprintw(ZoneScore, y, x,"%i", Score[Joueur][categorie-1]);
	wrefresh(ZoneScore);
}

