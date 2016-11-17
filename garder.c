#include <stdio.h>
#include <stdlib.h>

int Garder[5]={0,0,0,0,0};
void Garde(){
	int fini=0;
	int i;
	int choix;
	while(fini=0){
		printf("choisissez les dés a garder");
		switch(Choix){
			case 1:
				Garder[0]=1;
				break;
			case 2:
				Garder[1]=1;
				break;
			case 3:
				Garder[2]=1;
				break;
			case 4:
				Garder[3]=1;
				break;
			case 5:
				Garder[4]=1;
				break;
			case 6:
				fini=1;
				break;
		}
	}
	//for(i=0;i<4;i++){
	//	printf("%i",Garder[i]);
	//}
	//printf("%i",Garder[i]);
	
}
int main(){
	Garde();
}
		
