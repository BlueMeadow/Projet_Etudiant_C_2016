#include <stdio.h>
#include <stdlib.h>

int ChangerJoueur(){
	return joueur = (joueur+1)%nb_joueur;
	
}
int main(){
	int joueur =0;
	joueur=ChangerJoueur(joueur);
	//printf("%i\n",joueur);
	
}
