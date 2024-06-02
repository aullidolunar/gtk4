#ifndef _MAIN_H_INCLUDED
#define _MAIN_H_INCLUDED

#include <gtk/gtk.h>

typedef struct _AppData {
	GtkWidget *view;
	int pos;
	int index;
} AppData;

#endif