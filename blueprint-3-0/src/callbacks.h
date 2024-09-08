#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <gtk/gtk.h>
#include <glib/gi18n.h>
#ifdef ENABLE_I18L
#include <locale.h>
#endif

void on_activate(GtkApplication *);

#endif
