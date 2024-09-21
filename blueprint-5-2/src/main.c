#include "callbacks.h"

int main(int argc, char** argv) {
	
	GtkApplication *app;
	int status;
    gchar *ruta_directorio = g_path_get_dirname(argv[0]);
    gchar *locale = g_build_filename(ruta_directorio, "locale", NULL);
	
	setlocale (LC_ALL, "");
	bindtextdomain (PROGRAM_NAME, locale);
	bind_textdomain_codeset (PROGRAM_NAME, "UTF-8");
	textdomain (PROGRAM_NAME);
	
	g_free(locale);
    g_free(ruta_directorio);

	g_setenv ("GTK_CSD", USE_GTK_CSD, TRUE);
#ifdef WITH_CAIRO
	g_setenv ("GSK_RENDERER", "CAIRO", TRUE); // optimal
#else
	g_unsetenv ("GSK_RENDERER");
#endif

	app = gtk_application_new (PROGRAM_ID, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);	
	
	g_object_unref (app);
	return status;
}
