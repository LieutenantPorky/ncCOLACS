#ifndef WEAPONS_H
#define WEAPONS_H

#include "options.h"
#include "curses.h"

typedef struct SelectionState SelectionState;
typedef struct Sheet Sheet;

enum ATTACK_STATUS{
	NORMAL,
	ADVANTAGE,
	DISADVANTAGE,
	CRIT

};

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
void drawWeaponsBox(WeaponsBox*, Sheet*);
void rollAttack(SelectionState*, Sheet*, enum ATTACK_STATUS);




#endif
