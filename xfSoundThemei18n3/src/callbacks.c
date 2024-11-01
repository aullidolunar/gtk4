#include "callbacks.h"

int find_sound_themes(const char* sounds_dir, const gchar* curr_theme, GtkStringList *slist, int* selection) {
  GFile *path = g_file_new_for_path(sounds_dir);
  GError *error = NULL;
  int num = 0;
  GFileEnumerator *enumerator = g_file_enumerate_children (path, "standard::*", G_FILE_QUERY_INFO_NONE, NULL, &error);
  if (!enumerator) {
		g_print("g_file_enumerate_children: %s\n", error->message);
		g_error_free(error);
	} else {
    while(TRUE) {
			GFileInfo *info;
      g_file_enumerator_iterate (enumerator, &info, NULL, NULL, NULL);
			if (!info) break;
			if (g_file_info_get_file_type (info) == G_FILE_TYPE_DIRECTORY) {
				const char* item = g_file_info_get_name (info);
				gchar *theme = g_build_filename (sounds_dir, item, "index.theme", NULL);
				if (g_file_test(theme, G_FILE_TEST_IS_REGULAR)) {
					 num++;
           gtk_string_list_append (slist, item);
           if (!g_strcmp0(item, curr_theme)) {
             *selection = num;
           }
				}
        g_free(theme);
			}
		}
		g_file_enumerator_close (enumerator, NULL, NULL);
  }
  g_object_unref(path);
  return num;
}

G_MODULE_EXPORT void on_button_ok_clicked(GtkDropDown* dropdown) {
  guint pos = gtk_drop_down_get_selected(dropdown);
  if (pos) {
    GListModel *list = gtk_drop_down_get_model(dropdown);
    const gchar* sound_theme = gtk_string_list_get_string(GTK_STRING_LIST(list), pos);
#ifndef G_OS_WIN32
    XfconfChannel *channel = xfconf_channel_get("xsettings");
    xfconf_channel_set_string (channel, "/Net/SoundThemeName", sound_theme);
#else
    g_print("%s\n", sound_theme);
#endif
  }
}