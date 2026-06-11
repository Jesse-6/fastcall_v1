; Local library example library

format ELF64



include 'stdmacros.inc'
include 'fastcall.inc'
include 'stdio.inc'



public _init    ; Legacy ELF standard function called on library load (always called*)
public _fini    ; Same as above, but unload, only called when application uses __libc_start_main beforehand

public callback_at_exit
public console_write
public exit_group



_data   callbackptr         dq 0



_code   callback_at_exit:   endbr64
                            push        rbp

                            test        [gs:0], qword -1
                            jnz         .err
                            mov         rbp, rdi

                            atexit(rdi);

                            mov         [gs:0], rbp
                            xor         eax, eax
                            pop         rbp
                            ret

            .err:           mov         eax, -1
                            pop         rbp
                            ret


        console_write:      endbr64
                            sub         rsp, 8

                            fputs(rdi, **GOT.stdout);

                            lea         rsp, [rsp+8]
                            ret



        exit_group:         endbr64

                            test        [gs:0], qword -1
                            jz          @f
                            push        rdi
                            call        qword [gs:0]
                            pop         rdi

                    @@      xor         edx, edx
                            wrgsbase    rdx

                            mov         eax, 231    ; EXIT_GROUP
                            syscall



        _init:              endbr64
                            sub         rsp, 8

                            lea         rax, [callbackptr]
                            wrgsbase    rax

                            fputs("Library has been initialized on loading."\n, **GOT.stdout);

                            lea         rsp, [rsp+8]
                            ret



        _fini:              endbr64
                            sub         rsp, 8

                            fputs("Library has been finished on exit."\n, **GOT.stdout);

                            lea         rsp, [rsp+8]
                            ret



; Compiling:
;
; > fasm2 libexample.asm
; > ld -shared -lc -o libexample.so libexample.o
; > rm libexample.o
; > strip --strip-unneeded libexample.so
;
; Now use '-L. -rpath=. -lexample' on 'ld' linker command line to locally link this library into your applications.