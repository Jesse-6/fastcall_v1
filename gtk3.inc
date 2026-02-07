if ~ defined __GTK3_INC_INCLUDED__
	define __GTK3_INC_INCLUDED__
	define __GTK3_INC_INCLUDED__

    library 'libgtk-3.so.0'
    library 'libgdk-3.so.0'
    library 'libz.so.1'
    library 'libpangocairo-1.0.so.0'
    library 'libpango-1.0.so.0'
    library 'libharfbuzz.so.0'
    library 'libatk-1.0.so.0'
    library 'libcairo-gobject.so.2'
    library 'libcairo.so.2'
    library 'libgdk_pixbuf-2.0.so.0'
    library 'libgio-2.0.so.0'
    library 'libgobject-2.0.so.0'
    library 'libglib-2.0.so.0'

    define G_APPLICATION_DEFAULT_FLAGS 0
    define G_APPLICATION_FLAGS_NONE 0

    define G_LOG_FLAG_RECURSION    1
    define G_LOG_FLAG_FATAL        2
    define G_LOG_LEVEL_ERROR       4
    define G_LOG_LEVEL_CRITICAL    8
    define G_LOG_LEVEL_WARNING     16
    define G_LOG_LEVEL_MESSAGE     32
    define G_LOG_LEVEL_INFO        64
    define G_LOG_LEVEL_DEBUG       128
    define G_LOG_LEVEL_MASK        -4

    define G_LOG_WRITER_HANDLED    1
    define G_LOG_WRITER_UNHANDLED  0

    define G_PRIORITY_DEFAULT_IDLE 200
    define G_PRIORITY_HIGH_IDLE    100

    define G_CONNECT_DEFAULT 0
    define G_CONNECT_AFTER 1
    define G_CONNECT_SWAPPED 2
    
    define G_TYPE_FUNDAMENTAL_SHIFT 2
    
    define G_TYPE_INVALID           (0 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_NONE              (1 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_INTERFACE         (2 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_CHAR              (3 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_UCHAR             (4 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_BOOLEAN           (5 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_INT               (6 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_UINT              (7 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_LONG              (8 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_ULONG             (9 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_INT64             (10 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_UINT64            (11 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_ENUM              (12 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_FLAGS             (13 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_FLOAT             (14 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_DOUBLE            (15 shl G_TYPE_FUNDAMENTAL_SHIFT)
    define G_TYPE_STRING            (16 shl G_TYPE_FUNDAMENTAL_SHIFT)

    define GDK_EXPOSURE_MASK            2
    define GDK_POINTER_MOTION_MASK      4
    define GDK_POINTER_MOTION_HINT_MASK 8
    define GDK_BUTTON_MOTION_MASK       16
    define GDK_BUTTON1_MOTION_MASK      32
    define GDK_BUTTON2_MOTION_MASK      64
    define GDK_BUTTON3_MOTION_MASK      128
    define GDK_BUTTON_PRESS_MASK        256
    define GDK_BUTTON_RELEASE_MASK      512
    define GDK_KEY_PRESS_MASK           1024
    define GDK_KEY_RELEASE_MASK         2048
    define GDK_ENTER_NOTIFY_MASK        4096
    define GDK_LEAVE_NOTIFY_MASK        8192
    define GDK_FOCUS_CHANGE_MASK        16384
    define GDK_STRUCTURE_MASK           32768
    define GDK_PROPERTY_CHANGE_MASK     65536
    define GDK_VISIBILITY_NOTIFY_MASK   131072
    define GDK_PROXIMITY_IN_MASK        262144
    define GDK_PROXIMITY_OUT_MASK       524288
    define GDK_SUBSTRUCTURE_MASK        1048576
    define GDK_SCROLL_MASK              2097152
    define GDK_TOUCH_MASK               4194304
    define GDK_SMOOTH_SCROLL_MASK       8388608
    define GDK_TOUCHPAD_GESTURE_MASK    16777216
    define GDK_TABLET_PAD_MASK          33554432
    define GDK_ALL_EVENTS_MASK          67108862

    define GDK_WINDOW_STATE_WITHDRAWN        1
    define GDK_WINDOW_STATE_ICONIFIED        2
    define GDK_WINDOW_STATE_MAXIMIZED        4
    define GDK_WINDOW_STATE_STICKY           8
    define GDK_WINDOW_STATE_FULLSCREEN       16
    define GDK_WINDOW_STATE_ABOVE            32
    define GDK_WINDOW_STATE_BELOW            64
    define GDK_WINDOW_STATE_FOCUSED          128
    define GDK_WINDOW_STATE_TILED            256
    define GDK_WINDOW_STATE_TOP_TILED        512
    define GDK_WINDOW_STATE_TOP_RESIZABLE    1024
    define GDK_WINDOW_STATE_RIGHT_TILED      2048
    define GDK_WINDOW_STATE_RIGHT_RESIZABLE  4096
    define GDK_WINDOW_STATE_BOTTOM_TILED     8192
    define GDK_WINDOW_STATE_BOTTOM_RESIZABLE 16384
    define GDK_WINDOW_STATE_LEFT_TILED       32768
    define GDK_WINDOW_STATE_LEFT_RESIZABLE   65536

    define GTK_ALIGN_FILL                  0
    define GTK_ALIGN_START                 1
    define GTK_ALIGN_END                   2
    define GTK_ALIGN_CENTER                3
    define GTK_ALIGN_BASELINE              4
    
    define GTK_ICON_SIZE_INVALID        0
    define GTK_ICON_SIZE_MENU           1
    define GTK_ICON_SIZE_SMALL_TOOLBAR  2
    define GTK_ICON_SIZE_LARGE_TOOLBAR  3
    define GTK_ICON_SIZE_BUTTON         4
    define GTK_ICON_SIZE_DND            5
    define GTK_ICON_SIZE_DIALOG         6

    define GTK_ORIENTATION_HORIZONTAL      0
    define GTK_ORIENTATION_VERTICAL        1

    define GTK_PACK_START  0
    define GTK_PACK_END    1

    define GTK_RESPONSE_NONE       -1
    define GTK_RESPONSE_REJECT     -2
    define GTK_RESPONSE_ACCEPT     -3
    define GTK_RESPONSE_DELETE_EVENT -4
    define GTK_RESPONSE_OK         -5
    define GTK_RESPONSE_CANCEL     -6
    define GTK_RESPONSE_CLOSE      -7
    define GTK_RESPONSE_YES        -8
    define GTK_RESPONSE_NO         -9
    define GTK_RESPONSE_APPLY      -10
    define GTK_RESPONSE_HELP       -11

    define GTK_DIALOG_MODAL        1
    define GTK_DIALOG_DESTROY_WITH_PARENT 2
    define GTK_DIALOG_USE_HEADER_BAR 4

    define GTK_BUTTONS_NONE        0
    define GTK_BUTTONS_OK          1
    define GTK_BUTTONS_CLOSE       2
    define GTK_BUTTONS_CANCEL      3
    define GTK_BUTTONS_YES_NO      4
    define GTK_BUTTONS_OK_CANCEL   5

    define GTK_JUSTIFY_LEFT        0
    define GTK_JUSTIFY_RIGHT       1
    define GTK_JUSTIFY_CENTER      2
    define GTK_JUSTIFY_FILL        3

    define GTK_MESSAGE_INFO        0
    define GTK_MESSAGE_WARNING     1
    define GTK_MESSAGE_QUESTION    2
    define GTK_MESSAGE_ERROR       3
    define GTK_MESSAGE_OTHER       4

    define GTK_LEVEL_BAR_MODE_CONTINUOUS   0
    define GTK_LEVEL_BAR_MODE_DISCRETE     1
    
    define GTK_SELECTION_NONE               0
    define GTK_SELECTION_SINGLE             1
    define GTK_SELECTION_BROWSE             2
    define GTK_SELECTION_MULTIPLE           3

    define GTK_STATE_FLAG_NORMAL           0
    define GTK_STATE_FLAG_ACTIVE           1
    define GTK_STATE_FLAG_PRELIGHT         2
    define GTK_STATE_FLAG_SELECTED         4
    define GTK_STATE_FLAG_INSENSITIVE      8
    define GTK_STATE_FLAG_INCONSISTENT     16
    define GTK_STATE_FLAG_FOCUSED          32
    define GTK_STATE_FLAG_BACKDROP         64
    define GTK_STATE_FLAG_DIR_LTR          128
    define GTK_STATE_FLAG_DIR_RTL          256
    define GTK_STATE_FLAG_LINK             512
    define GTK_STATE_FLAG_VISITED          1024
    define GTK_STATE_FLAG_CHECKED          2048
    define GTK_STATE_FLAG_DROP_ACTIVE      4096

    define GTK_STYLE_PROVIDER_PRIORITY_USER        800
    define GTK_STYLE_PROVIDER_PRIORITY_FALLBACK    1
    
    define GTK_TREE_VIEW_GRID_LINES_NONE            0
    define GTK_TREE_VIEW_GRID_LINES_HORIZONTAL      1
    define GTK_TREE_VIEW_GRID_LINES_VERTICAL        2
    DEFINE GTK_TREE_VIEW_GRID_LINES_BOTH            3
    
    define GTK_WINDOW_TOPLEVEL              0
    define GTK_WINDOW_POPUP                 1
    
    PANGO_WEIGHT_THIN           = 100
    PANGO_WEIGHT_ULTRALIGHT     = 200
    PANGO_WEIGHT_LIGHT          = 300
    PANGO_WEIGHT_SEMILIGHT      = 350
    PANGO_WEIGHT_BOOK           = 380
    PANGO_WEIGHT_NORMAL         = 400
    PANGO_WEIGHT_MEDIUM         = 500
    PANGO_WEIGHT_SEMIBOLD       = 600
    PANGO_WEIGHT_BOLD           = 700
    PANGO_WEIGHT_ULTRABOLD      = 800
    PANGO_WEIGHT_HEAVY          = 900
    PANGO_WEIGHT_ULTRAHEAVY     = 1000

    ; NOTE: to be removed (I prefer keep structures out of reusable headers).
    ; struc GDKEVENTWINDOWSTATE
    ;         label . : .size - $
    ;         .type             rd 1
    ;                         rd 1
    ;         .window           rq 1
    ;         .send_event       rb 1
    ;                         rb 3
    ;         .changed_mask     rd 1
    ;         .new_window_state rd 1
    ;         .size:
    ; end struc
    ; 
    ; struc GDKRGBA
    ;         label . : .size - $
    ;         .red            rq 1
    ;         .green          rq 1
    ;         .blue           rq 1
    ;         .alpha          rq 1
    ;         .size:
    ; end struc
    ; 
    ; virtual at 0
    ; GDKEVENTWINDOWSTATE GDKEVENTWINDOWSTATE
    ; end virtual
    ; 
    ; virtual at 0
    ; GDKRGBA GDKRGBA
    ; end virtual

    ext proto g_application_run, qword, dword, qword
    ext proto g_clear_error, qword
    ext proto g_free, qword
    ext proto g_idle_add_full, dword, qword, qword, qword
    ext proto g_log, dword, dword, vararg
    ext proto g_log_set_writer_func, qword, qword, qword
    ext proto g_object_ref, qword
    ext proto g_object_set, qword, qword, vararg
    ext proto g_object_unref, qword
    ext proto g_print, qword, vararg
    ext proto g_printerr, qword, vararg
    ext proto g_signal_connect_data, qword, qword, qword, qword, dword, dword
    ext proto g_snprintf, qword, qword, qword, vararg
    ext noreturn proto g_thread_exit, qword
    ext proto g_thread_get_initialized, none
    ext proto g_thread_get_name, qword
    ext proto g_thread_init, qword
    ext proto g_thread_join, qword
    ext proto g_thread_new, qword, qword, qword
    ext proto g_thread_ref, qword
    ext proto g_thread_self, none
    ext proto g_thread_try_new, qword, qword, qword, qword
    ext proto g_thread_unref, qword
    ext proto g_thread_yield, none
    ext proto g_usleep, qword
    ext proto gdk_display_get_default, none
    ext proto gdk_event_handler_set, qword, qword, qword
    ext proto gdk_screen_get_default, none
    ext proto gdk_screen_is_composited, qword
    ext proto gdk_threads_add_idle_full, dword, qword, qword, qword
    ext proto gdk_threads_enter, none
    ext proto gdk_threads_init, none
    ext proto gdk_threads_leave, none
    ext proto gtk_application_new, qword, dword
    ext proto gtk_application_window_new, qword
    ext proto gtk_box_new, dword, dword
    ext proto gtk_box_set_child_packing, qword, qword, byte, byte, dword, dword
    ext proto gtk_box_set_homogeneous, qword, dword
    ext proto gtk_builder_add_callback_symbol, qword, qword, qword
    ext proto gtk_builder_add_from_file, qword, qword, qword
    ext proto gtk_builder_add_from_string, qword, qword, dword, qword
    ext proto gtk_builder_connect_signals, qword, qword
    ext proto gtk_builder_get_object, qword, qword
    ext proto gtk_builder_new, none
    ext proto gtk_builder_new_from_file, qword
    ext proto gtk_button_new_with_label, qword
    ext proto gtk_button_set_focus_on_click, qword, byte
    ext proto gtk_button_set_image, qword, qword
    ext proto gtk_button_set_label, qword, qword
    ext proto gtk_cell_renderer_pixbuf_new, none
    ext proto gtk_cell_renderer_text_new, none
    ext proto gtk_check_button_new, none
    ext proto gtk_check_button_new_with_label, qword
    ext proto gtk_check_button_new_with_mnemonic, qword
    ext proto gtk_combo_box_set_active_id, qword, qword
    ext proto gtk_combo_box_text_append, qword, qword, qword
    ext proto gtk_combo_box_text_append_text, qword, qword
    ext proto gtk_combo_box_text_get_active_text, qword
    ext proto gtk_combo_box_text_insert, qword, dword, qword, qword
    ext proto gtk_combo_box_text_insert_text, qword, dword, qword
    ext proto gtk_combo_box_text_prepend, qword, qword, qword
    ext proto gtk_combo_box_text_prepend_text, qword, qword
    ext proto gtk_combo_box_text_remove, qword, dword
    ext proto gtk_combo_box_text_remove_all, qword
    ext proto gtk_combo_box_set_active, qword, dword
    ext proto gtk_container_add, qword, qword
    ext proto gtk_css_provider_new, none
    ext proto gtk_css_provider_get_named, qword, qword
    ext proto gtk_css_provider_load_from_data, qword, qword, dword, qword
    ext proto gtk_css_provider_load_from_file, qword, qword, qword
    ext proto gtk_css_provider_load_from_path, qword, qword, qword
    ext proto gtk_css_provider_load_from_resource, qword, qword
    ext proto gtk_css_provider_to_string, qword
    ext proto gtk_dialog_new_with_buttons, qword, qword, dword, vararg
    ext proto gtk_dialog_run, qword
    ext proto gtk_drawing_area_new, none
    ext proto gtk_entry_get_text, qword
    ext proto gtk_entry_get_text_length, qword
    ext proto gtk_entry_set_placeholder_text, qword, qword
    ext proto gtk_entry_set_text, qword, qword
    ext proto gtk_grid_attach, qword, qword, dword, dword, dword, dword
    ext proto gtk_grid_insert_column, qword, dword
    ext proto gtk_grid_insert_row, qword, dword
    ext proto gtk_grid_new, none
    ext proto gtk_grid_set_column_homogeneous, qword, dword
    ext proto gtk_grid_set_column_spacing, qword, dword
    ext proto gtk_grid_set_row_homogeneous, qword, dword
    ext proto gtk_grid_set_row_spacing, qword, dword
    ext proto gtk_icon_theme_add_resource_path, qword, qword
    ext proto gtk_icon_theme_append_search_path, qword, qword
    ext proto gtk_icon_theme_get_for_screen, qword
    ext proto gtk_icon_theme_get_search_path, qword, qword, qword
    ext proto gtk_icon_theme_has_icon, qword, qword
    ext proto gtk_image_new_from_file, qword
    ext proto gtk_image_set_from_icon_name, qword, qword, dword
    ext proto gtk_image_set_pixel_size, qword, dword
    ext proto gtk_init, qword, qword
    ext proto gtk_init_check, qword, qword
    ext proto gtk_label_get_text, qword
    ext proto gtk_label_new, qword
    ext proto gtk_label_new_with_mnemonic, qword
    ext proto gtk_label_set_single_line_mode, qword, byte
    ext proto gtk_label_set_text, qword, qword
    ext proto gtk_label_set_justify, qword, dword
    ext proto gtk_label_set_xalign, qword, float
    ext proto gtk_label_set_yalign, qword, float
    ext proto gtk_level_bar_add_offset_value, qword, qword, double
    ext proto gtk_level_bar_get_inverted, qword
    ext proto gtk_level_bar_get_max_value, qword
    ext proto gtk_level_bar_get_min_value, qword
    ext proto gtk_level_bar_get_mode, qword
    ext proto gtk_level_bar_get_offset_value, qword, qword, qword
    ext proto gtk_level_bar_get_value, qword
    ext proto gtk_level_bar_new, none
    ext proto gtk_level_bar_new_for_interval, double, double
    ext proto gtk_level_bar_remove_offset_value, qword, qword
    ext proto gtk_level_bar_set_inverted, qword, byte
    ext proto gtk_level_bar_set_max_value, qword, double
    ext proto gtk_level_bar_set_min_value, qword, double
    ext proto gtk_level_bar_set_mode, qword, dword
    ext proto gtk_level_bar_set_value, qword, double
    ext proto gtk_list_store_append, qword, qword
    ext proto gtk_list_store_clear, qword
    ext proto gtk_list_store_new, dword, vararg
    ext proto gtk_list_store_remove, qword, qword
    ext proto gtk_list_store_set, qword, qword, vararg
    ext proto gtk_main, none
    ext noreturn proto gtk_main_do_event, qword
    ext proto gtk_main_iteration, none
    ext proto gtk_main_iteration_do, byte
    ext proto gtk_main_quit, none
    ext proto gtk_message_dialog_new, qword, dword, dword, dword, vararg
    ext proto gtk_native_dialog_run, qword
    ext proto gtk_orientable_get_orientation, qword
    ext proto gtk_orientable_set_orientation, qword, dword
    ext proto gtk_spin_button_get_value, qword
    ext proto gtk_spin_button_get_value_as_int, qword
    ext proto gtk_spin_button_set_increments, qword, double, double
    ext proto gtk_spin_button_set_range, qword, double, double
    ext proto gtk_spin_button_set_value, qword, double
    ext proto gtk_stack_get_child_by_name, qword, qword
    ext proto gtk_stack_set_visible_child, qword, qword
    ext proto gtk_stack_set_visible_child_full, qword, qword, dword
    ext proto gtk_stack_set_visible_child_name, qword, qword
    ext proto gtk_statusbar_get_context_id, qword, qword
    ext proto gtk_statusbar_get_message_area, qword
    ext proto gtk_statusbar_new, none
    ext proto gtk_statusbar_pop, qword, dword
    ext proto gtk_statusbar_push, qword, dword, qword
    ext proto gtk_statusbar_remove, qword, dword, dword
    ext proto gtk_statusbar_remove_all, qword, dword
    ext proto gtk_style_context_add_provider_for_screen, qword, qword, dword
    ext proto gtk_style_context_get_background_color, qword, dword, qword
    ext proto gtk_style_context_get_color, qword, dword, qword
    ext proto gtk_tree_model_get, qword, qword, vararg
    ext proto gtk_tree_store_append, qword, qword, qword
    ext proto gtk_tree_store_new, dword, vararg
    ext proto gtk_tree_store_set, qword, qword, vararg
    ext proto gtk_tree_view_column_add_attribute, qword, qword, qword, dword
    ext proto gtk_tree_view_append_column, qword, qword
    ext proto gtk_tree_view_column_new, none
    ext proto gtk_tree_view_column_pack_start, qword, qword, dword
    ext proto gtk_tree_view_column_set_cell_data_func, qword, qword, qword, qword, qword
    ext proto gtk_tree_view_column_set_title, qword, qword
    ext proto gtk_tree_view_expand_all, qword
    ext proto gtk_tree_view_get_model, qword
    ext proto gtk_tree_view_get_selection, qword
    ext proto gtk_tree_view_insert_column_with_attributes, qword, dword, qword, qword, vararg
    ext proto gtk_tree_view_new, none
    ext proto gtk_tree_view_new_with_model, qword
    ext proto gtk_tree_selection_set_mode, qword, dword
    ext proto gtk_tree_view_set_grid_lines, qword, dword
    ext proto gtk_tree_view_set_model, qword, qword
    ext proto gtk_toggle_button_get_active, qword
    ext proto gtk_toggle_button_get_inconsistent, qword
    ext proto gtk_toggle_button_get_mode, qword
    ext proto gtk_toggle_button_set_active, qword, dword
    ext proto gtk_toggle_button_set_inconsistent, qword, dword
    ext proto gtk_toggle_button_set_mode, qword, byte
    ext proto gtk_toggle_button_toggled, qword      ; according to GTK team, don't use this.
    ext proto gtk_widget_add_events, qword, dword
    ext proto gtk_widget_destroy, qword
    ext proto gtk_widget_get_style_context, qword
    ext proto gtk_widget_get_opacity, qword
    ext proto gtk_widget_get_parent, qword
    ext proto gtk_widget_queue_draw, qword
    ext proto gtk_widget_queue_draw_area, qword, dword, dword, dword, dword
    ext proto gtk_widget_set_events, qword, dword
    ext proto gtk_widget_set_halign, qword, dword
    ext proto gtk_widget_set_hexpand, qword, dword
    ext proto gtk_widget_set_margin_bottom, qword, dword
    ext proto gtk_widget_set_margin_end, qword, dword
    ext proto gtk_widget_set_margin_start, qword, dword
    ext proto gtk_widget_set_margin_top, qword, dword
    ext proto gtk_widget_set_name, qword, qword
    ext proto gtk_widget_set_opacity, qword, double
    ext proto gtk_widget_set_parent, qword, qword
    ext proto gtk_widget_set_sensitive, qword, dword
    ext proto gtk_widget_set_size_request, qword, dword, dword
    ext proto gtk_widget_set_tooltip_text, qword, qword
    ext proto gtk_widget_set_valign, qword, dword
    ext proto gtk_widget_set_vexpand, qword, dword
    ext proto gtk_widget_set_visible, qword, dword
    ext proto gtk_window_close, qword
    ext proto gtk_window_get_title, qword
    ext proto gtk_window_new, dword
    ext noreturn proto gtk_window_present, qword
    ext proto gtk_window_set_application, qword, qword
    ext proto gtk_window_set_default_icon_name, qword
    ext proto gtk_window_set_default_size, qword, dword, dword
    ext proto gtk_window_set_icon_name, qword, qword
    ext proto gtk_window_set_resizable, qword, dword
    ext proto gtk_window_set_title, qword, qword
    ext proto gtk_widget_show_all, qword
    ext proto gtk_widget_hide, qword
    ext proto gtk_widget_show, qword

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
	err "Duplicated inclusion of 'gtk3.inc' file.", 10
end if


