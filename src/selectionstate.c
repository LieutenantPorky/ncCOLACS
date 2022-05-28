#include "selectionstate.h"
#include "savesheet.h"

WINDOW * hintwindow;
int x;
int y;


SelectionState* getNewState() {
	SelectionState* new_state = malloc(sizeof(SelectionState));
	new_state->SelectedBox = ATTRIBUTES;
	new_state->SelectedItem = 0;

	getmaxyx(stdscr,y,x);
	hintwindow = newwin(4,x,y-4,0);
	return new_state;
}

void evalHint(SelectionState* s) {

	werase(hintwindow);
	switch(s->SelectedBox){

		case ATTRIBUTES:
			mvwaddstr(hintwindow,1,0,
					"s: save   "
				 );
			break;

		case WEAPONS:
			mvwaddstr(hintwindow,1,0,
					"s: save  r: roll weapon  a: roll with advantage  d: roll with disadvantage  c: roll crit"
				 );
			break;

		case CHARACTER:
			mvwaddstr(hintwindow,1,0,
					"s: save  e: add Exp  g-a: add Gold  g-r: remove Gold"
				 );
			break;

		case STATUS:
			mvwaddstr(hintwindow,1,0,
					"s: save  r: long rest   h-a: heal amount  h-d: short rest heal"
				 );
			mvwaddstr(hintwindow,2,0,
					"b: add bonus HP  d: add damage  i: roll initiative"
				 );
			break;
	}


}


void processInput(Sheet* sheet, SelectionState* state){

	drawSheet(sheet);
	int ch = wgetch(stdscr);

	switch(ch) {
		case 's':
			saveSheetDiag(sheet);
			break;

	default: 
		switch(state->SelectedBox){
			case ATTRIBUTES:
				execInputATTRIBUTES(ch,state,sheet);
				break;

			case CHARACTER:
				execInputCHARACTER(ch,state,sheet);
				break;

			case WEAPONS:
				execInputWEAPONS(ch,state,sheet);
				break;

			case STATUS:
				execInputSTATUS(ch,state,sheet);
				break;
		}
	}

	drawSheet(sheet);

	evalHint(state);
	drawHorizontal(hintwindow,0,x-1,0);
	wrefresh(hintwindow);
	mvprintw(40,40,"item: %d box: %d",state->SelectedItem, state->SelectedBox);


}

void execInputATTRIBUTES(int ch, SelectionState* state, Sheet* sheet) {
	switch (ch){
		case KEY_DOWN:
			state->SelectedItem = (state->SelectedItem +1) % NUM_ATTRIBUTES;
			break;
			


		case KEY_UP:
			
			if (state->SelectedItem == 0) {state->SelectedBox = CHARACTER;}
			else{state->SelectedItem = (state->SelectedItem -1 + NUM_ATTRIBUTES) % NUM_ATTRIBUTES;}
			break;

		case KEY_RIGHT:
			
			if (state->SelectedItem <NUM_ATTRIBUTES/2){
				state->SelectedBox = STATUS;
				state->SelectedItem = 0;
			}
			else{
				state->SelectedBox = WEAPONS;
				state->SelectedItem = 0;
			}
			break;
	}


}


void execInputWEAPONS(int ch, SelectionState* state, Sheet* sheet) {
	switch (ch){
		case KEY_DOWN:
			state->SelectedItem = (state->SelectedItem +1) % sheet->weaponsbox->numweapons;
			break;
			


		case KEY_UP:
			if (state->SelectedItem == 0) {state->SelectedBox = STATUS;}
			else{state->SelectedItem = (state->SelectedItem -1 + sheet->weaponsbox->numweapons) % sheet->weaponsbox->numweapons;}
			break;

		case KEY_LEFT:
			state->SelectedBox = ATTRIBUTES;
			state->SelectedItem = 0;
			break;

		case 'r':
			rollAttack(state, sheet, NORMAL);
			break;

		case 'a':
			rollAttack(state, sheet, ADVANTAGE);
			break;

		case 'd':
			rollAttack(state, sheet, DISADVANTAGE);
			break;
		case 'c':
			rollAttack(state, sheet, CRIT);
			break;
	}


}


void execInputCHARACTER(int ch, SelectionState* state, Sheet* sheet) {
	switch (ch){
		case KEY_DOWN:
			state->SelectedBox = ATTRIBUTES;
			break;
			


		case KEY_UP:
			state->SelectedBox = ATTRIBUTES;
			break;

		case 'e':
			addExpDiag(sheet);
			break;

		case 'g':
			int newch = wgetch(stdscr);

			switch (newch) {
				case 'a':
					addGoldDiag(sheet);
					break;
				case 'r':
					removeGoldDiag(sheet);
					break;
			}
			break;



	}


}


void execInputSTATUS(int ch, SelectionState* state, Sheet* sheet) {
	switch (ch){
		case KEY_UP:
			state->SelectedBox = CHARACTER;
			break;

		case KEY_DOWN:
			state->SelectedBox = WEAPONS;
			break;

		case KEY_LEFT:
			state->SelectedBox = ATTRIBUTES;
			break;

		case 'r':
			resetDiag(sheet);
			break;

		case 'h':
			int newch = wgetch(stdscr);
			switch(newch) {

				case 'a':
					healDiag(sheet);
					break;
				
				case 'd':
					healHDDiag(sheet);
					break;
			}
			break;

		case 'b':
			addBonusHPDiag(sheet);
			break;

		case 'd':
			damageDiag(sheet);
			break;


	}

}





