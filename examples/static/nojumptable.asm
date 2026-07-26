format ELF64 executable 3 at 800000h

include 'fastcall3.inc'

library 'libc.so.6'

ext noreturn indirect proto exit, dword
ext indirect proto usleep, qword
ext indirect proto fprintf, qword, qword, vararg
ext indirect proto fflush, qword
ext data stdout

_code     Start entry:        mov       rax, [stdout]
                              mov       rax, [rax]
                              mov       [stdout], rax
                              fprintf(stdout, "Sleeping now...");
                              fflush(stdout);
                              usleep(3'000'000);
                              fprintf(stdout, " done."\n);
                              exit(0);

