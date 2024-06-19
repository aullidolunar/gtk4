#include "MyDialogs.h"

GtkWidget* my_gtk_frame_new (const char* str)
{
	GtkWidget* self = gtk_frame_new (NULL);
	GtkWidget* label = gtk_label_new (NULL);
	gchar* markup = g_markup_printf_escaped ("<b>%s</b>", str);
	gtk_label_set_markup (GTK_LABEL (label), markup);
	gtk_frame_set_label_widget (GTK_FRAME (self), label);
// clean up:
	g_free (markup);
	return self;
}

GtkWidget* my_gtk_label_lefted_new (const gchar* str)
{
	GtkWidget* self = gtk_label_new (str);
	gtk_label_set_xalign (GTK_LABEL (self), 0.0);
	return self;
}

GtkWidget* my_gtk_label_new (const gchar* str)
{
	GtkWidget* self = gtk_label_new (NULL);
	gchar* markup = g_markup_printf_escaped ("<b>%s</b>", str);
	gtk_label_set_markup (GTK_LABEL (self), markup);
	gtk_label_set_xalign (GTK_LABEL (self), 1.0);
// clean up:
	g_free (markup);
	return self;
}

GtkWidget* my_gtk_label_ex_new (const gchar* str, gboolean is_bold, gdouble xalign_val)
{
	GtkWidget* self = gtk_label_new (NULL);
	if (is_bold)
	{
		gchar* markup = g_markup_printf_escaped ("<b>%s</b>", str);
		gtk_label_set_markup (GTK_LABEL (self), markup);
		g_free (markup);
	}
	else
	{
		gtk_label_set_text (GTK_LABEL (self), str);
	}
	gtk_label_set_xalign (GTK_LABEL (self), xalign_val);
	
	return self;
}

GtkWidget* my_gtk_button_new (const char* str, const char* icon_name)
{
	GtkWidget* self = gtk_button_new ();
	GtkWidget* image = gtk_image_new_from_icon_name (icon_name);
	GtkWidget* label = gtk_label_new_with_mnemonic (str);
	GtkWidget* child = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_append (GTK_BOX (child), image);
	gtk_box_append (GTK_BOX (child), label);
	gtk_button_set_child (GTK_BUTTON (self), child);
	return self;
}

