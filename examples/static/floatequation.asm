; Float point equation demo: fastcall3 supports float point numbers in equation!
; Handling it as a float pointer number/class result at compile time.

format ELF64 executable 3

entry Start         ; This is also supported to declare code entry point

use AMD64

include 'fastcall3.inc'
include 'stdio.inc'

_code   Start:              printf(<"Float equation result: %.2lf",10, \
                                "Integer equation result: %d",10, \
                                "Chars qword value: 0x%lX",10,0>, \
                                (5 - 3.14 + (0.33 * 2)), \          ; Float point equation
                                (5 + 2 * (5 + 164) / 2 - 1098), \   ; Integer equation
                                ('Jessé!!'));                       ; Chars as a number
                            exit(0);
