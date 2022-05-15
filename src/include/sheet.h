#define STR_SIZE 64
#define NUM_ATTRIBUTES 6



#ifndef SHEET
#define SHEET

#include <curses.h>
#include "lvl_info.h"
#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>


// define components of a character sheet

typedef struct {
	char name[STR_SIZE];
	char classname[STR_SIZE];
	int exp;
	int gold;
	WINDOW* w;
} CharacterBox;


typedef struct {
	int attributevalues[NUM_ATTRIBUTES];
	bool proficiencies[NUM_ATTRIBUTES];
	WINDOW* w;
} AttributesBox;

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
Sheet * makeDefaultSheet();
void saveSheet(Sheet*, char*);
Sheet* openSheet(char*);

void drawSheet(Sheet*);
void drawCharacterBox(CharacterBox*);
void drawAttributesBox(AttributesBox*);
void drawWeaponsBox(WeaponsBox*, Sheet*);

// Define graphics functions
void populateWindows(Sheet*);
void drawBorders(WINDOW *);

typedef struct {
	int SelectedBox;
	int SelectedItem;
} SelectionState;
extern SelectionState* state;

enum Boxes {
	CHARACTER,
	ATTRIBUTES,
	WEAPONS};
#endif
