#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "main.h"

void app_startup (GtkApplication*, gpointer);
void app_activate (GtkApplication*, gpointer);
void cb_open (GSimpleAction*, GVariant*, gpointer);
void cb_save (GSimpleAction*, GVariant*, gpointer);
void cb_quit (GSimpleAction*, GVariant*, gpointer);

#endif