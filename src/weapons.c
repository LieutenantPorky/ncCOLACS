#include "weapons.h"
#include "selectionstate.h"
#include "curses.h"


void rollAttack(SelectionState* state, Sheet* sheet) {
	
	// Calculate hit and damage rolls first
	int hit;
	int damage = 0;

	Weapon* wp = &sheet->weaponsbox->weapons[state->SelectedItem];
	int att = getBonus(sheet->attributesbox->attributevalues[wp->attr]);

	hit = 1+ (rand() % 20) + att + getProficiency(sheet->characterbox->exp);

	for (int i=0; i< wp->numdice;i++){
		damage += 1+(rand() % wp->die);
	}

	damage += att;

	// Display the results
	
	int mx, my;

	getmaxyx(stdscr, my,mx);

	WINDOW* win = newwin(4,10,my/2-2,mx/2-5);
	drawBorders(win);
	wattron(win, A_BOLD);
	mvwprintw(win,1,1,"HIT");
	mvwprintw(win,1,6,"DMG");
	wattroff(win, A_BOLD);
	mvwprintw(win,2,1,"%d",hit);
	mvwprintw(win,2,6,"%d",damage);

	wrefresh(win);

	int ch = wgetch(win);
	werase(win);
	wrefresh(win);


}



