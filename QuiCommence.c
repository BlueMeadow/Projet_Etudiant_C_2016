#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int QuiCommence(int nb_joueur){
	int joueur;
	int i;
	int com[4]={1,1,1,1};
	int max=0;
	int retient;
	int occ=1;
	srand(time(NULL)); // initialisation de rand
	for(joueur=0;joueur<nb_joueur;joueur++){
		if(com[joueur]>0){
			com[joueur] = rand()%6+1;
		}
		if(max==com[joueur]){
			occ++;
		}
		if(max<com[joueur]){
			max=com[joueur];
			retient=joueur;
			occ=1;
		}
		if(joueur+1==nb_joueur && occ >1){
			for(i=joueur;i>=0;i--){
				if(max>com[i]){
					com[i]=-1;
				}
			}
			max=0;
			joueur=-1;
		}
	}
	retient++;
	return retient;
}
int main(){
	QuiCommence(4);
}
