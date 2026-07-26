; Local library example application
; With libc main() and indirect call prototypes

format ELF64

include 'fastcall.inc'
include 'stdmacros.inc'

; libexample functions
ext proto callback_at_exit, qword
ext proto console_write, qword
ext indirect noreturn proto exit_group, dword    ; jmp prototype indirect (PLT-less)

; libc "PLT-less" functions - as indirectly declared here
ext indirect proto puts, qword
ext noreturn indirect proto __libc_start_main, qword, dword, qword, qword, qword, qword, qword



macro libc.StartMain mainproc
    match (mainptr), mainproc
        __libc_start_main(mainptr, [rsp+8], &rsp+16, NULL, NULL, rdx, rsp);
    else
        err "Invalid syntax.", 10
    end match
end macro



_code   Start entry:        libc.StartMain(&Main);


        Main:               sub         rsp, 8

                            callback_at_exit(&ExitCB);
                            console_write("Hello from example library!"\n);
                            puts("Test program is running...");

                            add         rsp, 8
                            xor         eax, eax
                            ret



        ExitCB:             lea         rsp, [rsp-8]

                            puts("Main program cleanup function executed successfully.");

                            lea         rsp, [rsp+8]
                            ret

; How to compile:
;
; > fasm2 test.libexample.asm
; > ld.lld -L /usr/lib -L. --rpath=. -s -lc -lexample -pie --dynamic-linker=/lib64/ld-linux-x86-64.so.2 -o test.libexample test.libexample.o
; > rm test.libexample.o
; > strip -R .comment test.libexample
;
;
; Run it after:
;
; > ./test.libexample
;