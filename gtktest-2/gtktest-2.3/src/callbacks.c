#include "callbacks.h"

void cb_ok_clicked (GtkButton* self, gpointer user_data)
{
	MyDialogInfo *di_ptr = user_data;
	di_ptr->response = GTK_RESPONSE_OK;
	g_main_loop_quit (di_ptr->loop);
}

void cb_cancel_clicked (GtkButton* self, gpointer user_data)
{
	MyDialogInfo *di_ptr = user_data;
	di_ptr->response = GTK_RESPONSE_CANCEL;
	g_main_loop_quit (di_ptr->loop);
}

gboolean cb_dlg_close_request (GtkWindow* self, gpointer user_data)
{
	MyDialogInfo *di_ptr = user_data;
	g_main_loop_quit (di_ptr->loop);
	return FALSE;
}

// add more rows
void cb_addtoview (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
// get the toplevel window associated to our GApplication
	GtkWindow* toplevel = my_app_get_toplevel (user_data);
	MyDialogInfo di = {0};
	input_dialog_show (toplevel, "Información del usuario", &di);
	if (di.response == GTK_RESPONSE_OK)
	{
		AppData *ad_ptr = my_app_get_data (user_data);
		GtkSelectionModel* selection = gtk_column_view_get_model (GTK_COLUMN_VIEW (ad_ptr->view));
		GListModel* model = gtk_single_selection_get_model (GTK_SINGLE_SELECTION (selection));
		CellItem *new_item = cell_item_new (di.nombre, di.carrera, di.grade);
		g_list_store_append (G_LIST_STORE (model), new_item);
// clean up:
		g_object_unref (new_item);
		g_free (di.nombre);
		g_free (di.carrera);
	}
}

// show the name and grade information based on a row number
void cb_showme1 (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
// get my data from user_data
	AppData* app = my_app_get_data (user_data);
	GtkWindow* toplevel = my_app_get_toplevel (user_data);
	GtkWidget *view = app->view;
	GtkSelectionModel* model = gtk_column_view_get_model (GTK_COLUMN_VIEW (view));
// helped by: https://discourse.gnome.org/t/gtk4-finding-a-row-data-on-gtkcolumnview/8465/2
	int n = g_list_model_get_n_items (G_LIST_MODEL (model));
	g_print ("Total rows: %d\n", n); // for example: 4
// fun part:
	int n_row = 1; // I choose row 1
// In gtktest-2.4, will test if n_row is a valid row position
// select row[n_row]:
	GObject *row = g_list_model_get_object (G_LIST_MODEL (model), n_row);
	output_dialog_show (toplevel, "Mostrar información seleccionada", n_row, CELL_ITEM (row));
// clean up:
	g_object_unref (row);
}

void cb_showme2 (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	AppData *app = my_app_get_data (user_data);
	GtkWidget *view = app->view;
// helped by: https://blog.gtk.org/2020/09/08/on-list-models/
	GtkSelectionModel *model = gtk_column_view_get_model (GTK_COLUMN_VIEW (view));
// get current zero-based position of the current row selected
	int selected_index = gtk_single_selection_get_selected (GTK_SINGLE_SELECTION (model));
	if (selected_index != GTK_INVALID_LIST_POSITION)
	{
		GtkWindow* toplevel = my_app_get_toplevel (user_data);
		//g_print ("Selected row index: %i\n", selected_index);
// You can use this one:
// GObject *row = g_list_model_get_object (G_LIST_MODEL (model), selected_index);
// or:
		GObject *row = gtk_single_selection_get_selected_item (GTK_SINGLE_SELECTION (model));
		output_dialog_show (toplevel, "Mostrar información seleccionada", selected_index, CELL_ITEM (row));
	}
	else
	{
		g_print ("Nothing is selected\n");
	}
}

void cb_quit (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	g_application_quit (G_APPLICATION (user_data));
}

void cb_gesture_pressed ( GtkGestureClick* self, gint n_press, gdouble x, gdouble y, gpointer user_data)
{
	if (n_press == 2)
	{
		gtk_editable_set_editable (GTK_EDITABLE (user_data), TRUE);
		gtk_widget_grab_focus (GTK_WIDGET (user_data));
	}
}

void factory_setup (GtkListItemFactory *factory, GtkListItem *list_item, gpointer user_data)
{
	GtkWidget *widget_item;
	int i = GPOINTER_TO_INT (user_data);
	GObject *item = gtk_list_item_get_item (list_item);
	
	if (i != ID_GRADE)
	{
		//https://stackoverflow.com/a/77180065/2030219
		widget_item = gtk_editable_label_new ("");
		gtk_editable_set_editable (GTK_EDITABLE (widget_item), FALSE);
		// https://stackoverflow.com/a/78560182/2030219 &&
		// https://stackoverflow.com/a/76614510/2030219
		GtkGesture *gesture = gtk_gesture_click_new ();
		g_signal_connect (gesture, "pressed", G_CALLBACK (cb_gesture_pressed), widget_item);
		gtk_widget_add_controller (widget_item, GTK_EVENT_CONTROLLER (gesture));
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
			gtk_editable_set_text (GTK_EDITABLE (widget_item), cell_item_get_name (CELL_ITEM (item)));
			g_object_bind_property (widget_item, "text", CELL_ITEM (item), "name", G_BINDING_SYNC_CREATE);
			break;
		case ID_CARRER:
			gtk_editable_set_text (GTK_EDITABLE (widget_item), cell_item_get_carrera (CELL_ITEM (item)));
			g_object_bind_property (widget_item, "text", CELL_ITEM (item), "carrera", G_BINDING_SYNC_CREATE);
			break;
		case ID_GRADE:
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget_item), cell_item_get_grade (CELL_ITEM (item)));
			g_object_bind_property (widget_item, "value", CELL_ITEM (item), "grado", G_BINDING_SYNC_CREATE);
			break;
	}
}