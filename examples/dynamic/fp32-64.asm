; Internal prototype demo: shows how to call internal functions using
; this high level syntax, plus some variations on passing float point
; type parameters

format ELF64

include 'fastcall.inc'
include 'stdio.inc'

proto show_32_float, float
proto show_64_float, double
proto show_80_float, tword
proto show_64_32_float, double, float

_data   fp_fmt:         db '%s value is: %'
            .type       db 'l'
            .end:       db 'f', 10, 0

        f80num:
            .1          xt 1.0
            .2          xt 2.0
            .3          xt 3.0
            .4          xt 4.0
            .5          xt 5.0

_code   Start entry:    show_32_float(1.111678);
                        show_64_float(2.121213);

                        show_80_float(TT);

                        finit
                        fld1
                        fadd        st0, st0
                        fsqrt
                        show_80_float(st0);

                        mov         eax, 11.344672
                        movd        xmm0, eax
                        show_32_float(xmm0);

                        mov         rdx, 1551.511508
                        movq        xmm0, rdx
                        show_64_float(xmm0);

                        show_32_float(1f);
                        show_64_float(2f);
                        show_32_float(float 67);
                        show_64_float(float 67 * 2);

                        mov         rax, 1345670.011001
                        movq        xmm3, rax
                        show_64_32_float(xmm3, 3.000331);

                        fprintf(stdout, "F80s: %Lf %Lf %Lf %Lf %Lf"\n, f80num.1, f80num.2, \
                                f80num.3, f80num.4, f80num.5);

                        exit(0);


        show_32_float:  cvtss2sd    xmm0, xmm0
                        sub         rsp, 8
                        fprintf(stdout, fp_fmt, "Float", xmm0);
                        add         rsp, 8
                        ret


        show_64_float:  sub         rsp, 8
                        fprintf(stdout, fp_fmt, "Double", xmm0);
                        add         rsp, 8
                        ret


        show_80_float:  sub         rsp, 8
                        xor         [fp_fmt.type], 20h
                        fprintf(stdout, fp_fmt, "Long double", dt [rsp+16]);
                        xor         [fp_fmt.type], 20h
                        add         rsp, 8
                        ret


    show_64_32_float:   cvtss2sd    xmm1, xmm1
                        sub         rsp, 8
                        fprintf(stdout, "One double: %lf; one float: %lf"\n, xmm0, xmm1);
                        add         rsp, 8
                        ret

; Build this example: > ./build fp32-64
