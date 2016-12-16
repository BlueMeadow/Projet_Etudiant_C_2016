
WINDOW *CreerFenetre(int Hauteur, int Longueur, int DebutY, int DebutX)
{	WINDOW *Fenetre;
	Fenetre = newwin(Hauteur, Longueur, DebutY, DebutX);
	wborder(Fenetre, '|', '|', '-', '-', '+', '+', '+', '+');		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(Fenetre);		/* Show that box 		*/
	return Fenetre;
}

void Nettoyer(WINDOW * Fenetre, int DebutY, int DebutX, int FinY, int FinX)
{
	int i, j;
	for (i = DebutY ; i < FinY ; i++)
		for (j = DebutX ; j < FinX ; j++)
			mvwprintw(Fenetre, i, j, " ");
}

void DetruireFenetre(WINDOW * Fenetre)
{
	wclear(Fenetre);
	wrefresh(Fenetre);
	delwin(Fenetre);
}
