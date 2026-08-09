; XCB complete window example: It has a title, an icon, and also
; handles the close button with an event (XWayland friendly)

; Showcasing that now, as of version 3.0.4+, sections/segments can
; be in any order.

format ELF64

include 'fastcall3.inc'
include 'xcb.inc'
include 'stdio.inc'

define_offset s XCB_SCREEN_T
define_offset ar XCB_INTERN_ATOM_REPLY_T
define_offset cm XCB_CLIENT_MESSAGE_EVENT_T
define_offset ge XCB_GENERIC_EVENT_T

_code   Start entry:    libc.StartMain(Main);

        Main:           push        0
                        push        rbp
                        push        rbx
                        push        r15
                        push        r14
                        push        r12
                        push        r13

                        xcb_connect(NULL, NULL);
                        mov         r14, rax

                        xcb_get_setup(rax);
                        xcb_setup_roots_iterator(rax);
                        mov         r15, rax

                        xcb_generate_id(r14);
                        mov         ebx, eax

                        xcb_intern_atom(r14, FALSE, icon_atom.size, icon_atom);
                        mov         ebp, eax
                        xcb_intern_atom(r14, FALSE, proto_atom.size, proto_atom);
                        mov         r12d, eax
                        xcb_intern_atom(r14, FALSE, quit_atom.size, quit_atom);
                        mov         r13d, eax

                        xcb_create_window(r14, XCB_COPY_FROM_PARENT, ebx, [r15+s.root], \
                                          0, 0, 360, 240, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, \
                                          [r15+s.root_visual], XCB_CW_BACK_PIXEL or \
                                          XCB_CW_OVERRIDE_REDIRECT, window);

                        xcb_intern_atom_reply(r14, ebp, NULL);
                        mov         rbp, rax
                        xcb_intern_atom_reply(r14, r12d, NULL);
                        mov         r12, rax
                        xcb_intern_atom_reply(r14, r13d, NULL);
                        mov         r13, rax

                        xcb_change_property(r14, XCB_PROP_MODE_REPLACE, ebx, XCB_ATOM_WM_NAME, \
                                            XCB_ATOM_STRING, 8, title.size, title);
                        xcb_change_property(r14, XCB_PROP_MODE_REPLACE, ebx, [rbp+ar.atom], \
                                            XCB_ATOM_CARDINAL, 32, icon_data.n, icon_data);
                        xcb_change_property(r14, XCB_PROP_MODE_REPLACE, ebx, [r12+ar.atom], \
                                            XCB_ATOM_ATOM, 32, 1, r13+ar.atom);
                        free(rbp);
                        mov         rbp, r13
                        mov         r13d, [r13+ar.atom]
                        free(r12);
                        free(rbp);

                        xcb_map_window(r14, ebx);
                        xcb_flush(r14);

                @@      xcb_wait_for_event(r14);
                        test        rax, rax
                        jz          @f
                        mov         rbp, rax
                        mov         dl, [rax+ge.response_type]
                        and         dl, 7Fh
                        cmp         dl, XCB_CLIENT_MESSAGE
                        jne         @f
                        mov         [rax+cm.data32+0*4], r13d
                        je          @f2

                @@      free(rbp);
                        jmp         @b2

                @@      free(rbp);
                @@      xcb_destroy_window(r14, ebx);
                        xcb_disconnect(r14);

                        pop         r13
                        pop         r12
                        pop         r14
                        pop         r15
                        pop         rbx
                        pop         rbp
                        pop         rax
                        ret

_rdata  icon_data:      dd 16, 16
            dd 090_FFFFFFh, 0CF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh
            dd 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0CF_0037FFh, 090_0037FFh
            dd 0CF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh
            dd 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0CF_0037FFh
            dd 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh
            dd 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh
            dd 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh
            dd 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh
            dd 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh
            dd 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh
            dd 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh
            dd 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh
            dd 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_000000h, 0FF_000000h
            dd 0FF_E8A000h, 0FF_E8A000h, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh
            dd 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_000000h, 0FF_000000h
            dd 0FF_E8A000h, 0FF_E8A000h, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh, 0FF_0037FFh

            dd 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_0037FFh, 0FF_0037FFh
            dd 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h
            dd 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_0037FFh, 0FF_0037FFh
            dd 0FF_FFFFFFh, 0FF_FFFFFFh, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h
            dd 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h
            dd 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h
            dd 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h
            dd 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h
            dd 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h
            dd 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h
            dd 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h
            dd 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h
            dd 0CF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h
            dd 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0CF_000000h
            dd 090_E8A000h, 0CF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h, 0FF_E8A000h
            dd 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0FF_000000h, 0CF_000000h, 090_000000h
            .n          = ($ - icon_data) / 4


        icon_atom:      db '_NET_WM_ICON'
            .size       = $ - icon_atom
        proto_atom:     db 'WM_PROTOCOLS'
            .size       = $ - proto_atom
        quit_atom:      db 'WM_DELETE_WINDOW'
            .size       = $ - quit_atom

        title:          db 'A window with an icon!'
            .size       = $ - title

        align 4
        window:
            .bgcolor    dd 0
            .ovdred     dd 0

; Build this example: ./build win_icon -lxcb
