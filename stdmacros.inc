; Standard macro package

if ~ defined __STANDARD_MACRO_PACKAGE_INCLUDED__
    define __STANDARD_MACRO_PACKAGE_INCLUDED__
    define __STANDARD_MACRO_PACKAGE_INCLUDED__

    include 'anon_label.inc'

    ; 'enum' is the recommended way to work with SMLP files and specification,
    ; because it makes it easy to manage/change/add/remove strings.
    ; Just manage/change/add/remove the constant as well, at the same position,
    ; without bothering with which value/index it actually is.
    ; NOTE: This works quite similar to C 'enum' statement, but have a step
    ; option which allows define step increment, and also allows to setup start
    ; value at its first parameter
    ;
    ; Define each constant as a number, ranging from 'start' value
    ; enum step <value> defines the step increment for each constant
    ;
    ; enum step also accepts shl <value> so it can define bit constants:
    ;
    ; enum step shl 1
    ; enum 1,   N_E0,\  ; = 1 = 00000001b
    ;           N_E1,\  ; = 2 = 00000010b
    ;           N_E2,\  ; = 4 = 00000100b
    ;           N_E3    ; = 8 = 00001000b
    ;
    ; Example:
    ;
    ; enum 0,   VALUE0, \
    ;           VALUE1, \
    ;           VALUE2, \
    ;           VALUE3
    ;
    ; Expands to:
    ;
    ; define VALUE0 0
    ; define VALUE1 1
    ; define VALUE2 2
    ; define VALUE3 3
    macro enum start, names&
        match =step= val, start
            define __ENUM_STEP__ val
        else
            if ~ start eqtype 0
                err "Invalid 'enum' enumeration macro usage", 10
            else
                local count
                count = start
                iterate name, names
                    local proxy
                    define proxy name
                    match const == value, proxy
                        repeat 1, i:value
                            define const i
                            if defined __ENUM_DEBUG__
                                display "Const: ",`const," Value: ",`i,10
                            end if
                        end repeat
                        count = value
                    else
                        repeat 1, i:count
                            define name i
                            if defined __ENUM_DEBUG__
                                display "Const: ", `name, " Value: ", `i, 10
                            end if
                        end repeat
                    end match
                    match =shl?= val, __ENUM_STEP__
                        count = count shl val
                    else
                        if defined __ENUM_STEP__
                            count = count + __ENUM_STEP__
                        else
                            count = count + 1
                        end if
                    end match
                end iterate
            end if
        end match
    end macro

    struc (point) entry line&   ; Allow: '_code Start entry endbr64' as entry point
        entry point
        match := instruction, line
            point: instruction
        else
            point: line
        end match
    end struc
    ;
    macro Main line&        ; self align Main label to be used with libc.StartMain
        align 4
        match := code, line
            ?Main: code
        else
            err "Syntax error.", 10
        end match
    end macro

    macro struct? definition&   ; Beautiful and flexible structure definition...
        match name= params, definition
            define __ACTUAL__ name
        else
            define __ACTUAL__ definition
        end match
        esc struc definition
        label . : .___sizeof_ - .
    end macro

    macro end?.struct?!         ; with probably all benefits from 'struc' directive included
        .___sizeof_:
        esc end struc
        virtual at 0
            match a, __ACTUAL__
                a a
                ; repeat 1, sz:.size
                ;     display "'", `a, "'", " size: ", `sz, 10
                ; end repeat
            end match
        end virtual
    end macro

; ======================================================================
; ======================================================================
; Bellow are some extension macros, that might help in specific cases

    ; Aligned data data types
    ;
    ; Use xb, xw, xd, xq, xt, xo, xy, xz to gerenate byte, word, dword, qword, tword,
    ; xword, yword and/or zword data types, which spawn with address aligned to its size.
    ;
    ; Accept *num (where num is the quantity) to reserve num variables (like rb, rd, rddq, etc.)
    ;
    ; var_dword xd 8000h    ; create dword variable 'var_dword' which is aligned to a dword boundary
    ;                       ; with 8000h value on it
    ; var_xmm   xo *16      ; allocate 16 variables of 16-byte (ddq) size, aligned to 16-byte address
    ;                       ; pointer
    ;
    if ~ defined __ALIGN_DATA_DISABLE__
        iterate <nam,typ,rtyp,val>, xb,db,rb,1, xw,dw,rw,2, xd,dd,rd,4, xq,dq,rq,8, \
            xt,dt,rt,8, xo,ddq,rdq,16, xy,dqq,rqq,32, xz,ddqq,rdqq,64
            struc nam? data*&
                align val
                match =* rsv, data
                    . rtyp rsv
                else
                    . typ data
                end match
            end struc
            macro nam? data*&
                align val
                match =* rsv, data
                    rtyp rsv
                else
                    typ data
                end match
            end macro
        end iterate
    end if


    ; Single line data macro: a convenience macro, to spawn one line with data that
    ; goes under respective section.
    ; Allows to declare data similar to C style, which may help maintain data near
    ; to the code that uses that data.
    ;
    ; NOTE: requires previous declaration of '_rdata', '_data' and/or '_bss' to work!
    ;
    ; _code Start entry:    nop                 ; Code section code
    ;
    ;                       @bss buff rb 4096   ; Create 'buff' variable at 'bss' section
    ;
    ;                       lea     rdi, [buff] ; This goes into 'code' section,
    ;                       mov     esi, 4095   ; following that previous 'nop'
    ;                       call    PLT.getcwd  ; instruction
    ;                       ; ...
    ;
    if ~ defined __SINGLE_LINE_DATA_DISABLE__
        if defined __FASTCALL_v1_INCLUDED__ ; It needs fastcall_v1.inc to work!
            macro @data line*&
                _data line
                _code
            end macro

            macro @rdata line*&
                _rdata line
                _code
            end macro

            macro @bss line*&
                _bss line
                _code
            end macro
        end if
    end if

else
    err "Duplicate inclusion of 'stdmacros.inc' file"
end if
