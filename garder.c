/**
* \file garder.c
* \brief Permet de sélectionner les dés que nous voulons garder ou non pour le prochain lancer.
* \version 1.0
* \date 15 novembre 2016
*/

void Garder (WINDOW *localwin, int Garde[5])
{
	int y, x, ch;
	y = 5; //indice d'ordonnée
	x = 14; // indice d'abscisse
	keypad(localwin, TRUE); //Permet l'utilisation des touches directionnelles
	
	wmove(localwin, y, x);
	wrefresh(localwin);
	do 
	{
		ch = wgetch(localwin);
		switch (ch)
		{
			case KEY_UP:  
				if ( y == 5 )
				/* Si on est en haut, on passe en bas */
				{
					y = 25;
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				else 
				/* Sinon on monte d'une case */
				{
					y-=5;
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				break;
			case KEY_DOWN:
				if ( y == 25 )
				/* Si on est en bas, on remonte en haut */
				{
					y = 5;
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				else 
				/* Sinon on descend d'une case */
				{
					y+=5;
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				break;
			case 32: 
				/* La touche espace sert à indiquer si on veut garder le de ou non */
				if ( Garde[y/5-1] == 0 )
				{
					waddch(localwin, 'G');
					Garde[y/5-1] = 1;
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				else
				{
					waddch(localwin, ' ');
					Garde[y/5-1] = 0;
					wmove(localwin, y, x);
					wrefresh(localwin);
				}
				break;
		}
	} while ( ch != 10 );	
	/* On valide la selection avec la touche entree */
}
