#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <locale.h>
#ifndef G_OS_WIN32
	#include <xfconf/xfconf.h>
#endif

int find_sound_themes(const gchar*, const gchar*, GtkStringList *, int*);

#endif
