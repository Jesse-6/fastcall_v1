format ELF64 executable 3

include 'fastcall3.inc'

entry Start

EXIT_SUCCESS = 0

library 'libc.so.6'

TRUE = 1
FALSE = 0
NULL = 0

ext indirect proto fprintf, qword, qword, vararg
ext indirect proto fputs, qword, qword
ext indirect noreturn proto exit, dword
ext data stdout

_code   Start:              mov     rax, [stdout]
                            push    [rax]
                            pop     [stdout]
                            fputs(<"Testing BETA3...",10,0>, [stdout]);
                            fprintf([stdout], "Math with constants: %u | %u | %u | % u"\n, \
                                TRUE, FALSE/TRUE, NULL*15+8, TRUE+NULL*600+TRUE*8);
                            exit(EXIT_SUCCESS);

; This showcases the old style syntax format.
; Still being fully supported by fascall version 3.
