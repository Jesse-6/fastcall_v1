format ELF64 executable 3 at 5000000000h

include 'fastcall_v1.inc'
include 'stdmacros.inc'
include 'libnotify.inc'
include 'gtk3.inc'
include 'stdio.inc'

_rdata  N.Message               db 'Please choose what to do wih the GTK Window...', 0
        N.Title                 db 'Hello from libnotify example 2!', 0
        AppName                 db 'net.fasm2.libnotify2', 0

_code   Start entry:            endbr64
                                libc.StartMain(&Main);

        Main:                   endbr64
                                enter       32, 0

                                gtk_init(NULL, NULL);

                                gtk_application_new(&AppName, G_APPLICATION_DEFAULT_FLAGS);
                                mov         r12, rax

                                notify_init(&AppName);
                                test        al, al
                                jz          .err

                                gtk_window_new(GTK_WINDOW_TOPLEVEL);
                                mov         r14, rax
                                g_signal_connect(rax, "destroy", &proto.gtk_main_quit, NULL);
                                gtk_window_set_resizable(r14, FALSE);
                                gtk_window_set_default_size(r14, 340, 140);
                                gtk_window_set_title(r14, "libnotify demo 2");

                                notify_notification_new \
                                    (&N.Title, &N.Message, "application-x-executable");
                                mov         rbx, rax
                                notify_notification_add_action \
                                    (rax, "action1", "Close window", &WinClose, r14, NULL);
                                notify_notification_add_action \
                                    (rbx, "action2", "Show message", &PutMessage, r14, NULL);
                                notify_notification_set_timeout(rbx, 30000);

                                gtk_widget_show(r14);

                                notify_notification_show(rbx, NULL);

                                gtk_main();

            .end:               nop
                                nop

                                g_object_unref(r12);

                                notify_uninit();

                                xor         eax, eax
                                leave
                                ret

            .err:               fputs(<"Could not initialize libnotify",10,0>, **stderr);

                                g_object_unref(r12);

                                mov         eax, 1
                                leave
                                ret



        ; Action callback: rdi = *Notification, rsi = * (str) action, rdx = user_data
        PutMessage:             endbr64
                                push        rbp
                                mov         rbp, rdx

                                gtk_window_set_title(rdx, "Smart decision!");
                                gtk_label_new \
                                    ("Thank you for allowing me to show you this message!");
                                xchg        rax, rbp
                                gtk_container_add(rax, rbp);
                                gtk_widget_show(rbp);

                                pop         rbp
                                ret



        WinClose:               endbr64
                                sub         rsp, 8

                                gtk_window_close(rdx);
                                fputs(<"Okay, I'm leaving now...",10,0>, **stdout);

                                add         rsp, 8
                                ret
