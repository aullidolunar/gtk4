#include "callbacks.h"
#include "CellItem.h"

void cb_open (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{

}

void cb_quit (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	g_application_quit (G_APPLICATION (user_data));
}

void factory_setup (GtkListItemFactory *factory, GtkListItem *list_item, gpointer user_data)
{
	GtkWidget *widget_item;
	int i = GPOINTER_TO_INT (user_data);
	
	if (i != ID_GRADE)
	{
		widget_item = gtk_label_new ("");
	}
	else
	{
		widget_item = gtk_spin_button_new_with_range (0, 10, 1);
		gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (widget_item), TRUE);
	}
	
	gtk_list_item_set_child (list_item, widget_item);
}

void factory_bind (GtkListItemFactory *factory, GtkListItem *list_item, gpointer user_data)
{
	int i = GPOINTER_TO_INT (user_data);
	GtkWidget *widget_item;

	widget_item = gtk_list_item_get_child (list_item);
	GObject *item = gtk_list_item_get_item (list_item);
	
	switch (i)
	{
		case ID_NAME:
			gtk_label_set_label (GTK_LABEL (widget_item), cell_item_get_name (CELL_ITEM (item)));
			break;
		case ID_CARRER:
			gtk_label_set_label (GTK_LABEL (widget_item), cell_item_get_carrera (CELL_ITEM (item)));
			break;
		case ID_GRADE:
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget_item), cell_item_get_grade (CELL_ITEM (item)));
			break;
	}
}