#include "weapons.h"
#include "selectionstate.h"
#include "curses.h"

void drawWeaponsBox(WeaponsBox* w, Sheet* s) {
	if (DEBUG) {
		Weapon *cw;
		printf("numweapons: %d\n",w->numweapons);
		for(int i=0;i<w->numweapons;i++) {
			cw=&w->weapons[i];
			printf("%s: %dd%d+%d\n",cw->name,cw->numdice,cw->die,s->attributesbox->attributevalues[cw->attr]);
		}
		return;
	}
	drawBorders(w->w);
	WINDOW* window = w->w;

	int name_len = 1;
	for(int i =0; i<w->numweapons;i++){
		Weapon * wp = &(w->weapons[i]);
		int new_name_len = strlen(wp->name);
		if (new_name_len>name_len){name_len = new_name_len;}
	}

	for(int i =0; i<w->numweapons;i++){
		Weapon * wp = &(w->weapons[i]);


		if (state->SelectedBox == WEAPONS && state->SelectedItem == i) {wattron(window, A_BLINK);}
		mvwprintw(window,1+2*i,1,"%s",wp->name);
		if (state->SelectedBox == WEAPONS && state->SelectedItem == i) {wattroff(window, A_BLINK);}

		wattron(window, A_BOLD);
		mvwprintw(window,1+2*i,name_len+2,"| %dD%d + %d |",wp->numdice,wp->die, 
			getBonus(s->attributesbox->attributevalues[wp->attr]));
		wattroff(window,A_BOLD);
	}

	wrefresh(w->w);
}

void addWeapon(WeaponsBox* wb, Weapon* w){
	// add a new weapon to the weaponsbox
	wb->numweapons++;
	wb->weapons = realloc(wb->weapons, wb->numweapons * sizeof(Weapon));
	wb->weapons[wb->numweapons - 1]= *w;
}


void rollAttack(SelectionState* state, Sheet* sheet,enum ATTACK_STATUS advantage) {
	
	// Calculate hit and damage rolls first
	int hit;
	int damage = 0;

	Weapon* wp = &sheet->weaponsbox->weapons[state->SelectedItem];
	int att = getBonus(sheet->attributesbox->attributevalues[wp->attr]);
	
	int roll = 1+ (rand() % 20);

	if (advantage != NORMAL) {

		int newroll = 1+ (rand() % 20);

		if (advantage == DISADVANTAGE){
			roll = (roll < newroll) ? roll : newroll;
		}
		else {
			roll = (roll > newroll) ? roll : newroll;
		}
	}
	hit = roll + att + getProficiency(sheet->characterbox->exp);


	for (int i=0; i< wp->numdice;i++){
		damage += 1+(rand() % wp->die);
	}

	damage += att;

	// Display the results
	
	int mx, my;

	getmaxyx(stdscr, my,mx);

	WINDOW* win = newwin(4,10,my/2-2,mx/2-5);

	// notify if a critical hit has happened
	if (roll ==20 || advantage == CRIT) {
		wattron(win, A_BOLD);
		drawBorders(win);
		mvwprintw(win,1,1,"CRITICAL");
		mvwprintw(win,2,1,"  HIT!  ");
		wattroff(win, A_BOLD);

		int ch = wgetch(win);
		werase(win);
		wrefresh(win);

		// Roll twice if crit

		for (int i=0; i< wp->numdice;i++){
			damage += 1+(rand() % wp->die);
		}

	}


	drawBorders(win);
	wattron(win, A_BOLD);
	mvwprintw(win,1,1,"HIT");

	if (advantage == ADVANTAGE) {mvwprintw(win,1,4,"+");}
	if (advantage == DISADVANTAGE) {mvwprintw(win,1,4,"-");}

	mvwprintw(win,1,6,"DMG");
	wattroff(win, A_BOLD);
	mvwprintw(win,2,1,"%d",hit);
	mvwprintw(win,2,6,"%d",damage);

	wrefresh(win);

	int ch = wgetch(win);
	werase(win);
	wrefresh(win);


}



