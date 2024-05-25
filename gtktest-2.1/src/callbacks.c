#include "callbacks.h"
#include "helper.h"

// ***

enum {
	ID_NAME = 0,
	ID_CARRERA
};

#define CAPITAL_TYPE_ITEM (capital_item_get_type())
G_DECLARE_FINAL_TYPE (CapitalItem, capital_item, CAPITAL, ITEM, GObject)

struct _CapitalItem
{
    GObject parent_instance;
    const char *name;
    const char *carrera;
};

struct _CapitalItemClass
{
    GObjectClass parent_class;
};

G_DEFINE_TYPE (CapitalItem, capital_item, G_TYPE_OBJECT)

void capital_item_init (CapitalItem *item)
{
}

void capital_item_class_init (CapitalItemClass *class)
{
}

CapitalItem * capital_item_new (const char* nombre, const char* carrera)
{
	CapitalItem *item = g_object_new (CAPITAL_TYPE_ITEM, NULL);
	item->name = nombre;
	item->carrera = carrera;
	return item;
}

const char* capital_item_get_value (CapitalItem *item, int index)
{
	switch (index)
	{
		case ID_NAME: return item->name;
		case ID_CARRERA: return item->carrera;
	}
}

// ***

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
	
	g_action_map_add_action_entries (G_ACTION_MAP (app), entries, G_N_ELEMENTS (entries), app);
	
	menubar = g_menu_new ();
	submenu1 = g_menu_new ();
	submenu11 = g_menu_new ();
	item1 = my_menu_item_new (app, "_Abrir", "app.folder1", "door", "<ctrl>a");
	item2 = my_menu_item_new (app, "_Guardar", "app.folder2", "door", "<ctrl>g");
	submenu12 = g_menu_new ();
	item3 = my_menu_item_new (app, "_Cerrar", "app.door", "door", "<ctrl>c");
	
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

void factory_setup( GtkListItemFactory *factory, GtkListItem *list_item, gpointer user_data)
{
	GtkWidget *label = gtk_label_new ("");
	gtk_list_item_set_child (list_item, label);
}

void factory_bind( GtkListItemFactory *factory, GtkListItem *list_item, gpointer user_data )
{
	GtkWidget *label;

	label = gtk_list_item_get_child (list_item);
	GObject *item = gtk_list_item_get_item (list_item);
    const char *value = capital_item_get_value (CAPITAL_ITEM(item), GPOINTER_TO_INT (user_data));
	gtk_label_set_label (GTK_LABEL (label), value);
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
	
	GtkWidget* scrolled_win = gtk_scrolled_window_new ();
	GListStore *model = g_list_store_new (G_TYPE_OBJECT);
	GtkSingleSelection *selection = gtk_single_selection_new (G_LIST_MODEL (model));
	GtkWidget* view = gtk_column_view_new (GTK_SELECTION_MODEL (selection));
		
	const char *column_names[] = { "Nombre", "Carrera", NULL };
	GtkColumnViewColumn* column;
	GtkListItemFactory *factories[2];
	for (int i = 0; column_names[i]; i++ ) {
		factories[i] = gtk_signal_list_item_factory_new ();
		g_signal_connect (factories[i], "setup", G_CALLBACK (factory_setup), NULL);
		g_signal_connect (factories[i], "bind", G_CALLBACK (factory_bind), GINT_TO_POINTER (i));
		column = gtk_column_view_column_new (column_names[i], factories[i]);
		gtk_column_view_append_column (GTK_COLUMN_VIEW (view), column);
	}
	
	g_list_store_append (model, capital_item_new ("Joel", "Ciencias de la Comunicación"));
	g_list_store_append (model, capital_item_new ("Hannia", "Diseño Gráfico"));
	g_list_store_append (model, capital_item_new ("", "Arquitectura"));
	g_list_store_append (model, capital_item_new ("Boni", ""));
	
	gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scrolled_win), view);
	gtk_window_set_child (GTK_WINDOW (win), scrolled_win);
	gtk_window_present (GTK_WINDOW (win));
}