format ELF64 executable 3 at 100000h

include 'fastcall3.inc'

library 'libc.so.6'

ext indirect proto printf, qword, vararg
ext indirect proto sleep, qword
ext indirect noreturn proto exit, dword
noreturn indirect proto to_intexit, dword
noreturn proto intexit, dword

_bss    e_offset                dq ?

_code   to_intexit              dq intexit
        intexit:                nop
                                nop
                                nop
                                nop
                                exit(edi);

        Start entry:            endbr64
                                finit
                                xor     eax, eax
                                mfence                          ; Measure empty benchmark frame impact
                                rdtsc
                                shl     rdx, 32
                                or      rax, rdx
                                push    rax
                                mfence
                                rdtsc
                                shl     rdx, 32
                                or      rax, rdx
                                push    rax
                                fild    qword [rsp]
                                fild    qword [rsp+8]
                                fsubp   st1, st0
                                fistp   qword [rsp]
                                pop     qword [e_offset]        ; empty number of cycles*, save it elsewhere

                                mfence    ; Do benchmark
                                rdtsc
                                shl     rdx, 32
                                or      rax, rdx
                                push    rax
                                ; test code goes here
                                ;sleep(1);
                                enter   32, 0
                                leave
                                mfence
                                rdtsc
                                shl     rdx, 32
                                or      rax, rdx
                                push    rax
                                fild    qword [rsp]
                                fild    qword [rsp+8]
                                fsubp   st1, st0
                                fistp   qword [rsp]
                                pop     rcx
                                sub     rcx, [e_offset]         ; Number of cycles
                                add     rsp, 16                 ; release allocated stack

                                printf("Done in %li cycles. Frame offset: %lu cycles."\n, rcx, e_offset);
                                to_intexit(0);
                                ; intexit(0);

