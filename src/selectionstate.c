#include "selectionstate.h"

SelectionState* getNewState() {
	SelectionState* new_state = malloc(sizeof(SelectionState));
	new_state->SelectedBox = ATTRIBUTES;
	new_state->SelectedItem = 0;
	return new_state;
}


void processInput(Sheet* sheet, SelectionState* state){

	drawSheet(sheet);
	int ch = wgetch(stdscr);

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
	}

	drawSheet(sheet);
	mvprintw(40,40,"item: %d box: %d",state->SelectedItem, state->SelectedBox);


}

void execInputATTRIBUTES(int ch, SelectionState* state, Sheet* sheet) {
	switch (ch){
		case KEY_DOWN:
			state->SelectedItem = (state->SelectedItem +1) % NUM_ATTRIBUTES;
			break;
			


		case KEY_UP:
			state->SelectedItem = (state->SelectedItem -1 + NUM_ATTRIBUTES) % NUM_ATTRIBUTES;
			break;

		case KEY_RIGHT:
			state->SelectedBox = WEAPONS;
			state->SelectedItem = 0;
			break;
	}

}


void execInputWEAPONS(int ch, SelectionState* state, Sheet* sheet) {
	switch (ch){
		case KEY_DOWN:
			state->SelectedItem = (state->SelectedItem +1) % sheet->weaponsbox->numweapons;
			break;
			


		case KEY_UP:
			state->SelectedItem = (state->SelectedItem -1 + sheet->weaponsbox->numweapons) % sheet->weaponsbox->numweapons;
			break;

		case KEY_LEFT:
			state->SelectedBox = ATTRIBUTES;
			state->SelectedItem = 0;
			break;

		case 'r':
			rollAttack(state, sheet);
			break;
	}

}


void execInputCHARACTER(int ch, SelectionState* state, Sheet* sheet) {

}





