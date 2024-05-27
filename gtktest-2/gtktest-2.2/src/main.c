#include "MyApp.h"

struct _AppData {
	GObject parent_instance;
	int pos;
	int index;
};

struct _AppDataClass
{
    GObjectClass parent_class;
};

G_DEFINE_TYPE (AppData, appdata, G_TYPE_OBJECT);

void appdata_init (AppData *pad)
{
}

void appdata_class_init (AppDataClass *class)
{
}


int main (int argc, char **argv)
{
	g_setenv ("GTK_CSD", "1", TRUE);
	g_setenv ("GSK_RENDERER", "CAIRO", TRUE);
	return g_application_run (G_APPLICATION (my_app_new ()), argc, argv);
}
