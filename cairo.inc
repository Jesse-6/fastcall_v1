if ~ defined __CAIRO_INC_INCLUDED__

    define __CAIRO_INC_INCLUDED__
    define __CAIRO_INC_INCLUDED__

    if ~ defined __USE_FASTCALL_v2__
        if ~ defined __ELF_MODE_DYNAMIC__
            if defined __GTK3_INC_INCLUDED__
            else if defined __GTK4_INC_INCLUDED__
            else
                    library 'libcairo.so'
            end if
        end if
    end if

    struct CAIRO_TEXT_EXTENTS_T
        .x_bearing      dq ?
        .y_bearing      dq ?
        .width          dq ?
        .height         dq ?
        .x_advance      dq ?
        .y_advance      dq ?
    end struct

    struct CAIRO_FONT_EXTENTS_T
        .ascent         dq ?
        .descent        dq ?
        .height         dq ?
        .max_x_advance  dq ?
        .max_y_advance  dq ?
    end struct

    CAIRO_FORMAT_ARGB32 := 0

    CAIRO_FONT_SLANT_NORMAL     := 0
    CAIRO_FONT_SLANT_ITALIC     := 1
    CAIRO_FONT_SLANT_OBLIQUE    := 2

    CAIRO_FONT_WEIGHT_NORMAL := 0
    CAIRO_FONT_WEIGHT_BOLD   := 1

    CAIRO_LINE_CAP_BUTT     := 0
    CAIRO_LINE_CAP_ROUND    := 1
    CAIRO_LINE_CAP_SQUARE   := 2

    CAIRO_LINE_JOIN_MITER   := 0
    CAIRO_LINE_JOIN_ROUND   := 1
    CAIRO_LINE_JOIN_BEVEL   := 2

    CAIRO_OPERATOR_CLEAR    := 0
    CAIRO_OPERATOR_SOURCE   := 1
    CAIRO_OPERATOR_OVER     := 2
    CAIRO_OPERATOR_IN       := 3
    CAIRO_OPERATOR_OUT      := 4
    CAIRO_OPERATOR_ATOP     := 5
    CAIRO_OPERATOR_DEST     := 6
    CAIRO_OPERATOR_DEST_OVER := 7
    CAIRO_OPERATOR_DEST_IN  := 8
    CAIRO_OPERATOR_DEST_OUT := 9
    CAIRO_OPERATOR_DEST_ATOP := 10
    CAIRO_OPERATOR_XOR      := 11
    CAIRO_OPERATOR_ADD      := 12
    CAIRO_OPERATOR_SATURATE := 13
    CAIRO_OPERATOR_MULTIPLY := 14
    CAIRO_OPERATOR_SCREEN   := 15
    CAIRO_OPERATOR_OVERLAY  := 16
    CAIRO_OPERATOR_DARKEN   := 17
    CAIRO_OPERATOR_LIGHTEN  := 18
    CAIRO_OPERATOR_COLOR_DODGE := 19
    CAIRO_OPERATOR_COLOR_BURN  := 20
    CAIRO_OPERATOR_HARD_LIGHT  := 21
    CAIRO_OPERATOR_SOFT_LIGHT  := 22
    CAIRO_OPERATOR_DIFFERENCE  := 23
    CAIRO_OPERATOR_EXCLUSION   := 24
    CAIRO_OPERATOR_HSL_HUE     :=25
    CAIRO_OPERATOR_HSL_SATURATION := 26
    CAIRO_OPERATOR_HSL_COLOR      := 27
    CAIRO_OPERATOR_HSL_LUMINOSITY := 28

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
    ext proto cairo_pattern_set_extend, qword, dword
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
    ext proto cairo_xcb_device_debug_cap_xrender_version, qword, dword, dword
    ext proto cairo_xcb_device_debug_cap_xshm_version, qword, dword, dword
    ext proto cairo_xcb_device_debug_get_precision, qword
    ext proto cairo_xcb_device_debug_set_precision, qword, dword
    ext proto cairo_xcb_device_get_connection, qword
    ext proto cairo_xcb_surface_create, qword, dword, qword, dword, dword
    ext proto cairo_xcb_surface_create_for_bitmap, qword, qword, dword, dword, dword
    ext proto cairo_xcb_surface_create_with_xrender_format, qword, qword, dword, qword, dword, dword
    ext proto cairo_xcb_surface_set_drawable, qword, dword, dword, dword
    ext proto cairo_xcb_surface_set_size, qword, dword, dword

else
    err "Duplicated inclusion of ""cairo.inc"" file.", 10
end if
