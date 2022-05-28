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
void addBonusHPDiag(Sheet* s); 
void healDiag(Sheet* s); 
void resetDiag(Sheet* s); 
void damageDiag(Sheet* s); 
void healHDDiag(Sheet* s); 
void rollInitiativeDiag(Sheet* s);


#endif
