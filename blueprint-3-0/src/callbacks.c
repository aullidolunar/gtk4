#include "callbacks.h"

G_MODULE_EXPORT void on_button1_clicked(GtkGrid* grid) {
	GtkAlertDialog *dialog;
	
	GtkWidget *parent = gtk_widget_get_parent(GTK_WIDGET(grid));
	GtkWidget *entry = gtk_grid_get_child_at(grid, 0, 0);
	
	const char* entry_text = gtk_editable_get_text (GTK_EDITABLE(entry));
	dialog = gtk_alert_dialog_new (_("This your text, my friend"));
	gtk_alert_dialog_set_detail (dialog, entry_text);
	gtk_alert_dialog_show (dialog, GTK_WINDOW(parent));
	g_object_unref (dialog);

}

void on_activate(GtkApplication *app) {
	GtkBuilder* builder = gtk_builder_new_from_resource(UI_RESOURCE_PATH);
	GtkWindow *window1 = GTK_WINDOW(gtk_builder_get_object(builder, "window1"));
	GtkIconTheme *icon_theme = gtk_icon_theme_get_for_display (gdk_display_get_default ());
	
	gtk_window_set_application (window1, app);
	gtk_icon_theme_add_resource_path (icon_theme, PROGRAM_RESOURCE_PATH);
#ifndef G_OS_WIN32
	gtk_window_set_default_icon_name (PROGRAM_NAME);
#endif
	
	gtk_window_present(window1);
	g_object_unref(builder);
}