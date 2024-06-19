#include "callbacks.h"

void cb_ok_clicked (GtkButton* self, gpointer user_data)
{
	MyDialogInfo *di_ptr = user_data;
	di_ptr->response = GTK_RESPONSE_OK;
	g_main_loop_quit (di_ptr->loop);
}

void cb_ok_clicked2 (GtkButton* self, gpointer user_data)
{
	MsgBoxInfo *mi_ptr = user_data;
	mi_ptr->response = GTK_RESPONSE_OK;
	g_main_loop_quit (mi_ptr->loop);
}

void cb_cancel_clicked (GtkButton* self, gpointer user_data)
{
	MyDialogInfo *di_ptr = user_data;
	di_ptr->response = GTK_RESPONSE_CANCEL;
	g_main_loop_quit (di_ptr->loop);
}

gboolean cb_dlg_close_request (GtkWindow* self, gpointer user_data)
{
	g_main_loop_quit (user_data);
	return FALSE;
}

// add more rows
void cb_addtoview (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
// get the toplevel window associated to our GApplication
	GtkWindow* toplevel = my_app_data_get_toplevel (user_data);
	MyDialogInfo di = {0};
	input_dialog_show (toplevel, "Información del usuario", &di, FALSE);
	if (di.response == GTK_RESPONSE_OK)
	{
		GtkWidget* view = my_app_data_get_view (user_data);
		GtkSelectionModel* selection = gtk_column_view_get_model (GTK_COLUMN_VIEW (view));
		GListModel* model = gtk_single_selection_get_model (GTK_SINGLE_SELECTION (selection));
		CellItem *new_item = cell_item_new (di.nombre, di.carrera, di.grade);
		g_list_store_append (G_LIST_STORE (model), new_item);
// clean up:
		g_object_unref (new_item);
		g_free (di.nombre);
	}
}

// edit/update data from selected row
void cb_edita (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	AppData *app = my_app_data_get_data (user_data);
	GtkSelectionModel *list_model = gtk_column_view_get_model (GTK_COLUMN_VIEW (app->view));
// get current row selected
	CellItem *sel_row = gtk_single_selection_get_selected_item (GTK_SINGLE_SELECTION (list_model));
	if (sel_row)
	{
		MyDialogInfo di = {0};
// get current selected data
		g_object_get (sel_row, "name", &di.nombre, "carrera", &di.carrera, "grado", &di.grade, NULL);
// show dialog with the data
		input_dialog_show (app->win, "Información del usuario", &di, TRUE);
		if (di.response == GTK_RESPONSE_OK)
		{
			g_object_set (sel_row, "name", di.nombre, "carrera", di.carrera, "grado", di.grade, NULL);
			g_free (di.nombre);
		}
	}
	else
	{
		MessageBox (app->win, "Información", "sel_row != 0", "No hay elmentos seleccionados en el view.");
	}
}

// show the name and grade information based on a row number
void cb_showme1 (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
// get my data from user_data
	AppData* app = my_app_data_get_data (user_data);
	GtkSelectionModel* list_model = gtk_column_view_get_model (GTK_COLUMN_VIEW (app->view));
// helped by: https://discourse.gnome.org/t/gtk4-finding-a-row-data-on-gtkcolumnview/8465/2
	int n_row = 1; // I choose row 1
// select row[n_row]:
	GObject *row_chosen = g_list_model_get_object (G_LIST_MODEL (list_model), n_row);
	if (row_chosen)
	{
		int n = g_list_model_get_n_items (G_LIST_MODEL (list_model));
		output_dialog_show (app->win, "Mostrar información seleccionada", n_row, n, CELL_ITEM (row_chosen));
// clean up:
		g_object_unref (row_chosen);
	}
	else
	{
		MessageBox (app->win, "Información", "row_chosen == NULL", "No se encontró el elemento en el view.");
	}
}

void cb_showme2 (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
// warning: app->list_model doesn't work here
	AppData *app = my_app_data_get_data (user_data);
// helped by: https://blog.gtk.org/2020/09/08/on-list-models/
	GtkSelectionModel *selection_model = gtk_column_view_get_model (GTK_COLUMN_VIEW (app->view));
	int n = g_list_model_get_n_items (G_LIST_MODEL (selection_model));
// get current zero-based position of the current row selected
	int selected_index = gtk_single_selection_get_selected (GTK_SINGLE_SELECTION (selection_model));
	if (selected_index != GTK_INVALID_LIST_POSITION)
	{
// get list store data:
 		GObject *row = g_list_model_get_object (G_LIST_MODEL (selection_model), selected_index);
		output_dialog_show (app->win, "Mostrar información seleccionada", selected_index, n, CELL_ITEM (row));
	}
	else
	{
		MessageBox (app->win, "Información", "n=0", "No hay elmentos en el view.");
	}
}

void cb_clean (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	GListStore* list_model = my_app_data_get_list_model (user_data);
	g_list_store_remove_all (list_model);
	// In gtktest-2.5, we will:
	// remove a single row base on selection or given index, fun time!
	// disable the menu actions to prevent show something is not in the view
}

void cb_quit (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	gtk_window_destroy (my_app_data_get_toplevel(user_data));
}

