format ELF64 executable 3

include 'fastcall3.inc'
include 'stdio.inc'

SIZE = 16384

_code   Start entry     mov     [resvalue], 55AA55AAh

                        mov     r10, [stdout]
                        push    [r10]
                        pop     [stdout]

                @bss    attvalue    xd ?        ; inline bss data entry

                        snprintf(resbuff, SIZE - 1, "Value at .bss variable is: 0x%08X."\n \
                                 "     At .data variable is: 0x%08X."\n, resvalue, expvalue);

                        lea     rdi, [resbuff]
                        lea     rdi, [rdi+rax]
                        neg     eax
                        mov     [attvalue], 0F0F_F0F0h
                        snprintf(rdi, (SIZE-1)+eax, msg_fmt2, attvalue);
                        fputs(resbuff, stdout);

                @rdata  msg_ptr:    xb 'Variable addresses:', 10, \
                                       '     resvalue: 0x%lX', 10, \
                                       '     expvalue: 0x%lX', 10, \
                                       '     attvalue: 0x%lX', 10, 0
                        snprintf(resbuff, SIZE - 1, msg_ptr, &resvalue, &expvalue, &attvalue);
                        fputs(resbuff, stdout);

                        exit(0);

_bss    resvalue        xd ?
        resbuff:        xb *SIZE

_rdata  expvalue        xd 11001100h
        msg_fmt2:       xb "      At @bss variable is: 0x%08X.", 10, 0


; As of version 3.0.4+ of fastcall macro, section/segment statements need not to follow a strict
; order. Also, macros @bss, @data and @rdata, that creates inline data statements, are now
; upgraded to attach its line statement to whatever its respective section is located.
; Previous multi _code, _rdata, _data or _bss statements usage work the same. See example
; 'test4' on how to use this.
;
; Build this example: > ./build ordertest
;
