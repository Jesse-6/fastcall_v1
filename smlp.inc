; Header for libsmlproto.so.0 library
; Available at https://github.com/Jesse-6/libsmlproto

if ~ defined __SMLP_FILE_INCLUDED__

    define __SMLP_FILE_INCLUDED__
    define __SMLP_FILE_INCLUDED__

    if ~ defined __USE_FASTCALL_v2__
        if ~ defined __ELF_MODE_DYNAMIC__
            library 'libsmlproto.so.0'
        end if
    end if

    ext proto SMLP_Cleanup, byte
    ext proto SMLP_GetIndexedString, dword
    ext proto SMLP_GetStringCount, none
    ext proto SMLP_InitLanguage, qword, qword, qword, qword
    ext proto SMLP_ParseEscapedString, qword, qword
    ext proto SMLP_SetExtendedMode, byte

else
    err "Duplicated inclusion of 'libsmlproto' header file"
end if
