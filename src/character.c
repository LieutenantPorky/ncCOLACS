#include "sheet.h"
#include "selectionstate.h"

void drawCharacterBox(CharacterBox* c){
	if (DEBUG){
		printf("name: %s, class: %s, exp: %d, gold: %d\n", c->name,c->classname,c->exp,c->gold);
		return;
	}

	WINDOW* window = c->w;
	if (state->SelectedBox == CHARACTER) {wattron(window,A_BLINK);}
	drawBorders(window);
	if (state->SelectedBox == CHARACTER) {wattroff(window,A_BLINK);}
	int x;
	int y;
	getmaxyx(window, y,x);

	mvwprintw(window,1,1,"LVL %d %s (+%d)", getLVL(c->exp), c->classname, getProficiency(c->exp));

	wattron(window,A_BOLD);
	mvwprintw(window,2,1,"GOLD: ");
	wattroff(window,A_BOLD);
	mvwprintw(window,2,8,"          ");
	mvwprintw(window,2,8,"%d",c->gold);

	int namelen = strlen(c->name);
	char buff[2* STR_SIZE];
	sprintf(buff,"LVL %d %s (+ %d)", getLVL(c->exp), c->classname, getProficiency(c->exp));

	// choose if to align on center or right
	int namex;
	if (namelen/2 + strlen(buff) + 4 < x/2) {namex = x/2 - namelen/2;}
	else {namex = x - namelen - 1;}
	wattron(window,A_BOLD);
	mvwprintw(window,1,namex,"%s",c->name);
	wattroff(window,A_BOLD);

	wrefresh(c->w);
}


void addExpDiag(Sheet* sheet) {
	int mx, my;

	getmaxyx(stdscr, my,mx);

	WINDOW* win = newwin(4,20,my/2-2,mx/2-10);
	drawBorders(win);

	char instr[STR_SIZE];
	mvwprintw(win,1,1,"Current Exp: %d", sheet->characterbox->exp);
	mvwprintw(win,2,1,"Add Exp: ");

	wrefresh(win);
	
	nocbreak();
	echo();
	wgetstr(win,instr);

	cbreak();
	noecho();

	werase(win);
	wrefresh(win);

	int newexp = 0;
	if (sscanf(instr,"%d",& newexp)) {sheet->characterbox->exp += newexp;}

}

void addGoldDiag(Sheet* sheet) {
	int mx, my;

	getmaxyx(stdscr, my,mx);

	WINDOW* win = newwin(4,20,my/2-2,mx/2-10);
	drawBorders(win);

	char instr[STR_SIZE];
	mvwprintw(win,1,1,"Add Gold");
	mvwprintw(win,2,1,"Amount: ");

	wrefresh(win);
	
	nocbreak();
	echo();
	wgetstr(win,instr);

	cbreak();
	noecho();

	werase(win);
	wrefresh(win);

	int goldamount = 0;
	if (sscanf(instr,"%d",& goldamount)) {sheet->characterbox->gold += goldamount;}
}

void removeGoldDiag(Sheet* sheet){
	int mx, my;

	getmaxyx(stdscr, my,mx);

	WINDOW* win = newwin(4,20,my/2-2,mx/2-10);
	drawBorders(win);

	char instr[STR_SIZE];
	mvwprintw(win,1,1,"Spend Gold");
	mvwprintw(win,2,1,"Amount: ");

	wrefresh(win);
	
	nocbreak();
	echo();
	wgetstr(win,instr);

	cbreak();
	noecho();

	werase(win);
	wrefresh(win);

	int goldamount = 0;
	if (sscanf(instr,"%d",& goldamount)) {
		if(goldamount <= sheet->characterbox->gold){
			sheet->characterbox->gold -= goldamount;
		} else {
			werase(win);
			wrefresh(win);
			wattron(win,A_BOLD);
			drawBorders(win);
			mvwprintw(win,1,1,"Insufficient");
			mvwprintw(win,2,1,"Gold");
			wattroff(win,A_BOLD);
			int ch=wgetch(win);
			werase(win);
			wrefresh(win);
		}
	}
}
