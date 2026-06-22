format ELF64

include 'fastcall.inc'
include 'stdmacros.inc'

ext proto printf, qword, vararg
ext proto sleep, qword
ext noreturn proto exit, dword
noreturn proto intexit, dword

_bss
        e_offset                dq ?

_code
        _intexit:               endbr64
                                nop
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
                                enter   0, 0
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

                                printf("Done in %li cycles. Frame offset: %lu cycles."\n, rcx, *e_offset);
                                intexit(0);

