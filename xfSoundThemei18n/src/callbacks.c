#include "callbacks.h"

void on_selection(GObject *object, G_GNUC_UNUSED GParamSpec *pspec, MyData *dat) {
	dat->index = gtk_drop_down_get_selected(GTK_DROP_DOWN(object));
	gtk_widget_set_sensitive(dat->button, dat->index && dat->index != dat->npos);
}

#ifndef G_OS_WIN32
void on_clicked(GtkButton *self, MyData *dat) {
	XfconfChannel *channel = xfconf_channel_get("xsettings");
	GtkStringObject *builder = gtk_drop_down_get_selected_item(GTK_DROP_DOWN(dat->drop_down));
	const char* sound_theme = gtk_string_object_get_string (builder);
	xfconf_channel_set_string (channel, "/Net/SoundThemeName", sound_theme);
	gtk_widget_set_sensitive(GTK_WIDGET(self), FALSE);
	dat->npos = dat->index;
	dat->index = 0;
}
#endif

void on_app_activate (GtkApplication *app, gpointer user_data) {
	
	int SPACING = 10;
	
	GtkWidget *win;
	GtkWidget *grid;
	GtkWidget *label;
	GtkWidget *picture;
	GtkIconTheme *icon_theme;
	
	MyData *dat = user_data;
	dat->npos = 0;
	dat->index = 0;
	
	win = gtk_application_window_new  (app);
	gtk_window_set_title (GTK_WINDOW (win), PROGRAM_NAME);
	icon_theme = gtk_icon_theme_get_for_display (gdk_display_get_default ());
	
	gtk_icon_theme_add_resource_path (icon_theme, "/gtk4/aullidolunar/" PROGRAM_NAME);
	
	gtk_window_set_default_icon_name (PROGRAM_NAME);

#ifdef G_OS_UNIX
	gtk_window_set_icon_name  (GTK_WINDOW (win), PROGRAM_NAME);
#endif
	
	grid = gtk_grid_new();
	gtk_widget_set_margin_start (grid, SPACING);
	gtk_widget_set_margin_end (grid, SPACING);
	gtk_widget_set_margin_top (grid, SPACING);
	gtk_widget_set_margin_bottom (grid, SPACING);
	
	gtk_grid_set_column_spacing (GTK_GRID(grid), SPACING);
	gtk_grid_set_row_spacing (GTK_GRID(grid), SPACING);
	
	label = gtk_label_new(_("Sound theme list:"));
	gtk_label_set_xalign(GTK_LABEL(label), 0.0);
	
	const char* sounds_dir = "/usr/share/sounds";
#ifndef G_OS_WIN32
	XfconfChannel *channel = xfconf_channel_get("xsettings");
	g_autofree gchar *curr_theme = xfconf_channel_get_string (channel, "/Net/SoundThemeName", "default");
#else
	const gchar* curr_theme = "";
#endif
	int z = 0;
	
	GtkStringList *builder = gtk_string_list_new (NULL);
	GError *error = NULL;
	
	GFile *path = g_file_new_for_path(sounds_dir);
	GFileEnumerator *enumerator = g_file_enumerate_children (path, "standard::*", G_FILE_QUERY_INFO_NONE, NULL, &error);
	gtk_string_list_append (builder, _("Choose one"));
	if (!enumerator) {
		g_print("g_file_enumerate_children %s: %s\n", _("generared an error"), error->message);
		g_error_free(error);
	} else {
		while(TRUE) {
			GFileInfo *info;
			g_file_enumerator_iterate (enumerator, &info, NULL, NULL, NULL);
			if (!info) break;
			
			if (g_file_info_get_file_type (info) == G_FILE_TYPE_DIRECTORY) {
				const char* item = g_file_info_get_name (info);
				g_autofree gchar *theme = g_build_filename (sounds_dir, item, "index.theme", NULL);
				if (g_file_test(theme, G_FILE_TEST_IS_REGULAR)) {
					if (!g_strcmp0(item, curr_theme)) {
						dat->npos = z;
						dat->npos++;
					}
					 gtk_string_list_append (builder, item);
				}
				z++;
			}
		}
		g_file_enumerator_close (enumerator, NULL, NULL);
	}
	g_clear_object (&path);

	dat->drop_down = gtk_drop_down_new(G_LIST_MODEL (builder), NULL);
	gtk_drop_down_set_selected(GTK_DROP_DOWN(dat->drop_down), dat->npos);
	dat->button = gtk_button_new_with_mnemonic(_("_Apply"));
	picture = gtk_image_new_from_resource ("/platform");
	gtk_image_set_pixel_size (GTK_IMAGE(picture), 96);
	gtk_widget_set_tooltip_text (picture, _("Your platform icon"));
	
	if (dat->npos) gtk_widget_set_sensitive(dat->button, FALSE);

// signals:
	g_signal_connect (dat->drop_down, "notify::selected", G_CALLBACK (on_selection), dat);
#ifndef G_OS_WIN32
	g_signal_connect (dat->button, "clicked", G_CALLBACK (on_clicked), dat);
#endif
	gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(grid), dat->drop_down, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), dat->button, 1, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), picture, 0, 2, 2, 1);
	gtk_window_set_child(GTK_WINDOW (win), grid);
	gtk_window_present (GTK_WINDOW (win));
}
