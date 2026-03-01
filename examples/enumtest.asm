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
            HUM_P4      ; = 104