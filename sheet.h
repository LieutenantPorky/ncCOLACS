#include <curses.h>

#define STR_SIZE 64
#define NUM_ATTRIBUTES 6

const char ATTRIBUTE_NAMES [][NUM_ATTRIBUTES] = {"STR","DEX","CON","INT","WIS","CHA"};
const int LVLINFO[20][3] = {
{0 ,1 ,2},
{300 ,2 ,2},
{900 ,3 ,2},
{2700 ,4 ,2},
{6500 ,5 ,3},
{14000 ,6 ,3},
{23000 ,7 ,3},
{34000 ,8 ,3},
{48000 ,9 ,4},
{64000 ,10,4},
{85000 ,11,4},
{100000 ,12,4},
{120000 ,13,5},
{140000 ,14,5},
{165000 ,15,5},
{195000 ,16,5},
{225000 ,17,6},
{265000 ,18,6},
{305000 ,19,6},
{355000 ,20,6}};

int getLVL(int exp) {
	for (int i = 1; i < 19; i++) {
		if (exp < LVLINFO[i][0]) { return i-1;}
	}
	return 20;
}
int getProficiency(int exp) {
	for (int i = 1; i < 19; i++) {
		if (exp < LVLINFO[i][0]) { return LVLINFO[i-1][2];}
	}
	return 6;
}
int getBonus(int attribute){return (attribute - 10)/2;}

static void init();
static void finish(int);


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
