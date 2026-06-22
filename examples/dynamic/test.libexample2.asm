; Main-less example: only _init() is called on example library
; Also (directly) libc-less binary ;)
format ELF64

include 'fastcall.inc'
include 'stdmacros.inc'

; libexample functions
ext proto callback_at_exit, qword
ext proto console_write, qword
ext noreturn proto exit_group, dword    ; jmp prototype

_code   Start entry:        callback_at_exit(&ExitCB);
                            console_write("Library function called from example application!"\n);
                            exit_group(0);



        ExitCB:             sub         rsp, 8

                            console_write("Application's cleanup routine executed successfully."\n);

                            add         rsp, 8
                            ret

; How to compile:
;
; > fasm2 test.libexample2.asm
; > ld.lld -L. --rpath=. -e Start -lexample -pie --dynamic-linker=/lib64/ld-linux-x86-64.so.2 -o test.libexample2 test.libexample2.o
; > rm test.libexample2.o
; > strip -R .comment test.libexample2
;
;
; Run it after:
;
; > ./test.libexample2
;