#include "callbacks.h"

int main(int argc, char** argv) {
	GtkApplication *app;
	int ret;
	MyData dat;
	
	g_setenv ("GTK_CSD", USE_GTK_CSD, TRUE);
#ifdef WITH_CAIRO
	g_setenv ("GSK_RENDERER", "CAIRO", TRUE); // optimal
#else
	g_unsetenv ("GSK_RENDERER");
#endif
	
	xfconf_init (NULL);
	app = gtk_application_new ("gtk4.aullidolunar." PROGRAM_NAME, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (on_app_activate), &dat);
	ret = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	xfconf_shutdown ();
	return ret;
}
