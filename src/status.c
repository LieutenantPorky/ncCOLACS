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
	drawVertical(win,0,5,14);

	mvwprintw(win,1,18,"HIT DICE");
	mvwprintw(win,3,20,"%dd%d",s->numhitdice,s->hitdie);

	wattron(win,A_BOLD);
	mvwprintw(win,6,3,"AC      Initiative:  ");
	wattroff(win,A_BOLD);
	mvwprintw(win,6,6,"%d",s->AC);
	mvwprintw(win,6,23,"%d",s->initiative);




	wrefresh(win);
}

void damageDiag(Sheet* s) {
	int mx, my;

	getmaxyx(stdscr, my,mx);

	WINDOW* win = newwin(4,20,my/2-2,mx/2-10);
	drawBorders(win);

	char instr[STR_SIZE];
	mvwprintw(win,1,1,"Deal damage");
	mvwprintw(win,2,1,"Amount: ");

	wrefresh(win);
	
	nocbreak();
	echo();
	wgetstr(win,instr);

	cbreak();
	noecho();

	werase(win);
	wrefresh(win);

	int dmg = 0;
	if (sscanf(instr,"%d",& dmg)) {
		if (s->statusbox->bonusHP > dmg) {
			s->statusbox->bonusHP -= dmg;
		}
		else {
			dmg -= s->statusbox->bonusHP;
			s->statusbox->bonusHP=0;
			s->statusbox->currentHP -= dmg;
		}
	}
}

void resetDiag(Sheet* s) {
	int mx, my;

	getmaxyx(stdscr, my,mx);

	WINDOW* win = newwin(4,20,my/2-2,mx/2-10);
	wattron(win,A_BOLD);
	drawBorders(win);
	wattroff(win,A_BOLD);

	mvwprintw(win,1,1,"Taking a long rest");

	wrefresh(win);

	s->statusbox->currentHP = s->statusbox->maxHP;
	s->statusbox->bonusHP = 0;
	s->statusbox->numhitdice = getLVL(s->characterbox->exp);
	s->statusbox->initiative = 0;

	wgetch(win);

	werase(win);
	wrefresh(win);

}

void healDiag(Sheet* s) {
	int mx, my;

	getmaxyx(stdscr, my,mx);

	WINDOW* win = newwin(4,20,my/2-2,mx/2-10);
	drawBorders(win);

	char instr[STR_SIZE];
	mvwprintw(win,1,1,"Heal");
	mvwprintw(win,2,1,"Amount: ");

	wrefresh(win);
	
	nocbreak();
	echo();
	wgetstr(win,instr);

	cbreak();
	noecho();

	werase(win);
	wrefresh(win);

	int dmg = 0;
	if (sscanf(instr,"%d",& dmg)) {

		s->statusbox->currentHP += dmg;
		if (s->statusbox->currentHP > s->statusbox->maxHP) {
			s->statusbox->currentHP = s->statusbox->maxHP;
		}

	}
		
}

void healHDDiag(Sheet* s) {
	int mx, my;

	getmaxyx(stdscr, my,mx);

	WINDOW* win = newwin(4,20,my/2-2,mx/2-10);

	if (s->statusbox->numhitdice <1) {
		wattron(win,A_BOLD);
		drawBorders(win);
		mvwprintw(win,1,1,"No Hit Dice!");
		wrefresh(win);
		wattroff(win,A_BOLD);
		wgetch(win);
		werase(win);
		wrefresh(win);
		return;
	}

	if (s->statusbox->currentHP == s->statusbox->maxHP) {
		wattron(win,A_BOLD);
		drawBorders(win);
		mvwprintw(win,1,1,"HP already max");
		wrefresh(win);
		wattroff(win,A_BOLD);
		wgetch(win);
		werase(win);
		wrefresh(win);
		return;
	}
	
	int old = s->statusbox->currentHP;
	s->statusbox->currentHP += (rand()% s->statusbox->hitdie) + 1 + getBonus(s->attributesbox->attributevalues[3]);
	if(s->statusbox->currentHP > s->statusbox->maxHP){
		s->statusbox->currentHP = s->statusbox->maxHP;
	}
	s->statusbox->numhitdice -=1;


	drawBorders(win);
	mvwprintw(win,1,1,"Healed: %d", s->statusbox->currentHP - old);
	mvwprintw(win,2,1,"Remaining: %dd%d",s->statusbox->numhitdice,s->statusbox->hitdie);

	wrefresh(win);
	wgetch(win);
	werase(win);
	wrefresh(win);
		
}

void addBonusHPDiag(Sheet* s) {
	int mx, my;

	getmaxyx(stdscr, my,mx);

	WINDOW* win = newwin(4,20,my/2-2,mx/2-10);
	drawBorders(win);

	char instr[STR_SIZE];
	mvwprintw(win,1,1,"Add Bonus HP");
	mvwprintw(win,2,1,"Amount: ");

	wrefresh(win);
	
	nocbreak();
	echo();
	wgetstr(win,instr);

	cbreak();
	noecho();

	werase(win);
	wrefresh(win);

	int dmg = 0;
	if (sscanf(instr,"%d",& dmg)) {

		s->statusbox->bonusHP += dmg;

	}
		
}
