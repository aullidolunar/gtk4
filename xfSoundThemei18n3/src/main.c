#include "callbacks.h"

void on_app_activate(GtkApplication *app) {
  GtkBuilder* builder = gtk_builder_new_from_resource(GLADE_FILE);
  GtkWindow *toplevel = GTK_WINDOW(gtk_builder_get_object(builder, "window1"));
  GtkDropDown *dropdown1 = GTK_DROP_DOWN(gtk_builder_get_object(builder, "dropdown1"));
  GtkIconTheme *icon_theme = gtk_icon_theme_get_for_display (gdk_display_get_default ());
  int selection = 0;
  
  gtk_window_set_application (toplevel, app);
  gtk_window_set_title (toplevel, PROGRAM_TITLE);
  gtk_icon_theme_add_resource_path (icon_theme, PROGRAM_RC_PATH);
  gtk_window_set_default_icon_name (PROGRAM_NAME);
  
  GListModel *model = gtk_drop_down_get_model(dropdown1);
  const gchar* sounds_dir = "/usr/share/sounds";
#ifndef G_OS_WIN32  
  XfconfChannel *channel = xfconf_channel_get("xsettings");
  gchar *curr_theme = xfconf_channel_get_string (channel, "/Net/SoundThemeName", "default");
#else
  gchar* curr_theme = g_strdup("default");
#endif
  
  if (find_sound_themes(sounds_dir, curr_theme, GTK_STRING_LIST(model), &selection)) {
    gtk_widget_set_sensitive(GTK_WIDGET(dropdown1), TRUE);
    gtk_drop_down_set_selected(dropdown1, selection);
  }
	
  g_free(curr_theme);
  gtk_window_present(toplevel);
  g_object_unref(builder);
}

int main(int argc, char** argv) {	
	g_setenv ("GTK_CSD", PROGRAM_GTK_CSD, TRUE);
#ifdef WITH_CAIRO
	g_setenv ("GSK_RENDERER", "CAIRO", TRUE); // optimal
#else
	g_unsetenv ("GSK_RENDERER");
#endif  
  
  gchar *ruta_directorio = g_path_get_dirname(argv[0]);
  gchar *locale = g_build_filename(ruta_directorio, "locale", NULL);
	
	setlocale (LC_ALL, "");
	bindtextdomain (PROGRAM_NAME, locale);
	bind_textdomain_codeset (PROGRAM_NAME, "UTF-8");
	textdomain (PROGRAM_NAME);

	GtkApplication *app;
	int ret;

#ifndef G_OS_WIN32
	xfconf_init (NULL);
#endif
	app = gtk_application_new (PROGRAM_ID, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (on_app_activate), NULL);
	ret = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
#ifndef G_OS_WIN32
	xfconf_shutdown ();
#endif
  g_free(locale);
  g_free(ruta_directorio);
	return ret;
}
