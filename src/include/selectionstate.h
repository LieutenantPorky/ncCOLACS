#ifndef SELECTION_STATE
#define SELECTION_STATE

#include "sheet.h"
#include "weapons.h"

enum Boxes {
	CHARACTER,
	ATTRIBUTES,
	WEAPONS,
	STATUS,
	DICEBOX};


typedef struct SelectionState{
	enum Boxes SelectedBox;
	int SelectedItem;
} SelectionState;
extern SelectionState* state;

SelectionState* getNewState();
void processInput(Sheet*, SelectionState*);

void execInputWEAPONS(int,SelectionState*,Sheet*);
void execInputATTRIBUTES(int,SelectionState*,Sheet*);
void execInputCHARACTER(int,SelectionState*,Sheet*);
void execInputSTATUS(int,SelectionState*,Sheet*);
void execInputDICE(int,SelectionState*,Sheet*);

#endif
