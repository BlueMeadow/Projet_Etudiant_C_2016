#include <stdio.h>
#include <stdlib.h>

/**
* \file debut.c
* \brief Permet de savoir le nombre de joueurs de la partie.
* \version 1.0
*/


/*	Programme principal */
int main(void){	
	
	int nbjoueur;
	int joueur;
	int x=2;
	int y=2;

	do
/* Affichage du menu et saisie du choix */
	{	
			mvwprintw(ZoneMenu, y, x, "\nRegles du jeu :\n");
			mvwprintw(ZoneMenu, y+1, x, " 1 - Si la partie se joue avec au moins deux joueurs, chaque joueur lance\n une fois les 5 des, celui qui fait le meilleur score, commence la partie.\n");
			mvwprintw(ZoneMenu, y+2, x, " 2 - Tous les joueurs peuvent faire trois lancers maximum des dés de leur choix quand c'est leur tour.\n");
			mvwprintw(ZoneMenu, y+3, x, " 3 - Au premier lancer, il a l'obligation de lancer les 5 dés.\n");
			mvwprintw(ZoneMenu, y+4, x, " 4 - Au second et au dernier lancer, s'il le souhaite, le joueur sélectionne les dés qu'il veut relancer.\n");
			mvwprintw(ZoneMenu, y+5, x, " 4 - Au troisième lancer, le joueur doit obligatoirement valider les points qu'il a obtenu avec le dernier lancer.\n\n");
			
			mvwprintw(ZoneMenu, y, x, "\nNombre de joueurs ?\n");
			mvwprintw(ZoneMenu, y+1, x, " 1 - Un joueur \n");
			mvwprintw(ZoneMenu, y+2, x, " 2 - Deux joueurs\n");
			mvwprintw(ZoneMenu, y+3, x, " 3 - Trois joueurs\n");
			mvwprintw(ZoneMenu, y+4, x, " 4 - Quatre joueurs\n");
			mvwprintw(ZoneMenu, y+5, x, " 5 - Quitter le jeu\n");
			mvwprintw(ZoneMenu, y+6, x, "Votre choix : ");
			scanf("%i",&joueur);

/* Traitement du choix de l'utilisateur */
			wclear(ZoneMenu);
			switch(joueur)
			{	case 1:	mvwprintw(ZoneMenu, y, x, "Vous voulez jouer en solitaire à notre jeu: "); nbjoueur = 1; /*Partie(nbjoueur);*/ break;
				case 2: mvwprintw(ZoneMenu, y, x, "Vous voulez jouer à deux à notre jeu: "); nbjoueur = 2; /*Partie(nbjoueur);*/ break;
				case 3: mvwprintw(ZoneMenu, y, x, "Vous voulez jouer à trois à notre jeu: "); nbjoueur = 3; /*Partie(nbjoueur);*/ break;
				case 4: mvwprintw(ZoneMenu, y, x, "Vous voulez jouer à quatre à notre jeu: "); nbjoueur = 4; /*Partie(nbjoueur);*/ break;
				case 5: break;
				default: mvwprintw(ZoneMenu, y, x, "Erreur: votre choix doit etre compris entre 1 et 4 inclus.\n");
			}
			endwin();
			
		}
	while(joueur != 5);

	mvwprintfw(ZoneMenu, y, x, "\nMerci d'avoir jouer à notre jeu !\n");
	return EXIT_SUCCESS;
}
