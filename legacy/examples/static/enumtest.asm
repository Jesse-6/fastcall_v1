; Demonstration on enum macro feature 'VAL = new',
; which creates the new value, and reassign it
; to the enum counter
;
; 'enum' syntax:
;
;    enum <start value>, sym1, sym2, ..., symN
;
;    enum step <step value> ; set step increment value
;
include 'stdmacros.inc'

define __ENUM_DEBUG__

; default step is already 1
enum 1, VALUE_A,\       ; = 1
        VALUE_B,\       ; = 2
        VALUE_C,\       ; = 3
        VALUE_D,\       ; = 4
        VALUE_E,\       ; = 5
        VALUE_J=10,\    ; = 10
        VALUE_K,\       ; = 11
        VALUE_L         ; = 12

enum step 8
enum 8, INDEX_A,\       ; = 8
        INDEX_B,\       ; = 16
        INDEX_C,\       ; = 24
        INDEX_D,\       ; = 32
        INDEX_E,\       ; = 40
        INDEX_J = 10*8,\; = 80
        INDEX_K,\       ; = 88
        INDEX_L         ; = 96

enum step 1
enum 100,   HUN,\       ; = 100
            HUN_P1,\    ; = 101
            HUN_P2,\    ; = 102
            HUN_P3,\    ; = 103
            HUN_P4      ; = 104

enum step shl 1
enum 1,     N_E0,\      ; = 1 = 1b
            N_E1,\      ; = 2 = 10b
            N_E2,\      ; = 4 = 100b
            N_E3,\      ; = 8 = 1000b
            N_E4,\      ; = 16 = 10000b
            N_E5,\      ; = 32 = 100000b
            N_E6,\      ; = 64 = 1000000b
            N_E7        ; = 128 = 10000000b
