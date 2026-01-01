; Demo program to test the latest mixed size effective address parameter fix, as of 2026-01-01.
; Also showcases how to multiply using lea instruction only, both inside and outside macro.

format ELF64 executable 3

use AMD64, CET_IBT

include 'fastcall_v1.inc'

include 'stdio.inc'

_code entry $
                                endbr64
                                cmp         [rsp], dword 2
                                jne         help
                                strtoul(*rsp+16, NULL, 10);
                                test        eax, eax
                                jz          err1
                                mov         ebx, eax
                                mov         eax, 4294967295
                                cqo
                                mov         r8d, 30
                                div         r8
                                cmp         ebx, eax
                                ja          err2
                                puts("Multiply demo using only lea instruction");
                                printf(<"Value at start: %u",10,10,0>, ebx);
                                printf(&fmt, ebx, 1, &rbx);             ; *
                                printf(&fmt, ebx, 2, &ebx*2);
                                printf(&fmt, ebx, 3, dq &ebx*2+ebx);    ; size override (-> rcx) **
                                printf(&fmt, ebx, 4, &ebx*4);
                                printf(&fmt, ebx, 5, &ebx*4+ebx);
                                lea         ebp, [ebx*2+ebx]
                                printf(&fmt, ebx, 6, &ebp*2);
                                printf(&fmt, ebx, 7, &ebx*4+ebp);
                                printf(&fmt, ebx, 8, &ebx*8);
                                printf(&fmt, ebx, 9, &ebx*8+ebx);
                                lea         r15d, [ebx+ebx]
                                printf(&fmt, ebx, 10, &ebx*8+r15d);
                                printf(&fmt, ebx, 11, &ebx*8+ebp);
                                printf(&fmt, ebx, 12, &ebp*4); 
                                printf(&fmt, ebx, 13, &ebp*4+ebx);
                                printf(&fmt, ebx, 14, &ebp*4+r15d);
                                printf(&fmt, ebx, 15, &ebp*4+ebp);
                                printf(&fmt, ebx, 16, &r15d*8);
                                printf(&fmt, ebx, 17, &r15d*8+ebx);
                                printf(&fmt, ebx, 18, &r15d*8+r15d);
                                printf(&fmt, ebx, 19, &r15d*8+ebp);
                                lea         r13d, [ebx*8+r15d]
                                lea         r14d, [ebx*8]
                                printf(&fmt, ebx, 20, &r13*2);          ; *
                                printf(&fmt, ebx, 21, &r13*2+rbx);      ; *
                                printf(&fmt, ebx, 22, &r13*2+r15);      ; *
                                printf(&fmt, ebx, 23, &r13*2+rbp);      ; *
                                printf(&fmt, ebx, 24, &r14*2+r14);      ; *
                                lea         r12, [r15d+ebp]             ; *
                                printf(&fmt, ebx, 25, &r13*2+r12);      ; *
                                printf(&fmt, ebx, 26, &r14d*2+r13d);
                                lea         r14d, [r14d+ebx]
                                printf(&fmt, ebx, 27, &r14d*3);
                                lea         r14d, [r14d*3]
                                printf(&fmt, ebx, 28, &r14d+ebx);
                                printf(&fmt, ebx, 29, &r14+r15);        ; *
                                printf(&fmt, ebx, 30, dq &r13d*3);      ; **
                                puts(<10,"Done.",0>);
                                exit(0);
        err2:                   puts("Number too big");
                                exit(3);
        err1:                   puts("Invalid number");
                                exit(1);
        help:                   puts("Type: 'lea_multiply NNN', where NNN is any 32 bit number");
                                exit(2);
                                
        fmt:                    db ' %u ✕ %u = %u',10,0
        
; * -> let 64-bit effective addressing on purpose, to test 64-bit and 32-bit complex effective addressing
