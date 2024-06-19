#ifndef _MY_APP_WINDOW_H_INCLUDED
#define _MY_APP_WINDOW_H_INCLUDED

#include "MyApp.h"

#define MY_APP_WINDOW_TYPE (my_app_window_get_type ())
G_DECLARE_FINAL_TYPE (MyAppWindow, my_app_window, MY, APP_WINDOW, GtkApplicationWindow)

MyAppWindow * my_app_window_new (MyApp *);

#endif