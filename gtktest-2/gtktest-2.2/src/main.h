#ifndef _MAIN_H_INCLUDED
#define _MAIN_H_INCLUDED

#include <gtk/gtk.h>

#define APP_TYPE_DATA (appdata_get_type())
G_DECLARE_FINAL_TYPE (AppData, appdata, APP, DATA, GObject)

#endif