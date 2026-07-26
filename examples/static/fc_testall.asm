format ELF64 executable 3

use AMD64

include 'fastcall3.inc'

library 'libc.so.6'

TRUE := 1
FALSE := 0
NULL := 0

ext proto puts, qword
ext noreturn proto __libc_start_main, qword, dword, qword, qword, qword, qword, qword, alias st_main
ext proto printf, qword, vararg
ext proto getpid, none

_rdata  bytevar         db 1
        wordvar         dw 2
        dwordvar        dd 4
        qwordvar        dq 8
        floatvar        dd 0.4
        doublevar       dq 0.8
        twordvar        dt 10.10

; WARNING!
; Type float (32 bit) will not work with printf() family of functions,
; because printf() as it is under C code always converts float values
; to double before passing it officially. Example here is for evaluation
; purposes only, i.e.; testing proper macro handling of such values.

_code   Start entry:    ; WARNING! See the user guide about using rsp register as parameters! WARNING!
                        st_main(lcMain, [rsp+8], rsp+16, NULL, NULL, rdx, rsp);
                        ud2

        lcMain:         push    r15
                        push    r14
                        enter   0, 0
                        getpid();
                        printf("Starting test process with PID: %u"\n, eax);
                        nop
                        nop
                        printf("Test TRUE | FALSE: %d | %d"\n, TRUE, FALSE);
                        xor     esi, esi
                        nop
                        nop
                        printf("Test force byte 0x%02X"\n, db 127);
                        xor     esi, esi
                        nop
                        nop
                        printf("Test force word 0x%04X"\n, dw 32767);
                        nop
                        nop
                        printf("Test force dword 0x%08X"\n, dd 80000000h);
                        nop
                        nop
                        printf("Test force float %.4f"\n, df 1000.5000);
                        nop
                        nop
                        printf("Test force double %.4lf"\n, dp 1.2345);
                        nop
                        nop
                        xor     esi, esi
                        printf("Byte var: %u"\n, bytevar);
                        printf("Word var: %u"\n, wordvar);
                        printf("Dword var: %u"\n, dwordvar);
                        printf("Qword var: %u"\n, qwordvar);
                        printf("Float var: %.1f"\n, df floatvar);
                        printf("Double var: %.1lf"\n, dp doublevar);
                        printf("Tword var: %.2Lf"\n, twordvar);
                        nop
                        nop
                        mov     eax, 7
                        printf("Testing 'lea' instruction for math. Result: %u"\n, eax*2+eax+6);
                        nop
                        nop
                        puts("Tests done. Exiting...");
                        leave
                        pop     r14
                        pop     r15
                        xor     eax, eax
                        ret

; Recomendation: use a debugger, such as edb-debugger to see the resulting code, and understand
; the effects of these parameter types on the generated instructions.
