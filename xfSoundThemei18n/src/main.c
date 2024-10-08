#include "callbacks.h"

int main(int argc, char** argv) {
	
    gchar *ruta_directorio = g_path_get_dirname(argv[0]);
    gchar *locale = g_build_filename(ruta_directorio, "locale", NULL);
	
	setlocale (LC_ALL, "");
	bindtextdomain (PROGRAM_NAME, locale);
	bind_textdomain_codeset (PROGRAM_NAME, "UTF-8");
	textdomain (PROGRAM_NAME);

	GtkApplication *app;
	int ret;
	MyData dat;

	g_setenv ("GTK_CSD", USE_GTK_CSD, TRUE);
#ifdef WITH_CAIRO
	g_setenv ("GSK_RENDERER", "CAIRO", TRUE); // optimal
#else
	g_unsetenv ("GSK_RENDERER");
#endif

#ifndef G_OS_WIN32
	xfconf_init (NULL);
#endif
	app = gtk_application_new ("gtk4.aullidolunar." PROGRAM_NAME, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (on_app_activate), &dat);
	ret = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
#ifndef G_OS_WIN32
	xfconf_shutdown ();
#endif
    g_free(locale);
    g_free(ruta_directorio);
	return ret;
}
