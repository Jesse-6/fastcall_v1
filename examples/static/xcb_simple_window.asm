; Simple XCB Window demo: that exits on close and has a title
; The smallest (I know so far) memory usage with a window I've seen!

format ELF64 executable 3 at 100000h

include 'fastcall3.inc'
include 'xcb.inc'
include 'stdio.inc'

define_offset s XCB_SCREEN_T

_code   Start entry:    mov         r11, [stderr]   ; Needed when using static ELFs
                        push        [r11]           ;
                        pop         [stderr]        ;

                        ; Connect to X using XCB
                        xcb_connect(NULL, NULL);
                        mov         r15, rax    ; r15 = *connection
                        test        rax, rax
                        jnz         @f
                        fputs("ERROR: can't connect to X!"\n, stderr);
                        exit(-1);

                        ; Iterate to obtain first screen
                @@      xcb_get_setup(rax);
                        xcb_setup_roots_iterator(rax);
                        mov         rbp, rax    ; rbp = *screen

                        ; Generate an ID for the window
                        xcb_generate_id(r15);
                        mov         ebx, eax    ; ebx = window

                        mov         r10d, [rbp+s.black_pixel]
                        sub         rsp, 8
                        push        r10         ; black background
                        mov         r9, rsp

                        ; Create the window
                        xcb_create_window(r15, XCB_COPY_FROM_PARENT, ebx, [rbp+s.root], \
                                          0, 0, 480, 320, 1, XCB_WINDOW_CLASS_INPUT_OUTPUT, \
                                          [rbp+s.root_visual], XCB_CW_BACK_PIXEL, r9);

                        ; Store window title
                        xcb_change_property(r15, XCB_PROP_MODE_REPLACE, ebx, XCB_ATOM_WM_NAME, \
                                            XCB_ATOM_STRING, 8, title.len, title);

                        ; Display window at obtained screen
                        xcb_map_window(r15, ebx);
                        xcb_flush(r15);             ; flush connection to actually display it

                        ; Events loop
                @@      xcb_wait_for_event(r15);
                        test        rax, rax
                        jz          @f

                        ; Free allocated memory by XCB event dispatcher
                        free(rax);
                        jmp         @b

                        ; At exit, free window and close connection with X
                @@      xcb_destroy_window(r15, ebx);
                        xcb_disconnect(r15)

                        ; No need to release stack, because we're not at main()! Just exit, then...
                        exit(0);

        title:          db 'XCB Simple Window'
        title.len = $ - title
