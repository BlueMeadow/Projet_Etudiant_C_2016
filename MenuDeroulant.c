

void Defilement (){
/* A faire dans une fenetre ayant moins de lignes que le texte que l'on veut afficher */
	int x, y, ch;
	
	x = 1;
	y = 1;
	
	do
	{
		ch = wgetch(ZoneMenu);
		switch(ch)
		{
			case KEY_UP : if (y > 1) y--; break;
			case KEY_DOWn : if (y < 52 - LINES) y++; break;
		}
		/* METTRE TOUTES LES LIGNES A AFFICHER ICI */
	} while (ch != 10) /* Entrée fait sortir de l'affichage des règles */
	/* Retour au menu ici */
}


void PageParPage (){
/* A faire dans une fenetre dont le nombre de ligne est supérieur à celui de toutes les pages */
	int ch, choix;
	
	choix = 1; /* Page 1 affichée par defaut */
	
	do
	{
		switch(choix)
		{
			case 1 : Page1(); break;
			case 2 : Page2(); break;
			case 3 : Page3(); break;
		}
		ch = wgetch(ZoneMenu);
		switch(ch)
		{
			
			case KEY_UP : if (choix > 1) choix--; break;
			case KEY_DOWN : if (y < 3) choix++; break;
		}
		/* METTRE TOUTES LES LIGNES A AFFICHER ICI */
	} while (ch != 10) /* Entrée fait sortir de l'affichage des règles */
	/* Retour au menu ici */
}

