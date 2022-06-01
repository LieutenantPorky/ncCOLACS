#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "options.h"

typedef struct Sheet Sheet;


typedef struct Equipment {
	char Name[STR_SIZE];
	char Description[STR_SIZE];
} Equipment;


typedef struct EquipmentBox {
	int NumEquipment;
	Equipment* Equipment;
} EquipmentBox;

void addEquipment(EquipmentBox* , Equipment *);
void removeEquipment(EquipmentBox*, int index);
void equipmentDiag(Sheet* s);

#endif
