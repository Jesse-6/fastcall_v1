if ~ defined __GTK4_INC_INCLUDED__
	define __GTK4_INC_INCLUDED__
	define __GTK4_INC_INCLUDED__
	
	library 'libgtk-4.so.1'
	library 'libpangocairo-1.0.so.0'
	library 'libpango-1.0.so.0'
	library 'libharfbuzz.so.0'
	library 'libgdk_pixbuf-2.0.so.0'
	library 'libcairo-gobject.so.2'
	library 'libcairo.so.2'
	library 'libvulkan.so.1'
	library 'libgraphene-1.0.so.0'
	library 'libgio-2.0.so.0'
	library 'libgobject-2.0.so.0'
	library 'libglib-2.0.so.0'
	
	define		G_APPLICATION_DEFAULT_FLAGS		0
	define		G_APPLICATION_FLAGS_NONE		0

	define		G_CONNECT_DEFAULT				0
	define		G_CONNECT_AFTER					1
	define		G_CONNECT_SWAPPED				2
	
	define		G_LOG_FLAG_RECURSION			1
	define		G_LOG_FLAG_FATAL				2
	
	define		G_LOG_LEVEL_ERROR				4
	define		G_LOG_LEVEL_CRITICAL			8
	define		G_LOG_LEVEL_WARNING				16
	define		G_LOG_LEVEL_MESSAGE				32
	define		G_LOG_LEVEL_INFO				64
	define		G_LOG_LEVEL_DEBUG				128
	define		G_LOG_LEVEL_MASK				-4

	define		GTK_ALIGN_CENTER				3
	define		GTK_ORIENTATION_HORIZONTAL		0
	define		GTK_ORIENTATION_VERTICAL		1
	
	ext proto g_application_run, qword, dword, qword
	ext proto g_log_set_writer_func, qword, qword, qword
	ext proto g_object_unref, qword
	ext proto g_log, qword, dword, qword, vararg
	ext proto g_print, vararg
	ext proto g_signal_connect_data, qword, qword, qword, qword, dword, dword
	ext proto gdk_display_get_default, none
	ext proto gtk_application_new, qword, dword
	ext proto gtk_application_window_new, qword
	ext proto gtk_box_append, qword, qword
	ext proto gtk_box_new, dword, dword
	ext proto gtk_box_set_homogeneous, qword, dword
	ext proto gtk_builder_add_from_file, qword, qword, qword
	ext proto gtk_builder_get_object, qword, qword
	ext proto gtk_builder_new, none
	ext proto gtk_button_new_with_label, qword
	ext proto gtk_grid_attach, qword, qword, dword, dword, dword, dword
	ext proto gtk_grid_new, none
	ext proto gtk_grid_set_column_homogeneous, qword, dword
	ext proto gtk_grid_set_column_spacing, qword, dword
	ext proto gtk_grid_set_row_homogeneous, qword, dword
	ext proto gtk_grid_set_row_spacing, qword, dword
	ext proto gtk_icon_theme_add_resource_path, qword, qword
	ext proto gtk_icon_theme_add_search_path, qword, qword
	ext proto gtk_icon_theme_get_for_display, qword
	ext proto gtk_icon_theme_get_search_path, qword
	ext proto gtk_icon_theme_has_icon, qword, qword
	ext proto gtk_label_new, qword
	ext proto gtk_label_set_text, qword, qword
	ext proto gtk_label_set_xalign, qword, float32
	ext proto gtk_label_set_yalign, qword, float32
	ext proto gtk_init, none
	ext proto gtk_init_check, none
	ext proto gtk_widget_set_halign, qword, dword
	ext proto gtk_widget_set_valign, qword, dword
	ext proto gtk_widget_set_visible, qword, dword
	ext proto gtk_window_close, qword
	ext proto gtk_window_destroy, qword
	ext proto gtk_window_get_icon_name, qword
	ext proto gtk_window_new, none
	ext proto gtk_window_present, qword
	ext proto gtk_window_set_application, qword, qword
	ext proto gtk_window_set_child, qword, qword
	ext proto gtk_window_set_default_icon_name, qword
	ext proto gtk_window_set_default_size, qword, dword, dword
	ext proto gtk_window_set_icon_name, qword, qword
	ext proto gtk_window_set_resizable, qword, dword
	ext proto gtk_window_set_title, qword, qword
	; ext noreturn proto gtk_widget_show_all, qword
	ext noreturn proto gtk_widget_hide, qword
	ext noreturn proto gtk_widget_show, qword
	

	macro g_signal_connect params&
		match (param), params
			g_signal_connect_data(param, 0, G_CONNECT_DEFAULT);
		end match
	end macro

	macro g_signal_connect_after params&
		match (param), params
			g_signal_connect_data(param, 0, G_CONNECT_AFTER);
		end match
	end macro

	macro g_signal_connect_swapped params&
		match (param), params
			g_signal_connect_data(param, 0, G_CONNECT_SWAPPED);
		end match
	end macro
	
else
	err "Duplicated inclusion of 'gtk4.inc' file.", 10
end if
