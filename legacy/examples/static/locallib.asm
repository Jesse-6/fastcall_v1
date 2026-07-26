format ELF64 executable 3 at 100_000h

include 'fastcall.inc'
include 'stdmacros.inc'
include 'stdio.inc'

libpath 'lib'           ; custom library path relative to this application's current folder
library 'libneptune.so' ; library at the above relative path

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
