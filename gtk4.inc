if ~ defined __GTK4_INC_INCLUDED__
	define __GTK4_INC_INCLUDED__
	define __GTK4_INC_INCLUDED__

	if ~ defined __USE_FASTCALL_v2__
		if ~ defined __ELF_MODE_DYNAMIC__
			library 'libgtk-4.so.1'
			library 'libpangocairo-1.0.so.0'
			library 'libpango-1.0.so.0'
			library 'libharfbuzz.so.0'
			library 'libgdk_pixbuf-2.0.so.0'
			library 'libcairo-gobject.so.2'
			if ~ defined __CAIRO_INC_INCLUDED__
				library 'libcairo.so.2'
			end if
			library 'libvulkan.so.1'
			library 'libgraphene-1.0.so.0'
			library 'libgio-2.0.so.0'
			library 'libgobject-2.0.so.0'
			library 'libglib-2.0.so.0'
		end if
	end if

	define		G_APPLICATION_DEFAULT_FLAGS		0
	define		G_APPLICATION_FLAGS_NONE		0
	define		G_APPLICATION_IS_SERVICE		1
	define		G_APPLICATION_IS_LAUNCHER		2
	define		G_APPLICATION_HANDLES_OPEN		4
	define		G_APPLICATION_HANDLES_COMMAND_LINE	8
	define		G_APPLICATION_SEND_ENVIRONMENT	16
	define		G_APPLICATION_NON_UNIQUE		32
	define		G_APPLICATION_CAN_OVERRIDE_APP_ID	64
	define		G_APPLICATION_ALLOW_REPLACEMENT	128
	define		G_APPLICATION_REPLACE			256

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


	define		G_PRIORITY_DEFAULT				0
	define		G_PRIORITY_DEFAULT_IDLE			200
	define		G_PRIORITY_HIGH					-100
	define		G_PRIORITY_HIGH_IDLE			100
	define		G_PRIORITY_LOW					300

	define		GDK_BUTTON_PRIMARY				1
	define		GDK_BUTTON_MIDDLE				2
	define		GDK_BUTTON_SECONDARY			3

	define		GTK_ALIGN_CENTER				3
	define		GTK_ORIENTATION_HORIZONTAL		0
	define		GTK_ORIENTATION_VERTICAL		1

	define		GTK_LEVEL_BAR_MODE_CONTINUOUS	0
	define		GTK_LEVEL_BAR_MODE_DISCRETE		1

	define		GTK_STYLE_PROVIDER_PRIORITY_FALLBACK	1
	define		GTK_STYLE_PROVIDER_PRIORITY_THEME		200
	define		GTK_STYLE_PROVIDER_PRIORITY_SETTINGS	400
	define		GTK_STYLE_PROVIDER_PRIORITY_APPLICATION	600
	define		GTK_STYLE_PROVIDER_PRIORITY_USER		800

	ext proto g_application_run, qword, dword, qword
	ext proto g_idle_add_full, dword, qword, qword, qword
	ext proto g_list_model_get_n_items, qword
	ext proto g_log, qword, dword, qword, vararg
	ext proto g_log_set_writer_func, qword, qword, qword
	ext proto g_main_context_iteration, qword, dword
	ext proto g_main_loop_new, qword, dword
	ext proto g_main_loop_quit, qword
	ext proto g_main_loop_run, qword
	ext proto g_object_ref, qword
	ext proto g_object_ref_sink, qword
	ext proto g_object_run_dispose, qword
	ext proto g_object_unref, qword
	ext proto g_print, qword, vararg
	ext proto g_printerr, qword, vararg
	ext proto g_signal_connect_data, qword, qword, qword, qword, dword, dword
	ext proto g_signal_handler_disconnect, qword, qword
	ext proto gdk_cairo_set_source_rgba, qword, qword
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
	ext proto gtk_css_provider_load_from_file, qword, qword
	ext proto gtk_css_provider_load_from_path, qword, qword
	ext proto gtk_css_provider_load_from_string, qword, qword
	ext proto gtk_css_provider_new, none
	ext proto gtk_css_provider_to_string, qword
	ext proto gtk_drawing_area_get_content_height, qword
	ext proto gtk_drawing_area_get_content_width, qword
	ext proto gtk_drawing_area_new, none
	ext proto gtk_drawing_area_set_content_height, qword, dword
	ext proto gtk_drawing_area_set_content_width, qword, dword
	ext proto gtk_drawing_area_set_draw_func, qword, qword, qword, qword
	ext proto gtk_frame_new, qword
	ext proto gtk_frame_set_child, qword, qword
	ext proto gtk_gesture_click_new, none
	ext proto gtk_gesture_drag_new, none
	ext proto gtk_gesture_single_set_button, qword, dword
	ext proto gtk_grid_attach, qword, qword, dword, dword, dword, dword
	ext proto gtk_grid_new, none
	ext proto gtk_grid_remove, qword, qword
	ext proto gtk_grid_set_column_homogeneous, qword, dword
	ext proto gtk_grid_set_column_spacing, qword, dword
	ext proto gtk_grid_set_row_homogeneous, qword, dword
	ext proto gtk_grid_set_row_spacing, qword, dword
	ext proto gtk_icon_theme_add_resource_path, qword, qword
	ext proto gtk_icon_theme_add_search_path, qword, qword
	ext proto gtk_icon_theme_get_for_display, qword
	ext proto gtk_icon_theme_get_search_path, qword
	ext proto gtk_icon_theme_has_icon, qword, qword
	ext proto gtk_init, none
	ext proto gtk_init_check, none
	ext proto gtk_label_new, qword
	ext proto gtk_label_set_text, qword, qword
	ext proto gtk_label_set_xalign, qword, float32
	ext proto gtk_label_set_yalign, qword, float32
	ext proto gtk_level_bar_add_offset_value, qword, qword, double
	ext proto gtk_level_bar_new, none
	ext proto gtk_level_bar_new_for_interval, double, double
	ext proto gtk_level_bar_set_inverted, qword, dword
	ext proto gtk_level_bar_set_max_value, qword, double
	ext proto gtk_level_bar_set_min_value, qword, double
	ext proto gtk_level_bar_set_mode, qword, dword
	ext proto gtk_level_bar_set_value, qword, double
	ext proto gtk_native_get_surface, qword
	ext proto gtk_orientable_set_orientation, qword, dword
	ext proto gtk_scrolled_window_new, none
	ext proto gtk_scrolled_window_set_child, qword, qword
	ext proto gtk_style_context_add_provider_for_display, qword, qword, dword
	ext proto gtk_widget_add_controller, qword, qword
	ext proto gtk_widget_get_clipboard, qword
	ext proto gtk_widget_get_color, qword, qword
	ext proto gtk_widget_get_height, qword
	ext proto gtk_widget_get_native, qword
	ext proto gtk_widget_get_width, qword
	ext proto gtk_widget_hide, qword
	ext proto gtk_widget_queue_draw, qword
	ext proto gtk_widget_set_halign, qword, dword
	ext proto gtk_widget_set_hexpand, qword, dword
	ext proto gtk_widget_set_name, qword, qword
	ext proto gtk_widget_set_opacity, qword, double
	ext proto gtk_widget_set_parent, qword, qword
	ext proto gtk_widget_set_size_request, qword, dword, dword
	ext proto gtk_widget_set_tooltip_markup, qword, qword
	ext proto gtk_widget_set_tooltip_text, qword, qword
	ext proto gtk_widget_set_valign, qword, dword
	ext proto gtk_widget_set_vexpand, qword, dword
	ext proto gtk_widget_set_visible, qword, dword
	ext proto gtk_widget_show, qword
	ext proto gtk_widget_unparent, qword
	ext proto gtk_window_close, qword
	ext proto gtk_window_destroy, qword
	ext proto gtk_window_get_icon_name, qword
	ext proto gtk_window_get_toplevels, none
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
