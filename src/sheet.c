#include "sheet.h"
#include "selectionstate.h"

void drawBorders(WINDOW * screen) {
	int x;
	int y;
	getmaxyx(screen, y,x);
	for (int i = 0; i<y; i++) {mvwaddch(screen, i, 0, '|');}
	for (int i = 0; i<y; i++) {mvwaddch(screen, i, x-1, '|');}
	for (int i = 0; i<x; i++) {mvwaddch(screen, 0, i, '-');}
	for (int i = 0; i<x; i++) {mvwaddch(screen, y-1, i, '-');}

	mvwaddch(screen, 0, 0, '+');
	mvwaddch(screen, y-1, 0, '+');
	mvwaddch(screen, 0, x-1, '+');
	mvwaddch(screen, y-1, x-1, '+');
}

void drawVertical(WINDOW * screen, int iy, int fy, int x) {
	for (int i = iy; i<fy;i++) {mvwaddch(screen,i,x, '|');}
	mvwaddch(screen,iy,x,'+');
	mvwaddch(screen,fy,x,'+');

}

void drawHorizontal(WINDOW * screen, int ix, int fx, int y) {
	for (int i = ix; i<fx;i++) {mvwaddch(screen,y,i, '-');}
	mvwaddch(screen,y,ix,'+');
	mvwaddch(screen,y,fx,'+');

}

void populateWindows(Sheet* s) {
	int MAIN_X;
	int MAIN_Y;
	getmaxyx(stdscr,MAIN_Y,MAIN_X);

	// character box
	int c_x = 0;
	int c_y = 0;
	int c_h = 4;
	int c_w = MAIN_X;

	// attributes box
	int a_x = 0;
	int a_y = c_y+c_h+1;
	int a_h = 2+NUM_ATTRIBUTES*4;
	int a_w = 10;

	// status box
	int s_x = a_x+a_w+1;
	int s_y = c_y+c_h+1;
	int s_h = 8;
	int s_w = 21;

	// weapons box
	int w_x = a_x+a_w+1;
	int w_y = s_y+s_h+1;
	int w_h = 2+ 2 * s->weaponsbox->numweapons;
	int w_w = MAIN_X/2;



	s->characterbox->w = newwin(c_h,c_w,c_y,c_x);
	s->attributesbox->w = newwin(a_h,a_w,a_y,a_x);
	s->statusbox->w = newwin(s_h,s_w,s_y,s_x);
	s->weaponsbox->w = newwin(w_h,w_w,w_y,w_x);
}

void drawSheet(Sheet* s){
	drawCharacterBox(s->characterbox);
	drawAttributesBox(s->attributesbox);
	drawStatusBox(s->statusbox,s);
	drawWeaponsBox(s->weaponsbox,s);
}






