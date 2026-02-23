; libnotify.so.4.0.0 fasm2 fastcall_v1 header
;
; Library documentation is at: https://gnome.pages.gitlab.gnome.org/libnotify/index.html
;

if ~ defined __LIB_NOTIFY_INCLUDED__

    define __LIB_NOTIFY_INCLUDED__
    define __LIB_NOTIFY_INCLUDED__

    library 'libnotify.so.4.0.0'

    define NOTIFY_CLOSED_REASON_UNSET       -1
    define NOTIFY_CLOSED_REASON_EXPIRED     1
    define NOTIFY_CLOSED_REASON_DISMISSED   2
    define NOTIFY_CLOSED_REASON_API_REQUEST 3
    define NOTIFY_CLOSED_REASON_UNDEFINED   4

    define NOTIFY_EXPIRES_DEFAULT   -1
    define NOTIFY_EXPIRES_NEVER     0

    define NOTIFY_URGENCY_LOW       0
    define NOTIFY_URGENCY_NORMAL    1
    define NOTIFY_URGENCY_CRITICAL  2

    ext proto notify_get_app_icon, none
    ext proto notify_get_app_name, none
    ext proto notify_get_server_caps, none
    ext proto notify_get_server_info, qword, qword, qword, qword
    ext proto notify_init, qword
    ext proto notify_is_inited, none
    ext proto notify_notification_add_action, qword, qword, qword, qword, qword, qword
    ext proto notify_notification_clear_actions, qword
    ext proto notify_notification_clear_hints, qword
    ext proto notify_notification_close, qword, qword
    ext proto notify_notification_get_activation_app_launch_context, qword
    ext proto notify_notification_get_activation_token, qword
    ext proto notify_notification_get_closed_reason, qword
    ext proto notify_notification_new, qword, qword, qword
    ext proto notify_notification_set_app_icon, qword, qword
    ext proto notify_notification_set_app_name, qword, qword
    ext proto notify_notification_set_category, qword, qword
    ext proto notify_notification_set_hint, qword, qword, qword
    ext proto notify_notification_set_icon_from_pixbuf, qword, qword
    ext proto notify_notification_set_image_from_pixbuf, qword, qword
    ext proto notify_notification_set_timeout, qword, dword
    ext proto notify_notification_set_urgency, qword, dword
    ext proto notify_notification_show, qword, qword
    ext proto notify_notification_update, qword, qword, qword, qword
    ext proto notify_set_app_icon, qword
    ext proto notify_set_app_name, qword
    ext proto notify_uninit, none

else
    err "Duplicated inclusion of libnotify include file.", 10
end if