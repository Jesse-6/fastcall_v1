; XCB Window headerless example: a full example on how to use this macro toolkit in detail
; Also a good example on how to create a Window using the beautiful XCB library!
;
format ELF64            ; ELF dynamic type (PIE enabled)

include 'fastcall3.inc' ; Our powerhouse goes here...

; libc.so.6 prototypes
ext proto __libc_start_main, qword, dword, qword, qword, qword, qword, qword
ext proto fputs, qword, qword
ext proto free, qword
ext data stderr:qword

; libxcb.so.1 prototypes
ext proto xcb_change_property, qword, byte, dword, dword, dword, byte, dword, qword
ext proto xcb_connect, qword, qword
ext proto xcb_create_window, qword, byte, dword, dword, word, word, word, word, word, word, dword, dword, qword
ext proto xcb_destroy_window, qword, dword
ext proto xcb_disconnect, qword
ext proto xcb_flush, qword
ext proto xcb_generate_id, qword
ext proto xcb_get_setup, qword
ext proto xcb_intern_atom, qword, byte, word, qword
ext proto xcb_intern_atom_reply, qword, qword, qword
ext proto xcb_map_window, qword, dword
ext proto xcb_setup_roots_iterator, qword
ext proto xcb_wait_for_event, qword

; XCB structures (offset only)
struct atom     ; alias for XCB_INTERN_ATOM_REPLY_T
    .response_type          db ?
                            db ?
    .sequence               dw ?
    .length                 dd ?
    .atom                   dd ?
end struct&

struct cme      ; alias for XCB_CLIENT_MESSAGE_EVENT_T
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
end struct&

struct screen   ; alias for XCB_SCREEN_T
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
end struct&

; XCB constants
XCB_ATOM_ATOM                   = 4
XCB_ATOM_STRING                 = 31
XCB_ATOM_WM_NAME                = 39
XCB_CLIENT_MESSAGE              = 33
XCB_COPY_FROM_PARENT            = 0
XCB_CW_EVENT_BACK_PIXEL         = 1 shl 1
XCB_PROP_MODE_REPLACE           = 0
XCB_WINDOW_CLASS_INPUT_OUTPUT   = 1

_bss    connection          xq ?
        window              xd ?
            .bg_pixel       xd ?

_code   Start entry:        __libc_start_main(Main, [rsp+8], rsp+16, NULL, NULL, rdx, rsp);

        Main:               push        rbp     ; This is a real C 'int main()' entry point!
                            push        r13
                            push        r12

                            ; open connection to X
                            xcb_connect(NULL, NULL);
                            mov         [connection], rax   ; save connection

                            ; obtain screen
                            xcb_get_setup(rax);
                            xcb_setup_roots_iterator(rax);
                            mov         rbp, rax            ; rbp = *screen

                            ; non-blocking request atoms and ID
                            xcb_intern_atom(connection, FALSE, 12, <"WM_PROTOCOLS">);
                            push        rax                 ; ¹ save cookie for later
                            xcb_intern_atom(connection, FALSE, 16, <"WM_DELETE_WINDOW">);
                            push        rax                 ; ²
                            xcb_generate_id(connection);
                            mov         [window], eax       ; IDs are dword at XCB

                            mov         [window.bg_pixel], 00_09_0B_21h     ; dark blue background

                            ; Create a window, but do not show it yet
                            xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, [rbp+screen.root], \
                                0, 0, 480, 300, 2, XCB_WINDOW_CLASS_INPUT_OUTPUT, [rbp+screen.root_visual], \
                                XCB_CW_EVENT_BACK_PIXEL, &window.bg_pixel);

                            ; Receive atom replies and apply their properties to window
                            pop         r12
                            pop         r13
                            xcb_intern_atom_reply(connection, r12, NULL);
                            mov         r12, rax            ; ² WM_DELETE_WINDOW *atom
                            xcb_intern_atom_reply(connection, r13, NULL);
                            mov         r13, rax            ; ¹ WM_PROTOCOLS *atom
                            xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, [r13+atom.atom], \
                                XCB_ATOM_ATOM, 32, 1, r12+atom.atom);
                            ; Store window title
                            xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, XCB_ATOM_WM_NAME, \
                                XCB_ATOM_STRING, 8, 32, <"XCB Window example - with fasm2!">);

                            ; Display window and flush everything altered
                            xcb_map_window(connection, window);
                            xcb_flush(connection);

                            ; Events' loop
                    @@      xcb_wait_for_event(connection);
                            mov         rbp, rax                ; save for release later, *event memory
                            mov         cl, [rax]               ; .event_type in all XCB structures
                            and         cl, not 80h             ; as did in any XCB example I've seen
                            cmp         cl, XCB_CLIENT_MESSAGE  ; only message we deal in thie example
                            jne         @b
                            mov         r10d, [rax+cme.data32+0]    ; get atom to compare
                            cmp         r10d, [r12+atom.atom]       ; compare with WM_DELETE_WINDOW atom
                            jne         @b

                            ; Exit when user clicks 'x' close button
                            free(r13);
                            free(r12);
                            free(rbp);
                            xcb_destroy_window(connection, window);
                            xcb_disconnect(connection);

                            fputs("A clean exit is executed from the XCB Window."\n, stderr);

                            pop         r12
                            pop         r13
                            pop         rbp
                            xor         eax, eax    ; => return(0);
                            ret



; build this (using my provided build script) with:
;
; > ./build xcbwindow -lxcb
;