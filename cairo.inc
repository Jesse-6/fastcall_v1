if ~ defined __CAIRO_INC_INCLUDED__

    define __CAIRO_INC_INCLUDED__
    define __CAIRO_INC_INCLUDED__

    if ~ defined __USE_FASTCALL_v2__
        if defined __GTK3_INC_INCLUDED__
        else if defined __GTK4_INC_INCLUDED__
        else
            library 'libcairo.so'
        end if
    end if

    define CAIRO_FORMAT_ARGB32 0

    define CAIRO_FONT_SLANT_NORMAL 0
    define CAIRO_FONT_SLANT_ITALIC 1
    define CAIRO_FONT_SLANT_OBLIQUE 2

    define CAIRO_FONT_WEIGHT_NORMAL 0
    define CAIRO_FONT_WEIGHT_BOLD 1

    define CAIRO_LINE_CAP_BUTT 0
    define CAIRO_LINE_CAP_ROUND 1
    define CAIRO_LINE_CAP_SQUARE 2

    define CAIRO_LINE_JOIN_MITER 0
    define CAIRO_LINE_JOIN_ROUND 1
    define CAIRO_LINE_JOIN_BEVEL 2

    ext proto cairo_arc, qword, double, double, double, double, double
    ext proto cairo_arc_negative, qword, double, double, double, double, double
    ext proto cairo_clip, qword
    ext proto cairo_close_path, qword
    ext proto cairo_create, qword
    ext proto cairo_curve_to, qword, double, double, double, double, double, double
    ext proto cairo_destroy, qword
    ext proto cairo_device_to_user_distance, qword, qword, qword
    ext proto cairo_fill, qword
    ext proto cairo_fill_preserve, qword
    ext proto cairo_font_extents, qword, qword
    ext proto cairo_image_surface_create, dword, dword, dword
    ext proto cairo_image_surface_create_from_png, qword
    ext proto cairo_image_surface_get_width, qword
    ext proto cairo_image_surface_get_height, qword
    ext proto cairo_line_to, qword, double, double
    ext proto cairo_mask, qword, qword
    ext proto cairo_matrix_init, qword, double, double, double, double, double, double  ; *
    ext proto cairo_matrix_init_scale, qword, double, double
    ext proto cairo_move_to, qword, double, double
    ext proto cairo_new_path, qword
    ext proto cairo_new_sub_path, qword
    ext proto cairo_paint, qword
    ext proto cairo_paint_with_alpha, qword, double
    ext proto cairo_pattern_add_color_stop_rgb, qword, double, double, double, double
    ext proto cairo_pattern_add_color_stop_rgba, qword, double, double, double, double, double
    ext proto cairo_pattern_create_for_surface, qword
    ext proto cairo_pattern_create_linear, double, double, double, double
    ext proto cairo_pattern_create_radial, double, double, double, double, double, double
    ext proto cairo_pattern_destroy, qword
    ext proto cairo_pattern_set_matrix, qword, qword
    ext proto cairo_rectangle, qword, double, double, double, double
    ext proto cairo_rel_curve_to, qword, double, double, double, double, double, double
    ext proto cairo_rel_line_to, qword, double, double
    ext proto cairo_rel_move_to, qword, double, double
    ext proto cairo_restore, qword
    ext proto cairo_rotate, qword, double
    ext proto cairo_save, qword
    ext proto cairo_scale, qword, double, double
    ext proto cairo_select_font_face, qword, qword, dword, dword
    ext proto cairo_set_dash, qword, qword, dword, double
    ext proto cairo_set_extend, qword, dword
    ext proto cairo_set_fill_rule, qword, dword
    ext proto cairo_set_font_size, qword, double
    ext proto cairo_set_line_cap, qword, dword
    ext proto cairo_set_line_join, qword, dword
    ext proto cairo_set_line_width, qword, double
    ext proto cairo_set_operator, qword, dword
    ext proto cairo_set_source, qword, qword
    ext proto cairo_set_source_rgb, qword, double, double, double
    ext proto cairo_set_source_rgba, qword, double, double, double, double
    ext proto cairo_set_source_surface, qword, qword, double, double    ; * to be reviewed
    ext proto cairo_show_text, qword, qword
    ext proto cairo_stroke, qword
    ext proto cairo_stroke_preserve, qword
    ext proto cairo_surface_destroy, qword
    ext proto cairo_surface_write_to_png, qword, qword
    ext proto cairo_text_extents, qword, qword, qword
    ext proto cairo_text_path, qword, qword
    ext proto cairo_transform, qword, qword
    ext proto cairo_translate, qword, double, double    ; *

else
    err "Duplicated inclusion of ""cairo.inc"" file.", 10
end if
