#include "callbacks.h"

void showAboutDlg(GtkWindow* parent) {
  gtk_show_about_dialog(parent,
    "program-name", PROGRAM_NAME,
    "version", PROGRAM_VERSION,
    "comments", _(PROGRAM_DESC),
    "logo-icon-name", "platform",
	NULL
  );
}

void on_button1_clicked(GtkGrid* grid) {
  GtkAlertDialog *dialog;
  
  GtkWidget *parent = gtk_widget_get_parent(GTK_WIDGET(grid));
  GtkWidget *check1 = gtk_grid_get_child_at(grid, 1, 1);
  
  if (gtk_check_button_get_active(GTK_CHECK_BUTTON(check1))) {
    showAboutDlg(GTK_WINDOW(parent));
  } else {
    GtkWidget *entry = gtk_grid_get_child_at(grid, 2, 0);
    const char* entry_text = gtk_editable_get_text (GTK_EDITABLE(entry));
    dialog = gtk_alert_dialog_new (_("This your text, my friend"));
    gtk_alert_dialog_set_detail (dialog, entry_text);
    gtk_alert_dialog_show (dialog, GTK_WINDOW(parent));
    g_object_unref (dialog);
  }
  
}

GtkWidget *my_button_new(const gchar* label, const gchar* icon_name) {
  GtkWidget *self;
  GtkWidget *child;
  GtkWidget *icon;
  GtkWidget *_label;
  
  self = gtk_button_new();
  icon = gtk_image_new_from_icon_name (icon_name);
  _label = gtk_label_new_with_mnemonic (label);
  child = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  
  gtk_box_append(GTK_BOX(child), icon);
  gtk_box_append(GTK_BOX(child), _label);
  gtk_button_set_child(GTK_BUTTON(self), child);
  
  return self;
}

void on_activate(GtkApplication *app) {
  
  GtkIconTheme *icon_theme = gtk_icon_theme_get_for_display (gdk_display_get_default ());
  gtk_icon_theme_add_resource_path (icon_theme, PROGRAM_RC_PATH);
    
  GtkWidget *window1 = gtk_application_window_new(app);
  gtk_window_set_default_icon_name (PROGRAM_NAME);
  gtk_window_set_title (GTK_WINDOW(window1), PROGRAM_NAME);
  
  GtkWidget *grid1 = gtk_grid_new();
  g_object_set (G_OBJECT(grid1), "margin-start", 10, "margin-top", 10, "margin-end", 10, "margin-bottom", 10, NULL);
  gtk_grid_set_column_spacing(GTK_GRID(grid1), 10);
  gtk_grid_set_row_spacing(GTK_GRID(grid1), 10);
  
  GtkWidget *platform = gtk_image_new_from_resource(PROGRAM_RC_PATH "/platform.png");
  gtk_image_set_pixel_size(GTK_IMAGE(platform), 64);
  gtk_widget_set_tooltip_text(platform, _("Your platform icon"));
  
  GtkWidget *label1 = gtk_label_new(_("Type something nice:"));
  gtk_widget_set_hexpand(label1, FALSE);
  
  GtkWidget *entry1 = gtk_entry_new();
  gtk_widget_set_tooltip_text(entry1, _("Information to show on dialog"));
  gtk_widget_set_hexpand(entry1, TRUE);
  
  GtkWidget *button1 = my_button_new(_("_OK"), "myenter");
  GtkWidget *button2 = my_button_new(_("_Close"), "myclose");
  gtk_widget_set_tooltip_text(button2, _("Exit the application"));
  
  GtkWidget *check1 = gtk_check_button_new_with_mnemonic(_("Show GtkAboutDialog"));
   
  g_signal_connect_swapped(button1, "clicked", G_CALLBACK(on_button1_clicked), grid1);
  g_signal_connect_swapped(button2, "clicked", G_CALLBACK(gtk_window_destroy), window1);
  g_object_bind_property (check1, "active", entry1, "sensitive", G_BINDING_INVERT_BOOLEAN);
  
  gtk_grid_attach(GTK_GRID(grid1), platform, 0, 0, 1, 2);
  gtk_grid_attach(GTK_GRID(grid1), label1, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid1), entry1, 2, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid1), button1, 3, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid1), button2, 4, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid1), check1, 1, 1, 3, 1);
  gtk_window_set_child(GTK_WINDOW(window1), grid1);
  gtk_window_present(GTK_WINDOW(window1));
}
