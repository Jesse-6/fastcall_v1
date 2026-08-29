if ~ defined __XCB_SYNC_INC_INCLUDED__
    define __XCB_SYNC_INC_INCLUDED__
    define __XCB_SYNC_INC_INCLUDED__

    if ~ defined __ELF_MODE_DYNAMIC__
        library 'libxcb-sync.so.1'
    end if

    struct XCB_SYNC_INITIALIZE_REPLY_T
        .response_type  db ?
                        db ?
        .sequence       dw ?
        .length         dd ?
        .major_version  db ?
        .minor_version  db ?
                        rb 22
    end struct

    struct XCB_SYNC_INT64_T
        .hi             dd ?
        .lo             dd ?
    end struct

    struct XCB_SYNC_QUERY_COUNTER_REPLY_T
        .response_type  db ?
                        db ?
        .sequence       dw ?
        .length         dd ?
        .counter_value  XCB_SYNC_INT64_T
    end struct

    ext data xcb_sync_id

    ext proto xcb_sync_create_counter, qword, dword, qword
    ext proto xcb_sync_create_counter_checked, qword, dword, qword
    ext proto xcb_sync_destroy_counter, qword, dword
    ext proto xcb_sync_destroy_counter_checked, qword, dword
    ext proto xcb_sync_initialize, qword, byte, byte
    ext proto xcb_sync_initialize_reply, qword, dword, qword
    ext proto xcb_sync_query_counter, qword, dword
    ext proto xcb_sync_query_counter_reply, qword, dword, qword
    ext proto xcb_sync_set_counter, qword, dword, qword
    ext proto xcb_sync_set_counter_checked, qword, dword, qword

end if
