#include <gtk/gtk.h>

void cb_open (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
    g_print ("Documento abierto\n");
}

void cb_save (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
    g_print ("Documento guardado\n");
}

void cb_quit (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
    g_application_quit (G_APPLICATION (user_data));
}

void app_startup (GtkApplication *app, gpointer user_data)
{
	GMenu *menubar;
	GMenu *submenu1;
	GMenu *submenu11;
	GMenu *submenu12;
	GMenuItem *item1;
	GMenuItem *item2;
	GMenuItem *item3;
	
	GtkIconTheme *theme = gtk_icon_theme_get_for_display (gdk_display_get_default ());
	gtk_icon_theme_add_resource_path (theme, "/gtk4/aullidolunar/gtktest");
	
	const GActionEntry entries[] =
    {
        {"folder1", cb_open, NULL, NULL, NULL, { 0, 0, 0 }},
        {"folder2", cb_save, NULL, NULL, NULL, { 0, 0, 0 }},
        {"door", cb_quit, NULL, NULL, NULL, { 0, 0, 0 }}
    };
	
	const gchar *folder1[] = {"<ctrl>a", NULL};
	const gchar *folder2[] = {"<ctrl>g", NULL};
	const gchar *door[] = {"<ctrl>c", NULL};
	
	g_action_map_add_action_entries (G_ACTION_MAP (app), entries, G_N_ELEMENTS (entries), app);
	gtk_application_set_accels_for_action (app, "app.folder1", folder1);
	gtk_application_set_accels_for_action (app, "app.folder2", folder2);
	gtk_application_set_accels_for_action (app, "app.door", door);
	
	menubar = g_menu_new ();
	submenu1 = g_menu_new ();
	submenu11 = g_menu_new ();
	item1 = g_menu_item_new ("_Abrir", "app.folder1");
	item2 = g_menu_item_new ("_Guardar", "app.folder2");
	submenu12 = g_menu_new ();
	item3 = g_menu_item_new ("_Cerrar", "app.door");
	// is expected not to show menu icons in gtk 4.15.1 and Gio 2.81.0, but
	// works in gtk3
	g_menu_item_set_attribute (item3, G_MENU_ATTRIBUTE_ICON, "s", "door", NULL);
	
	g_menu_append_item (submenu11, item1);
	g_menu_append_item (submenu11, item2);
	g_menu_append_section (submenu1, NULL, G_MENU_MODEL (submenu11));
	g_menu_append_item (submenu12, item3);
	g_menu_append_section (submenu1, NULL, G_MENU_MODEL (submenu12));
	g_menu_append_submenu (menubar, "_Programa", G_MENU_MODEL (submenu1));
	
	g_object_unref (item3);
	g_object_unref (item2);
	g_object_unref (item1);
	g_object_unref (submenu12);
	g_object_unref (submenu11);
	g_object_unref (submenu1);
	gtk_application_set_menubar (app, G_MENU_MODEL (menubar));
}

void app_activate (GtkApplication *app, gpointer user_data)
{
	GtkWidget *win;
	GtkIconTheme *icon_theme;
	
	win = gtk_application_window_new  (app);
	gtk_window_set_title (GTK_WINDOW (win), PROGRAM_NAME);
	icon_theme = gtk_icon_theme_get_for_display (gdk_display_get_default ());
	// Same as gapplication_id in tk_application_new
	gtk_icon_theme_add_resource_path (icon_theme, "/gtk4/aullidolunar/gtktest");
	// PROGRAM_NAME = icon set name, normally same as your proyect name
	if (gtk_icon_theme_has_icon (icon_theme, PROGRAM_NAME))
	{
		gtk_window_set_default_icon_name (PROGRAM_NAME);
		gtk_window_set_icon_name  (GTK_WINDOW (win), PROGRAM_NAME);
	}
	
    gtk_application_window_set_show_menubar (GTK_APPLICATION_WINDOW (win), TRUE);
	gtk_window_present (GTK_WINDOW (win));
}

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
