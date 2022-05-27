#ifndef CHARACTER_H
#define CHARACTER_H

#include "options.h"
#include "curses.h"

typedef struct SelectionState SelectionState;
typedef struct Sheet Sheet;

typedef struct {
	char name[STR_SIZE];
	char classname[STR_SIZE];
	int exp;
	int gold;
	WINDOW* w;
} CharacterBox;


void drawCharacterBox(CharacterBox*);

void addExpDiag(Sheet* );
void addGoldDiag(Sheet* );
void removeGoldDiag(Sheet* );

#endif
