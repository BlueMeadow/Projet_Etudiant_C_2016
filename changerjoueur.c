#include <stdio.h>
#include <stdlib.h>

int ChangerJoueur(){
	return joueur = joueur%nb_joueur+1;
	
}
int main(){
	int joueur =0;
	joueur=ChangerJoueur(joueur);
	//printf("%i\n",joueur);
}
