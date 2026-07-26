format ELF64

use AMD64, CET_IBT

include 'fastcall.inc'
include 'stdmacros.inc'
include 'stdio.inc'


; Demonstration on 'alias' features:
proto called, qword                     ; a normal internal prototype
alias @called, called                   ; making @called() calls called
proto called2, qword, alias called2     ; This resolves to ?called2 label
proto errorout, qword, alias error      ; inline alias error() to resolve to errorout
                                        ;   errorout() doesn't exist in this case
proto finish, dword ; normal unaliased internal prototype, which resolves to _finish



_data   quitMsg             db "Quitting...", 0
            ; All anonymous data with be placed here!



_code align 8
        Start entry:            endbr64
                                @called("My message to you.");
                                called2("'fasmg' language ?way.");
                                error("This isn't an error!");
                                finish(0);

        called:                 endbr64
                                sub         rsp, 8
                                puts(rdi);
                                add         rsp, 8
                                ret

        ?called2:               endbr64
                                jmp         called

        errorout:               endbr64
                                push        rbp
                                push        rdi
                                xor         al, al
                                mov         ecx, -1
                                repne       scasb
                                mov         [rdi-1], word 10
                                pop         rdi
                                fputs(rdi, *stderr);
                                pop         rbp
                                ret

        _finish:                endbr64
                                push        rdi
                                puts(&quitMsg);
                                exit(*rsp+8);
