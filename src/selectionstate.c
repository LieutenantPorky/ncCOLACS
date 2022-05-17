#include "selectionstate.h"

SelectionState* getNewState() {
	SelectionState* new_state = malloc(sizeof(SelectionState));
	new_state->SelectedBox = ATTRIBUTES;
	new_state->SelectedItem = 0;
	return new_state;
}


void processInput(Sheet* sheet, SelectionState* state){

	int ch = wgetch(stdscr);

	switch(state->SelectedBox){
		case ATTRIBUTES:
			execInputATTRIBUTES(ch,state);
			break;
		
		case CHARACTER:
			execInputCHARACTER(ch,state);
			break;

		case WEAPONS:
			execInputWEAPONS(ch,state);
			break;
	}

	drawSheet(sheet);

	mvprintw(40,40,"item: %d box: %d",state->SelectedItem, state->SelectedBox);


}

void execInputATTRIBUTES(int ch, SelectionState* state) {
	switch (ch){
		case KEY_DOWN:
			state->SelectedItem = (state->SelectedItem +1) % NUM_ATTRIBUTES;
			break;
			


		case KEY_UP:
			state->SelectedItem = (state->SelectedItem -1 + NUM_ATTRIBUTES) % NUM_ATTRIBUTES;
			break;
	}

}


void execInputCHARACTER(int ch, SelectionState* state) {

}


void execInputWEAPONS(int ch, SelectionState* state) {

}





