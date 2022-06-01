
#ifndef SHEET
#define SHEET



#include <curses.h>
#include "lvl_info.h"
#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "weapons.h"
#include "attributes.h"
#include "character.h"
#include "status.h"
#include "dice.h"
#include "equipment.h"







typedef struct Sheet{
	CharacterBox* characterbox;
	WeaponsBox* weaponsbox;
	AttributesBox* attributesbox;
	StatusBox* statusbox;
	DiceBox* dicebox;
	EquipmentBox* equipmentbox;

} Sheet;


void drawSheet(Sheet*);
void drawVertical(WINDOW *, int, int, int);
void drawHorizontal(WINDOW *, int, int, int);
void populateWindows(Sheet*);
void drawBorders(WINDOW *);




#endif
