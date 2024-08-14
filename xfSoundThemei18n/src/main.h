#ifndef MAIN_H
#define MAIN_H

#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <locale.h>
#ifndef G_OS_WIN32
	#include <xfconf/xfconf.h>
#endif

typedef struct _MYDATA {
	GtkWidget *drop_down;
	GtkWidget *button;
	int index;
	int npos;
} MyData;

#endif
