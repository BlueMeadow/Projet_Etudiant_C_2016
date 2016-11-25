#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//

int De[5] = {0, 0 , 0 , 0, 0};

int main(){
	//pour que se soit vraiment aleatoire
	srand(time(0));
	for(int i = 0; i < 5; i++){
		if(garder[i] == 0){	
			//choisie un chiffre entre 1 et 6 
			De[i] = rand()%6+1;
			printf("Les dés sont %i.\n", De[i]);
		}
	}
}
