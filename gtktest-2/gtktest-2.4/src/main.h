#ifndef _MAIN_H_INCLUDED
#define _MAIN_H_INCLUDED

#include <gtk/gtk.h>

typedef struct _AppData {
	GtkWindow* win;
	GtkWidget *view;
	GListStore *list_model;
	int pos;
	int index;
} AppData;

#endif