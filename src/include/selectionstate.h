#ifndef SELECTION_STATE
#define SELECTION_STATE

#include "sheet.h"
#include "curses.h"

enum Boxes {
	CHARACTER,
	ATTRIBUTES,
	WEAPONS};


typedef struct {
	enum Boxes SelectedBox;
	int SelectedItem;
} SelectionState;
extern SelectionState* state;

SelectionState* getNewState();
void processInput(Sheet*, SelectionState*);

void execInputWEAPONS(int,SelectionState*);
void execInputATTRIBUTES(int,SelectionState*);
void execInputCHARACTER(int,SelectionState*);

#endif
