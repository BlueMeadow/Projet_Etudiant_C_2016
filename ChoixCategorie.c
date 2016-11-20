

void ChoixCategorie (int *Categorie, WINDOW *localwin)
{
	int y, x;
	y = 5; //indice d'ordonnée
	x = 4; // indice d'abscisse
	char vcour; 
	keypad(localwin, TRUE); //Permet l'utilisation des touches directionnelles
	
	wmove(localwin, y, x);
	waddch(localwin, 'X'); 
	wrefresh(localwin);
	wmove(localwin, y, x);
	
	do 
	{
		vcour = getch();
		switch (vcour)
		{
			case KEY_UP:  
				/* Fleche du haut entree */
				if (y == 5)
				{
					wmove(localwin, y, x);
					waddch(localwin, ' ');
					//wrefresh(localwin);
					/* On remet un vide car on change de catégorie */
					y = 20; 
					/* Si on est en haut du tableau, on passe en bas */
					wmove(localwin, y, x);
					waddch(localwin, 'X');
					wrefresh(localwin);
				}
				else if (y == 14)
				{
					wmove(localwin, y, x);
					waddch(localwin, ' ');
					//wrefresh(localwin);
					/* On remet un vide car on change de catégorie */
					y = 10; 
					/* On passe les 3 lignes centrales du tableau de score */
					wmove(localwin, y, x);
					waddch(localwin, 'X');
					wrefresh(localwin);
				}
				else 
				{
					wmove(localwin, y, x);
					waddch(localwin, ' ');
					y--;
					/* On remonte d'une case */
					wmove(localwin, y, x);
					waddch(localwin, 'X');
					wrefresh(localwin);
				}
				break;
			
			case KEY_DOWN:
				/* Fleche du bas entree */
				if (y == 20)
				{
					wmove(localwin, y, x);
					waddch(localwin, ' ');
					//wrefresh(localwin);
					/* On remet un vide car on change de catégorie */
					y = 5; 
					/* Si on est en bas du tableau, on passe en haut */
					wmove(localwin, y, x);
					waddch(localwin, 'X');
					wrefresh(localwin);
				}
				else if (y == 10)
				{
					wmove(localwin, y, x);
					waddch(localwin, ' ');
					//wrefresh(localwin);
					/* On remet un vide car on change de catégorie */
					y = 14; 
					/* On passe les 3 lignes centrales du tableau de score */
					wmove(localwin, y, x);
					waddch(localwin, 'X');
					wrefresh(localwin);
				}
				else 
				{
					wmove(localwin, y, x);
					waddch(localwin, ' ');
					y++;
					/* On descend d'une case */
					wmove(localwin, y, x);
					waddch(localwin, 'X');
					wrefresh(localwin);
				}
				break;
		}
		if (y < 11) *Categorie = y - 5;
		else *Categorie = y - 8;
	} while (ch != 13) 
		/* Entrée valide le choix */
}
	