// custom dialog to add items to the view's list model:
// edit_mode = TRUE, show current selected data to edit for in dialog
// otherwise, empty fields to add new ones
void input_dialog_show (GtkWindow* toplevel, const char* title, MyDialogInfo *di_ptr, gboolean edit_mode)
{
	di_ptr->response = GTK_RESPONSE_NONE; // default: when the user clicks on the close or [X] button

	GtkWidget *dialog = gtk_window_new ();
	gtk_window_set_transient_for (GTK_WINDOW (dialog), toplevel);
	gtk_window_set_destroy_with_parent (GTK_WINDOW (dialog), TRUE);
	gtk_window_set_modal (GTK_WINDOW (dialog), TRUE);
	gtk_window_set_resizable (GTK_WINDOW (dialog), FALSE);
	gtk_window_set_title (GTK_WINDOW (dialog), title);
	gtk_window_set_icon_name (GTK_WINDOW (dialog), "any-user-info");
	
	GtkWidget *child = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
	GtkWidget *content = my_gtk_frame_new ("Datos del estudiante");
	g_object_set (G_OBJECT (content), "margin-top", 10, "margin-start", 10, "margin-end", 10, NULL);
	GtkWidget *frame_child = gtk_grid_new ();
	g_object_set (G_OBJECT (frame_child), "margin-top", 10, "margin-start", 10,  "margin-end", 10, "margin-bottom", 10, NULL);
	gtk_grid_set_row_spacing (GTK_GRID (frame_child), 10);
	gtk_grid_set_column_spacing (GTK_GRID (frame_child), 10);
	
	GtkWidget* user_card = gtk_image_new_from_resource ("/gtk4/aullidolunar/gtktest/user-card");
	gtk_image_set_icon_size (GTK_IMAGE (user_card), GTK_ICON_SIZE_LARGE);
	
	GtkWidget *name_entry = gtk_entry_new ();
	GtkWidget *carrier = gtk_drop_down_new_from_strings (load_carreras_string ());
	GtkWidget *grade = gtk_spin_button_new_with_range (0, 10, 1);
	gtk_spin_button_set_wrap (GTK_SPIN_BUTTON (grade), TRUE);
	
	GtkWidget *sep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	
	GtkWidget *buttons_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_widget_set_margin_bottom (buttons_box, 10);
	gtk_widget_set_margin_end (buttons_box, 10);
	
	GtkWidget *button_spacer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_widget_set_hexpand (button_spacer, TRUE);
	GtkWidget* button_ok = my_gtk_button_new ("_Aceptar", "ok-icon");
	GtkWidget* button_cancel = my_gtk_button_new ("_Cancelar", "cancel-icon");

// show data if apply:
	if (edit_mode)
	{
		gtk_editable_set_text (GTK_EDITABLE (name_entry), di_ptr->nombre);
		gtk_drop_down_set_selected (GTK_DROP_DOWN (carrier), di_ptr->carrera);
		gtk_spin_button_set_value (GTK_SPIN_BUTTON (grade), di_ptr->grade);
// clean up:
		g_free (di_ptr->nombre);
	}

// callbacks:
	g_signal_connect (button_ok, "clicked", G_CALLBACK (cb_ok_clicked), di_ptr);
	g_signal_connect (button_cancel, "clicked", G_CALLBACK (cb_cancel_clicked), di_ptr);
	g_signal_connect (dialog, "close-request", G_CALLBACK (cb_dlg_close_request), di_ptr);

// layout:
	gtk_grid_attach (GTK_GRID (frame_child), user_card, 0, 0, 1, 3);	
	gtk_grid_attach (GTK_GRID (frame_child), my_gtk_label_new ("Nombre:"), 1, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (frame_child), name_entry, 2, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (frame_child), my_gtk_label_new ("Carrera:"), 1, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (frame_child), carrier, 2, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (frame_child), my_gtk_label_new ("Calificación:"), 1, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (frame_child), grade, 2, 2, 1, 1);
	gtk_frame_set_child (GTK_FRAME (content), frame_child);
	gtk_box_append (GTK_BOX (child), content);
	gtk_box_append (GTK_BOX (child), sep);
	gtk_box_append (GTK_BOX (buttons_box), button_spacer);
	gtk_box_append (GTK_BOX (buttons_box), button_ok);
	gtk_box_append (GTK_BOX (buttons_box), button_cancel);
	gtk_box_append (GTK_BOX (child), buttons_box);
	gtk_window_set_child (GTK_WINDOW (dialog), child);

	gtk_window_present (GTK_WINDOW (dialog));
	di_ptr->loop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (di_ptr->loop);
	g_main_loop_unref (di_ptr->loop);
// get the data:
	if (di_ptr->response == GTK_RESPONSE_OK)
	{
		const gchar* nombre = gtk_editable_get_text (GTK_EDITABLE (name_entry));
		
		di_ptr->nombre = g_strdup (nombre);
		di_ptr->carrera = gtk_drop_down_get_selected (GTK_DROP_DOWN (carrier));
		di_ptr->grade = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (grade));
		
	}

	if (di_ptr->response != GTK_RESPONSE_NONE)
		gtk_window_destroy (GTK_WINDOW (dialog));

}

/* show user information based in given row position */
void output_dialog_show (GtkWindow* toplevel, const char* title, int n_pos, int n_items, CellItem* row)
{
	MyDialogInfo di = {0};
	di.response = GTK_RESPONSE_NONE;
	di.loop = g_main_loop_new (NULL, FALSE);
	
	GtkWindow *dialog = GTK_WINDOW(gtk_window_new ());
	gtk_window_set_transient_for (dialog, toplevel);
	gtk_window_set_destroy_with_parent (dialog, TRUE);
	gtk_window_set_modal (dialog, TRUE);
	gtk_window_set_resizable (dialog, FALSE);
	gtk_window_set_title (dialog, title);
	gtk_window_set_icon_name (dialog, "any-user-info");
	
	GtkWidget *child = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
	GtkWidget *content = my_gtk_frame_new ("Datos del estudiante");
	g_object_set (G_OBJECT (content), "margin-top", 10, "margin-start", 10, "margin-end", 10, NULL);
	
	GtkWidget *frame_child = gtk_grid_new ();
	g_object_set (G_OBJECT (frame_child), "margin-top", 10, "margin-start", 10,  "margin-end", 10, "margin-bottom", 10, NULL);
	gtk_grid_set_row_spacing (GTK_GRID (frame_child), 10);
	gtk_grid_set_column_spacing (GTK_GRID (frame_child), 10);
	
	GtkWidget* user_card = gtk_image_new_from_resource ("/gtk4/aullidolunar/gtktest/user-card");
	gtk_image_set_pixel_size (GTK_IMAGE (user_card), 64);
	
	GtkWidget *sep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	
	GtkWidget *buttons_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_widget_set_margin_bottom (buttons_box, 10);
	gtk_widget_set_margin_end (buttons_box, 10);
	
	GtkWidget *button_spacer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_widget_set_hexpand (button_spacer, TRUE);
	GtkWidget* button_ok = my_gtk_button_new ("_Aceptar", "ok-icon");

// callbacks:
	g_signal_connect (button_ok, "clicked", G_CALLBACK (cb_ok_clicked), &di);
	g_signal_connect (dialog, "close-request", G_CALLBACK (cb_dlg_close_request), di.loop);

// get data from row:
	const gchar* nombre = cell_item_get_name (CELL_ITEM (row));
	int carrera = cell_item_get_carrera (CELL_ITEM (row));
	gchar* grade = g_strdup_printf ("%i", cell_item_get_grade (CELL_ITEM (row)));
	gchar* num = g_strdup_printf ("%d de %i", n_pos+1, n_items);

// layout
	gtk_grid_attach (GTK_GRID (frame_child), user_card, 0, 0, 1, 4);
	gtk_grid_attach (GTK_GRID (frame_child), my_gtk_label_new ("No.:"), 1, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (frame_child), my_gtk_label_lefted_new (num), 2, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (frame_child), my_gtk_label_new ("Nombre:"), 1, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (frame_child), my_gtk_label_lefted_new (nombre), 2, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (frame_child), my_gtk_label_new ("Carrera:"), 1, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (frame_child), my_gtk_label_lefted_new (get_carrera_from_carreras (carrera)), 2, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (frame_child), my_gtk_label_new ("Calificación:"), 1, 3, 1, 1);
	gtk_grid_attach (GTK_GRID (frame_child), my_gtk_label_lefted_new (grade), 2, 3, 1, 1);
	gtk_frame_set_child (GTK_FRAME (content), frame_child);
	gtk_box_append (GTK_BOX (child), content);
	gtk_box_append (GTK_BOX (child), sep);
	gtk_box_append (GTK_BOX (buttons_box), button_spacer);
	gtk_box_append (GTK_BOX (buttons_box), button_ok);
	gtk_box_append (GTK_BOX (child), buttons_box);
	gtk_window_set_child (GTK_WINDOW (dialog), child);

	gtk_window_present (GTK_WINDOW (dialog));
	g_main_loop_run (di.loop);
	
	if (di.response != GTK_RESPONSE_NONE)
		gtk_window_destroy (GTK_WINDOW (dialog));

// clean up:
	g_main_loop_unref (di.loop);
	g_free (num);
	g_free (grade);
}

