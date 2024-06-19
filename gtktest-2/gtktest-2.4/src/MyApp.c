#include "MyApp.h"
#include "MyAppWindow.h"
#include "callbacks.h"
#include "CellItem.h"

struct _MyApp
{
	GtkApplication parent;
	AppData *data;
};

G_DEFINE_TYPE (MyApp, my_app, GTK_TYPE_APPLICATION);

void my_app_init (MyApp *app)
{
}

AppData* my_app_data_get_data (GApplication *app)
{
	return MY_APP (app)->data;
}

GtkWindow* my_app_data_get_toplevel (GApplication *app)
{
	return MY_APP (app)->data->win;
}

GtkWidget* my_app_data_get_view (GApplication *app)
{
	return MY_APP (app)->data->view;
}

GListStore* my_app_data_get_list_model (GApplication *app)
{
	return MY_APP (app)->data->list_model;
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
	GMenu *menu_sec1;
	GMenu *menu_sec2;
	GMenu *menu_sec3;
	GMenu *menu_sec4;
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
        {"agrega", cb_addtoview, NULL, NULL, NULL, { 0, 0, 0 }},
        {"edita", cb_edita, NULL, NULL, NULL, { 0, 0, 0 }},
        {"limpieza", cb_clean, NULL, NULL, NULL, { 0, 0, 0 }},
        {"muestra1", cb_showme1, NULL, NULL, NULL, { 0, 0, 0 }},
        {"muestra2", cb_showme2, NULL, NULL, NULL, { 0, 0, 0 }},
        {"salida", cb_quit, NULL, NULL, NULL, { 0, 0, 0 }}
    };
    g_action_map_add_action_entries (G_ACTION_MAP (app), entries, G_N_ELEMENTS (entries), app);
    const gchar *agrega[] = {"<ctrl>a", NULL};
    const gchar *edita[] = {"<ctrl>e", NULL};
    const gchar *limpieza[] = {"<ctrl>l", NULL};
    const gchar *carga1[] = {"<ctrl>b", NULL};
    const gchar *carga2[] = {"<ctrl>d", NULL};
    const gchar *salida[] = {"<ctrl>s", "<ctrl>w", "<ctrl>q", NULL};
    gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.agrega", agrega);
    gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.edita", edita);
    gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.limpieza", limpieza);
    gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.muestra1", carga1);
    gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.muestra2", carga2);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.salida", salida);

// create child container:
	child = gtk_grid_new ();

// UI:
	menu_model = g_menu_new ();
	menu_sec1 = g_menu_new ();
	menu_sec2 = g_menu_new ();
	menu_sec3 = g_menu_new ();
	menu_sec4 = g_menu_new ();
	g_menu_append (menu_sec1, "_Agregar...", "app.agrega");
	g_menu_append (menu_sec1, "_Editar...", "app.edita");
	g_menu_append_section (menu_model, NULL, G_MENU_MODEL (menu_sec1));
	g_menu_append (menu_sec2, "_Limpiar", "app.limpieza");
	g_menu_append_section (menu_model, NULL, G_MENU_MODEL (menu_sec2));
	g_menu_append (menu_sec3, "_Mostrar 1", "app.muestra1");
	g_menu_append (menu_sec3, "_Mostrar 2", "app.muestra2");
	g_menu_append_section (menu_model, NULL, G_MENU_MODEL (menu_sec3));
	g_menu_append (menu_sec4, "_Salir", "app.salida");
	g_menu_append_section (menu_model, NULL, G_MENU_MODEL (menu_sec4));
	
	button = gtk_menu_button_new ();
	gtk_widget_set_hexpand (button, FALSE);
	gtk_menu_button_set_icon_name (GTK_MENU_BUTTON (button), "action_ui");
	gtk_menu_button_set_menu_model (GTK_MENU_BUTTON (button), G_MENU_MODEL (menu_model));
	
	hspacer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_widget_set_hexpand (hspacer, TRUE);
	
	scrolled_win = gtk_scrolled_window_new ();
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	
	MY_APP (app)->data->list_model = g_list_store_new (G_TYPE_OBJECT);
	selection = gtk_single_selection_new (G_LIST_MODEL (MY_APP (app)->data->list_model));
	MY_APP (app)->data->view = gtk_column_view_new (GTK_SELECTION_MODEL (selection));
	//gtk_column_view_set_single_click_activate (GTK_COLUMN_VIEW (view), FALSE);
	gtk_widget_set_hexpand (MY_APP (app)->data->view, TRUE);
	gtk_widget_set_vexpand (MY_APP (app)->data->view, TRUE);
	const char *column_names[] = { "Nombre", "Carrera", "Grado", NULL };
	for (int i = 0; column_names[i]; i++)
	{
		factory = gtk_signal_list_item_factory_new ();
		g_signal_connect (factory, "setup", G_CALLBACK (factory_setup), GINT_TO_POINTER (i));
		g_signal_connect (factory, "bind", G_CALLBACK (factory_bind), GINT_TO_POINTER (i));
		column = gtk_column_view_column_new (column_names[i], factory);
		gtk_column_view_append_column (GTK_COLUMN_VIEW (MY_APP (app)->data->view), column);
	}
// testing the model:
	g_list_store_append (MY_APP (app)->data->list_model, cell_item_new ("Joel", 0, 10));
	g_list_store_append (MY_APP (app)->data->list_model, cell_item_new ("Foo", 1, 12));
	g_list_store_append (MY_APP (app)->data->list_model, cell_item_new ("Bar", 2, -6));
	g_list_store_append (MY_APP (app)->data->list_model, cell_item_new ("Buz", 3, 5));
	
	gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scrolled_win), MY_APP (app)->data->view);

// layout:
	gtk_grid_attach (GTK_GRID (child), button, 0, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (child), hspacer, 1, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (child), scrolled_win, 0, 1, 2, 1);
	gtk_window_set_child (GTK_WINDOW (win), child);

// Associate the toplevel to our GApplication:
	MY_APP (app)->data->win = GTK_WINDOW (win);

// test the association:
	gtk_window_present (MY_APP (app)->data->win);

// clean up:
	g_object_unref (menu_sec4);
	g_object_unref (menu_sec3);
	g_object_unref (menu_sec2);
	g_object_unref (menu_sec1);
	g_object_unref (menu_model);
	g_object_unref (theme);
}

void my_app_dispose (GObject* obj)
{
	GListStore* list_model = my_app_data_get_list_model (G_APPLICATION (obj));
	g_object_unref (list_model);
	g_clear_object (&list_model);
	G_OBJECT_CLASS (my_app_parent_class)->dispose (obj);
}

void my_app_finalize (GObject* obj)
{
	// some internal
	G_OBJECT_CLASS (my_app_parent_class)->finalize (obj);
}

void my_app_class_init (MyAppClass *klass)
{
	G_APPLICATION_CLASS (klass)->activate = my_app_activate;
	G_OBJECT_CLASS (klass)->dispose = my_app_dispose;
	G_OBJECT_CLASS (klass)->finalize = my_app_finalize;
}

MyApp *my_app_new (AppData *pad)
{
	MyApp *obj = g_object_new (MY_APP_TYPE, "application-id", PROJECT_APPID, "flags", G_APPLICATION_DEFAULT_FLAGS, NULL);
	obj->data = pad;
	return obj;
}
