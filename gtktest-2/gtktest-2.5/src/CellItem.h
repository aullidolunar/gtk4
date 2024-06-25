#ifndef _CELL_ITEM_H_INCLUDED
#define _CELL_ITEM_H_INCLUDED

#include "main.h"

#define CELL_TYPE_ITEM (cell_item_get_type())
G_DECLARE_FINAL_TYPE (CellItem, cell_item, CELL, ITEM, GObject)

CellItem * cell_item_new (const char*, int, int);

const char* cell_item_get_name (CellItem*);
int cell_item_get_carrera (CellItem*);
int cell_item_get_grade (CellItem*);

void cell_item_set_name (CellItem* ci, const char*);
void cell_item_set_carrera (CellItem*, int);
void cell_item_set_grade (CellItem*, int);

const char** load_carreras_string ();
const char* get_carrera_from_carreras (int);

#endif