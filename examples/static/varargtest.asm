format ELF64 executable 3
entry Start

use AMD64

include 'fastcall3.inc'

library 'libc.so.6'

ext proto printf, qword, vararg
ext proto puts, qword
ext noreturn proto exit, dword
ext proto snprintf, qword, dword, qword, vararg

_data   bigfloat                dt 7777.7774

_bss    tempbuff:               rb 256

_code   Start:                  puts("Starting vararg type tests...");
                                printf("First call with 1 fixed parameter."\n);
                                printf("This one has %u %u %u %u %u %u %u %u %u %s."\n, 2, 3, 4, 5, \
                                    6, 7, 8, 9, 10, "parameters");
                                printf("Parameter double: %.4lf"\n, 1010.0101);
                                printf("Parameter long double: %.4Lf %u %u %u %u %u %u %.4Lf"\n,\
                                    dt 3010.0103, 1, 2, 3, 4, 5, 6, bigfloat);
                                snprintf(tempbuff, 256, "Buffer contents: %u %ld.", 1234567890, \
                                    -513'463'456'245'733);
                                lea     r10, [tempbuff]
                                mov     [r10+rax], word 0Ah
                                puts(tempbuff);
                                puts("... finished.");
                                exit(0);

