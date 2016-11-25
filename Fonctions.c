#include <stdio.h>

/**
* \fn fonctionplus.c
* \brief Permet de connaitre le résultat de la combinaison des 5 dés
* \author Nathan Oualet
* \version 1.0
*/

int De[5] = {1,2,3,4,5};

void TabOccurences(){

	//parcourt les 5 dés lancés, on incremente le nombre de valeurs trouvés
	// dans le tableau d'occurences correspondant à la valeur du dé

	int tabOccu[6] = {0,0,0,0,0,0};

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
}

int isBrelan(){
	int i, j, cptvalide = 0;

	int valeuri, valeurj;

	for(i =0; i<5; i++){
		for( j = 4; i<j; j--){
			valeuri = De[i];
			valeurj = De[j];
			
			//s'il trouve trois dés identiques, la condition s'arrete, et retourne le résultat
			if (cptvalide==3) break;

			if (valeuri == valeurj){
				cptvalide++;
			}
		}

	}
	return ( cptvalide == 3);
}


int isCarre(){
	int i;
	int j;
	
	int total = 0;
	
	for( i = 0; i < 5 ; i++){
		
		for( j=0; j<5; j++){
			
			if(De[i] == De[j] && i != j ){
				//i!=j pour qu'il ne compte pas si les deux sont sur la meme case
				total++;
			}
		}
		if(total == 3){
			return 1;

		}
		total=0;
	}
	return 0;
}



int isFull(){
	
	int tabOccu[6] = {0,0,0,0,0,0};

	TabOccurences();

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

//Calcul de la petit suite

int isPtSuite(){
	
	int i;
	int j;
	
	int tabOccu[6] = {0,0,0,0,0,0};

	TabOccurences();

	for(i=0;i<5;i++){
		tabOccu[De[i]-1]++;
	}

	for(j=0;j<=2;j++){
		if(tabOccu[j] > 0 && tabOccu[j+1] > 0 && tabOccu[j+2] > 0 && tabOccu[j+3] > 0)
			return 1;

	}
	return 0;
}

int isGdSuite(){
	
	int i;
	int j;
	
	int tabOccu[6] = {0,0,0,0,0,0};

	TabOccurences();

	for( i = 0;i < 5; i++){
		//compte le nombre d'occurence
		tabOccu[De[i]-1]++;
	}
	for( j=0; j<1; j++){
		if(tabOccu[0] == 1){
			//pour trouver si il y a un 1
			if((tabOccu[j] > 0) && (tabOccu[j+1] > 0) && (tabOccu[j+2] > 0) && (tabOccu[j+3] > 0) && (tabOccu[j+4] > 0)){
				return 1;
			}
		}else{
			if((tabOccu[j+1] > 0) && (tabOccu[j+2] > 0) && (tabOccu[j+3] > 0) && (tabOccu[j+4] > 0) && (tabOccu[j+5] > 0)){
				//pour trouver si il y a un six
				return 1;
			}
		}
	}
	return 0;
}
int isYahtzee(){
	
	int tabOccu[6] = {0,0,0,0,0,0};

	TabOccurences();

	//on parcourt la tab Occurences, si on trouve 5 dans tabOccu, on trouve un Yahtzee donc 5 dés de même valeur.

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
	
	int valCarre = isCarre();
	
	int valPetit = isPtSuite();
	
	int valGrand = isGdSuite();

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
	
	if ( valCarre == 1){
		printf("Vous avec un Carre.\n");
	}
	else{
		printf("pas de Carre.\n");

	}
	
	if ( valPetit == 1){
		
		printf("Vous avec une petite Suite.\n");
	}
	else{
		printf("pas de petite suite.\n");

	}
	
	if ( valGrand == 1){
		printf("Vous avec une grande suite.\n");
	}
	else{
		printf("pas de grande suite.\n");

	}

}
