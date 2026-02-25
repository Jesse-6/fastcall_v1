; Standard macro package

if ~ defined __STANDARD_MACRO_PACKAGE_INCLUDED__
    define __STANDARD_MACRO_PACKAGE_INCLUDED__
    define __STANDARD_MACRO_PACKAGE_INCLUDED__

    include 'anon_label.inc'

    ; 'enum' is the recommended way to work with SMLP files and specification,
    ; because it makes it easy to manage/change/add/remove strings.
    ; Just manage/change/add/remove the constant as well, at the same position,
    ; without bothering with which value/index it actually is.
    ; NOTE: this is similar, although not equal to C 'enum' statement!
    ;
    ; Define each constant as a number, ranging from 'start' value
    ; enum step <value> defines the step increment for each constant
    ;
    ; Example:
    ;
    ; enum 0,   VALUE0, \
    ;           VALUE1, \
    ;           VALUE2, \
    ;           VALUE3
    ;
    ; Expand to:
    ;
    ; define VALUE0 0
    ; define VALUE1 1
    ; define VALUE2 2
    ; define VALUE3 3
    macro enum start, names&
        match =step= val, start
            __ENUM_STEP__ = val
        else
            if ~ start eqtype 0
                err "Invalid 'enum' enumeration macro usage", 10
            else

            local count
            count = start
                iterate name, names
                    repeat 1, i:count
                        define name i
                        if defined __ENUM_DEBUG__
                            display "Const: ", `name, " Value: ", `i, 10
                        end if
                    end repeat
                    if defined __ENUM_STEP__
                        count = count + __ENUM_STEP__
                    else
                        count = count + 1
                    end if
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
else
    err "Duplicate inclusion of 'stdmacros.inc' file"
end if
