/**
* \file calcul.c
* \brief Calcul le score du joueur selon la catégorie choisie
* \version 1.0 
*/

int CalculScore(int * joueur){
	int i;
	int total=0;
	switch(Categorie){
	/* choix score a utiliser */		
		case 1 :
		case 2 :
		case 3 :
		case 4 :
		case 5 :
		case 6 :
		/* fonction qui calcule le score pour les dés de un a six */
			Score[*joueur][Categorie] = total;
			break;			
		case 7:
			if(isBrelan())
				Score[*joueur][Categorie] = de[0]+De[1]+De[2]+De[3]+De[4]+De[5];
			break;
			
		case 8:
			if(isCarre()){
				Score[*joueur][Categorie] = De[0]+De[1]+De[2]+De[3]+De[4]+De[5];
			break;
			
		case 9:
			if(isFull()){
				Score[*joueur][Categorie] = 25;
			break;
			
		case 10:
			if(isPtSuite()){
				Score[*joueur][Categorie] = 30;
			break;
			
		case 11:
			if(isGdSuite()){
				Score[*joueur][Categorie] = 40;
			break;
			
		case 12:
			if(isYahtzee()){
				Score[*joueur][Categorie] = 50;
			break;
			
		case 13:
			Score[*joueur][Categorie] = De[0]+De[1]+De[2]+De[3]+De[4]+De[5];
			break;
		
		
	}
}	
