if ~ defined __XCB_INC_INCLUDED__
    define __XCB_INC_INCLUDED__
    define __XCB_INC_INCLUDED__

    if ~ defined __ELF_MODE_DYNAMIC__
        library 'libxcb.so.1'
    end if

    struct XCB_ARC_T X:?, Y:?, W:?, H:?, A1:?, A2:?
        .x      dw X
        .y      dw Y
        .width  dw W
        .height dw H
        .angle1 dw A1
        .angle2 dw A2
    end struct

    struct XCB_BUTTON_PRESS_EVENT_T
        .response_type      db ?
        .detail             db ?
        .sequence           dw ?
        .time               dd ?
        .root               dd ?
        .event              dd ?
        .child              dd ?
        .root_x             dw ?
        .root_y             dw ?
        .event_x            dw ?
        .event_y            dw ?
        .state              dw ?
        .same_screen        db ?
                            rb 1
    end struct

    struct XCB_CLIENT_MESSAGE_EVENT_T
        .response_type          db ?
        .format                 db ?
        .sequence               dw ?
        .window                 dd ?
        .type                   dd ?
        .data:
        virtual at .data
            .data8              rb 20
        end virtual
        virtual at .data
            .data16             rw 10
        end virtual
        virtual at .data
            .data32             rd 5
        end virtual
    end struct

    struct XCB_DEPTH_T
        .depth          db ?
                        db ?
        .visuals_len    dw ?
                        rb 4
    end struct

    struct XCB_DEPTH_ITERATOR_T
        .rax:
        .data       dq ?
        .rdx:
        .rem        dd ?
        .index      dd ?
    end struct

    struct XCB_DESTROY_NOTIFY_EVENT_T
        .response_type          db ?
                                db ?
        .sequence               dw ?
        .event                  dd ?
        .window                 dd ?
    end struct

    struct XCB_ENTER_NOTIFY_EVENT_T
        .response_type          db ?
        .detail                 db ?
        .sequence               dw ?
        .time                   dd ?
        .root                   dd ?
        .event                  dd ?
        .child                  dd ?
        .root_x                 dw ?
        .root_y                 dw ?
        .event_x                dw ?
        .event_y                dw ?
        .state                  dw ?
        .mode                   db ?
        .same_screen_focus      db ?
    end struct

    struct XCB_EXPOSE_EVENT_T
        .response_type          db ?
                                db ?
        .sequence               dw ?
        .window                 dd ?
        .x                      dw ?
        .y                      dw ?
        .width                  dw ?
        .height                 dw ?
        .count                  dw ?
                                rb 2
    end struct

    struct XCB_GENERIC_ERROR_T
        .response_type  db ?
        .error_code     db ?
        .sequence       dw ?
        .resource_id    dd ?
        .minor_code     dw ?
        .major_code     db ?
                        db ?
                        rd 5
        .full_sequence  dd ?
    end struct

    struct XCB_GENERIC_EVENT_T
        .response_type          db ?
                                db ?
        .sequence               dw ?
                                rd 7
        .full_sequence          dd ?
    end struct

    struct XCB_GET_GEOMETRY_REPLY_T
        .response_type          db ?
        .depth                  db ?
        .sequence               dw ?
        .length                 dd ?
        .root                   dd ?
        .x                      dw ?
        .y                      dw ?
        .width                  dw ?
        .height                 dw ?
        .border_width           dw ?
    end struct

    struct XCB_INTERN_ATOM_REPLY_T
        .response_type          db ?
                                db ?
        .sequence               dw ?
        .length                 dd ?
        .atom                   dd ?
    end struct

    struct XCB_MOTION_NOTIFY_EVENT_T
        .response_type          db ?
        .detail                 db ?
        .sequence               dw ?
        .time                   dd ?
        .root                   dd ?
        .event                  dd ?
        .child                  dd ?
        .root_x                 dw ?
        .root_y                 dw ?
        .event_x                dw ?
        .event_y                dw ?
        .state                  dw ?
        .same_screen            db ?
                                db ?
    end struct

    struct XCB_POINT_T X:?, Y:?
        .x      dw X
        .y      dw Y
    end struct

    struct XCB_QUERY_EXTENSION_REPLY_T
        .response_type      db ?
                            db ?
        .sequence           dw ?
        .length             dd ?
        .present            db ?
        .major_opcode       db ?
        .first_event        db ?
        .first_error        db ?
    end struct

    struct XCB_RECTANGLE_T X:?, Y:?, W:?, H:?
        .x      dw X
        .y      dw Y
        .width  dw W
        .height dw H
    end struct

    struct XCB_SCREEN_T
        .root                   dd ?
        .default_colormap       dd ?
        .white_pixel            dd ?
        .black_pixel            dd ?
        .current_input_masks    dd ?
        .width_in_pixels        dw ?
        .height_in_pixels       dw ?
        .width_in_millimeters   dw ?
        .height_in_millimeters  dw ?
        .min_installed_maps     dw ?
        .mex_installed_maps     dw ?
        .root_visual            dd ?
        .backing_stores         db ?
        .save_unders            db ?
        .root_depth             db ?
        .allowed_depths_len     db ?
    end struct

    struct XCB_SCREEN_ITERATOR_T
        .rax:
        .data                   dq ?
        .rdx:
        .rem                    dd ?
        .index                  dd ?
    end struct&

    struct XCB_SEGMENT_T X1:?, Y1:?, X2:?, Y2:?
        .x1     dw X1
        .y1     dw Y1
        .x2     dw X2
        .y2     dw Y2
    end struct

    struct XCB_SETUP_T
        .status                         db ?
                                        db ?
        .protocol_major_version         dw ?
        .protocol_minor_version         dw ?
        .length                         dw ?
        .release_number                 dd ?
        .resource_id_base               dd ?
        .resource_id_mask               dd ?
        .motion_buffer_size             dd ?
        .vendor_len                     dw ?
        .maximum_request_length         dw ?
        .roots_len                      db ?
        .pixmap_formats_len             db ?
        .image_byte_order               db ?
        .bitmap_format_bit_order        db ?
        .bitmap_format_scanline_unit    db ?
        .bitmap_format_scanline_pad     db ?
        .min_keycode                    db ?
        .max_keycode                    db ?
                                        rb 4
    end struct

    struct XCB_VISUALTYPE_ITERATOR_T
        .rax:
        .data       dq ?
        .rdx:
        .rem        dd ?
        .index      dd ?
    end struct

    struct XCB_VISUALTYPE_T
        .visual_id          dd ?
        .class              db ?
        .bits_per_rgb_value db ?
        .colormap_entries   dw ?
        .red_mask           dd ?
        .green_mask         dd ?
        .blue_mask          dd ?
                            rb 4
    end struct

    ; NOTE: not standard names: created to ease major errors understanding
    X11_ERROR_BAD_REQUEST           = 1
    X11_ERROR_BAD_VALUE             = 2
    X11_ERROR_BAD_WINDOW            = 3
    X11_ERROR_BAD_PIXMAP            = 4
    X11_ERROR_BAD_ATOM              = 5
    X11_ERROR_BAD_CURSOR            = 6
    X11_ERROR_BAD_FONT              = 7
    X11_ERROR_BAD_MATCH             = 8
    X11_ERROR_BAD_DRAWABLE          = 9
    X11_ERROR_BAD_ACCESS            = 10
    X11_ERROR_BAD_ALLOC             = 11
    X11_ERROR_BAD_COLOR             = 12
    X11_ERROR_BAD_GC                = 13
    X11_ERROR_BAD_ID_CHOICE         = 14
    X11_ERROR_BAD_NAME              = 15
    X11_ERROR_BAD_LENGTH            = 16
    X11_ERROR_BAD_IMPLEMENTATION    = 17

    XCB_COLORMAP_ALLOC_NONE := 0
    XCB_COLORMAP_ALLOC_ALL  := 1


    XCB_ATOM_NONE           := 0
    XCB_ATOM_ANY            := 0
    XCB_ATOM_PRIMARY        := 1
    XCB_ATOM_SECONDARY      := 2
    XCB_ATOM_ARC            := 3
    XCB_ATOM_ATOM           := 4
    XCB_ATOM_BITMAP         := 5
    XCB_ATOM_CARDINAL       := 6
    XCB_ATOM_COLORMAP       := 7
    XCB_ATOM_CURSOR         := 8
    XCB_ATOM_CUT_BUFFER0    := 9
    XCB_ATOM_CUT_BUFFER1    := 10
    XCB_ATOM_CUT_BUFFER2    := 11
    XCB_ATOM_CUT_BUFFER3    := 12
    XCB_ATOM_CUT_BUFFER4    := 13
    XCB_ATOM_CUT_BUFFER5    := 14
    XCB_ATOM_CUT_BUFFER6    := 15
    XCB_ATOM_CUT_BUFFER7    := 16
    XCB_ATOM_DRAWABLE       := 17
    XCB_ATOM_FONT           := 18
    XCB_ATOM_INTEGER        := 19
    XCB_ATOM_PIXMAP         := 20
    XCB_ATOM_POINT          := 21
    XCB_ATOM_RECTANGLE      := 22
    XCB_ATOM_RESOURCE_MANAGER   := 23
    XCB_ATOM_RGB_COLOR_MAP      := 24
    XCB_ATOM_RGB_BEST_MAP       := 25
    XCB_ATOM_RGB_BLUE_MAP       := 26
    XCB_ATOM_RGB_DEFAULT_MAP    := 27
    XCB_ATOM_RGB_GRAY_MAP       := 28
    XCB_ATOM_RGB_GREEN_MAP      := 29
    XCB_ATOM_RGB_RED_MAP        := 30
    XCB_ATOM_STRING             := 31
    XCB_ATOM_VISUALID           := 32
    XCB_ATOM_WINDOW             := 33
    XCB_ATOM_WM_COMMAND         := 34
    XCB_ATOM_WM_HINTS           := 35
    XCB_ATOM_WM_CLIENT_MACHINE  := 36
    XCB_ATOM_WM_ICON_NAME       := 37
    XCB_ATOM_WM_ICON_SIZE       := 38
    XCB_ATOM_WM_NAME            := 39
    XCB_ATOM_WM_NORMAL_HINTS    := 40
    XCB_ATOM_WM_SIZE_HINTS      := 41
    XCB_ATOM_WM_ZOOM_HINTS      := 42
    XCB_ATOM_MIN_SPACE          := 43
    XCB_ATOM_NORM_SPACE         := 44
    XCB_ATOM_MAX_SPACE          := 45
    XCB_ATOM_END_SPACE          := 46
    XCB_ATOM_SUPERSCRIPT_X      := 47
    XCB_ATOM_SUPERSCRIPT_Y      := 48
    XCB_ATOM_SUBSCRIPT_X        := 49
    XCB_ATOM_SUBSCRIPT_Y        := 50
    XCB_ATOM_UNDERLINE_POSITION := 51
    XCB_ATOM_UNDERLINE_THICKNESS    := 52
    XCB_ATOM_STRIKEOUT_ASCENT       := 53
    XCB_ATOM_STRIKEOUT_DESCENT      := 54
    XCB_ATOM_ITALIC_ANGLE          := 55
    XCB_ATOM_X_HEIGHT           := 56
    XCB_ATOM_QUAD_WIDTH         := 57
    XCB_ATOM_WEIGHT             := 58
    XCB_ATOM_POINT_SIZE         := 59
    XCB_ATOM_RESOLUTION         := 60
    XCB_ATOM_COPYRIGHT          := 61
    XCB_ATOM_NOTICE             := 62
    XCB_ATOM_FONT_NAME          := 63
    XCB_ATOM_FAMILY_NAME        := 64
    XCB_ATOM_FULL_NAME          := 65
    XCB_ATOM_CAP_HEIGHT         := 66
    XCB_ATOM_WM_CLASS           := 67
    XCB_ATOM_WM_TRANSIENT_FOR   := 68

    XCB_KEY_PRESS           := 2
    XCB_KEY_RELEASE         := 3
    XCB_BUTTON_PRESS        := 4
    XCB_BUTTON_RELEASE      := 5
    XCB_MOTION_NOTIFY       := 6
    XCB_ENTER_NOTIFY        := 7
    XCB_LEAVE_NOTIFY        := 8
    XCB_EXPOSE              := 12
    XCB_CREATE_NOTIFY       := 16
    XCB_DESTROY_NOTIFY      := 17
    XCB_UNMAP_NOTIFY        := 18
    XCB_MAP_NOTIFY          := 19
    XCB_RESIZE_REQUEST      := 25
    XCB_CLIENT_MESSAGE      := 33

    XCB_CAP_STYLE_NOT_LAST      := 0
    XCB_CAP_STYLE_BUTT          := 1
    XCB_CAP_STYLE_ROUND         := 2
    XCB_CAP_STYLE_PROJECTING    := 3

    XCB_COORD_MODE_ORIGIN   := 0
    XCB_COORD_MODE_PREVIOUS := 1

    XCB_COPY_FROM_PARENT    := 0

    XCB_CW_BACK_PIXMAP          := 1
    XCB_CW_BACK_PIXEL           := 2
    XCB_CW_BORDER_PIXMAP        := 4
    XCB_CW_BORDER_PIXEL         := 8
    ; ...
    XCB_CW_OVERRIDE_REDIRECT    := 512
    XCB_CW_EVENT_MASK           := 2048
    ; ...
    XCB_CW_COLORMAP             := 8192

    XCB_EVENT_MASK_NO_EVENT                 := 0
    XCB_EVENT_MASK_KEY_PRESS                := 1
    XCB_EVENT_MASK_KEY_RELEASE              := 2
    XCB_EVENT_MASK_BUTTON_PRESS             := 4
    XCB_EVENT_MASK_BUTTON_RELEASE           := 8
    XCB_EVENT_MASK_ENTER_WINDOW             := 16
    XCB_EVENT_MASK_LEAVE_WINDOW             := 32
    XCB_EVENT_MASK_POINTER_MOTION           := 64
    XCB_EVENT_MASK_POINTER_MOTION_HINT      := 128
    XCB_EVENT_MASK_BUTTON_1_MOTION          := 256
    XCB_EVENT_MASK_BUTTON_2_MOTION          := 512
    XCB_EVENT_MASK_BUTTON_3_MOTION          := 1024
    XCB_EVENT_MASK_BUTTON_4_MOTION          := 2048
    XCB_EVENT_MASK_BUTTON_5_MOTION          := 4096
    XCB_EVENT_MASK_BUTTON_MOTION            := 8192
    XCB_EVENT_MASK_KEYMAP_STATE             := 16384
    XCB_EVENT_MASK_EXPOSURE                 := 32768
    XCB_EVENT_MASK_VISIBILITY_CHANGE        := 65536
    XCB_EVENT_MASK_STRUCTURE_NOTIFY         := 131072
    XCB_EVENT_MASK_RESIZE_REDIRECT          := 262144
    XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY      := 524288
    XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT    := 1048576
    XCB_EVENT_MASK_FOCUS_CHANGE             := 2097152
    XCB_EVENT_MASK_PROPERTY_CHANGE          := 4194304
    XCB_EVENT_MASK_COLOR_MAP_CHANGE         := 8388608
    XCB_EVENT_MASK_OWNER_GRAB_BUTTON        := 16777216

    XCB_GC_FUNCTION                 := 1
    XCB_GC_PLANE_MASK               := 2
    XCB_GC_FOREGROUND               := 4
    XCB_GC_BACKGROUND               := 8
    XCB_GC_LINE_WIDTH               := 16
    XCB_GC_LINE_STYLE               := 32
    XCB_GC_CAP_STYLE                := 64
    XCB_GC_JOIN_STYLE               := 128
    XCB_GC_FILL_STYLE               := 256
    XCB_GC_FILL_RULE                := 512
    XCB_GC_TILE                     := 1024
    XCB_GC_STIPPLE                  := 2048
    XCB_GC_TILE_STIPPLE_ORIGIN_X    := 4096
    XCB_GC_TILE_STIPPLE_ORIGIN_Y    := 8192
    XCB_GC_FONT                     := 16384
    XCB_GC_SUBWINDOW_MODE           := 32768
    XCB_GC_GRAPHICS_EXPOSURES       := 65536
    XCB_GC_CLIP_ORIGIN_X            := 131072
    XCB_GC_CLIP_ORIGIN_Y            := 262144
    XCB_GC_CLIP_MASK                := 524288
    XCB_GC_DASH_OFFSET              := 1048576
    XCB_GC_DASH_LIST                := 2097152
    XCB_GC_ARC_MODE                 := 4194304

    XCB_IMAGE_FORMAT_XY_BITMAP  := 0
    XCB_IMAGE_FORMAT_XY_PIXMAP  := 1
    XCB_IMAGE_FORMAT_Z_PIXMAP   := 2

    XCB_JOIN_STYLE_MITER    := 0
    XCB_JOIN_STYLE_ROUND    := 1
    XCB_JOIN_STYLE_BEVEL    := 2

    XCB_POLY_SHAPE_COMPLEX      := 0
    XCB_POLY_SHAPE_NONCONVEX    := 1
    XCB_POLY_SHAPE_CONVEX       := 2

    XCB_PROP_MODE_REPLACE   := 0
    XCB_PROP_MODE_PREPEND   := 1
    XCB_PROP_MODE_APPEND    := 2

    XCB_WINDOW_CLASS_COPY_FROM_PARENT   := 0
    XCB_WINDOW_CLASS_INPUT_OUTPUT       := 1
    XCB_WINDOW_CLASS_INPUT_ONLY         := 2

    ext proto xcb_aux_sync, qword
    ext proto xcb_change_gc, qword, dword, dword, qword
    ext proto xcb_change_gc_checked, qword, dword, dword, qword
    ext proto xcb_change_property, qword, byte, dword, dword, dword, byte, dword, qword
    ext proto xcb_change_property_checked, qword, byte, dword, dword, dword, byte, dword, qword
    ext proto xcb_change_window_attributes, qword, dword, dword, qword
    ext proto xcb_change_window_attributes_checked, qword, dword, dword, qword
    ext proto xcb_clear_area, qword, byte, dword, word, word, word, word
    ext proto xcb_clear_area_checked, qword, byte, dword, word, word, word, word
    ext proto xcb_close_font, qword, dword
    ext proto xcb_close_font_checked, qword, dword
    ext proto xcb_configure_window, qword, dword, word, qword
    ext proto xcb_configure_window_checked, qword, dword, word, qword
    ext proto xcb_connect, qword, qword
    ext proto xcb_copy_area, qword, dword, dword, dword, word, word, word, word, word, word
    ext proto xcb_copy_area_checked, qword, dword, dword, dword, word, word, word, word, word, word
    ext proto xcb_create_gc, qword, dword,dword, dword, qword
    ext proto xcb_create_gc_checked, qword, dword, dword, dword, qword
    ext proto xcb_create_colormap, qword, byte, dword, dword, dword
    ext proto xcb_create_colormap_checked, qword, byte, dword, dword, dword
    ext proto xcb_create_pixmap, qword, byte, dword, dword, word, word
    ext proto xcb_create_pixmap_checked, qword, byte, dword, dword, word, word
    ext proto xcb_create_window, \
        qword, byte, dword, dword, word, word, word, word, word, word, dword, dword, qword
    ext proto xcb_create_window_checked, \
        qword, byte, dword, dword, word, word, word, word, word, word, dword, dword, qword
    ext proto xcb_depth_next, qword
    ext proto xcb_depth_visuals_iterator, qword
    ext proto xcb_destroy_window, qword, dword
    ext proto xcb_destroy_window_checked, qword, dword
    ext proto xcb_disconnect, qword
    ext proto xcb_fill_poly, qword, dword, dword, byte, byte, dword, qword
    ext proto xcb_fill_poly_checked, qword, dword, dword, byte, byte, dword, qword
    ext proto xcb_flush, qword
    ext proto xcb_free_gc, qword, dword
    ext proto xcb_free_gc_checked, qword, dword
    ext proto xcb_free_colormap, qword, dword
    ext proto xcb_free_colormap_checked, qword, dword
    ext proto xcb_free_pixmap, qword, dword
    ext proto xcb_free_pixmap_checked, qword, dword
    ext proto xcb_generate_id, qword
    ext proto xcb_get_extension_data, qword, qword
    ext proto xcb_get_geometry, qword, dword
    ext proto xcb_get_geometry_reply, qword, dword, qword
    ext proto xcb_get_setup, qword
    ext proto xcb_image_text_8, qword, byte, dword, dword, word, word, qword
    ext proto xcb_image_text_8_checked, qword, byte, dword, dword, word, word, qword
    ext proto xcb_intern_atom, qword, byte, word, qword
    ext proto xcb_intern_atom_reply, qword, qword, qword
    ext proto xcb_map_window, qword, dword
    ext proto xcb_map_window_checked, qword, dword
    ext proto xcb_open_font, qword, dword, word, qword
    ext proto xcb_open_font_checked, qword, dword, word, qword
    ext proto xcb_poll_for_event, qword
    ext proto xcb_poly_arc, qword, dword, dword, dword, qword
    ext proto xcb_poly_arc_checked, qword, dword, dword, dword, qword
    ext proto xcb_poly_fill_arc, qword, dword, dword, dword, qword
    ext proto xcb_poly_fill_arc_checked, qword, dword, dword, dword, qword
    ext proto xcb_poly_fill_rectangle, qword, dword, dword, dword, qword
    ext proto xcb_poly_fill_rectangle_checked, qword, dword, dword, dword, qword
    ext proto xcb_poly_line, qword, byte, dword, dword, dword, qword
    ext proto xcb_poly_line_checked, qword, byte, dword, dword, dword, qword
    ext proto xcb_poly_point, qword, byte, dword, dword, dword, qword
    ext proto xcb_poly_point_checked, qword, byte, dword, dword, dword, qword
    ext proto xcb_poly_rectangle, qword, dword, dword, dword, qword
    ext proto xcb_poly_rectangle_checked, qword, dword, dword, dword, qword
    ext proto xcb_poly_segment, qword, dword, dword, dword, qword
    ext proto xcb_poly_segment_checked, qword, dword, dword, dword, qword
    ext proto xcb_request_check, qword, dword
    ext proto xcb_screen_allowed_depths_iterator, qword
    ext proto xcb_screen_next, qword
    ext proto xcb_send_event, qword, byte, dword, dword, qword
    ext proto xcb_send_event_checked, qword, byte, dword, dword, qword
    ext proto xcb_setup_roots_iterator, qword
    ext proto xcb_unmap_window, qword, dword
    ext proto xcb_unmap_window_checked, qword, dword
    ext proto xcb_visualtype_next, qword
    ext proto xcb_wait_for_event, qword

end if
