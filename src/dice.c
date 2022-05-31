#include "dice.h"
#include "selectionstate.h"
#include "options.h"

void drawDiceBox(DiceBox* d){
	
	drawBorders(d->w);

	for (int i=0; i<NUM_DICE;i++){
		mvwprintw(d->w,2*i,1,"----");
		wattron(d->w,A_BOLD);
		if (state->SelectedBox == DICEBOX & state->SelectedItem == i){wattron(d->w,A_BLINK);}
		mvwprintw(d->w,2*i+1,1,"D%d",DICE[i]);
		if (state->SelectedBox == DICEBOX & state->SelectedItem == i){wattroff(d->w,A_BLINK);}
		wattroff(d->w,A_BOLD);
		//mvwprintw(d->w,3*i+2,1,"----");
	}

	wrefresh(d->w);

}

void rollDieDiag(SelectionState* state, Sheet* s) {

	int die = DICE[state->SelectedItem];
	
	// dialogue box to choose number of dice
	int mx, my;
	getmaxyx(stdscr, my,mx);
	WINDOW* w1 = newwin(4,14,my/2-2,mx/2-7);

	drawBorders(w1);
	mvwprintw(w1,1,1,"Rolling D%d",die);
	mvwprintw(w1,2,1,"Number: ");
	wrefresh(w1);

	char input_str[STR_SIZE];
	nocbreak();
	echo();
	wgetstr(w1,input_str);
	cbreak();
	noecho();
	werase(w1);
	wrefresh(w1);

	drawSheet(s);

	int numdice =1;

	int res = sscanf(input_str,"%d",& numdice);

	refresh();

	if (res && numdice > 1){

		int total = 0;

		int w_x = numdice * 4+1;
		w_x = (w_x>10) ? w_x : 10;
		WINDOW* w2 = newwin(4,w_x,my/2-2, mx/2 - w_x/2);

		for (int i = 0; i<numdice; i++) {
			int roll = (rand()%die)+1;
			if (die==20 && roll == 20) {wattron(w2,A_BOLD);}
			mvwprintw(w2,1,1+4*i,"%d, ",roll);
			if (die==20 && roll == 20) {wattroff(w2,A_BOLD);}
			total+=roll;
		}

		drawBorders(w2);
		wattron(w2,A_BOLD);
		mvwprintw(w2,2,1,"TOTAL: %d",total);
		wattroff(w2,A_BOLD);
		wrefresh(w2);

		wgetch(w2);
		werase(w2);
		wrefresh(w2);
	}
	else {
		WINDOW* w2 = newwin(4,6,my/2-2,mx/2-3);
		wattron(w2,A_BOLD);
		mvwprintw(w2,1,1,"D%d:",die);
		wattroff(w2,A_BOLD);
		int roll = (rand()%die)+1;
		if (die==20 && roll == 20) {wattron(w2,A_BOLD);}
		mvwprintw(w2,2,1," %d",roll);
		if (die==20 && roll == 20) {wattroff(w2,A_BOLD);}
		drawBorders(w2);
		wrefresh(w2);

		wgetch(w2);
		werase(w2);
		wrefresh(w2);

	}

}
