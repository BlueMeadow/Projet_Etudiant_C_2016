/**
* \file DetruireFenetre.c
* \brief Effacer une fenetre qui se trouve au même emplacement
* \author Fernandes SIMON
* \version 1.0
* \date 5 décembre 2016
*/

void DetruireFenetre(WINDOW * Fenetre)
{
	wclear(Fenetre);
	wrefresh(Fenetre);
	delwin(Fenetre);
}
