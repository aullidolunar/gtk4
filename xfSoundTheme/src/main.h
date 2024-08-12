#ifndef MAIN_H
#define MAIN_H

#include <gtk/gtk.h>
#include <xfconf/xfconf.h>

typedef struct _MYDATA {
	GtkWidget *drop_down;
	GtkWidget *button;
	int index;
	int npos;
} MyData;

#endif
