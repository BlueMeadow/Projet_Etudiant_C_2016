/**
* \file MenuDeroulant.c
* \author Simon Fernandes et Benoit Combasteix
* \version 1.0
* \fn Defilement()
* \return Permet de faire défiler un texte qui est plus grand que la console
*/


void Defilement (){
/* A faire dans une fenetre ayant moins de lignes que le texte que l'on veut afficher */
	int x, y, ch;
	WINDOW * ZoneRegles;
	ZoneRegles =  newwin(30, 64, 1, 1);	
	wrefresh(ZoneRegles);
	keypad(ZoneRegles, TRUE);
	y = 1;
	
	do
	{

		wclear(ZoneRegles);
		/* Copier Les règles ici */
		wrefresh(ZoneRegles);
		ch = wgetch(ZoneRegles);
		switch (ch)
		{
			case KEY_UP:  
				if ( y > -24 )
				{
					y = y-1;
				}
				break;
			case KEY_DOWN:
				if ( y < 1)
				{
					y = y + 1;

				}
				break;
		}

	} while (ch != 10); /* Entrée fait sortir de l'affichage des règles */
	/* Retour au menu ici */
}



int main()
{
	int ch;
	initscr();
	cbreak();
	noecho(); /* Les trois lignes au dessus sont dan MiseEnPlace() */
	Defilement();
	endwin();
}
