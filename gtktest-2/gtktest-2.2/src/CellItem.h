#ifndef _CELL_ITEM_H_INCLUDED
#define _CELL_ITEM_H_INCLUDED
#include "main.h"

#define CELL_ITEM_TYPE (cell_item_get_type())
G_DECLARE_FINAL_TYPE (CellItem, cell_item, CELL, ITEM, GObject)

CellItem * cell_item_new (const char*, const char*, int);

const char* cell_item_get_name (CellItem*);
const char* cell_item_get_carrera (CellItem*);
int cell_item_get_grade (CellItem*);
void cell_item_set_grade (CellItem*, int );
void cell_item_set_name (CellItem* ci, const char*);
void cell_item_set_carrera (CellItem*, const char*);
#endif