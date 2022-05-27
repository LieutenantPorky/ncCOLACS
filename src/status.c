#include "sheet.h"
#include "selectionstate.h"
#include "curses.h"

void drawStatusBox(StatusBox* s, Sheet* sheet){

	WINDOW* win = s->w;

	int x;
	int y;

	getmaxyx(win,y,x);

	if (state->SelectedBox == STATUS) {wattron(win,A_BLINK);}
	drawBorders(win);
	if (state->SelectedBox == STATUS) {wattroff(win,A_BLINK);}
	
	wattron(win,A_BOLD);
	mvwprintw(win,3,3,"HP --- + ");
	wattroff(win,A_BOLD);

	mvwprintw(win,2,6,"   ");
	mvwprintw(win,2,6,"%d", s->currentHP);
	mvwprintw(win,4,6,"   ");
	mvwprintw(win,4,6,"%d", s->maxHP);

	mvwprintw(win,3,12,"   ");
	mvwprintw(win,3,12,"%d",s->bonusHP);

	drawHorizontal(win,0,x-1,5);

	wattron(win,A_BOLD);
	mvwprintw(win,6,3,"AC      I  ");
	wattroff(win,A_BOLD);
	mvwprintw(win,6,6,"%d",s->AC);
	mvwprintw(win,6,13,"%d",s->initiative);




	wrefresh(win);
}
