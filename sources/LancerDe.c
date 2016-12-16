/**
* \file lancerDe.c
* \author Nathan OUALET et Benoir Combasteix
* \fn lancerDe()
* \return Retourne une suite de 5 dés lancés au hasard
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int De[5] = {0, 0 , 0 , 0, 0};

int lancerDe(){
	//initialisation des valeurs aléatoires, à chaque tirage
	srand(time(0));
	
	for(int i = 0; i < 5; i++){
		if(garder[i] == 0){	
			//lancement des dés et sélection d'un chiffre entre 1 et 6 avec le hasard
			De[i] = rand()%6+1;
			printf("Les dés sont %i.\n", De[i]);
		}
	}
}

int main(){
	lancerDe();
	
}
