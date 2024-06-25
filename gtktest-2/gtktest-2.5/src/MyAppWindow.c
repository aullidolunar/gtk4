#include "MyAppWindow.h"

struct _MyAppWindow
{
	GtkApplicationWindow parent;
};

G_DEFINE_TYPE (MyAppWindow, my_app_window, GTK_TYPE_APPLICATION_WINDOW);

void my_app_window_init (MyAppWindow *app)
{
}

void my_app_window_class_init (MyAppWindowClass *class)
{
}

MyAppWindow * my_app_window_new (MyApp *app)
{
	return g_object_new (MY_APP_TYPE_WINDOW, "application", app, NULL);
}
