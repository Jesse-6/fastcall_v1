format ELF64

include 'fastcall3.inc'
include 'stdio.inc'

PI = 3.14159265358979323846

_code   Start entry:        endbr64
                            printf(<"Testing signed numbers: %d, %ld, %d, %ld,", \
                                "  %u, %ld, %d, %ld, %u, %ld, 0x%016lX",10,0>, \
                                -578'906, dq -2'147'483'648, -2'147'483'648, dq -1, 4'294'967'295, \
                                -4'294'967'295, 0, -4'294'967'296, +2'147'483'647, +2'147'483'648, \
                                8000_0000_0000_0000h);
                            printf("Value of π on FPU:   %.19Lf."\n, π); ; TT or π is a tword only parameter!
                            printf("π as a 64-bit float: %.19lf."\n, PI);
                            mov         edx, PI
                            movd        xmm15, edx
                            cvtss2sd    xmm0, xmm15
                            printf("π as a 32-bit float: %.19lf."\n, xmm0);
                            exit(EXIT_SUCCESS);

; NOTE
; π is a constant supported natively by x87 FPU.
; When you pass either TT or π to a vararg parameter or tword size parameter,
; fastcall macro code process with fldpi instruction.
; SSE/AVX don't have this constant hardcoded, so, I choose to not directly
; support π for them. But you can create a constant with a name and pass it
; anyway, as shown in this example.
; If you have not defined TT or π, it will always be a tword parameter. So,
; for vararg, it is detected as tword type and size by default.
;

; To compile: > ./build test_numbers
