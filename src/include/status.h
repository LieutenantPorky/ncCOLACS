#ifndef STATUS_H
#define STATUS_H

#include "options.h"
#include "curses.h"

typedef struct SelectionState SelectionState;
typedef struct Sheet Sheet;

typedef struct StatusBox{
	int maxHP;
	int currentHP;
	int bonusHP;
	int hitdie;
	int numhitdice;
	int AC;
	int initiative;
	WINDOW* w;
} StatusBox;

void drawStatusBox(StatusBox*, Sheet*);


#endif
