; This code shows an example of a dynamic executable that has a read-write-execute
; '.text' section. It must be linked using either 'lld' or 'mold', because GNU 'ld'
; linker apply some kind of censorship regarding '.text' named section.
; Also naming code section other than '.text', messes up with a lot of things when
; using GBU 'ld' linker, render a binary that has a RWX section, but is completely
; broken/unusable.
;
; NOTE: 'lld' or 'mold' aren't standard on Linus O.S.es. They must be installed
; prior to its utilization. Any of these is good enough, but 'lld' delivers an
; even smaller binary than 'mold'.
;
; NOTE(2): both suggested linkers tag themselves on the binary in a '.comment'
; section: to get it as clean as possible, one can remove these sections by using
; 'strip -R .comment <binaryname>' on the final binary.

format ELF64

include 'fastcall.inc'
include 'stdmacros.inc'
include 'stdio.inc'

_code rwx   Start entry:        ; Issue at: 'https://board.flatassembler.net/topic.php?p=248646#248646'
                                signal(SIGINT, &.break);    ; Issue is '.sublabel' cannot be used in the same line as 'label:'

                                fprintf(*stdout, "This program modifies a counter present in a code section!"\n);

                        @@      inc         [count]

                                usleep(100'000);
                                test        [flags], 1
                                jnz         .exit

                                fprintf(*stdout, <13,"Counter value: %lu ",0>, *count);
                                fflush(*stdout);

                                jmp         @b

                .break:         or          [flags], 1
                                ret

                .exit:          fprintf(*stdout, <8,8,32,32,10,0>);
                                exit(0);

            align 16
            count               dq 0
            flags               db 1111_1110b