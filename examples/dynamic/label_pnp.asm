format ELF64

include 'fastcall3.inc'     ; The almighty header behind this stuff
include 'stdio.inc'         ; Reusable header related to libc.so.6

CONSTANT1 := 585585h        ; Numeric literal data labels
CONSTANT2 = 100001h         ;

_rdata
        DATA            dd 800008h                              ; By value [data] label
        POINTER:        db 'this is a pointer-type label', 0    ; By reference pointer label

_code   Start entry:    libc.StartMain(Main);       ; This is a macro at 'stdio.inc' header

        Main:           push        0

                @1      fprintf(stdout, "Values of 'CONSTANT's are: 0x%X 0x%X."\n, CONSTANT1, CONSTANT2);
                @2      fprintf(stdout, "Data at 'DATA' variable is: 0x%X."\n, DATA);
                @3      fprintf(stdout, "String at pointer 'POINTER' label is: '%s'."\n, POINTER);

                        pop         rax
                        ret

        ; For reference, about the last parameters of each line:
        ;
        ; Data at '@1' label resolves to: mov reg, CONSTANTx
        ; Data at '@2' label resolves to: mov reg, [DATA]
        ; Data at '@3' label resolves to: lea reg, [POINTER]
        ;
