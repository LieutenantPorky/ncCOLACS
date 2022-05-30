#ifndef DICE_H
#define DICE_H
#define NUM_DICE 7
#include "options.h"
#include "curses.h"

typedef struct SelectionState SelectionState;
typedef struct Sheet Sheet;

static const int DICE[] = {20,4,6,8,10,12,100};

typedef struct DiceBox {
	WINDOW* w;
}DiceBox;

void drawDiceBox(DiceBox*);
void rollDieDiag(SelectionState*, Sheet*);

#endif
