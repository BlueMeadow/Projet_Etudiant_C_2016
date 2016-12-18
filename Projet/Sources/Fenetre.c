#include "../include/Global.h"

WINDOW *CreerFenetre(int Hauteur, int Longueur, int DebutY, int DebutX)
/* \fn CreerFenetre(int Hauteur, int Longueur, int DebutY, int DebutX)
* \brief Alloue de la mémoire et dessine une fenetre ncurses 
* \param Hauteur Nombre de lignes de la fenetre
* \param Longueur Nombre de colonnes de la fenetre
* \param DebutY Ordonnée du coin haut gauche de la fenetre
* \param DebutX Abscisse du coin haut gauche de la fenetre
*\ return Un pointeur sur une fenetre ncurses
*/
{	WINDOW *Fenetre;
	Fenetre = newwin(Hauteur, Longueur, DebutY, DebutX);
	wborder(Fenetre, '|', '|', '-', '-', '+', '+', '+', '+');		
	wrefresh(Fenetre);		/* Show that box 		*/
	return Fenetre;
}

void Nettoyer(WINDOW * Fenetre, int DebutY, int DebutX, int FinY, int FinX)
/* \fn Nettoyer(WINDOW * Fenetre, int DebutY, int DebutX, int FinY, int FinX)
* \brief Efface une zone dans une fenetre ncurses
* \param Pointeur sur une fenetre ncurses
* \param DebutY Ordonnée du coin haut gauche de la zone à effacer
* \param DebutX Abscisse du coin haut gauche de la zone à effacer
* \param FinY Ordonnée du coin bas droit de la zone à effacer
* \param FinX Abscisse du coin bas droit de la zone à effacer
*/
{
	int i, j;
	for (i = DebutY ; i <= FinY ; i++)
		for (j = DebutX ; j <= FinX ; j++)
			mvwprintw(Fenetre, i, j, " ");
	wrefresh(Fenetre);
}

void DetruireFenetre(WINDOW * Fenetre)
{
/* \fn DetruireFenetre(WINDOW * Fenetre)
* \brief Libère la mémoire et efface une fenetre ncurses
/ \param Fenetre Pointeur sur un fenetre ncurses
*/
	wclear(Fenetre);
	wrefresh(Fenetre);
	delwin(Fenetre);
}
