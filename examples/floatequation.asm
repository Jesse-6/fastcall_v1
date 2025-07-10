; Float point equation demo: fastcall_v1 now supports float point numbers in equation!
;  Handling it as a float pointer number/class result at compile time.

format ELF64 executable 3
entry Start
use AMD64, CET_IBT

include 'anon_label.inc'
include 'fastcall_v1.inc'
include 'stdio.inc'

_code   align 4
        Start:              endbr64
                            printf(<"Float equation result: %.2lf",10, \
                                "Integer equation result: %d",10, \
                                "Chars qword value: 0x%lX",10,0>, \
                                (5 - 3.14 + (0.33 * 2)), \          ; Float point equation
                                (5 + 2 * (5 + 164) / 2 - 1098), \   ; Integer equation
                                ('Jessé!!'));                       ; Chars as a number
                            exit(0);
