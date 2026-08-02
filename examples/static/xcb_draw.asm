format ELF64 executable 3 at 8C_9500h shl 16

include 'fastcall3.inc'
include 'xcb.inc'
include 'stdio.inc'

define_offset event XCB_GENERIC_EVENT_T
define_offset scr XCB_SCREEN_T

_rdata  points:
            .0          XCB_POINT_T 20, 20
            .1          XCB_POINT_T 20, 50
            .2          XCB_POINT_T 50, 20
            .3          XCB_POINT_T 50, 50

        polyline:
            .0          XCB_POINT_T 100, 20
            .1          XCB_POINT_T  20, 80  ; rest of points are relative
            .2          XCB_POINT_T 100, -70 ;
            .3          XCB_POINT_T 30, 30   ;

        segments:
            .0          XCB_SEGMENT_T 390, 20, 480, 50
            .1          XCB_SEGMENT_T 420, 65, 530, 140

        rectangles:
            .0          XCB_RECTANGLE_T 80, 130, 160, 60
            .1          XCB_RECTANGLE_T 370, 120, 30, 120

        arcs:
            .0          XCB_ARC_T 30, 240, 170, 170, 0, 120 shl 6
            .1          XCB_ARC_T 350, 235, 200, 140, 0, 285 shl 6

        triangle:
            .0          XCB_POINT_T 20, 380
            .1          XCB_POINT_T 560, 0
            .2          XCB_POINT_T -280, -360
            .3          XCB_POINT_T -280, 360

        title:          xb 'XCB Drawing Functions Example'

_data   window          xd 0
            .values:
            .bgcolor    xd 0
            .mask       xd XCB_EVENT_MASK_EXPOSURE

        gc_black        xd ?
            .values:
            .fgcolor    xd 0
            .linewidth  xd 0
            .cap        xd XCB_CAP_STYLE_PROJECTING
            .join       xd XCB_JOIN_STYLE_ROUND
            .grexp      xd 0

        gc_green        xd ?
            .values:
            .fgcolor    xd 00_BB_F2_C1h
            .linewidth  xd 7
            .join       xd XCB_CAP_STYLE_ROUND
            .grexp      xd 0

_bss    connection      xq ?

_code   Begin entry:    mov     r11, [stderr]
                        push    [r11]
                        pop     [stderr]

                        libc.StartMain(Main);

        Main:           push    rbp
                        push    rbx
                        push    r14

                        xcb_connect(NULL, NULL);
                        mov     [connection], rax

                        xcb_get_setup(rax);
                        xcb_setup_roots_iterator(rax);
                        mov     rbp, rax    ; rbp = *screen

                        xcb_generate_id(connection);
                        mov     [window], eax
                        xcb_generate_id(connection);
                        mov     [gc_black], eax
                        xcb_generate_id(connection);
                        mov     [gc_green], eax

                        lea     rdi, [gc_black.fgcolor]
                        lea     rsi, [rbp+scr.black_pixel]
                        movsd
                        lea     rdi, [window.bgcolor]
                        lea     rsi, [rbp+scr.white_pixel]
                        movsd

                        xcb_create_gc(connection, gc_black, [rbp+scr.root], XCB_GC_FOREGROUND or \
                            XCB_GC_LINE_WIDTH or XCB_GC_CAP_STYLE or XCB_GC_JOIN_STYLE or \
                            XCB_GC_GRAPHICS_EXPOSURES, gc_black.values);
                        xcb_create_gc(connection, gc_green, [rbp+scr.root], XCB_GC_FOREGROUND or \
                            XCB_GC_LINE_WIDTH or XCB_GC_JOIN_STYLE or XCB_GC_GRAPHICS_EXPOSURES, \
                            gc_green.values);

                        xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, [rbp+scr.root], \
                            0, 0, 600, 400, 10, XCB_WINDOW_CLASS_INPUT_OUTPUT, [rbp+scr.root_visual], \
                            XCB_CW_BACK_PIXEL or XCB_CW_EVENT_MASK, window.values);
                        xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, XCB_ATOM_WM_NAME, \
                            XCB_ATOM_STRING, 8, 29, title);

                        xcb_map_window(connection, window);
                        xcb_flush(connection);

                        xor     r14, r14    ; events counter

           .event_poll: fprintf(stderr, <13,"Events: %lu  ",0>, r14);

                        xcb_wait_for_event(connection);
                        test    rax, rax
                        jz      .end

                        inc     r14
                        mov     rbx, rax
                        mov     dl, [rax+event.response_type]
                        and     dl, 0111_1111b
                        cmp     dl, XCB_EXPOSE
                        jne     @f

                        ; EXPOSE event
                        xcb_poly_line(connection, XCB_COORD_MODE_PREVIOUS, window, gc_green, 4, triangle);

                        xcb_poly_point(connection, XCB_COORD_MODE_ORIGIN, window, gc_black, 4, points);
                        xcb_poly_line(connection, XCB_COORD_MODE_PREVIOUS, window, gc_black, 4, polyline);
                        xcb_poly_segment(connection, window, gc_black, 2, segments);
                        xcb_poly_rectangle(connection, window, gc_black, 2, rectangles);
                        xcb_poly_arc(connection, window, gc_black, 2, arcs);

                        xcb_flush(connection);
                        free(rbx);
                        jmp     .event_poll

                        ; unhandled events
                @@      free(rbx);
                        jmp     .event_poll

            .end:       xcb_disconnect(connection);
                        fprintf(stderr, <10,0>);

                        pop     r14
                        pop     rbx
                        pop     rbp
                        xor     eax, eax
                        ret
