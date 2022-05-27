#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "options.h"
#include "curses.h"

#define NUM_ATTRIBUTES 6

typedef struct SelectionState SelectionState;
typedef struct Sheet Sheet;

typedef struct AttributesBox{
	int attributevalues[NUM_ATTRIBUTES];
	bool proficiencies[NUM_ATTRIBUTES];
	WINDOW* w;
} AttributesBox;

void drawAttributesBox(AttributesBox*);





#endif
