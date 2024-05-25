#include "helper.h"

GMenuItem* my_menu_item_new (GtkApplication *app, const gchar* label, const gchar* detailed_action, const gchar* icon_name, const gchar* accel)
{
	GMenuItem *item;
	// https://github.com/ToshioCP/Gtk4-tutorial/blob/main/gfm/sec17.md
	item = g_menu_item_new (label, detailed_action);
	if (icon_name)
		g_menu_item_set_attribute (item, G_MENU_ATTRIBUTE_ICON, "s", icon_name, NULL);

    if (accel && app)
	{
		const char* accels[] = {accel, NULL};
        gtk_application_set_accels_for_action (app, detailed_action, accels);
	}
	return item;
}

