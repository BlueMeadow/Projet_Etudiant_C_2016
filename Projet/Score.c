int isBrelan()
{
	/* VRAI si 3 dés ont la même valeur */
	int i;
	for( i = 0; i < 6 ; i++)
	{
		if (Occurrences[i] > 2)
			return 1;
	}
	return 0;
}

int isCarre()
{
	/* VRAI si 4 dés ont la même valeur */
	int i;
	
	for( i = 0; i < 6 ; i++)
	{
		if (Occurrences[i] > 3)
			return 1;
	}
	return 0;		
}

int isYahtzee()
{

	/* VRAI si les 5 dés ont la même valeur */

	for (int i=0; i < 6; i++){
		if ( Occurrences[i] == 5){
			return 1;
		}
	}
	return 0;
}

int isFull()
{
	/* VRAI si on a un brelan et une paire */
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
	return (isYahtzee());
	/* Un Yahtzee est condéré comme un Full */
}



int isPtSuite()
{
	/* VRAI si 4 dés se suivent */
	int i;
	int j;

	for(j=0;j<=2;j++){
		if(Occurrences[j] > 0 && Occurrences[j+1] > 0 && Occurrences[j+2] > 0 && Occurrences[j+3] > 0)
			return 1;

	}
	return 0;
}

int isGdSuite()
{
	/* VRAI si 5 dés se suivent */
	int i;
	
	for(i = 0; i < 1; i++)
	{
		if ((Occurrences[i] > 0) && (Occurrences[i+1] > 0) && (Occurrences[i+2] > 0) && (Occurrences[i+3] > 0) && (Occurrences[i+4] > 0))
			return 1;
	}
	return 0;
}

void CalculScore(int Joueur, int Categorie)
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
				Score[Joueur][Categorie-1] = 50;
			else
				Score[Joueur][Categorie-1] = 0;
			break;
			
		case 13:
			Score[Joueur][Categorie-1] = De[0]+De[1]+De[2]+De[3]+De[4];
			break;
	}
}	

void ChoixCategorie (int *Categorie, WINDOW *Fenetre, int Joueur)
{
	int y, x;
	y = 5; //indice d'ordonnée
	x = 4; // indice d'abscisse
	int ch; 
	keypad(Fenetre, TRUE); //Permet l'utilisation des touches directionnelles
	
	wmove(Fenetre, y, x);
	wrefresh(Fenetre);

	
	do 
	{
		ch = wgetch(Fenetre);
		switch (ch)
		{
			case KEY_UP:  
				/* Fleche du haut entree */
				if (y == 5)
				{
					y = 20; 
					/* Si on est en haut du tableau, on passe en bas */
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else if (y == 14)
				{
					/* On remet un vide car on change de catégorie */
					y = 10; 
					/* On passe les 3 lignes centrales du tableau de score */
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else 
				{
					y--;
					/* On remonte d'une case */
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				break;
			
			case KEY_DOWN:
				/* Fleche du bas entree */
				if (y == 20)
				{
					y = 5; 
					/* Si on est en bas du tableau, on passe en haut */
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else if (y == 10)
				{
					y = 14; 
					/* On passe les 3 lignes centrales du tableau de score */
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				else 
				{

					y++;
					/* On descend d'une case */
					wmove(Fenetre, y, x);
					wrefresh(Fenetre);
				}
				break;
		}
		if (y < 11) *Categorie = y - 4;
		else *Categorie = y - 7;
		if(Score[Joueur][*Categorie-1] != -1){
			mvwprintw(ZoneMessage, 2, 2 ,"                                                                  ");
			mvwprintw(ZoneMessage, 3, 2 ,"                                                                  ");
			mvwprintw(ZoneMessage, 2, 2, "Cette categorie est déja prise.");
			mvwprintw(ZoneMessage, 3, 2, "Choisissez en une autre.");
			wrefresh(ZoneMessage);
			ch = '0';
			wmove(ZoneScore, y, x);
			wrefresh(ZoneScore);		
		}
		else
		{
			mvwprintw(ZoneMessage, 2, 2 ,"                                                                  ");
			mvwprintw(ZoneMessage, 3, 2 ,"                                                                  ");
			wrefresh(ZoneMessage);
			wmove(ZoneScore, y, x);
			wrefresh(ZoneScore);	
		}
			
	} while (ch != 10); 
		/* Entrée valide le choix */
}

void EcrireScore(int Joueur)
{
	int categorie;
	int x = 2;
	int y = 2;
	int i;
	int j;
	
	mvwprintw(ZoneMessage ,y ,x ,"Veuillez choisir la catégorie");
	wrefresh(ZoneMessage);
	ChoixCategorie(&categorie ,ZoneScore,Joueur); 
	CalculScore(Joueur, categorie);
	
	/* choix de la colonne */
	x = 24 + 10 * Joueur;
	/* choix de la ligne */
	
	

	if(categorie < 7)
		y = categorie + 4;
	else
		y = categorie + 7;
	
	/*affiche le score */
	mvwprintw(ZoneScore, y, x,"%i", Score[Joueur][categorie-1]);
	wrefresh(ZoneScore);
}

