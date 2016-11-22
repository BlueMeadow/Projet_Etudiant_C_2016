#include <stdio.h>

/**
* \fn fonctionplus.c
* \brief Permet de connaitre le résultat de la combinaison des 5 dés
* \author Nathan Oualet
*/



int De[5] = {5,2,5,2,2};

int isBrelan(){
	int i, j, cptvalide = 0;
	
	int valeuri, valeurj;
	
	for(i =0; i<5; i++){
		for( j = 4; i<j; j--){
			valeuri = De[i];
			valeurj = De[j];
			
			if (cptvalide==3) break; 
			
			if (valeuri == valeurj){
				cptvalide++;
			}		
		}
	
	}
	return ( cptvalide == 3);	
}

/*
int isCarre(){
//par benoit

}
*/
int isFull(){
	
	int tabOccu[6] = {0,0,0,0,0,0};
	
	
	//parcourt les 5 dés lancés, on incremente le nombre de valeurs trouvés
	// dans le tableau d'occurences correspondant à la valeur du dé
	for( int i = 0; i < 5; i++){
		switch(De[i]){
			case 1: tabOccu[0]++; break;
			case 2: tabOccu[1]++; break;
			case 3: tabOccu[2]++; break;
			case 4: tabOccu[3]++; break;
			case 5: tabOccu[4]++; break;
			case 6: tabOccu[5]++; break;
		}
	
	}
	int cpt3 = 0 , cpt2 = 0;
	
	//On a notre tableau d'occurences, maintenant on va circuler dans le tab d'occurences, pour voir s'il y a un full.
	
	for (int j = 0; j < 6; j++){
		
		if ( tabOccu[j]==3){
			cpt3++;
		}	
		else if( tabOccu[j] == 2){
			cpt2++;
		}	
	}
	
	if ( (cpt3 == 1) && (cpt2 == 1) ){
		return 1;
	}
	else{
		return 0;
	}

}

/*
int isPtSuite(){
//benoit


}

int isGdSuite(){
//benoit


}*/

int isYahtzee(){
	
	int tabOccu[6] = {0,0,0,0,0,0};
	
	//parcourt les 5 dés lancés, on incremente la valeur de tabOccu, quand on trouve une valeur correspondante à la position dans tab occu
	
	for( int i = 0; i < 5; i++){
		switch(De[i]){
			case 1: tabOccu[0]++; break;
			case 2: tabOccu[1]++; break;
			case 3: tabOccu[2]++; break;
			case 4: tabOccu[3]++; break;
			case 5: tabOccu[4]++; break;
			case 6: tabOccu[5]++; break;
		}
	
	}
	
	//on parcourt la tab Occurences, si on trouve 5 dans tabOccu, on trouve un Yahtzee - 5 dés de même valeur-.
	
	for (int i=0; i < 6; i++){
		if ( tabOccu[i] == 5){
			return 1;
		}
	}
	return 0;
}

int main(){
//test des fonctions précédentes.
	
	int valBrelan = isBrelan();
	
	int valYaht = isYahtzee();
	
	int valFull = isFull();
	
	if (valBrelan == 1){
		
		printf("UN brelan. \n");
	}
	else{
		printf("pas de brelan.\n");	
	}
	
	if ( valYaht == 1){
		printf("Vous avec un Yahtzee.\n");
	}
	else{
		printf("pas de yahms. \n");
	
	}
	
	if ( valFull == 1){
		printf("Vous avec un Full.\n");
	}
	else{
		printf("pas de Full.\n");
	
	}
	

}

