#include "sheet.h"
#include <curses.h>


void addEquipmentDiag(Sheet* s, WINDOW* w);
void deleteEquipmentDiag(Sheet* s, WINDOW* w, int index);
void editEquipmentDiag(Sheet* s, WINDOW* w, int index);
void displayEquipmentDiag(Sheet* s, WINDOW* w, int index);
void editEquipment(Equipment* e, WINDOW* w);
void drawEquipment(Sheet* s, WINDOW* w, int selected); 



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
	int selected = 0;

	while (ch != ESC) {
		werase(e_win);
		wattron(e_win, A_BOLD);
		mvwprintw(e_win,1,e_x/2-5,"EQUIPMENT");
		drawBorders(e_win);
		wattroff(e_win,A_BOLD);
		drawEquipment(s,e_win, selected);
		wrefresh(e_win);


		ch = wgetch(e_win);

		switch(ch) {
			case KEY_DOWN:
				selected = (selected + 1) % s->equipmentbox->NumEquipment;
				break;

			case KEY_UP:
				selected = (selected - 1 + s->equipmentbox->NumEquipment) % s->equipmentbox->NumEquipment;
				break;

			case 'a':
				addEquipmentDiag(s, e_win);
				break;

			case 'e':
				editEquipmentDiag(s,e_win,selected);
				break;

			case ENTER:
				displayEquipmentDiag(s,e_win,selected);
				break;

		}
		mvwprintw(e_win,34,1,"%d", ch);
		wrefresh(e_win);

	}


	werase(e_win);
	wrefresh(e_win);
	delwin(e_win);



}

void drawEquipment(Sheet* s, WINDOW* w, int selected) {
	for(int i =0; i<s->equipmentbox->NumEquipment; i++) {
		if (i==selected) {wattron(w,A_BLINK);}
		mvwprintw(w,4+i*2,4,"%s",s->equipmentbox->Equipment[i].Name);
		if (i==selected) {wattroff(w,A_BLINK);}
	}
}

void displayEquipmentDiag(Sheet* s, WINDOW* w, int selected) {

	Equipment* e = & s->equipmentbox->Equipment[selected];
	int e_x;
	int e_y;

	int edit_w = 80;
	int edit_h = 20;

	getmaxyx(w,e_y,e_x);

	WINDOW* editw = newwin(edit_h, edit_w, e_y/2 - edit_h/2, e_x/2-edit_w/2);
	keypad(editw, TRUE);  /* enable keyboard mapping */


	//WINDOW* editw = newwin(edit_h, edit_w, e_y/2 - edit_h/2, e_x/2-edit_w/2);
	//
	// Keep Name and Description inputs in separate windows for text wrapping

	WINDOW* name_w = newwin(1,edit_w-8,e_y/2 - edit_h/2 + 1,e_x/2-edit_w/2 + 7);
	WINDOW* description_w = newwin(edit_h-5,edit_w-2,e_y/2 - edit_h/2 + 4, e_x/2-edit_w/2 + 1);


	int ch = 'a';

	while (ch != ESC){

		wattron(editw,A_BOLD);
		mvwprintw(editw,1,1,"NAME: ");
		mvwprintw(editw,3,1,"DESCRIPTION: ");
		wattroff(editw,A_BOLD);

		drawBorders(editw);
		wrefresh(editw);

		mvwprintw(name_w,0,0,"%s",e->Name);
		wrefresh(name_w);

		mvwprintw(description_w,0,0,"%s",e->Description);
		wrefresh(description_w);

		ch = wgetch(editw);

	}
	
	werase(name_w);
	werase(description_w);
	werase(editw);

	delwin(name_w);
	delwin(description_w);
	delwin(editw);


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



	editEquipment(neweq, w);
	addEquipment(s->equipmentbox, neweq);

}

void editEquipmentDiag(Sheet* s, WINDOW* w, int index){
	editEquipment(& s->equipmentbox->Equipment[index],w);
}

void editEquipment(Equipment* e, WINDOW* w){

	int e_x;
	int e_y;

	int edit_w = 80;
	int edit_h = 20;

	getmaxyx(w,e_y,e_x);

	WINDOW* editw = newwin(edit_h, edit_w, e_y/2 - edit_h/2, e_x/2-edit_w/2);
	keypad(editw, TRUE);  /* enable keyboard mapping */


	//WINDOW* editw = newwin(edit_h, edit_w, e_y/2 - edit_h/2, e_x/2-edit_w/2);
	//
	// Keep Name and Description inputs in separate windows for text wrapping
	
	WINDOW* name_w = newwin(1,edit_w-8,e_y/2 - edit_h/2 + 1,e_x/2-edit_w/2 + 7);
	WINDOW* description_w = newwin(edit_h-5,edit_w-2,e_y/2 - edit_h/2 + 4, e_x/2-edit_w/2 + 1);



	
	int selected = 0;
	int ch = 'a';

	WINDOW* selected_w;
	char* selected_s;
	char input_str[STR_SIZE];

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

		mvwprintw(name_w,0,0,"%s",e->Name);
		wrefresh(name_w);

		mvwprintw(description_w,0,0,"%s",e->Description);
		wrefresh(description_w);

		ch = wgetch(editw);

		switch (ch){

			case KEY_UP:
				selected = (selected + 1) % 2;
				break;

			case KEY_DOWN:
				selected = (selected - 1) % 2;
				break;

			case ENTER:


				if (selected == 0) {
					selected_w = name_w;
					selected_s = e->Name;
				} else {
					selected_w = description_w;
					selected_s = e->Description;
				}

				werase(selected_w);
				wrefresh(selected_w);

				nocbreak();
				echo();
				wgetstr(selected_w,input_str);

				if (strlen(input_str)) {strcpy(selected_s,input_str);}
				

				cbreak();
				noecho();



				break;
		}
	}
	
	werase(name_w);
	werase(description_w);
	werase(editw);

	delwin(name_w);
	delwin(description_w);
	delwin(editw);


}
