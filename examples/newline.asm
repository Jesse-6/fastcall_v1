; This is a demo on the new feature: \n
; It makes anon string parameters new line + null terminated,
; To make it as feasible as "string" parameter (which is also auto null terminated)
; Also to beautify your code :)

; So:
;
;    func("string");
;
;    Leads to:
;
;    anonXXX db "string", 0
;
; And now:
;    func("string"\n);
;
;    Leads to:
;
;    anonXXX db "string", 10, 0

format ELF64 executable 3

include 'fastcall_v1.inc'
include 'stdmacros.inc'
include 'stdio.inc'

_code   Start entry:        endbr64
                            fputs(<"This is the old fashioned way...",10,0>, **stdout);
                            fputs("And this is the NEW way!"\n, **stdout);
                            fputs("It is already auto null terminated."\n, **stdout);
                            fputs("Just like this format.", **stdout);
                            fputc(10, **stdout);
                            fputs("So, use now this elegant '\n' new style!"\n, **stdout);
                            fputs("Made during a sleepless night at: 2026-02-25"\n, **stdout);
                            fputs(<"You will still need this strict style ", \
                                "if your strings are of complex type.",10, \
                                "And, as it always have been, it keeps being ", \
                                "a literal data format, ", \
                                "create every byte you put within <> ", \
                                " as the exact anon data, without any additions.",10,0>, **stdout);
                            exit(0);

