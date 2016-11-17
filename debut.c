#include <stdio.h>
#include <stdlib.h>
//
/*	Programme principal */
int main(void){	
	
	int nbjoueur;
	int joueur;


	do
/* Affichage du menu et saisie du choix */
	{	printf("\nRegles du jeu :\n");
		printf(" 1 - Si la partie se joue avec au moins deux joueurs, chaque joueur lance\n une fois les 5 des, celui qui fait le meilleur score, commence la partie.\n");
		printf(" 2 - Tous les joueurs peuvent faire trois lancers maximum des dés de leur choix quand c'est leur tour.\n");
		printf(" 3 - Au premier lancer, il a l'obligation de lancer les 5 dés.\n");
		printf(" 4 - Au second et au dernier lancer, s'il le souhaite, le joueur sélectionne les dés qu'il veut relancer.\n");
		printf(" 4 - Au troisième lancer, le joueur doit obligatoirement valider les points qu'il a obtenu avec le dernier lancer.\n\n");
		
		printf("\nNombre de joueurs ?\n");
		printf(" 1 - Un joueur \n");
		printf(" 2 - Deux joueurs\n");
		printf(" 3 - Trois joueurs\n");
		printf(" 4 - Quatre joueurs\n");
		printf(" 5 - Quitter le jeu\n");
		printf("Votre choix : ");
		scanf("%i",&joueur);

/* Traitement du choix de l'utilisateur */
		switch(joueur)
		{	case 1: printf("Vous voulez jouer en solitaire à notre jeu: "); nbjoueur = 1; /*Partie(nbjoueur);*/ break;
			case 2: printf("Vous voulez jouer à deux à notre jeu: "); nbjoueur = 2; /*Partie(nbjoueur);*/ break;
			case 3: printf("Vous voulez jouer à trois à notre jeu: "); nbjoueur = 3; /*Partie(nbjoueur);*/ break;
			case 4: printf("Vous voulez jouer à quatre à notre jeu: "); nbjoueur = 4; /*Partie(nbjoueur);*/ break;
			case 5: break;
			default: printf("Erreur: votre choix doit etre compris entre 1 et 4 inclus.\n");
		}
		
	}
	while(joueur != 5);

	printf("Meri d'avoir jouer à notre jeu !\n");
	return EXIT_SUCCESS;
}
