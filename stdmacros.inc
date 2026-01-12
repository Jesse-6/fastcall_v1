; Standard macro package

if ~ defined __STANDARD_MACRO_PACKAGE_INCLUDED__
    define __STANDARD_MACRO_PACKAGE_INCLUDED__
    define __STANDARD_MACRO_PACKAGE_INCLUDED__

    include 'anon_label.inc'
    
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
