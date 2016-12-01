/**
* \file changerjoueur.c
* \brief Permet de changer de numéro de joueur
* \author Benoit COMBASTEIX
* \date 20 novembre 2016
* \fn ChangerJoueur()
* \return Livre le numéro de joueur qui suit celui qui a joué
*/

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
