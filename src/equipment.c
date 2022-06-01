#include "sheet.h"
#include <curses.h>


void addEquipmentDiag(Sheet* s, WINDOW* w);
void deleteEquipmentDiag(Sheet* s, WINDOW* w, int index);
void editEquipmentDiag(Sheet* s, WINDOW* w, int index);
void editEquipment(Equipment* e, WINDOW* w);
void drawEquipment(Sheet* s, WINDOW* w); 



void equipmentDiag(Sheet* s) {
	// First, create the window to display the equipment
	
	int MAIN_X;
	int MAIN_Y;

	getmaxyx(stdscr,MAIN_Y,MAIN_X);

	int x_shrink = 10;
	int y_shrink = 6;

	WINDOW* e_win = newwin(MAIN_Y - y_shrink, MAIN_X - x_shrink, 0+y_shrink/2, 0+x_shrink/2);
	keypad(e_win, TRUE);  /* enable keyboard mapping */

	int e_x;
	int e_y;

	getmaxyx(e_win,e_y,e_x);




	wrefresh(e_win);


	// Main loop
	//
	int ch = 0;

	while (ch != ESC) {
		werase(e_win);
		wattron(e_win, A_BOLD);
		mvwprintw(e_win,1,e_x/2-5,"EQUIPMENT");
		drawBorders(e_win);
		wattroff(e_win,A_BOLD);
		drawEquipment(s,e_win);
		wrefresh(e_win);


		ch = wgetch(e_win);

		switch(ch) {
			case 'a':
				addEquipmentDiag(s, e_win);
				break;

		}
	mvwprintw(e_win,34,1,"%d", ch);
	wrefresh(e_win);

	}


	werase(e_win);
	wrefresh(e_win);
	delwin(e_win);



}

void drawEquipment(Sheet* s, WINDOW* w) {
	for(int i =0; i<s->equipmentbox->NumEquipment; i++) {
		mvwprintw(w,4+i*2,4,"%s",s->equipmentbox->Equipment[i].Name);
	}
}


void addEquipment(EquipmentBox* box, Equipment* eq){
	box->NumEquipment++;
	box->Equipment = realloc(box->Equipment,sizeof(Equipment)*box->NumEquipment);
	box->Equipment[box->NumEquipment-1] = *eq;

}

void addEquipmentDiag(Sheet* s, WINDOW* w){
	Equipment* neweq = malloc(sizeof(Equipment));
	strcpy(neweq->Name,"The ring of power");
	strcpy(neweq->Description,"Something nasty");

	int e_x;
	int e_y;

	int edit_w = 80;
	int edit_h = 20;

	getmaxyx(w,e_y,e_x);

	WINDOW* edit_win = newwin(edit_h, edit_w, e_y/2 - edit_h/2, e_x/2-edit_w/2);
	keypad(edit_win, TRUE);  /* enable keyboard mapping */

	editEquipment(neweq, edit_win);
	delwin(edit_win);
	addEquipment(s->equipmentbox, neweq);

}

void editEquipment(Equipment* e, WINDOW* editw){



	//WINDOW* editw = newwin(edit_h, edit_w, e_y/2 - edit_h/2, e_x/2-edit_w/2);
	
	int selected = 0;
	int ch = 'a';

	while (ch != ESC){

		wattron(editw,A_BOLD);
		if (selected == 0) {wattron(editw,A_BLINK);}
		mvwprintw(editw,1,1,"NAME: ");
		if (selected == 0) {wattroff(editw,A_BLINK);}

		if (selected != 0) {wattron(editw,A_BLINK);}
		mvwprintw(editw,3,1,"DESCRIPTION: ");
		if (selected != 0) {wattroff(editw,A_BLINK);}
		wattroff(editw,A_BOLD);

		drawBorders(editw);
		wrefresh(editw);
		mvwprintw(stdscr,34,1,"%d", ch);
		wrefresh(stdscr);

		ch = wgetch(editw);

		switch (ch){

			case KEY_UP:
				selected = (selected + 1) % 2;
				break;

			case KEY_DOWN:
				selected = (selected - 1) % 2;
				break;

			case ENTER:

				break;
		}
	}


}
