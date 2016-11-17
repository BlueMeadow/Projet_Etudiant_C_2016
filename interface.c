#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int De[5]={1};

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

void de_un(WINDOW *localwin){
	wprintw(localwin, "+-------+");
	wprintw(localwin, "|       |");
	wprintw(localwin, "|   O   |");
	wprintw(localwin, "|       |");
	wprintw(localwin, "+-------+\n");
}						
/*void de_deux(void){
	wprintw("\n+--------+");
	wprintw("\n|  O     |");
	wprintw("\n|        |");
	wprintw("\n|      O |");
	wprintw("\n+--------+\n");
}					
void de_trois(void){
	wprintw("\n+-------+");
	wprintw("\n| O     |");
	wprintw("\n|   O   |");
	wprintw("\n|     O |");
	wprintw("\n+-------+\n");
}					
void de_quatre(void){
	wprintw("+-------+");
	wprintw("\n| O   O |");
	wprintw("\n|       |");
	wprintw("\n| O   O |");
	wprintw("\n+-------+\n");
}					
void de_cinq(void){
	wprintw("\n+-------+");
	wprintw("\n| O   O |");
	wprintw("\n|   O   |");
	wprintw("\n| O   O |");
	wprintw("\n+-------+\n");
}					
void de_six(void){
	wprintw("\n+-------+");
	wprintw("\n| O   O |");
	wprintw("\n| O   O |");
	wprintw("\n| O   O |");
	wprintw("\n+-------+\n");
}
*/ 


void AffichageDe(int De[5], WINDOW *localwin)
{
	for(int i = 0 ; i < 5 ; i++)
	{
		switch(De[i])
		{
			case 1 : de_un(localwin);
			/*case 2 : de_deux();
			case 3 : de_trois();
			case 4 : de_quatre();
			case 5 : de_cinq();
			case 6 : de_six();*/
		}
	}
}
			



int main()
{	
	initscr();
	int startx, starty, width, height;
	char ch;
	WINDOW *ZoneDe;
	WINDOW *ZoneMessage;
	WINDOW *ZoneAide;
	WINDOW *ZoneScore;
	//MiseEnPlace();
	initscr();
	cbreak();
	noecho();
	refresh();
	//height = 30;
	//width = 12;
	//starty = 3;	
	//startx = 3;	
	ZoneAide = create_newwin(30,30,3,85);
	ZoneDe = create_newwin(30, 12, 3, 3);
	ZoneScore = create_newwin(20,70,3,15);
	ZoneMessage = create_newwin(10,70,23,15);
	wprintw(ZoneDe, "Hello World !");
	//AffichageDe(De, ZoneDe);
	refresh();
	do
	{
		ch = getch();
	}while (tolower(ch) != 'j');	
	endwin();			/* End curses mode		  */
	return 0;
}


WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void destroy_win(WINDOW *local_win)
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}