int MessageBox (GtkWindow* toplevel, const gchar* caption, const gchar* title, const gchar* body)
{
	MsgBoxInfo mbi = {0};
	mbi.response = GTK_RESPONSE_NONE;
	mbi.loop = g_main_loop_new (NULL, FALSE);
	
	GtkWindow *dialog = GTK_WINDOW(gtk_window_new ());
	gtk_window_set_transient_for (dialog, toplevel);
	gtk_window_set_destroy_with_parent (dialog, TRUE);
	gtk_window_set_modal (dialog, TRUE);
	gtk_window_set_resizable (dialog, FALSE);
	gtk_window_set_title (dialog, caption);
	
	GtkWidget *child = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
	g_object_set (G_OBJECT (child), "margin-top", 10, "margin-start", 10,  "margin-end", 10, "margin-bottom", 10, NULL);
	
	GtkWidget *content = gtk_grid_new ();
	gtk_grid_set_row_spacing (GTK_GRID (content), 10);
	gtk_grid_set_column_spacing (GTK_GRID (content), 10);
// Idea from https://stackoverflow.com/a/75807197/2030219
	GtkWidget* msgbox_icon = gtk_picture_new_for_resource ("/gtk4/aullidolunar/gtktest/user-card");
	
	GtkWidget *sep = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	
	GtkWidget *buttons_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
	GtkWidget *button_spacer = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_widget_set_hexpand (button_spacer, TRUE);
	GtkWidget* button_ok = my_gtk_button_new ("_Aceptar", "ok-icon");
	
	g_signal_connect (button_ok, "clicked", G_CALLBACK (cb_ok_clicked2), &mbi);
	g_signal_connect (dialog, "close-request", G_CALLBACK (cb_dlg_close_request), mbi.loop);
	
	gtk_grid_attach (GTK_GRID (content), msgbox_icon, 0, 0, 1, 2);
	gtk_grid_attach (GTK_GRID (content), my_gtk_label_ex_new (title, TRUE, 0.0), 1, 0, 1, 1);
	gtk_grid_attach (GTK_GRID (content), my_gtk_label_ex_new (body, FALSE, 0.0), 1, 1, 1, 1);
	gtk_box_append (GTK_BOX (child), content);
	gtk_box_append (GTK_BOX (child), sep);
	gtk_box_append (GTK_BOX (buttons_box), button_spacer);
	gtk_box_append (GTK_BOX (buttons_box), button_ok);
	gtk_box_append (GTK_BOX (child), buttons_box);
	gtk_window_set_child (GTK_WINDOW (dialog), child);

	gtk_window_present (GTK_WINDOW (dialog));
	g_main_loop_run (mbi.loop);
	
	if (mbi.response != GTK_RESPONSE_NONE)
		gtk_window_destroy (GTK_WINDOW (dialog));
	
	return mbi.response;
}