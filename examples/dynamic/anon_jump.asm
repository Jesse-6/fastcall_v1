; This demo showcases the 3 types of anonymous labels provided by
; fastcall3 macro package:
;
; '@n', with targeted tags: @nb and @nf, where n is a number from 1 to 16;
; '@@', with targeted tags: @bn and @fn, where n is a number from 1 to 16;
;       also @b and @f, being equivalent to @b1 and @f1, repectively;
; @@@, with targeted tags: @@b and @@f.
;
; Letter b means backward, which is above on the code,
; and f means forward, which means below.
;
; Assuming n as a number from 1 to 16:
;
; @n works similar to fasm2 standard extended macros, where every @n
; with its respective @nf and @nb works in parallel, and every @nf
; and @nb jumps only to its respective @n label;
;
; @@ works by jump 'n' counts of @@ labels above or below: so @bn and @fn
; jumps n @@ labels above or below, respectively @bn and @fn;
;
; @@@ does the same, but it has one level only @@b for @@@ label above,
; and @@f for @@@ label below.
;
; They work completely independent each other. So, pick one or many that
; best suits your preferences. All are included for versatility.
;
; NOTE: this example must be seen setp-by-step with edb-debugger,
; or similar software!
;

format ELF64

include 'fastcall3.inc'
include 'stdio.inc'

_rdata  msgSuccess:     db 'If you see this message, the jumps were'
                        db ' successfull and found the exit point.', 10, 0

_code   Start entry:            jmp     @1f

                                ; The nop blocks here are
                                ; just to help visual identification
                                ; at the debugger screen of
                                ; each block!

                                nop
                                nop
                                nop
                                nop

                                ; These labels are similar to fasm2
                                ; @n extended labels

                        @7      jmp     @7b
                        @8      jmp     @8f
                        @8      jmp     @7b

                                nop
                                nop
                                nop
                                nop

                        @16     jmp     @16f
                        @15     jmp     @15f
                        @14     jmp     @14f
                        @13     jmp     @14b
                        @12     jmp     @12f
                        @11     jmp     @11f
                        @10     jmp     @10f
                        @9      jmp     @9f
                        @8      jmp     @8f
                        @6      jmp     @7f
                        @4      jmp     @5f
                        @3      jmp     @4b
                        @2      jmp     @2f
                        @1      jmp     @2b
                        @2      jmp     @3b
                        @5      jmp     @6b
                        @7      jmp     @8b
                        @8      jmp     @9b
                        @9      jmp     @10b
                        @10     jmp     @10f
                        @10     jmp     @11b
                        @11     jmp     @12b
                        @12     jmp     @13b
                        @14     jmp     @15b
                        @15     jmp     @16b
                        @16     jmp     @f

                                nop
                                nop
                                nop
                                nop

                        @6      jmp     @f2
                        @4      jmp     @5f
                        @3      jmp     @4b
                        @2      jmp     @2f
                        @1      jmp     @2b
                        @2      jmp     @3b
                        @5      jmp     @6b

                                nop
                                nop
                                nop
                                nop

                        @@      jmp     @2f
                        @2      jmp     @f

                                nop
                                nop
                                nop
                                nop

                                ; They're case insensitive
                                ; to also better accomodate
                                ; user preferences

                        @1      jmp     @1F
                        @2      jmp     @2F
                        @3      jmp     @3F
                        @4      jmp     @4F
                        @5      jmp     @5F
                        @6      jmp     @6F
                        @7      jmp     @7F
                        @8      jmp     @8F
                        @9      jmp     @9F
                        @10     jmp     @10F
                        @11     jmp     @11F
                        @12     jmp     @12F
                        @13     jmp     @13F
                        @14     jmp     @14F
                        @15     jmp     @15F
                        @16     jmp     @16F
                        @@      jmp     @16F
                        @16     jmp     @15F
                        @15     jmp     @14B
                        @14     jmp     @13B
                        @13     jmp     @12B
                        @12     jmp     @11B
                        @11     jmp     @10B
                        @10     jmp     @9B
                        @9      jmp     @8B
                        @8      jmp     @7B
                        @7      jmp     @6B
                        @6      jmp     @5B
                        @5      jmp     @4B
                        @4      jmp     @3B
                        @3      jmp     @2B
                        @2      jmp     @1B
                        @1      jmp     @1F

                                nop
                                nop
                                nop
                                nop

                        @8      jmp     @9f
                        @7      jmp     @7f
                        @6      jmp     @6f
                        @5      jmp     @5f
                        @4      jmp     @4f
                        @3      jmp     @3f
                        @2      jmp     @2f
                        @1      nop
                                jmp     @1f
                        @1      jmp     @2b
                        @2      jmp     @3b
                        @3      jmp     @4b
                        @4      jmp     @5b
                        @5      jmp     @6b
                        @6      jmp     @7b
                        @7      jmp     @8b
                        @9      jmp     @9f

                                nop
                                nop
                                nop
                                nop

                                ; And below, is another @@ label type, which is
                                ; my original concept with almos 2 decades now.
                                ; There are 2 independent types below:
                                ; @@ and its relatives @bx @fx, also @b and @f;
                                ; @@@ and its relatives @@b and @@f;

                        @9      jmp     @f
                        @@      jmp     .odd
                        @@@     jmp     @@F

                                nop
                                nop
                                nop
                                nop

                        @@      jmp     @f15
                        @@      jmp     @f13
                        @@      jmp     @f11
                        @@      jmp     @f9
                        @@      jmp     @f7
                        @@      jmp     @f5
                        @@      jmp     @f3
                        @@      jmp     @f1
                .odd:           nop
                                jmp     @b1
                        @@      jmp     @b3
                        @@      jmp     @b5
                        @@      jmp     @b7
                        @@      jmp     @b9
                        @@      jmp     @b11
                        @@      jmp     @b13
                        @@      jmp     @b15
                        @@      jmp     .even

                                nop
                                nop
                                nop
                                nop

                                ; Also, they're case insensitive

                        @@      jmp     @F16
                        @@      jmp     @F14
                        @@      jmp     @F12
                        @@      jmp     @F10
                        @@      jmp     @F8
                        @@      jmp     @F6
                        @@      jmp     @F4
                        @@      jmp     @F2
                .even:          nop
                                nop
                                jmp     @F
                        @@      jmp     @B2
                        @@      jmp     @B4
                        @@      jmp     @B6
                        @@      jmp     @B8
                        @@      jmp     @B10
                        @@      jmp     @B12
                        @@      jmp     @B14
                        @@      jmp     @B16
                        @@      jmp     @@b

                                nop
                                nop
                                nop
                                nop

                        @@      jmp     @f
                        @@@     jmp     @b

                                nop
                                nop
                                nop
                                nop

                        @@      fputs(msgSuccess, stdout);
                                exit(0);
