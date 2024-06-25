#ifndef _MYAPP_H_INCLUDED
#define _MYAPP_H_INCLUDED

#include "main.h"

#define MY_TYPE_APP (my_app_get_type ())
G_DECLARE_FINAL_TYPE (MyApp, my_app, MY, APP, GtkApplication)

MyApp *my_app_new ();
AppData* my_app_data_get_data (GApplication *);
GtkWindow* my_app_data_get_toplevel (GApplication *);
GtkWidget* my_app_data_get_view (GApplication *);
GListStore* my_app_data_get_list_model (GApplication *);

#endif