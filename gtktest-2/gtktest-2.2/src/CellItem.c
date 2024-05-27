#include "CellItem.h"

struct _CellItem
{
    GObject parent_instance;
    const char *name;
    const char *carrera;
    int grado;
};

struct _CellItemClass
{
    GObjectClass parent_class;
};

G_DEFINE_TYPE (CellItem, cell_item, G_TYPE_OBJECT)

void cell_item_init (CellItem *item)
{
}

void cell_item_class_init (CellItemClass *class)
{
}

CellItem * cell_item_new (const char* nombre, const char* carrera, int grado)
{
	CellItem *item = g_object_new (CELL_ITEM_TYPE, NULL);
	item->name = nombre;
	item->carrera = carrera;
	item->grado = grado;
	return item;
}

const char* cell_item_get_name (CellItem* ci)
{
	return ci->name;
}

const char* cell_item_get_carrera (CellItem* ci)
{
	return ci->carrera;
}

int cell_item_get_grade (CellItem* ci)
{
	return ci->grado;
}