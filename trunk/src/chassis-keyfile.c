/* Copyright (C) 2007, 2008 MySQL AB */ 

#include "chassis-keyfile.h"

int chassis_keyfile_to_options(GKeyFile *keyfile, const gchar *ini_group_name, GOptionEntry *config_entries) {
	GError *gerr = NULL;
	int ret = 0;
	int i, j;
	
	/* all the options are in the group for "mysql-proxy" */

	if (!keyfile) return -1;
	if (!g_key_file_has_group(keyfile, ini_group_name)) return 0;

	/* set the defaults */
	for (i = 0; config_entries[i].long_name; i++) {
		GOptionEntry *entry = &(config_entries[i]);
		gchar *arg_string;
		gchar **arg_string_array;
		gboolean arg_bool = 0;
		gint arg_int = 0;
		gdouble arg_double = 0;
		gsize len = 0;

		switch (entry->arg) {
		case G_OPTION_ARG_STRING: 
			/* is this option set already */
			if (NULL == entry->arg_data || NULL != *(gchar **)(entry->arg_data)) break;

			arg_string = g_key_file_get_string(keyfile, ini_group_name, entry->long_name, &gerr);
			if (!gerr) {
				/* strip trailing spaces */
				*(gchar **)(entry->arg_data) = g_strchomp(arg_string);
			}
			break;
		case G_OPTION_ARG_STRING_ARRAY: 
			/* is this option set already */
			if (NULL == entry->arg_data || NULL != *(gchar ***)(entry->arg_data)) break;

			arg_string_array = g_key_file_get_string_list(keyfile, ini_group_name, entry->long_name, &len, &gerr);
			if (!gerr) {
				for (j = 0; arg_string_array[j]; j++) {
					g_strchomp(arg_string_array[j]);
				}	
				*(gchar ***)(entry->arg_data) = arg_string_array;
			}
			break;
		case G_OPTION_ARG_NONE: 
			arg_bool = g_key_file_get_boolean(keyfile, ini_group_name, entry->long_name, &gerr);
			if (!gerr) {
				*(int *)(entry->arg_data) = arg_bool;
			}
			break;
		case G_OPTION_ARG_INT: 
			arg_int = g_key_file_get_integer(keyfile, ini_group_name, entry->long_name, &gerr);
			if (!gerr) {
				*(gint *)(entry->arg_data) = arg_int;
			}
			break;
#if GLIB_MAJOR_VERSION >= 2 && GLIB_MINOR_VERSION >= 12 
		case G_OPTION_ARG_DOUBLE: 
			arg_double = g_key_file_get_double(keyfile, ini_group_name, entry->long_name, &gerr);
			if (!gerr) {
				*(gint *)(entry->arg_data) = arg_double;
			}
			break;
#endif
		default:
			g_error("%s: (keyfile) the option %d can't be handled", G_STRLOC, entry->arg);
			break;
		}

		if (gerr) {
			if (gerr->code != G_KEY_FILE_ERROR_KEY_NOT_FOUND) {
				g_message("%s", gerr->message);
				ret = -1;
			}

			g_error_free(gerr);
			gerr = NULL;
		}
	}

	return ret;
}


