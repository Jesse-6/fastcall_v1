format ELF64

include 'fastcall.inc'
include 'stdmacros.inc'
include 'stdio.inc'

; libneptune exported functions
ext proto GetLastError, none
ext proto Neptune.Init, none
ext proto PutString, qword, dword
ext noreturn proto Return, dword
ext proto Sleep, dword

_data   align 1 ; libneptune appends a LF char at the end of string,
                ; so we need a R/W segment for anonymous strings output

_code   Start entry:        dprintf(STDERR_FILENO, "Starting Neptune library from custom path...");

                            ; All functions below are called from the example library
                            ; at 'lib/' directory
                            Neptune.Init();
                            GetLastError();
                            Sleep(1560);
                            GetLastError();
                            mov         ebx, eax
                            PutString(\n "Message from Neptune library!", STDOUT_FILENO);
                            Sleep(2600);
                            Return(ebx);

; To build project:
;
; > fasm2 locallib.asm
; > ld.lld -L /usr/lib -L lib --rpath=lib -s -pie -lc -lneptune --dynamic-linker=/lib64/ld-linux-x86-64.so.2 -o locallib locallib.o
; > strip -R .comment locallib
;
; And then, run it:
;
; > ./locallib
;