#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int QuiCommence(int nb_joueur){
	int joueur;
	int i;
	int com[4]={0,0,0,0};
	int max=0;
	int retient;
	srand(time(NULL)); // initialisation de rand
	for(joueur=0;joueur<nb_joueur;joueur++){
		com[joueur] = rand()%6+1;
		printf("Les dés sont %i.\n", com[joueur]);
		if(max<com[joueur]){
			max=com[joueur];
			retient=joueur;
		}
	}
	retient++;
	printf("le joueur %i ayant fais le plus gros score c'est lui qui commence.\n",retient);
	return retient;
}
int main(){
	QuiCommence(4);
}
