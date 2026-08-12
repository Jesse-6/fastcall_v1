if ~ defined __XCB_ICCCM_INC_INCLUDED__
    define __XCB_ICCCM_INC_INCLUDED__
    define __XCB_ICCCM_INC_INCLUDED__

    if ~ defined __ELF_MODE_DYNAMIC__
        library 'libxcb-icccm.so.4'
    end if

    XCB_ICCCM_SIZE_HINT_US_SIZE = 1 shl 1
    XCB_ICCCM_SIZE_HINT_P_POSITION = 1 shl 2
    XCB_ICCCM_SIZE_HINT_P_SIZE = 1 shl 3
    XCB_ICCCM_SIZE_HINT_P_MIN_SIZE = 1 shl 4
    XCB_ICCCM_SIZE_HINT_P_MAX_SIZE = 1 shl 5
    XCB_ICCCM_SIZE_HINT_P_RESIZE_INC = 1 shl 6
    XCB_ICCCM_SIZE_HINT_P_ASPECT = 1 shl 7
    XCB_ICCCM_SIZE_HINT_BASE_SIZE = 1 shl 8
    XCB_ICCCM_SIZE_HINT_P_WIN_GRAVITY = 1 shl 9

    struct XCB_SIZE_HINTS_T a:?, b:?, c:?, d:?, e:?, f:?, g:?, h:?, i:?, j:?, k:?, l:?, m:?, n:?, o:?, p:?, q:?, r:?
        .flags          dd a
        .x              dd b
        .y              dd c
        .width          dd d
        .height         dd e
        .min_width      dd f
        .min_height     dd g
        .max_width      dd h
        .max_height     dd i
        .width_inc      dd j
        .height_inc     dd k
        .min_aspect_num dd l
        .min_aspect_den dd m
        .max_aspect_num dd n
        .max_aspect_den dd o
        .base_width     dd p
        .base_height    dd q
        .win_gravity    dd r
    end struct

    ext proto xcb_icccm_set_wm_size_hints, qword, dword, dword, qword
    ext proto xcb_icccm_size_hints_set_min_size, qword, dword, dword
    ext proto xcb_icccm_size_hints_set_max_size, qword, dword, dword

end if