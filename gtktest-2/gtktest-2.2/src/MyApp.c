#include "MyApp.h"
#include "MyAppWindow.h"
#include "callbacks.h"
#include "CellItem.h"

struct _MyApp
{
	GtkApplication parent;
};

G_DEFINE_TYPE (MyApp, my_app, GTK_TYPE_APPLICATION);

void my_app_init (MyApp *)
{
}

void my_app_activate (GApplication *app)
{
	MyAppWindow *win;
	GtkWidget *child;
	GtkWidget *button;
	GtkWidget *hspacer;
	GtkWidget *scrolled_win;
	GtkWidget *view;
	GMenu *menu_model;
	GListStore *list_model;
	GtkColumnViewColumn* column;
	GtkListItemFactory *factory;
	GtkSingleSelection *selection;

// create window:
	win = my_app_window_new (MY_APP (app));
	GtkIconTheme *theme = gtk_icon_theme_get_for_display (gdk_display_get_default ());
	gtk_icon_theme_add_resource_path (theme, "/gtk4/aullidolunar/" PROGRAM_NAME);
	gtk_window_set_default_icon_name (PROGRAM_NAME);
	gtk_window_set_icon_name (GTK_WINDOW (win), PROGRAM_NAME);
	gtk_window_set_title (GTK_WINDOW (win), PROJECT_NAME_TITLE);

// action entries:
	const GActionEntry entries[] =
    {
        {"carga", cb_open, NULL, NULL, NULL, { 0, 0, 0 }},
        {"salida", cb_quit, NULL, NULL, NULL, { 0, 0, 0 }}
    };
    g_action_map_add_action_entries (G_ACTION_MAP (app), entries, G_N_ELEMENTS (entries), app);
    const gchar *carga[] = {"<ctrl>c", NULL};
    const gchar *salida[] = {"<ctrl>s", "<ctrl>w", "<ctrl>q", NULL};
    gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.carga", carga);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.salida", salida);

// create child container:
	child = gtk_grid_new ();

// UI:
	menu_model = g_menu_new ();
	g_menu_append (menu_model, "_Cargar", "app.carga");
	g_menu_append (menu_model, "_Salir", "app.salida");
	
	button = gtk_menu_button_new ();
	gtk_widget_set_hexpand (button, FALSE);
	gtk_menu_button_set_icon_name (GTK_MENU_BUTTON (button), "action_ui");
	gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (button), G_MENU_MODEL (menu_model));
	
	hspacer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_widget_set_hexpand (hspacer, TRUE);
	
	scrolled_win = gtk_scrolled_window_new ();
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	
	list_model = g_list_store_new (G_TYPE_OBJECT);
	selection = gtk_single_selection_new (G_LIST_MODEL (list_model));
	view = gtk_column_view_new (GTK_SELECTION_MODEL (selection));
	gtk_widget_set_hexpand (view, TRUE);
	gtk_widget_set_vexpand (view, TRUE);
	const char *column_names[] = { "Nombre", "Carrera", "Grado", NULL };
	for (int i = 0; column_names[i]; i++)
	{
		factory = gtk_signal_list_item_factory_new ();
		g_signal_connect (factory, "setup", G_CALLBACK (factory_setup), GINT_TO_POINTER (i));
		g_signal_connect (factory, "bind", G_CALLBACK (factory_bind), GINT_TO_POINTER (i));
		column = gtk_column_view_column_new (column_names[i], factory);
		gtk_column_view_append_column (GTK_COLUMN_VIEW (view), column);
	}
// testing the model:
	g_list_store_append (list_model, cell_item_new ("Joel", "Ciencias de la Comunicación", 10));
	g_list_store_append (list_model, cell_item_new ("Foo", "Cinematografía", 7));
	g_list_store_append (list_model, cell_item_new ("Bar", "Derecho", 25));
	g_list_store_append (list_model, cell_item_new ("Buz", "Diseño de Modas", -5));
	
	gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scrolled_win), view);

// layout:
	gtk_grid_attach (GTK_GRID (child), button, 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (child), hspacer, 1, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (child), scrolled_win, 0, 1, 2, 1);
	gtk_window_set_child (GTK_WINDOW (win), child);

// show window:
	gtk_window_present (GTK_WINDOW (win));
	//udata->index = 0;

// clean up:
	//g_object_unref (selection);
	//g_object_unref (list_model);
	g_object_unref (menu_model);
	g_object_unref (theme);
}

void my_app_class_init (MyAppClass *class)
{
	G_APPLICATION_CLASS (class)->activate = my_app_activate;
}

MyApp *my_app_new (void)
{
	return g_object_new (MY_APP_TYPE, "application-id", PROJECT_APPID, "flags", G_APPLICATION_DEFAULT_FLAGS, NULL);
}
