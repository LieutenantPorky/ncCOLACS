#include "sheet.h"
#include "selectionstate.h"

void drawAttributesBox(AttributesBox * a){
	if (DEBUG){
		for (int i =0; i<NUM_ATTRIBUTES; i++){
			printf("%s: %d%c\n",ATTRIBUTE_NAMES[i], a->attributevalues[i], (a->proficiencies[i])? '*' : ' ');
		}
		return;
	}
	drawBorders(a->w);
	WINDOW* window = a->w;

	for(int i = 0; i<NUM_ATTRIBUTES;i++){
		int y = 1 + i*4;
		mvwprintw(window,y,1,"-------");
		wattron(window,A_BOLD);
		if (state->SelectedBox == ATTRIBUTES && state->SelectedItem == i) {wattron(window, A_BLINK);}
		char * flag = (char*) a->proficiencies[i] ? "*" : " ";
		mvwprintw(window,y+1,1,"%s%s    ",flag,ATTRIBUTE_NAMES[i]);
		wattroff(window,A_BOLD);
		mvwprintw(window,y+2,1," %d(%+d) ", a->attributevalues[i], getBonus(a->attributevalues[i]));
		if (state->SelectedBox == ATTRIBUTES && state->SelectedItem == i) {wattroff(window, A_BLINK);}
		mvwprintw(window,y+3,1,"-------");



	}

	wrefresh(a->w);
}

void rollAttributeDiag(SelectionState* state, Sheet* sheet){

	int att = getBonus(sheet->attributesbox->attributevalues[state->SelectedItem]);
	
	int roll = 1+ (rand() % 20);

	
	// Display the results
	
	int mx, my;

	getmaxyx(stdscr, my,mx);

	WINDOW* win = newwin(4,10,my/2-2,mx/2-5);

	// notify if a critical hit has happened
	if (roll ==20) {
		wattron(win, A_BOLD);
		drawBorders(win);
		mvwprintw(win,1,1,"CRITICAL");
		mvwprintw(win,2,1,"  HIT!  ");
		wattroff(win, A_BOLD);

		int ch = wgetch(win);
		werase(win);
		wrefresh(win);


	}


	drawBorders(win);
	wattron(win, A_BOLD);
	mvwprintw(win,1,1,"%s SAVE", ATTRIBUTE_NAMES[state->SelectedItem]);
	wattroff(win, A_BOLD);
	mvwprintw(win,2,4,"%d",roll + att);

	wrefresh(win);

	int ch = wgetch(win);
	werase(win);
	wrefresh(win);


}