void cb_gesture_pressed (GtkGestureClick* self, gint n_press, gdouble x, gdouble y, gpointer user_data)
{
	if (n_press == 2)
	{
		gtk_editable_set_editable (GTK_EDITABLE (user_data), TRUE);
		gtk_widget_grab_focus (GTK_WIDGET (user_data));
	}
	else
	{
		gtk_editable_set_editable (GTK_EDITABLE (user_data), FALSE);
	}
}

void on_editable_done_editing1 (GObject* self, GParamSpec* pspec, gpointer user_data)
{
	
	gboolean editing_mode = gtk_editable_label_get_editing (GTK_EDITABLE_LABEL (self));
	gboolean editable_has_focus = gtk_widget_has_focus (GTK_WIDGET (self));
	
// Done editing and no more focus in theory the user "entered" some string, but...
// fixme: also means "Escape" was hitted, keeping the same string
	if (!editing_mode && !editable_has_focus)
	{
// Fixme: don't store the data if user didn't change the editable string:
		const gchar* new_text = gtk_editable_get_text (GTK_EDITABLE (self));
		CellItem *item = gtk_list_item_get_item (user_data);
// According to ToshioCP/Gobject-tutorial, the "new" string is stored in the list model and no signal/notification is emitted in
// g_object_bind_property (CELL_ITEM (item), "name", widget_item, "text", G_BINDING_SYNC_CREATE);
// so, in theory, this won't create the ping-pong effect:
		cell_item_set_name (item, new_text);
// now, go and see if "new_text" is the updated name of the user («Ctrl+d» in the current selected row)
	}
}

void on_editable_done_editing2 (GObject* self, GParamSpec* pspec, gpointer user_data)
{
	FocusData *fd = user_data;
	gboolean editable_has_focus = gtk_widget_has_focus (GTK_WIDGET (self));
	if (editable_has_focus)
	{
// the editable has focus, so grab the current text:	
		const gchar* old_text = gtk_editable_get_text (GTK_EDITABLE (self));
		fd->cache_str = g_strdup (old_text);
// notify we have string cache
		fd->have_cache = 1;
	}
	else
	{
// editable lost focus, be sure that we have something previous:
		if (fd->have_cache)
		{
// compare cache string with current one:
			const gchar* new_text = gtk_editable_get_text (GTK_EDITABLE (self));
			if (!g_strcmp0(fd->cache_str, new_text))
			{
// always save new ones:
				CellItem *item = gtk_list_item_get_item (fd->item);
				cell_item_set_name (item, new_text);
			}
// restore to original state
			fd->have_cache = 0;
		}
// remove cache if any
		g_free (fd->cache_str);
	}
}

void destroy_data (FocusData* ptr)
{
	g_free (ptr->cache_str);
	g_slice_free (FocusData, ptr);
}

void factory_setup (GtkListItemFactory *factory, GtkListItem *list_item, gpointer user_data)
{
	GtkWidget *widget_item;
	int i = GPOINTER_TO_INT (user_data);
	
	switch (i)
	{
		case ID_NAME:
			//https://stackoverflow.com/a/77180065/2030219
			widget_item = gtk_editable_label_new ("");
			gtk_editable_set_editable (GTK_EDITABLE (widget_item), FALSE);
			// https://stackoverflow.com/a/78560182/2030219 &&
			// https://stackoverflow.com/a/76614510/2030219
			GtkGesture *gesture = gtk_gesture_click_new ();
			g_signal_connect (gesture, "pressed", G_CALLBACK (cb_gesture_pressed), widget_item);
			gtk_widget_add_controller (widget_item, GTK_EVENT_CONTROLLER (gesture));
// Idea from https://discourse.gnome.org/t/signal-after-finishing-entry-editing/14739/3:
// connect to has-focus property to detect when the user enable or disable the editable field
// See section "Notify signal" in https://github.com/ToshioCP/Gobject-tutorial/blob/main/gfm/sec5.md#notify-signal
			FocusData* fd = g_slice_new0 (FocusData);
			fd->item = list_item;
// g_signal_connect_data helps to allocate the focus data and remove the resources when no longer need them
			g_signal_connect_data (widget_item, "notify::has-focus", G_CALLBACK (on_editable_done_editing2), fd, (GClosureNotify) destroy_data, 0);
			break;
		case ID_CARRER:
			widget_item = gtk_drop_down_new_from_strings (load_carreras_string ());
			break;
		case ID_GRADE:
			widget_item = gtk_spin_button_new_with_range (0, 10, 1);
			gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (widget_item), TRUE);
			break;
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
// For now, we don't use:
// 			g_object_bind_property (CELL_ITEM (item), "name", widget_item, "text", G_BINDING_BIDIRECTIONAL);
// to avoid the "ping-pong" loop between "name" and "text". Every single keypress in widget_item triggers notify::text
			g_object_bind_property (CELL_ITEM (item), "name", widget_item, "text", G_BINDING_SYNC_CREATE);
			break;
		case ID_CARRER:
			gtk_drop_down_set_selected (GTK_DROP_DOWN (widget_item), cell_item_get_carrera (CELL_ITEM (item)));
			g_object_bind_property (CELL_ITEM (item), "carrera", widget_item, "selected", G_BINDING_BIDIRECTIONAL);
			break;
		case ID_GRADE:
			gtk_spin_button_set_value (GTK_SPIN_BUTTON (widget_item), cell_item_get_grade (CELL_ITEM (item)));
			g_object_bind_property (CELL_ITEM (item), "grado", widget_item, "value", G_BINDING_BIDIRECTIONAL);
			break;
	}
}
