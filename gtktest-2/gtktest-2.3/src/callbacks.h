#ifndef _CALLBACKS_H_INCLUDED
#define _CALLBACKS_H_INCLUDED

#include "MyApp.h"
#include "CellItem.h"
#include "MyDialogs.h"

enum
{
	ID_NAME = 0,
	ID_CARRER,
	ID_GRADE
};

void cb_addtoview (GSimpleAction *, GVariant *, gpointer);
void cb_showme1 (GSimpleAction *, GVariant *, gpointer);
void cb_showme2 (GSimpleAction *, GVariant *, gpointer);
void cb_quit (GSimpleAction *, GVariant *, gpointer);
void factory_setup(GtkListItemFactory *, GtkListItem *, gpointer);
void factory_bind (GtkListItemFactory *, GtkListItem *, gpointer);
void cb_ok_clicked (GtkButton*, gpointer);
void cb_cancel_clicked (GtkButton*, gpointer);
gboolean cb_dlg_close_request (GtkWindow*, gpointer);

#endif