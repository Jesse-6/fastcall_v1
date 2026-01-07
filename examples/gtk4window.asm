format ELF64 executable 3 at 100000h
entry Start

include 'fastcall_v1.inc'
include 'anon_label.inc'
include 'stdio.inc'
include 'gtk4.inc'

_code
        Start:                      endbr64
                                    libc.StartMain(&main);     ; This is a macro
                                    ud2
        align 4
        hActivate:                  endbr64
                                    enter           32, 0
                                    push            r14
                                    push            r13
                                    mov             [rsp+16], rdi   ; *app
                                    mov             [rsp+24], rsi   ; user_data (NULL)
                                    gtk_application_window_new(rdi);
                                    mov             r13, rax
                                    gtk_window_set_title(rax, "Fasm2 GTK4 Window!");
                                    gtk_window_get_icon_name(r13);
                                    test            rax, rax
                                    jz              @f
                                    g_print(<"Changing current window icon: '%s'...",10,0>, rax);
                                    gtk_window_set_icon_name(r13, "face-cool");
                                    gtk_window_get_icon_name(r13);
                                    g_print(<"... for '%s'.",10,0>, rax);
                                    jmp             @f2
                            @@      g_print("Could not obtain window icon, ");
                                    gtk_window_set_icon_name(r13, "face-angel");
                                    gtk_window_get_icon_name(r13);
                                    g_print(<"but now it is: '%s'",10,0>, rax);
                            @@      gtk_window_set_default_size(r13, 480, 320);
                                    gtk_window_present(r13);
                                    pop             r13
                                    pop             r14
                                    g_log(NULL, G_LOG_LEVEL_MESSAGE, "Activate event is done.");
                                    leave
                                    ret
                                    
        align 4
        main:                       endbr64
                                    enter           32, 0
                                    mov             [rsp], edi   ; argc
                                    mov             [rsp+8], rsi   ; argv[]
                                    mov             [rsp+16], rdx   ; env[]
                                    push            rbx
                                    push            r15
                                    gtk_application_new("org.gtk.fasmg.gtkwindow", G_APPLICATION_DEFAULT_FLAGS);
                                    mov             r15, rax
                                    g_signal_connect(rax, "activate", &hActivate, NULL);
                                    g_application_run(r15, [rsp+16], [rsp+24]);
                                    mov             rbx, rax
                                    g_object_unref(r15);
                                    mov             rax, rbx
                                    pop             r15
                                    pop             rbx
                                    leave
                                    ret
