#include "../include/Global.h"

int main(){	
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
