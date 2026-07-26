; The sane, smallest possible 'Hello World' working executable (I can imagine)
; that contains a 'int main(void)' C function, and also returns 0 as its main() result,
; copycat of 'first C programming lesson, example 1' model.
; To rival any native C code in this planet... ;)

format ELF64 executable 3 at 100000h

include 'fastcall3.inc'
include 'stdio.inc'

_code   Start entry:        libc.StartMain(Main);       ; Just like C programs always does



        Main:               push        0               ; main() function

                            printf("Hello World!"\n);

                            pop         rax             ; returns previously pushed 0 value
                            ret

; To compile:
;
; > fasm2 hello_world.asm
;
; And then, run it:
;
; > ./hello_world
;
; At the time of this commit, it results in a 810-byte size executable!
