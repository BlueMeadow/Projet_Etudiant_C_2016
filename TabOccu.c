#include <stdio.h>
#include <stdlib.h>
//

void TabOccurences(){

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
}
