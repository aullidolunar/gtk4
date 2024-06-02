#ifndef _MYAPP_H_INCLUDED
#define _MYAPP_H_INCLUDED

#include "main.h"

#define MY_APP_TYPE (my_app_get_type ())
G_DECLARE_FINAL_TYPE (MyApp, my_app, MY, APP, GtkApplication)

MyApp *my_app_new (AppData*);
AppData* my_app_get_data (GApplication *);

#endif