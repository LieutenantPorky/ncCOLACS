
#ifndef SHEET
#define SHEET

#define NUM_ATTRIBUTES 6


#include <curses.h>
#include "lvl_info.h"
#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	int attributevalues[NUM_ATTRIBUTES];
	bool proficiencies[NUM_ATTRIBUTES];
	WINDOW* w;
} AttributesBox;



typedef struct {
	char name[STR_SIZE];
	char classname[STR_SIZE];
	int exp;
	int gold;
	WINDOW* w;
} CharacterBox;



typedef struct{
	char name[STR_SIZE];
	int attr;
	int numdice;
	int die;
} Weapon;

typedef struct {
	int numweapons;
	int selected;
	Weapon* weapons;
	WINDOW* w;
} WeaponsBox;

void addWeapon(WeaponsBox*, Weapon*);



typedef struct {
	CharacterBox* characterbox;
	WeaponsBox* weaponsbox;
	AttributesBox* attributesbox;
} Sheet;


void drawSheet(Sheet*);
void populateWindows(Sheet*);
void drawBorders(WINDOW *);




void drawAttributesBox(AttributesBox*);
void drawCharacterBox(CharacterBox*);
void drawWeaponsBox(WeaponsBox*, Sheet*);
#endif
