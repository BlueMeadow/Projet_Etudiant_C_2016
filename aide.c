#include <stdio.h>
#include <stdlib.h>
int De[5]={3,3,6,5,4};

void aide(int isAide){//demande d'entrer 1 si on veut l'aide
	int y=2;
	int x=2;
	attron(A_BOLD);
	mvwprintw(ZoneAide, 2, 13, "AIDE");
	attrof(A_BOLD);
	y++;
	if(isAide){
		if(isBrelan()){
			mvwprintw(ZoneAide, y, x, "il y a un brelan dans les dés lancer");
			y++;
		}
		if(isCarre()){
			mvwprintw(ZoneAide, y, x, "il y a un Carre dans les dés lancer");
			y++;
		}
		if(isFull()){
			mvwprintw(ZoneAide, y, x, "il y a un Full dans les dés lancer");
			y++;
		}
		if(isPtSuite()){
			mvwprintw(ZoneAide, y, x, "il y a une Petite Suite dans les dés lancer");
			y++;
		}
		if(isGdSuite()){
			mvwprintw(ZoneAide, y, x, "il y a une Grande Suite dans les dés lancer");
			y++;
		}
		if(isYahtzee()){
			mvwprintw(ZoneAide, y, x, "il y a un Yahtzee dans les dés lancer");
			y++;
		}
	}
	else{
		mvwprintw(ZoneAide, y, x, "l'aide n'est pas activée");
	}
}