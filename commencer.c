void commencer ( int joueur){
	switch(joueur){
		case 1: printf("Vous voulez jouer en solitaire à notre jeu: "); nbjoueur = 1; Partie(); break;
		case 2: printf("Vous voulez jouer à deux à notre jeu: "); nbjoueur = 2; Partie(); break;
		case 3: printf("Vous voulez jouer à trois à notre jeu: "); nbjoueur = 3; Partie(); break;
		case 4: printf("Vous voulez jouer à quatre à notre jeu: "); nbjoueur = 4; Partie(); break;
			
	}


}