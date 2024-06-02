#ifndef _CALLBACKS_H_INCLUDED
#define _CALLBACKS_H_INCLUDED

#include "main.h"
#include "MyApp.h"
#include "CellItem.h"

enum
{
	ID_NAME = 0,
	ID_CARRER,
	ID_GRADE
};

void cb_showme1 (GSimpleAction *, GVariant *, gpointer);
void cb_showme2 (GSimpleAction *, GVariant *, gpointer);
void cb_quit (GSimpleAction *, GVariant *, gpointer);
void factory_setup(GtkListItemFactory *, GtkListItem *, gpointer);
void factory_bind (GtkListItemFactory *, GtkListItem *, gpointer);

#endif