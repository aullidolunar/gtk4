#include "callbacks.h"

int main (int argc, char **argv)
{
	GtkApplication *app;
	int ret;
	
	g_setenv ("GTK_CSD", "0", FALSE);
	g_setenv ("GSK_RENDERER", "CAIRO", TRUE);
	app = gtk_application_new ("gtk4.aullidolunar." PROGRAM_NAME, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "startup", G_CALLBACK (app_startup), NULL);
	g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
	ret = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
    return ret;
}
