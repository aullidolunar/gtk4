#include <gtk/gtk.h>

void cb_quit (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
    g_application_quit (G_APPLICATION (user_data));
}

void app_startup (GtkApplication *app, gpointer user_data)
{
	GMenu *menubar;
	GMenu *submenu1;
	GMenuItem *item;
	
	const GActionEntry entries[] =
    {
        {"door", cb_quit, NULL, NULL, NULL, { 0, 0, 0 }}
    };
	
	const gchar *door[] = {"<ctrl>c", NULL};
	
	g_action_map_add_action_entries (G_ACTION_MAP (app), entries, G_N_ELEMENTS (entries), app);
	gtk_application_set_accels_for_action (app, "app.door", door);
	
	menubar = g_menu_new ();
	submenu1 = g_menu_new();
	item = g_menu_item_new ("_Cerrar", "app.door");
	
	g_menu_append_item (submenu1, item);
	g_menu_append_submenu (menubar, "_Programa", G_MENU_MODEL (submenu1));
	
	g_object_unref (item);
	g_object_unref (submenu1);
	gtk_application_set_menubar (app, G_MENU_MODEL (menubar));
}

void app_activate (GtkApplication *app, gpointer user_data)
{
	GtkWidget *win;
	
	win = gtk_application_window_new  (app);
	gtk_window_set_title (GTK_WINDOW (win), PROGRAM_NAME);
	
    gtk_application_window_set_show_menubar (GTK_APPLICATION_WINDOW (win), TRUE);
	gtk_window_present (GTK_WINDOW (win));
}

int main (int argc, char **argv)
{
	GtkApplication *app;
	int ret;
	
	g_setenv ("GTK_CSD", "0", FALSE);
	g_setenv ("GSK_RENDERER", "CAIRO", TRUE);
	app = gtk_application_new ("gtk4.aullidolunar." PROJECT_ID, G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "startup", G_CALLBACK (app_startup), NULL);
	g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
	ret = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
    return ret;
}
