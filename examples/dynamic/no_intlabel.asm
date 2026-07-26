format ELF64

use AMD64

include 'fastcall3.inc'
include 'stdio.inc'


; Demonstration on 'alias' features:
proto called, qword                     ; a normal internal prototype
alias @called, called                   ; making @called() calls called
; proto called2, qword, alias called2     ; ² This is now obsolete and neet not to be used
proto errorout, qword, alias error      ; inline alias error() to resolve to errorout
                                        ;   errorout() doesn't exist in this case
proto finish, dword ; normal unaliased internal prototype, which resolves to finish internal function

_data       quitMsg:            db "Quitting...", 0
            ; All anonymous data wiLL be placed here!

_code align 8
        Start entry:            @called("My message to you.");
                                ; called2("'fasmg' language ?way."); ¹
                                error("This isn't an error!");
                                finish(0);

        called:                 sub         rsp, 8
                                puts(rdi);
                                add         rsp, 8
                                ret

        ; ?called2:               jmp         called      ; ¹ DEPRECATED: see above

        errorout:               push        rbp
                                push        rdi
                                xor         al, al
                                mov         ecx, -1
                                repne       scasb
                                mov         [rdi-1], word 10
                                pop         rdi
                                fputs(rdi, stderr);
                                pop         rbp
                                ret

        ; _finish:                push        rdi       ; '_' prior to function label isn't needed
        finish:                 push        rdi         ; anymore: this problem is now solved
                                puts(quitMsg);
                                exit([rsp+8]);

; To compile: > ./build no_intlabel
