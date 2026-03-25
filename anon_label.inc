if ~ defined __ANON_LABEL_INCLUDED__
  define __ANON_LABEL_INCLUDED__
  define __ANON_LABEL_INCLUDED__
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

  ; :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  ; ::: @n anonymous label macro:
  ;     For convenience, I also included a slightly modified version
  ;     of Tomasz Grysztar's @@ macro, that already coexist in perfect
  ;     harmony with the above @@ macro. Indeed, both can be used in
  ;     parallel, and doesn't affect each other.
  ;     It works identical to fasm2 original version, but:
  ;      - it is a placeholder macro, just like the @@ above, no need
  ;        to '@1:', just '@1' for the label;
  ;      - if lets @@, @b and @f to be handled by the above macro;
  ;      - assuming 'n' as number, @n ranges from 1 to 16
  ;
  ;   As stated by Tomasz at his version:
  ;   @1              ; A:
  ;       je      @1f ; jumps to C
  ;       jg      @2f ; jumps to B
  ;       loop    @1b ; jmps to A
  ;   @2  ; do stuff  ; B:
  ;       loop @2b    ; jmps to B
  ;   @1  nop         ; C:
  ;
  ;   One brave enough to use both macros should know:
  ;
  ;   (assuming x as number from 1 to 16):
  ;
  ;   - @bx and @fx refers to my original version;
  ;   - @xb and @xf refers to this variant version.
  ;
  ;   Example:
  ;
  ;   @4  jmp     @f2 ; A: jumps to C
  ;   @@  jmp     @4f ; B: jumps to D
  ;   @@  jmp     @4b ; C: jumps to A
  ;   @4  jmp     @b  ; D: jumps to C
  ;   @@  jmp     @b3 : E: jumps to B

  macro @INIT name,prefix
    macro name tail&
      match label, prefix#f?
        label#: tail
        prefix#b? equ prefix#f?
      end match
      local anonymous
      prefix#f? equ anonymous
    end macro
    define prefix#f?
    name
  end macro

  repeat 16
    @INIT @#%,@#%
  end repeat

  purge @INIT
  ;
  ; ATTENTION!
  ; This one has the following caveat:
  ;
  ; @1    jmp    @1f  ; A: jumps to A
  ; @1    jmp    @1b  ; B: jumps to A
  ;
  ; With the "classical" (for this macro kit) version:
  ;
  ; @@    jmp    @f   ; A: jumps to B
  ; @@    jmp    @b   ; B: jumps to B
  ;
  ; As a recommendation, one can just avoid the first two uses, to
  ; avoid misunderstandings within code. When not in the same line,
  ; both works equally:
  ;
  ; @1                ; A
  ;       jmp    @1f  ; jumps to B
  ; @1                ; B
  ;       jmp    @1b  ; jumps to B
  ;
  ; :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
else
  err "Duplicated inclusion of 'anon_label.inc' file.", 10
end if