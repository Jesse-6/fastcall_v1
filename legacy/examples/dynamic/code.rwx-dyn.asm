; Self modifying code section example: it kind of replaces the missing '_code rwx' functionality,
; unavailable to dynamic ELF '.text' section when using GNU 'ld' as linker.
; After succeeded mprotect() call, this '.text' section behaves the same as '_code rwx'.

format ELF64

include 'fastcall.inc'
include 'stdmacros.inc'
include 'stdio.inc'

_code   Start entry:        lea         rdi, [$]
                            mov         r10, 0_FFFF_FFFF_FFFF_F000h
                            and         rdi, r10
                            mprotect(rdi, 4096, (PROT_READ or PROT_WRITE or PROT_EXEC));
                            test        eax, eax
                            jz          @f
                            fprintf(*stderr, &errfmt, "failed: ");
                            perror(NULL);
                            exit(1);

                    @@      fprintf(*stderr, &errfmt, "succeeded!"\n);

                            signal(SIGINT, &.break);

                    @@      inc         [count]

                            usleep(500'000);
                            test        [flags], 1
                            jnz         .end

                            fprintf(*stdout, <13,"Code section counter value: %lu",0>, *count);
                            fflush(*stdout);
                            jmp         @b

            .end:           fprintf(*stdout, "%s"\n "Finished."\n, <8,8,"  ",0>);
                            exit(0);

            .break:         or          [flags], 1
                            ret

        errfmt              xb 'Change memory protection %s', 0

        count               xq 0
        flags               xb 1111_1110b

; To compile:
;
; > ./build.sh code.rwx-dyn
;
; And then, run it:
;
; > ./code.rwx-dyn
;
; A good (and tested) way to see the change, is to look using edb-debugger under 'View->Memory Regions'
; before and after that mprotect() call, looking at the page address of that 'Start' entry point.
