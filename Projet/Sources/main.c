#include "../include/Global.h"

int main(){
/* \fn main
* \brief Initialise l'affichage ncurses, lance le menu
*/	
	initscr();
	cbreak();
	noecho();
	refresh();
	EcranTitre();
	do
	{
		Menu();
	} while (1);	
}
