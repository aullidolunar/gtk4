#include "CellItem.h"

struct _CellItem
{
    GObject parent_instance;
    char *name;
    int carrera;
    int grado;
};

struct _CellItemClass
{
    GObjectClass parent_class;
};

enum {
    PROP_NAME = 1,
    PROP_CARRER = 2,
    PROP_GRADE = 3,
    N_PROPERTIES
};

GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

G_DEFINE_TYPE (CellItem, cell_item, G_TYPE_OBJECT)

void cell_item_get_property (GObject *object, guint prop_id, GValue *value, GParamSpec *pspec)
{
	CellItem *self = CELL_ITEM (object);
	
	switch (prop_id)
	{
		case PROP_NAME:
			g_value_set_string (value, self->name);
			break;
		case PROP_CARRER:
			g_value_set_int (value, self->carrera);
			break;
		case PROP_GRADE:
			g_value_set_int (value, self->grado);
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
	}
}

void cell_item_set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
	CellItem *self = CELL_ITEM (object);

	switch (prop_id)
	{
		case PROP_NAME:
			g_free (self->name);
			self->name = g_value_dup_string (value);
			break;
		case PROP_CARRER:
			self->carrera = g_value_get_int (value);
			break;
		case PROP_GRADE:
			self->grado = g_value_get_int (value);
			break;
		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
	}
}

void cell_item_init (CellItem *item)
{
	item->name = NULL;
	item->carrera = 0;
	item->grado = 0;
}

void cell_item_dispose (GObject* obj)
{
	G_OBJECT_CLASS (cell_item_parent_class)->dispose (obj);
}

void cell_item_finalize (GObject* obj)
{
	CellItem* self = CELL_ITEM (obj);
	g_free (self->name);
	G_OBJECT_CLASS (cell_item_parent_class)->finalize (obj);
}

void cell_item_class_init (CellItemClass *klass)
{
	GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
	gobject_class->get_property = cell_item_get_property;
	gobject_class->set_property = cell_item_set_property;
	gobject_class->dispose = cell_item_dispose;
	gobject_class->finalize = cell_item_finalize;
	

	obj_properties[PROP_NAME] = g_param_spec_string ("name", NULL, NULL, NULL, G_PARAM_READWRITE);
	obj_properties[PROP_CARRER] = g_param_spec_int ("carrera", NULL, NULL, 0, 15, 0, G_PARAM_READWRITE);
	obj_properties[PROP_GRADE] = g_param_spec_int ("grado", NULL, NULL, 0, 10, 0, G_PARAM_READWRITE);

	g_object_class_install_properties (gobject_class, N_PROPERTIES, obj_properties);
}

CellItem * cell_item_new (const char* nombre, int carrera, int grado)
{
	CellItem *item = g_object_new (CELL_ITEM_TYPE, NULL);
	item->name = g_strdup (nombre);
	item->carrera = carrera;
	item->grado = CLAMP (grado, 0, 10);
	return item;
}

const char* cell_item_get_name (CellItem* ci)
{
	return ci->name;
}

int cell_item_get_carrera (CellItem* ci)
{
	return ci->carrera;
}

int cell_item_get_grade (CellItem* ci)
{
	return ci->grado;
}

void cell_item_set_name (CellItem* ci, const char* name)
{
	g_free (ci->name);
	ci->name = g_strdup (name);
}

void cell_item_set_carrera (CellItem* ci, int carrera)
{
	ci->carrera = carrera;
}

void cell_item_set_grade (CellItem* ci, int num)
{
	ci->grado = num;
}

const char** load_carreras_string ()
{
	static const char* carreras[] = {
		"Ciencias de la Comunicación",
		"Cinematografía",
		"Derecho",
		"Diseño de Modas",
		"Ingeniería Civil",
		"Ciencias de la Educación",
		"Contaduría Pública",
		NULL
	};
	return carreras;
}

const char* get_carrera_from_carreras (int index)
{
	return load_carreras_string ()[index];
}