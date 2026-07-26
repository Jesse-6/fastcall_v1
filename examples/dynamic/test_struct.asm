; By value/by reference example demo.
;
; A simple concept was introduced with version 3 of fastcall macro toolkit:
;
;  - Labels that are attached directly to data types, are data labels, and
;  are referenced by its data content (and size): parsed usually as:
;
;    label1 dd 0     ; defined dword size data label
;
;    mov reg, [label1]  ; accessed by default as mov from [data]
;
;  - Labels that are isolated by a colon (:), regardless of what follows them,
;  are now by reference labels, that are parsed as effective addresses:
;
;    label2: db 'This is an address type label', 10, 0 ; pointer 'label:'
;
;    lea reg, [label2]  ; accessed by its address as a default behavior.
;
;  - Constants, defines and/or equ labels are accessed as literal data:
;
;    label3 equ 5
;    label4 = 6
;    label5 := 7
;    define label6 8
;
;    mov reg, label3
;    mov reg, label4
;    mov reg, label5
;    mov reg, label6
;
;  This is now called default behavior, and can be overriden with the
;  classical symbols:
;
;  &label = is rendered as an address label, passed by reference;
;  [label] = is rendered as a data label, passed by value at memory.
;
;  Labels attached to structures are considered by reference labels by default,
;  but its contents is dependendant on its definition, as seen in this example.
;

format ELF64

include 'fastcall3.inc'
include 'stdio.inc'

struct DUMMY1
    .a              dq ?    ; data member
    .b              dq ?    ; data member
    .c              dq ?    ; data member
end struct

struct SUB_FIELD
    .sub_a          dq ?    ; data member
    .sub_b          dq ?    ; data member
    .sub_c:         dq ?    ; pointer member
    .sub_d:         dq ?    ; pointer member
    .sub_e          DUMMY2  ; pointer member, as it is attached to a structure symbol
end struct

struct TEST_FIELDS
    .data.first     dq ?    ; data member
    .data.second    dq ?    ; data member
    .ptr.first:     dq ?    ; pointer member
    .ptr.second:    dq ?    ; pointer member
    .what.third     SUB_FIELD ; pointer member
    .data.fourth    dq ?    ; data member
    .data.fifth:    dq ?    ; pointer member
end struct

struct DUMMY2
    .d:             dq ?    ; pointer member
    .e:             dq ?    ; pointer member
    .f:             dq ?    ; pointer member
    .g              dq ?    ; data member
end struct

; This struct, that is closed with 'end struct&', has offset symbol of itself and
; its contents. So, sizeof(DUMMY3) value, and DUMMY3.x, DUMMY3.y and DUMMY3.z are
; valid absolute offsets to use with variable positions (like a register value).
struct DUMMY3
    .x              dq ?
    .y              dq ?
    .z:             dq ?
end struct&

_bss    dmys            DUMMY2
        var             TEST_FIELDS
        dmye            DUMMY1
        dmyrem          DUMMY3

_code   Start entry:    libc.StartMain(Main);   ; Main is a pointer label, as it's defined 'Main:'

        Main:           push        0

                        fputs("Loading structure...", stdout); ; stdout is a data label
                        fflush(stdout);

                        mov         [var.data.first], +1000
                        mov         [var.data.second], +2000
                        mov         [var.what.third.sub_e.g], -3000

                        fputs(" done."\n, stdout);
                        fflush(stdout);

                        fprintf(stderr, "Dumping fields:"\n \
                            " Data: %d, %d, %d   Address: 0x%lX, 0x%lX, 0x%lX"\n, \
                            var.data.first, var.data.second, var.what.third.sub_e.g, \
                            var.ptr.first, var.ptr.second, var.what.third.sub_e.f);

                        fprintf(stdout, .testpost);

                        mov         [dmyrem.y], -1'000'000'998
                        mov         [dmyrem.z], qword 666'666
                        lea         rcx, [dmyrem]

                        fprintf(stdout, "Value accessed indirectly: %ld"\n, [rcx+DUMMY3.y]);
                        fprintf(stdout, "Address of z member: 0x%lX"\n, dmyrem.z);
                        fprintf(stdout, "Data of z member: %ld"\n, [dmyrem.z]);     ; classical enforce data type

                        ; Entry symbols resolve to 'Symbol:', so, they're parsed by reference by default:
                        ; At the following case, 'Start' is rendered: 'lea rdx, [Start]'.
                        fprintf(stdout, "This program's entry point address is: 0x%lX"\n, Start);

                        pop         rax
                        ret

            .testpost:  db 'This message pointer must be seen as address type!', 10, 0
