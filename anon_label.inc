purge @@
purge @@@
; :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; ::: Anonymous multi level labels include file for fasmg/fasm2
;
; By: Jessé Gonçalves
; Start Date: 2025 05 03
;
; (The ugly variable and label names here are intentionaly chosen
; so you can use the remaining beautiful ones in your code ;))
;
; :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

; :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; ::: @@@ anonymous label macro
;
;  Usage:
;
;  @@@          mov     rax, [mtvar]    ; @@@ is the anon label
;               test    al, -1
;               jp      @@b             ; @@b jumps to previous
;               js      @@f             ; @@f jumps to next
;               nop
;               lock add [mtvar], r12
;               ; ...
;  @@@          cmovc   esi, r15d
;               ; ...
;               ; ...
__lbl_count2_ = 1
define @@f? ..@@@_UL_1
macro @@@ line&
  cnt = __lbl_count2_
  repeat 1, i:cnt
    define @@b? ..@@@_UL_#i
  end repeat
  cnt = cnt + 1
  repeat 1, i:cnt
    define @@f? ..@@@_UL_#i
  end repeat
  repeat 1, i:__lbl_count2_
    ..@@@_UL_#i: line
  end repeat
  __lbl_count2_ = __lbl_count2_ + 1
end macro
;
; :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

; :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; ::: @@ anonymous label macro
;     Work similar to @@@, but it has 16 previous and 16 next labels
;  to jump (above and below), identified by the number (x)
;  at @bx and @fx
;
;     Tip: @b = @b1 and @f = @f1 - For aesthetic purposes
;
_desired_levels_ = 16   ; WARNING: number of possible jumps (more means more time processing every @@)
__lbl_count_ = _desired_levels_  ; be careful when tweaking this, no one needs more than 10!
repeat 1, i: __lbl_count_
  define @f? ..@@_UL_#i
  x = i
  y = x + _desired_levels_
  z = 1
  while x < y
    repeat 1, j: z, k: x
      define @f#j? ..@@_UL_#k
    end repeat
    z = z + 1
    x = x + 1
  end while
end repeat
purge x, y, z
macro @@ line&
  local x, y, z, cnt
  cnt = __lbl_count_ - (_desired_levels_ - 1)
  x = 1
  y = _desired_levels_
  z = _desired_levels_
  while z >= x
    repeat 1, h: y, i: cnt
      define @b#h? ..@@_UL_#i
      if h = 1
        ; display '@b', '->', `i, ' '
        define @b? ..@@_UL_#i
      end if
      ; display '@b', `h, '->', `i, ' '
    end repeat
    cnt = cnt + 1
    y = y - 1
    x = x + 1
  end while
  ; display 10
  x = 1
  z = _desired_levels_
  while x <= z
    repeat 1, h: x, i: cnt
      if h = 1
        define @f? ..@@_UL_#i
        ; display '@f', '->', `i, ' '
      end if
      define @f#h? ..@@_UL_#i
      ; display '@f', `h, '->', `i, ' '
    end repeat
    cnt = cnt + 1
    x = x + 1
  end while
  purge x, y, z
  ; display 10
  repeat 1, i:__lbl_count_
    ..@@_UL_#i#: line
  end repeat
  __lbl_count_ = __lbl_count_ + 1
end macro
;
; :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
