#include "MyApp.h"

int main (int argc, char **argv)
{
	AppData ad = {0};
	g_setenv ("GTK_CSD", "1", TRUE);
	g_setenv ("GSK_RENDERER", "CAIRO", TRUE);
	return g_application_run (G_APPLICATION (my_app_new (&ad)), argc, argv);
}
