; ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; ### SystemV ABI C style fastcall macro: ###
; By Jessé Gonçalves (jesse6)
;
;     If you find bugs or problems using this macro, you may share at flat assembler
; thread related to C-style fastcall macro or e-mail me at: jesse6.2023@proton.me.
;     It should contain the code causing the problem, and any evidence (like fasm2/fasmg
; error output or debugger data) that might add detail to the exact issue.
;     Also any common doubt is welcome, because I have to admit that this
; has become a quite sophisticated "mini language" by itself.
; NOTE: customized versions of this will not be supported by me! You probably are
; on your own if modifying anything inside here!
;     So, for proper support, make sure to test with this original macro set before submit
; an issue to be solved. Make a copy of it as a backup before any modification.
;
;   *********************************
;   * Starting: Alpha on 2025 05 08 *
;   * Beta1 at: 2025 05 28          *
;   * Beta2 at: 2025 05 31          *
;   * Beta3 at: 2025 06 05          *
;   * Stable v1 at: 2025 06 07      *
;   *********************************
;
; Allows functions to be called very similar to the C style format, adding convenience
; and horizontality to a very repetitive task on assembly: calling standardized functions!
;
;
; :::::::::::::::
; ::: Parameter force size and type:
; db -> byte
; dw -> word
; dd -> dword
; dq -> qword
; dt -> tword
; df -> float32
; dp -> float64
; dt -> float80
;
;  Argument support:
;
;  - Registers: GPR, XMM, MMX, FPU.
;  - Memory data: [var] or *var parameter
;  - Pointer: &pointer: effective address of pointer
;  - Pointer of a pointer: **indirect loads *data and then loads [data] again
;  - Number expression: (x+y-(z*4)-b)
;  - Signed 32 and 64 bit numbers +num -num
;  - Forced: db, dw, dd, df, dq, dp or dt param  force size on varargs
;  - Boolean or NULL: predefined parameters that pass 1 or 0 optimized
;  - Float: pass a float point number (created as data, except 0). float is 32, double is 64 bit
;  - String: load the 'string' into data and pass its pointer into parameter
;  - Extended string: <'string',10,0> is created as data and its pointer is the parameter
;  - Unsigned 32 and 64 bit num
;  - labels is treated as numbers, use *label or [label] for data, &label for pointer,
;              **label for indirect pointer to data

; ;;; USAGE:
;
; proto snprintf, qword, dword, qword, vararg
; proto fprintf, qword, qword, vararg
; proto fopen, qword, qword
; proto fclose, qword
; proto getpid, none
;
; SomeCode:
;       ; ...
;       getpid();
;       mov     [pid], rax
;       ; ...
;       mov     r11, [fileName_ptr]
;       snprintf(&buff, 64, '/%s/%s/%s/%', &folder1, &folder2, &folder3, r11);
;       fopen('path/to/file', &writestr);
;       ; ...
;       snprintf(&buff2+256, 128, *indirectptr, xmm0, r8w);
;       ; ...
;       fprintf(**stderr, <"Could not do something.",10,0>);
;       fclose(rbp);
;
; proto accepts:
;
;  - ext proto: external called function
;  - noreturn proto: jumped function
;  - indirect proto: called [ptrfunction]
;  - ext noreturn proto: external jumped function
;  - ext indirect proto: external called [function] (namespace for imported function is __imp)
;  - ext indirect noreturn proto: external indirect jumped [function]
;  - ext noreturn indirect proto: same as previous
;
;  - ext data: used to prototype external imported data (like stdin, stdout, COLOR_PAIRS, etc.)

; ::: Parameter type definitions:
;
FUNC_PARA_TYPE_UNKNOWN  = -1
FUNC_PARA_TYPE_EMPTY	= 0
FUNC_PARA_TYPE_MEMORY   = 1
FUNC_PARA_TYPE_PTRPTR   = 2
FUNC_PARA_TYPE_ADDR     = 3
FUNC_PARA_TYPE_PTR      = 4
FUNC_PARA_TYPE_EQUATION = 5
FUNC_PARA_TYPE_SIGN32   = 6
FUNC_PARA_TYPE_SIGN64   = 7
FUNC_PARA_TYPE_FCBYTE   = 8
FUNC_PARA_TYPE_FCWORD   = 9
FUNC_PARA_TYPE_FCDWORD  = 10
FUNC_PARA_TYPE_FCQWORD  = 11
FUNC_PARA_TYPE_FCTWORD  = 12
FUNC_PARA_TYPE_TOPSC    = 13
FUNC_PARA_TYPE_BOOLEAN  = 14
FUNC_PARA_TYPE_NULL     = 15
FUNC_PARA_TYPE_FLOAT    = 16
FUNC_PARA_TYPE_STRING   = 17
FUNC_PARA_TYPE_NUMBER32 = 18
FUNC_PARA_TYPE_NUMBER64 = 19
FUNC_PARA_TYPE_REGLBYTE = 20
FUNC_PARA_TYPE_REGHBYTE = 21
FUNC_PARA_TYPE_REGWORD  = 22
FUNC_PARA_TYPE_REGDWORD = 23
FUNC_PARA_TYPE_REGQWORD = 24
FUNC_PARA_TYPE_REGXMM   = 25
FUNC_PARA_TYPE_REGYMM   = 26
FUNC_PARA_TYPE_REGZMM   = 27
FUNC_PARA_TYPE_REGMM    = 28
FUNC_PARA_TYPE_REGFPU   = 29
FUNC_PARA_TYPE_REGCRX   = 30
FUNC_PARA_TYPE_REGDRX   = 31
FUNC_PARA_TYPE_LABEL    = 32    ; DEPRECATED on this version: completety unreliable
FUNC_PARA_TYPE_XSTRING	= 33
FUNC_PARA_TYPE_FCFLOAT	= 34	; df parameter
FUNC_PARA_TYPE_FCDOUBLE = 35	; dp parameter
FUNC_PARA_TYPE_PI_NUMBER = 36	; number PI (TT or π parameter)
;
; ::: "System V ABI parameter classes"
SYSTEMV_PARA_CLASS_NONE		= 0
SYSTEMV_PARA_CLASS_REGISTER = 1
SYSTEMV_PARA_CLASS_XMM      = 2
SYSTEMV_PARA_CLASS_MEMORY   = 3
SYSTEMV_PARA_CLASS_VARARG	= 4   ; Special type for handling vararg paramter
SYSTEMV_PARA_CLASS_LDOUBLE	= SYSTEMV_PARA_CLASS_MEMORY + 8	; Special type for handling fpu float type
;
; :::::::::::::::::::::::::::::::::

; ==================================================================================
; ==================================================================================
; ::: The following macros were copied from 'elfsym.inc' and 'import64.inc' files
; ::: at fasmg package, except 'importv', which is a variation from 'import'.
; ::: This is the actually chosen method for importing functions: it generates the
; ::: smallest executable possible, a completely debloated binary in comparison to
; ::: what you will get linking with 'ld' or 'gcc', with the minimum requirements
; ::: for it to use external functions. Unfortunately, it only supports
; ::: 'format ELF64 executable 3', generating only fixed address executables
; ::: (not PIE).
;

namespace __imp
	DT_NULL    = 0
	DT_NEEDED  = 1
	DT_HASH    = 4
	DT_STRTAB  = 5
	DT_SYMTAB  = 6
	DT_RELA    = 7
	DT_RELASZ  = 8
	DT_RELAENT = 9
	DT_STRSZ   = 10
	DT_SYMENT  = 11
	DT_REL	   = 17
	DT_RELSZ   = 18
	DT_RELENT  = 19

	STB_LOCAL  = 0
	STB_GLOBAL = 1
	STB_WEAK   = 2

	STT_NOTYPE  = 0
	STT_OBJECT  = 1
	STT_FUNC    = 2
	STT_SECTION = 3
	STT_FILE    = 4

	R_X86_64_NONE		= 0
	R_X86_64_64			= 1
	R_X86_64_PC32		= 2
	R_X86_64_GOT32		= 3
	R_X86_64_PLT32		= 4
	R_X86_64_COPY		= 5
	R_X86_64_GLOB_DAT	= 6
	R_X86_64_JUMP_SLOT	= 7
	R_X86_64_RELATIVE	= 8
	R_X86_64_GOTPCREL	= 9
	R_X86_64_32			= 10
	R_X86_64_32S		= 11
	R_X86_64_16			= 12
	R_X86_64_PC16		= 13
	R_X86_64_8			= 14
	R_X86_64_PC8		= 15
	R_X86_64_DPTMOD64	= 16
	R_X86_64_DTPOFF64	= 17
	R_X86_64_TPOFF64	= 18
	R_X86_64_TLSGD		= 19
	R_X86_64_TLSLD		= 20
	R_X86_64_DTPOFF32	= 21
	R_X86_64_GOTTPOFF	= 22
	R_X86_64_TPOFF32	= 23
	R_X86_64_PC64		= 24
	R_X86_64_GOTOFF64	= 25
	R_X86_64_GOTPC32	= 26

	macro Elf64_Sym name:0,value:0,size:0,bind:0,type:0,other:0,shndx:0
		dd name
		db bind shl 4 + type
		db other
		dw shndx
		dq value
		dq size
	end macro

	virtual at 0
		Elf64_Sym
		sizeof.Elf64_Sym = $
	end virtual

	macro Elf64_Rel offset:0,symbol:0,type:0
		dq offset
		dq symbol shl 32 + type
	end macro

	virtual at 0
		Elf64_Rel
		sizeof.Elf64_Rel = $
	end virtual

	macro Elf64_Rela offset:0,symbol:0,type:0,addend:0
		dq offset
		dq symbol shl 32 + type
		dq addend
	end macro

	virtual at 0
		Elf64_Rela
		sizeof.Elf64_Rela = $
	end virtual

	macro importv &definitions
		local strtab,strsz,symtab,rel,relsz,hash
		; aligned to 8-byte padding of 0's inside previous interpreter section
		segment dynamic readable
		irpv library, needed@dynamic
			dq DT_NEEDED,strtab.needed#%-strtab
		end irpv
		dq DT_STRTAB,strtab-ELF.DYNAMIC
		dq DT_STRSZ,strsz
		dq DT_SYMTAB,symtab-ELF.DYNAMIC
		dq DT_SYMENT,sizeof.Elf64_Sym
		dq DT_RELA,rela-ELF.DYNAMIC
		dq DT_RELASZ,relasz
		dq DT_RELAENT,sizeof.Elf64_Rela
		dq DT_HASH,hash-ELF.DYNAMIC
		dq DT_NULL,0
		segment readable writeable
		symtab: Elf64_Sym
		local count
		count = 0
		irpv name, definitions
			Elf64_Sym strtab.name-strtab,0,0,STB_GLOBAL,STT_FUNC,0,0
			count = count+1
		end irpv
		rela:
		irpv name, definitions
			Elf64_Rela ?name-ELF.DYNAMIC,%,R_X86_64_64
		end irpv
		relasz = $-rela
		hash:
		dd 1,count+1
		dd 0
		repeat count
			dd %
		end repeat
		dd 0
		strtab db 0
		irpv name, definitions
			strtab.name db `name,0
		end irpv
		irpv library, needed@dynamic
			strtab.needed#% db library,0
		end irpv
		strsz = $-strtab
		ptrtab:
		align 8, 255
		irpv name, definitions
			?name dq 0
		end irpv
	end macro
end namespace
; ==================================================================================
; ==================================================================================

; ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
;   _code, _data and _rdata macros are used to initialize respective segments and
; to define output areas for anonymous strings and data under fastcall macro.
;   _bss should be used to create a new data segment for uninitialized data.
;   _code rwx creates a self modifying code segment with read, write and execute
; permissions.
;   NOTE: The first defined of any of these also parses the import table used
; by any 'ext proto' or 'ext data' before.
;
__RDATA_ONLINE__ = 0
__DATA_ONLINE__ = 0
__CODE_ONLINE__ = 0
__BSS_ONLINE__ = 0
__V_SECTION_OPEN__ = 0

macro _rdata line&  ; Read only initialized data segment
  if __ext_dcount_ > 0 | __ext_icount_ > 0 & ~ (__RDATA_ONLINE__ or __DATA_ONLINE__ \
    or __CODE_ONLINE__ or __BSS_ONLINE__)
      extern2_
  end if
  if __RDATA_ONLINE__ = 0
    if __V_SECTION_OPEN__
      esc end virtual
    end if
    segment readable
    __RDATA_ONLINE__ = 1
    virtual
      __rdata_ptr:: ; Anonymous data from higher macros
    end virtual
    postpone
      virtual __rdata_ptr
        if __V_SECTION_OPEN__
          esc end virtual
        end if
        load __rdata_ptr.contents : $ - $$ from $$
        __V_SECTION_OPEN__ = 0
      end virtual
    end postpone
    virtual __rdata_ptr
      match =align?= any, line
        line
      else
        align 64, '*'
        line
	  end match
    end virtual
    db __rdata_ptr.contents
    esc virtual __rdata_ptr
      __V_SECTION_OPEN__ = 1
  else
    if __V_SECTION_OPEN__
      esc end virtual
    end if
    esc virtual __rdata_ptr
    line
    __V_SECTION_OPEN__ = 1
  end if
end macro

macro _data line&   ; Read/write initialized data segment
  if __ext_dcount_ > 0 | __ext_icount_ > 0 & ~ (__RDATA_ONLINE__ or __DATA_ONLINE__ \
    or __CODE_ONLINE__ or __BSS_ONLINE__)
      extern2_
  end if
  if __DATA_ONLINE__ = 0
    if __V_SECTION_OPEN__
      esc end virtual
    end if
    segment readable writeable
    __DATA_ONLINE__ = 1
    virtual
      __data_ptr::
    end virtual
    postpone
      if __V_SECTION_OPEN__
        esc end virtual
      end if
      virtual __data_ptr
        load __data_ptr.contents : $ - $$ from $$
      end virtual
      __V_SECTION_OPEN__ = 0
    end postpone
    virtual __data_ptr
      match =align?= any, line
        line
      else
        align 64, '*'
        line
      end match
	end virtual
	db __data_ptr.contents
	esc virtual __data_ptr
      __V_SECTION_OPEN__ = 1
  else
    if __V_SECTION_OPEN__
      esc end virtual
    end if
    esc virtual __data_ptr
      line
      __V_SECTION_OPEN__ = 1
  end if
end macro

macro _bss line&	;WARNING: Alpha stage. ; Uninitialized data segment
  if __ext_dcount_ > 0 | __ext_icount_ > 0 & ~ (__RDATA_ONLINE__ or __DATA_ONLINE__ \
    or __CODE_ONLINE__ or __BSS_ONLINE__)
      extern2_
  end if
  if __BSS_ONLINE__ = 0
    if __CODE_ONLINE__
      err "_bss section macro must be placed before any _code statement!", 10
    end if
    if __V_SECTION_OPEN__
      esc end virtual
    end if
    segment readable writeable
    __BSS_ONLINE__ = 1
    ; virtual
    ;   __bss_ptr::
    ; end virtual
    postpone
      if __V_SECTION_OPEN__
        esc end virtual
      end if
      __V_SECTION_OPEN__ = 0
    end postpone
    ; esc virtual __bss_ptr
    match =align?= any, line
      line
    else
      align 64
      line
    end match
    __V_SECTION_OPEN__ = 0
  else
    if __V_SECTION_OPEN__
      esc end virtual
    end if
    err "_bss is alpha stage: so far, only one _bss macro is allowed.", 10
    ; esc virtual __bss_ptr
    ; line
    ; __V_SECTION_OPEN__ = 0
  end if
end macro

macro _code line&   ; Code segment
  if __ext_dcount_ > 0 | __ext_icount_ > 0 & ~ (__RDATA_ONLINE__ or __DATA_ONLINE__ \
    or __CODE_ONLINE__ or __BSS_ONLINE__)
      extern2_
  end if
  if __CODE_ONLINE__ = 0
    if __V_SECTION_OPEN__
      esc end virtual
    end if
    match =rwx?= any, line
      segment readable writeable executable
    else match =rwx?, line
      segment readable writeable executable
    else
      segment readable executable
    end match
    __CODE_ONLINE__ = 1
    virtual
      __code_ptr::	; This is for outputing anonymous data in the same section
    end virtual
    postpone
      if __V_SECTION_OPEN__
        esc end virtual
      end if
      virtual __code_ptr
        load __code_ptr.contents : $ - $$ from $$
        __V_SECTION_OPEN__ = 0
      end virtual
    end postpone
    match =align?= any, line
      line
    end match
    db __code_ptr.contents	; If there's only a _code section, anonymous data will be placed
    ; esc virtual __code_ptr	; before the code in the same section.
    match =rwx?= any, line
      match =align?= value, any
        any
      else
        align 4, 90h
      end match
    else match =rwx?, line
      align 4, 90h
    else
      match =align?= any, line
        line
      else
        align 4, 90h
        line
      end match
    end match
    __V_SECTION_OPEN__ = 0
  else
    if __V_SECTION_OPEN__
      esc end virtual
    end if
    ; esc virtual __code_ptr
    line
    __V_SECTION_OPEN__ = 0
  end if
end macro
;
; WARNING!
; Reuse of _code, _data and _rdata is now possible, but, if you are going to use it,
; _data and _rdata must have been stated prior to the first _code statement!
; The first _data, _rdata and _code creates the output area for the next _data and
; _rdata uses. _code is the default output area when it is first created for the
; rest of the code.
; _bss does not support reuse unfortunately, due to virtual directive not handling
; uninitialized data. And it needs unconditionaly to the stated before _code to
; work properly!
;
; As a safety rule:
;  - _rdata and _data are virtualized segments all time, that resolves at
;      compile (postpone) time;
;  - _code and _bss are real output segment areas;
;  - reuse of _code only closes previously opened virtual data or rdata
;      area, and returns to _code real area.
;
; NOTE: for non reusable mode, _data, _rdata and _code can be placed anywhere
;         in the code, but _bss must be placed before _code.
;
;

; ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
; internal macro to get qword register for any GP register
macro get_q_register register*
	local RegID, info, class
	info = register metadata 1
	class = info metadata 1
	if class relativeto x86.reg
		RegID = 0 scaleof info
		if RegID = 0
			__q_reg = rax
		else if RegID = 1
			__q_reg = rcx
		else if RegID = 2
			__q_reg = rdx
		else if RegID = 3
			__q_reg = rbx
		else if RegID = 4
			__q_reg = rsp
		else if RegID = 5
			__q_reg = rbp
		else if RegID = 6
			__q_reg = rsi
		else if RegID = 7
			__q_reg = rdi
		else if RegID = 8
			__q_reg = r8
		else if RegID = 9
			__q_reg = r9
		else if RegID = 10
			__q_reg = r10
		else if RegID = 11
			__q_reg = r11
		else if RegID = 12
			__q_reg = r12
		else if RegID = 13
			__q_reg = r13
		else if RegID = 14
			__q_reg = r14
		else if RegID = 15
			__q_reg = r15
		else
			err "Error: register not found or unknown/unsupported type.", 10
		end if
	else
		err "Error: register not found or unknown/unsupported type.", 10
	end if
end macro

; internal macro that detects parameter type and properties
macro testtype dest&
	; display "Probing: ", `dest, '... '
	__type_id_ = FUNC_PARA_TYPE_UNKNOWN
	define __type_para_ -1
	__type_size_ equ 10101010
	match first=,last, dest
		__type_id_ = FUNC_PARA_TYPE_XSTRING
		define __type_para_ first,last
		__type_size_ equ 8
	else match=., dest
		__type_id_ = FUNC_PARA_TYPE_EMPTY
		define __type_para_ .
		__type_size_ equ 8
	else match , dest
		__type_id_ = FUNC_PARA_TYPE_EMPTY
		define __type_para_ .
		__type_size_ equ 8
	else match [i], dest
		__type_id_ = FUNC_PARA_TYPE_MEMORY
		define __type_para_ i
		match some+thing, i
			__type_size_ equ 0
		else match some-thing, i
			__type_size_ equ 0
		else
			local info, class
			info = 1 metadataof i
			class = 1 metadataof info
			if class relativeto x86.reg
				__type_size_ equ 0
			else
				__type_size_ equ sizeof i
			end if
		end match
	else match **i, dest
		__type_id_ = FUNC_PARA_TYPE_PTRPTR
		define __type_para_ i
		__type_size_ equ 0
	else match &i, dest
		__type_id_ = FUNC_PARA_TYPE_ADDR
		define __type_para_ i
		local info, class
		info = 1 metadataof i
		class = 1 metadataof info
		if class relativeto x86.reg
			__type_size_ equ 0 scaleof class
		else
			__type_size_ equ 8
		end if
	else match *i, dest
		__type_id_ = FUNC_PARA_TYPE_PTR
		define __type_para_ i
		match some+thing, i
			__type_size_ equ 0
		else match some-thing, i
			__type_size_ equ 0
		else
			local info, class
			info = 1 metadataof i
			class = 1 metadataof info
			if class relativeto x86.reg
				__type_size_ equ 0
			else
				__type_size_ equ sizeof i
			end if
		end match
	else match (i), dest
		__type_id_ = FUNC_PARA_TYPE_EQUATION
		local tmpresult
		tmpresult = (i)
		if tmpresult eqtype 0.0		; Added equation with float point numbers
			__type_id_ = FUNC_PARA_TYPE_FLOAT
			define __type_para_ i
			__type_size_ = 8
		else if i eqtype ""
			repeat 1, num:i
				define __type_para_ num
			end repeat
		else
			define __type_para_ i
		end if
		__type_size_ equ 0
	else match +i, dest
		if dest eqtype 0.0
			__type_id_ = FUNC_PARA_TYPE_FLOAT
			__type_para_ equ dest
			__type_size_ = 8
		else if i >= 1 & i <= 7FFFFFFFh
			__type_id_ = FUNC_PARA_TYPE_SIGN32
			__type_para_ = dest
			__type_size_ = 4
		else if i >= 7FFFFFFFh & i <= 7FFFFFFFFFFFFFFFh
			__type_id_ = FUNC_PARA_TYPE_SIGN64
			__type_para_ = dest
			__type_size_ = 8
		end if
	else match -i, dest
		if dest eqtype 0.0
			__type_id_ = FUNC_PARA_TYPE_FLOAT
			__type_para_ equ dest
			__type_size_ = 8
		else if i >= 1 & i <= 80000000h
			__type_id_ = FUNC_PARA_TYPE_SIGN32
			__type_para_ equ dest
			__type_size_ = 4
		else if i > 80000000h & i <= 7FFFFFFFFFFFFFFFh
			__type_id_ = FUNC_PARA_TYPE_SIGN64
			__type_para_ equ dest
			__type_size_ = 8
		end if
	else match =db? a, dest
		__type_id_ = FUNC_PARA_TYPE_FCBYTE
		define __type_para_ a
		__type_size_ equ 1
	else match =dw? a, dest
		__type_id_ = FUNC_PARA_TYPE_FCWORD
		define __type_para_ a
		__type_size_ equ 2
	else match =dd? a, dest
		__type_id_ = FUNC_PARA_TYPE_FCDWORD
		define __type_para_ a
		__type_size_ equ 4
	else match =dq? a, dest
		__type_id_ = FUNC_PARA_TYPE_FCQWORD
		define __type_para_ a
		__type_size_ equ 8
	else match =dt? a, dest
		__type_id_ = FUNC_PARA_TYPE_FCTWORD
		define __type_para_ a
		__type_size_ equ 10
	else match =df? a, dest
		__type_id_ = FUNC_PARA_TYPE_FCFLOAT
		define __type_para_ a
		__type_size_ equ 4
	else match =dp? a, dest
		__type_id_ = FUNC_PARA_TYPE_FCDOUBLE
		define __type_para_ a
		__type_size_ equ 8
	else match =TRUE, dest
		__type_id_ = FUNC_PARA_TYPE_BOOLEAN
		define __type_para_ 1
		__type_size_ equ 0
	else match =FALSE, dest
		__type_id_ = FUNC_PARA_TYPE_BOOLEAN
		define __type_para_ 0
		__type_size_ equ 0
	else match =NULL, dest
		__type_id_ = FUNC_PARA_TYPE_NULL
		define __type_para_ 0
		__type_size_ equ 0
	else match =π, dest
		__type_id_ = FUNC_PARA_TYPE_PI_NUMBER
		__type_size_ equ 10
		define __type_para_ 3.1415926535897932385
	else match =TT, dest
		__type_id_ = FUNC_PARA_TYPE_PI_NUMBER
		__type_size_ equ 10
		define __type_para_ 3.1415926535897932385
	else match complex= expr, dest
		__type_id_ = FUNC_PARA_TYPE_UNKNOWN
		define __type_para_ 65535
		__type_size_ equ 65535
	else
		local info, class
		info = 1 metadataof dest
		class = 1 metadataof info
		if class relativeto x86.reg
			define __type_para_ dest
			__type_size_ equ 0 scaleof class
			if __type_size_ = 8
				__type_id_ = FUNC_PARA_TYPE_REGQWORD
			else if __type_size_ = 4
				__type_id_ = FUNC_PARA_TYPE_REGDWORD
			else if __type_size_ = 2
				__type_id_ = FUNC_PARA_TYPE_REGWORD
			else if __type_size_ = 1
				__type_id_ = FUNC_PARA_TYPE_REGLBYTE
			end if
		else if info relativeto SSE.reg
			__type_id_ = FUNC_PARA_TYPE_REGXMM
			define __type_para_ dest
			__type_size_ equ 16
		else if info relativeto MMX.reg
			__type_id_ = FUNC_PARA_TYPE_REGMM
			define __type_para_ dest
			__type_size_ equ 8
		else if info relativeto st
			__type_id_ = FUNC_PARA_TYPE_REGFPU
			define __type_para_ dest
			__type_size_ equ 10
		else if info relativeto AVX.reg
			__type_id_ = FUNC_PARA_TYPE_REGYMM
			define __type_para_ dest
			__type_size_ equ 32
		else if info relativeto AVX_512.reg
			__type_id_ = FUNC_PARA_TYPE_REGZMM
			define __type_para_ dest
			__type_size_ equ 64
		else if info relativeto x86.sreg
			__type_id_ = FUNC_PARA_TYPE_REGDWORD
			define __type_para_ dest
			__type_size_ equ 4
		else if info relativeto x86.crx
			__type_id_ = FUNC_PARA_TYPE_REGQWORD
			define __type_para_ dest
			__type_size_ equ 8
		else if info relativeto x86.drx
			__type_id_ = FUNC_PARA_TYPE_REGQWORD
			define __type_para_ dest
			__type_size_ equ 8
		else if dest eqtype 0.0
			__type_id_ = FUNC_PARA_TYPE_FLOAT
			define __type_para_ dest
			__type_size_ equ 8
		else if dest eqtype ""
			__type_id_ = FUNC_PARA_TYPE_STRING
			define __type_para_ dest
			__type_size_ equ 8
		else if dest >=0 & dest <=4294967295
			__type_id_ = FUNC_PARA_TYPE_NUMBER32
			define __type_para_ dest
			__type_size_ equ 4
		else if dest <= 0FFFFFFFFFFFFFFFFh
			__type_id_ = FUNC_PARA_TYPE_NUMBER64
			define __type_para_ dest
			__type_size_ equ 8
		else
			__type_id_ = FUNC_PARA_TYPE_UNKNOWN
			define __type_para_ 255
			__type_size_ equ 255
		end if
	end match
	; irpv param, __type_para_
	; 	indx %%
	; 	repeat 1, sz:__type_size_, t:__type_id_
	; 		display " parameter: '", `param, "' size: ", `sz, " type: ", `t, 10
	; 	end repeat
	; 	break
	; end irpv
end macro

; internal macro to append anonymous data to a virtual section
PUT_ANON_DATA_STRING	= 9
PUT_ANON_DATA_STRINGZ	= 7
__anon_data_count_		= 0
macro put_anon_data dtype, data&	; It depends on _code, _radata or _data macros to work
	if __RDATA_ONLINE__ = 1
		virtual __rdata_ptr
	else if __DATA_ONLINE__ = 1
		virtual __data_ptr
	else if __CODE_ONLINE__ = 1
		virtual __code_ptr
	else
		err "Undefined anonymous data context. Needed: _code, _rdata or _data to work.", 10
	end if
			repeat 1, i:__anon_data_count_
				if dtype = PUT_ANON_DATA_STRINGZ		; put null terminated string
					.._anon_data_#i db data, 0
				else if dtype = PUT_ANON_DATA_STRING	; exact string (no alteration)
					.._anon_data_#i db data
				else if dtype eq dword 					; 32-bit number
					.._anon_data_#i dd data
				else if dtype eq qword					; 64-bit number
					.._anon_data_#i dq data
				else if dtype eq tword					; 80-bit float number
					.._anon_data_#i dt data
				else
					err "Unsupported anon data type.", 10
				end if
				_anon_data_curr_ = .._anon_data_#i
			end repeat
		end virtual
	__anon_data_count_ = __anon_data_count_ + 1
end macro

; internal parameter parser
macro put_parameter index, class, parameter, psize
	local   creg, cregq, cregd, cregw, cregb, xmmsel, ymmsel, zmmsel
	if __type_id_ = FUNC_PARA_TYPE_EMPTY
		if class = SYSTEMV_PARA_CLASS_MEMORY
			__mexpect_ = __mexpect_ - 1	; This helps on keep tracking for reverse parameter order
			sub rsp, 8
		else if class = SYSTEMV_PARA_CLASS_LDOUBLE
			__mexpect_ = __mexpect_ - 2 - (index and 1)
			if index and 1
				sub rsp, 24
			else
				sub rsp, 16
			end if
		end if
		; Do nothing otherwise
	else if class = SYSTEMV_PARA_CLASS_REGISTER
		if  index = 1
			creg equ rdi
			cregq equ rdi
			cregd equ edi
			cregw equ di
			cregb equ dil
		else if index = 2
			creg equ rsi
			cregq equ rsi
			cregd equ esi
			cregw equ si
			cregb equ sil
		else if index = 3
			creg equ rdx
			cregq equ rdx
			cregd equ edx
			cregw equ dx
			cregb equ dl
		else if index = 4
			creg equ rcx
			cregq equ rcx
			cregd equ ecx
			cregw equ cx
			cregb equ cl
		else if index = 5
			creg equ r8
			cregq equ r8
			cregd equ r8d
			cregw equ r8w
			cregb equ r8b
		else if index = 6
			creg equ r9
			cregq equ r9
			cregd equ r9d
			cregw equ r9w
			cregb equ r9b
		else
			err "Exceeded register index.", 10
		end if
		if __type_id_ = FUNC_PARA_TYPE_MEMORY | __type_id_ = FUNC_PARA_TYPE_PTR
			if psize = qword
				if __type_size_ = 8 | __type_size_ = 0
					mov cregq, [parameter]
				else if __type_size_ = 4
					mov cregd, [parameter]
				else if __type_size_ = 2
					movzx cregd, word [parameter]
				else if __type_size_ = 1
					movzx cregd, byte [parameter]
				else
					err "Parameter size not supported at register parameter.", 10
				end if
			else if psize = dword
				if __type_size_ = 4 | __type_size_ = 0
					mov cregd, [parameter]
				else if __type_size_ = 2
					movzx cregd, word [parameter]
				else if __type_size_ = 1
					movzx cregd, byte [parameter]
				else if __type_size_ = 8
					mov cregd, dword [parameter]
				else
					err "Parameter size not supported at register parameter.", 10
				end if
			else if psize = word
				if __type_size_ = 2 | __type_size_ = 0
					mov cregw, [parameter]
				else if __type_size_ = 1
					movzx cregw, byte [parameter]
				else if __type_size_ = 8
					mov cregw, [parameter]
				else if __type_size_ = 4
					mov cregw, [parameter]
				else
					err "Parameter size not supported at register parameter.", 10
				end if
			else if psize = byte
				mov cregb, [parameter]
			else
				err "Invalid register parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_NUMBER32
			if psize = qword
				if parameter = 0
					xor cregd, cregd
				else
					mov cregd, parameter
				end if
			else if psize = dword
				if parameter = 0
					xor cregd, cregd
				else
					mov cregd, parameter
				end if
			else if psize = word
				if parameter = 0
					xor cregw, cregw
				else
					mov cregw, parameter
				end if
			else if psize = byte
				if parameter = 0
					xor cregb, cregb
				else
					mov cregb, parameter
				end if
			else
				err "Invalid register parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_NUMBER64
			if psize = qword
				if parameter = 0
					xor cregd, cregd
				else
					mov cregq, parameter
				end if
			else
				err "Invalid register parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_SIGN32
			if psize = qword
				mov cregq, parameter
			else if psize = dword
				mov cregd, parameter
			else if psize = word
				mov cregw, parameter
			else if psize = byte
				mov cregb, parameter
			else
				err "Invalid register parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_SIGN64
			if psize = qword
				mov cregq, parameter
			else
				err "Invalid register parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_ADDR
			if psize = qword
				if __type_size_ = 8
					lea cregq, [parameter]
				else if __type_size_ = 4
					lea cregd, [parameter]
				end if
			else if psize = dword
				lea cregd, [parameter]
			else
				err "Invalid register parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_REGQWORD
			if psize = qword
				if ~ cregq eq parameter
					mov cregq, parameter
				end if
			else
				err "Invalid register parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_REGDWORD
			if psize = qword
				if ~ cregd eq parameter
					mov cregd, parameter
				end if
			else if psize = dword
				if ~ cregd eq parameter
					mov cregd, parameter
				end if
			else
				err "Invalid register parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_REGWORD
			if psize = qword
				movzx cregd, parameter
			else if psize = dword
				movzx cregd, parameter
			else if psize = word
				if ~ cregw eq parameter
					mov cregw, parameter
				end if
			else
				err "Invalid register parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_REGLBYTE
			if psize = qword
				movzx cregd, parameter
			else if psize = dword
				movzx cregd, parameter
			else if psize = word
				movzx cregw, parameter
			else if psize = byte
				if ~ cregb eq parameter
					mov cregb, parameter
				end if
			else
				err "Invalid register parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_STRING
			if psize = qword
				put_anon_data PUT_ANON_DATA_STRINGZ, parameter
				lea cregq, [_anon_data_curr_]
			else if psize = dword
				mov cregd, parameter	; dword, word, byte -> string will be
			else if psize = word		; passed as chars instead of data
				mov cregw, parameter	; pointer
			else if psize = byte
				mov cregb, parameter
			else
				err "Invalid register parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_XSTRING
			if psize = qword
				put_anon_data PUT_ANON_DATA_STRING, parameter
				lea cregq, [_anon_data_curr_]
			else
				err "Invalid size for complex string parameter", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_EQUATION
			if psize = qword  ; NOTE: 0 extend 32 bit values
				if parameter < 2147483648 & parameter >= 0
					mov cregd, parameter
				else
					mov cregq, parameter
				end if
			else if psize = dword
				mov cregd, parameter
			else if psize = word
				mov cregw, parameter
			else if psize = byte
				mov cregb, parameter
			else
				err "Invalid register parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_PTRPTR
			if psize = qword
				mov cregq, [parameter]
				mov cregq, [cregq]
			else if psize = dword
				mov cregq, [parameter]
				mov cregd, [cregq]
			else if psize = word
				mov cregq, [parameter]
				movzx cregd, word [cregq]
			else if psize = byte
				mov cregq, [parameter]
				movzx cregd, byte [parameter]
			else
				err "Invalid register parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_NULL
			if psize = qword
				xor cregd, cregd
			else if psize = dword
				xor cregd, cregd
			else if psize = word
				xor cregw, cregw
			else if psize = byte
				xor cregb, cregb
			else
				err "Invalid register parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_BOOLEAN
			if parameter eq TRUE
				if psize = qword
					mov cregd, 1
				else if psize = dword
					mov cregd, 1
				else if psize = word
					mov cregw, 1
				else if psize = byte
					mov cregb, 1
				else
					err "Invalid register parameter size.", 10
				end if
			else if parameter eq FALSE
				if psize = qword
					xor cregd, cregd
				else if psize = dword
					xor cregd, cregd
				else if psize = word
					xor cregw, cregw
				else if psize = byte
					xor cregb, cregb
				else
					err "Invalid register parameter size.", 10
				end if
			end if
		else if __type_id_ = FUNC_PARA_TYPE_REGMM
			if psize = qword
				movq cregq, parameter
			else if psize = dword
				movd cregd, parameter
			else
				err "Invalid size for MMX register parameter.", 10
			end if
			__fpu_ne_ = 1
		else
			err "Unsupported parameter type: ", `parameter, 10
		end if
	else if class = SYSTEMV_PARA_CLASS_MEMORY
		if __mexpect_ <> index
			err "Memory class got out of balance. Check macro code.", 10
		end if

		cregq equ r9	; r9 is the only trash register
		cregd equ r9d	; others are preserved, following the rule
		cregw equ r9w	; of inverse register parameter passing
		cregb equ r9b

		if __type_id_ = FUNC_PARA_TYPE_MEMORY | __type_id_ = FUNC_PARA_TYPE_PTR
			if psize = qword
				push [parameter]
			else if psize = dword
				mov cregd, [parameter]
				push cregq
			else if psize = word
				movzx cregd, word [parameter]
				push cregq
			else if psize = byte
				movzx cregd, byte [parameter]
				push cregq
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_ADDR
			if psize = qword
				if __type_size_ = 8
					lea cregq, [parameter]
				else if __type_size_ = 4
					lea cregd, [parameter]
				end if
				push cregq
			else if psize = dword
				lea cregd, [parameter]
				push cregq
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_NUMBER32
			if psize = qword
				if parameter > 7FFFFFFFh
					mov cregd, parameter
					push cregq
				else
					push parameter
				end if
			else if psize = dword
				if parameter > 7FFFFFFFh
					mov cregd, parameter
					push cregq
				else
					push parameter
				end if
			else if psize = word
				push parameter
			else if psize = byte
				push parameter
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_NUMBER64
			if psize = qword
				mov cregq, parameter
				push cregq
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_SIGN32
			if psize = qword
				push parameter
			else if psize = dword
				push parameter
			else if psize = word
				push parameter
			else if psize = byte
				push parameter
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_SIGN64
			if psize = qword
				mov cregq, parameter
				push cregq
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_REGQWORD
			if psize = qword
				push parameter
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_REGDWORD
			if psize = qword
				get_q_register parameter
				if parameter eq esp		; Protection to not modify (e|r)sp register
					mov cregd, parameter
					push cregq
				else
					mov parameter, parameter	; ensure zero upper 32 bits
					push __q_reg
				end if
			else if psize = dword
				get_q_register parameter
				push __q_reg
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_REGWORD
			if psize = qword
				get_q_register parameter
				if parameter eq sp
					movzx cregd, parameter
					push cregq
				else
					movzx __q_reg, parameter
					push __q_reg
				end if
			else if psize = dword
				get_q_register parameter
				if parameter eq sp
					movzx cregd, parameter
					push cregq
				else
					movzx __q_reg, parameter
					push __q_reg
				end if
			else if psize = word
				get_q_register parameter
				push __q_reg
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_REGLBYTE
			if psize = qword
				get_q_register parameter
				if parameter eq spl
					movzx cregd, parameter
					push cregq
				else
					movzx __q_reg, parameter
					push __q_reg
				end if
			else if psize = dword
				get_q_register parameter
				if parameter eq spl
					movzx cregd, parameter
					push cregq
				else
					movzx __q_reg, parameter
					push __q_reg
				end if
			else if psize = word
				get_q_register parameter
				if parameter eq spl
					movzx cregd, parameter
					push cregq
				else
					movzx __q_reg, parameter
					push __q_reg
				end if
			else if psize = byte
				get_q_register parameter
				push __q_reg
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_REGXMM
			if psize = qword
				movq [rsp-8], parameter
				sub rsp, 8
			else if psize = dword
				movd [rsp-8], parameter
				sub rsp, 8
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_FLOAT
			if psize = qword | psize = double
				put_anon_data qword, parameter
				push [_anon_data_curr_]
			else if psize = dword | psize = float
				mov	cregd, parameter
				push cregq
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_EQUATION
			if psize = qword
				if parameter > 7FFFFFFFh
					mov cregq, parameter
					push cregq
				else
					push parameter
				end if
			else if psize = dword
				if parameter > 7FFFFFFFh
					mov cregq, parameter
					push cregq
				else
					push parameter
				end if
			else if psize = word
				push parameter
			else if psize = byte
				push parameter
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_STRING
			if psize = qword
				put_anon_data PUT_ANON_DATA_STRINGZ, parameter
				lea cregq, [_anon_data_curr_]
				push cregq
			else if psize = dword
				push parameter
			else if psize = word
				push parameter
			else if psize = byte
				push parameter
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_XSTRING
			if psize = qword
				put_anon_data PUT_ANON_DATA_STRING, parameter
				lea cregq, [_anon_data_curr_]
				push cregq
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_PTRPTR
			if psize = qword
				mov cregq, [parameter]
				push qword [cregq]
				; mov cregq, [cregq]
				; push cregq
			else if psize = dword
				mov cregq, [parameter]
				mov cregd, [cregq]
				push cregq
			else if psize = word
				mov cregq, [parameter]
				movzx cregd, word [cregq]
				push cregq
			else if psize = byte
				mov cregq, [parameter]
				movzx cregd, byte [cregq]
				push cregq
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_NULL
			if psize = qword
				push 0
			else if psize = dword
				push 0
			else if psize = word
				push 0
			else if psize = byte
				push 0
			else
				err "Invalid memory class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_BOOLEAN
			if parameter eq TRUE
				push 1
			else if parameter eq FALSE
				push 0
			end if
		else if __type_id_ = FUNC_PARA_TYPE_REGMM
			if psize = qword
				movq [rsp-8], parameter
			else if psize = dword
				movd [rsp-8], parameter
			else
				err "Invalid size for MMX register parameter.", 10
			end if
			sub rsp, 8
			__fpu_ne_ = 1
		else
			err "Unsupported memory class parameter.", 10
		end if
		__mexpect_ = __mexpect_ - 1	; function sanity checker
	else if class = SYSTEMV_PARA_CLASS_XMM
		if index = 1
			xmmsel equ xmm0
			ymmsel equ ymm0
			zmmsel equ zmm0
		else if index = 2
			xmmsel equ xmm1
			ymmsel equ ymm1
			zmmsel equ zmm1
		else if index = 3
			xmmsel equ xmm2
			ymmsel equ ymm2
			zmmsel equ zmm2
		else if index = 4
			xmmsel equ xmm3
			ymmsel equ ymm3
			zmmsel equ zmm3
		else if index = 5
			xmmsel equ xmm4
			ymmsel equ ymm4
			zmmsel equ zmm4
		else if index = 6
			xmmsel equ xmm5
			ymmsel equ ymm5
			zmmsel equ zmm5
		else if index = 7
			xmmsel equ xmm6
			ymmsel equ ymm6
			zmmsel equ zmm6
		else if index = 8
			xmmsel equ xmm7
			ymmsel equ ymm7
			zmmsel equ zmm7
		else
			err "Exceeded xmm register index.", 10
		end if

		if __type_id_ = FUNC_PARA_TYPE_REGXMM
			if psize = float
				if  ~ xmmsel eq parameter
					movss xmmsel, parameter
				end if
			else if psize = double
				if ~ xmmsel eq parameter
					movsd xmmsel, parameter
				end if
			else
				err "Wrong xmm class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_MEMORY | __type_id_ = FUNC_PARA_TYPE_PTR
			if psize = float
				movss xmmsel, [parameter]
			else if psize = double
				movsd xmmsel, [parameter]
			else
				err "Wrong xmm class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_FLOAT
			if psize = float
				if parameter = 0
					pxor xmmsel, xmmsel
				else
					put_anon_data dword, parameter
					movss xmmsel, [_anon_data_curr_]
				end if
			else if psize = double
				if parameter = 0
					pxor xmmsel, xmmsel
				else
					put_anon_data qword, parameter
					movsd xmmsel, [_anon_data_curr_]
				end if
			else
				err "Wrong xmm class parameter size.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_REGYMM
			if psize = yword
				if ~ ymmsel eq parameter
					vmovdqa ymmsel, parameter
				end if
				; TODO
			else
				err "Wrong ymm size operand.", 10
			end if
		else if __type_id_ = FUNC_PARA_TYPE_REGZMM
		if psize = zword
			if ~ zmmsel eq parameter
				vmovdqa zmmsel, parameter
			end if
			; TODO
		else
			err "Wrong zmm size operand.", 10
		end if
		else
			err "Wrong xmm parameter type.", 10
		end if
	else if class = SYSTEMV_PARA_CLASS_LDOUBLE	; This is done for reverse order only!
		if psize = tword							; WARNING! Value sanity is not checked
			if __type_id_ = FUNC_PARA_TYPE_FLOAT	; within LDOUBLE class! ###
				if parameter = 0.0
					fldz
				else if parameter = 1.0
					fld1
				else
					put_anon_data tword, parameter
					fld tword [_anon_data_curr_]
				end if
				fstp tword [rsp-16]
				if index and 1
					sub rsp, 24
				else
					sub rsp, 16
				end if
			else if __type_id_ = FUNC_PARA_TYPE_PTR | __type_id_ = FUNC_PARA_TYPE_MEMORY
				fld tword [parameter]
				fstp tword [rsp-16]
				if index and 1
					sub rsp, 24
				else
					sub rsp, 16
				end if
			else if __type_id_ = FUNC_PARA_TYPE_REGFPU	; avoid this
				if parameter eq st0
					fstp tword [rsp-16]
					fldz
					__fpu_ne_ = 1
				else
					fxch parameter
					fstp tword [rsp-16]
					fld tword [rsp-16]
					fxch parameter
					__fpu_ne_ = 1
				end if
				if index and 1
					sub rsp, 24
				else
					sub rsp, 16
				end if
			else if __type_id_ = FUNC_PARA_TYPE_PI_NUMBER ; Enabled π number support!
				fldpi				; because it is a FPU hardware builtin constant
				fstp tword [rsp-16]
				if index and 1
					sub rsp, 24
				else
					sub rsp, 16
				end if
			else
				err "Wrong parameter type for tword size argument.", 10
			end if
			__mexpect_ = __mexpect_ - 2 - (index and 1)
		else
			err "Wrong parameter type for tword size argument.", 10
		end if
	else
		err "put_parameter: wrong class type: ", `parameter, ', ', `class,  10
	end if
end macro

; internal pre parser that detects size override
macro put_parameter2 index, class, parameter, psize	; detect forced size beforehand
	if __type_id_ = FUNC_PARA_TYPE_FCQWORD
		match a, parameter
			testtype a
			__type_size_ = 8
			put_parameter index, class, __type_para_, qword
		end match
	else if __type_id_ = FUNC_PARA_TYPE_FCDWORD
		match a, parameter
			testtype a
			__type_size_ = 4
			put_parameter index, class, __type_para_, dword
		end match
	else if __type_id_ = FUNC_PARA_TYPE_FCWORD
		match a, parameter
			testtype a
			__type_size_ = 2
			put_parameter index, class, __type_para_, word
		end match
	else if __type_id_ = FUNC_PARA_TYPE_FCBYTE
		match a, parameter
			testtype a
			__type_size_ = 1
			put_parameter index, class, __type_para_, byte
		end match
	else if __type_id_ = FUNC_PARA_TYPE_FCDOUBLE
		match a, parameter
			testtype a
			__type_size_ = 8
			put_parameter index, class, __type_para_, double
		end match
	else if __type_id_ = FUNC_PARA_TYPE_FCFLOAT
		match a, parameter
			testtype a
			__type_size_ = 4
			put_parameter index, class, __type_para_, float
		end match
	else if __type_id_ = FUNC_PARA_TYPE_FCTWORD
		match a, parameter
			testtype a
			__type_size_ = 10
			put_parameter index, class, __type_para_, tword
		end match
	else
		put_parameter index, class, parameter, psize
	end if
end macro

; internal fastcall macro itself
macro fastcall func, args&
	local stackalloc, xmmcount, memcount, regcount, xmmargs
	stackalloc	= 0

	regcount = func__.#func.par0.regcnt
	xmmcount = func__.#func.par0.xmmcnt
	memcount = func__.#func.par0.memcnt
	__mexpect_ = func__.#func.par0.memcnt	; Memory class expected memory "parameter counter"
											; (error control)
	xmmargs = 0		; vararg number of xmm arguments
	__fpu_ne_ = 0	; signal to issue emms prior to call function

	if func__.#func.par0.isVararg > func__.#func.par0.attr
		if (memcount mod 2)
			if func__.#func.par0.jmp
				stackalloc = memcount
			else
				sub rsp, 8
				stackalloc = memcount + 1
			end if
		else
			if func__.#func.par0.jmp
				sub rsp, 8
				stackalloc = memcount + 1
			else
				stackalloc = memcount
			end if
		end if
	end if
	if func__.#func.par0.attr > 0
		iterate arg, args	; ATTENTION: iterate decapsulates '<>' off parameter!
			if % = 1
				if func__.#func.par0.isVararg > func__.#func.par0.attr ; no vararg condition
					if %% <> func__.#func.par0.attr
						err "Function '", `func, "()' number of passed parameters is wrong.", 10
					end if
				end if
			end if
			if (%% - % + 1) < func__.#func.par0.isVararg
				indx %% - % + 1
				repeat 1, r:regcount, x:xmmcount, m:memcount, i: %% - % + 1
					if func__.#func.par#i.class = SYSTEMV_PARA_CLASS_REGISTER
						testtype arg
						put_parameter2 r, SYSTEMV_PARA_CLASS_REGISTER, \
							__type_para_, func__.#func.par#i.size
						regcount = regcount - 1
					else if func__.#func.par#i.class = SYSTEMV_PARA_CLASS_XMM
						testtype arg
						put_parameter2 x, SYSTEMV_PARA_CLASS_XMM, __type_para_, \
							func__.#func.par#i.size
						xmmcount = xmmcount - 1
					else if func__.#func.par#i.class = SYSTEMV_PARA_CLASS_MEMORY
						testtype arg
						put_parameter2 m, SYSTEMV_PARA_CLASS_MEMORY, __type_para_, \
							func__.#func.par#i.size
						memcount = memcount - 1
					else if func__.#func.par#i.class = SYSTEMV_PARA_CLASS_LDOUBLE
						testtype arg
						put_parameter2 func__.#func.par#i.align, SYSTEMV_PARA_CLASS_LDOUBLE, \
							__type_para_, func__.#func.par#i.size
						memcount = memcount - 2 - (func__.#func.par#i.align and 1)
					end if
				end repeat
			else
				if % = 1	; First time? Define the temporary prototype
					local ldcount, totalcount, ldhelper
					totalcount = 0
					ldcount = 0
					iterate argp, args
						if (% + func__.#func.par0.isVararg - 1) > %%	; Exit point
							__vararg.par0.attr = totalcount
							__vararg.par0.memcnt = memcount - func__.#func.par0.memcnt
							__vararg.par0.regnt = regcount - func__.#func.par0.regcnt
							__vararg.par0.xmmcnt = xmmcount - func__.#func.par0.xmmcnt
							__vararg.par0.ldcnt = ldcount
							__mexpect_ = memcount
							xmmargs = xmmcount
							if (memcount mod 2)
								if func__.#func.par0.jmp
									stackalloc = memcount
								else
									sub rsp, 8
									stackalloc = memcount + 1
								end if
							else
								if func__.#func.par0.jmp
									sub rsp, 8
									stackalloc = memcount + 1
								else
									stackalloc = memcount
								end if
							end if
							break
						end if
						indx % + func__.#func.par0.isVararg - 1
						testtype argp
						if __type_id_ = FUNC_PARA_TYPE_ADDR | __type_id_ = FUNC_PARA_TYPE_REGQWORD | \
							__type_id_ = FUNC_PARA_TYPE_NUMBER64 | __type_id_ = FUNC_PARA_TYPE_SIGN64 | \
							__type_id_ = FUNC_PARA_TYPE_STRING | __type_id_ = FUNC_PARA_TYPE_XSTRING | \
							__type_id_ = FUNC_PARA_TYPE_FCQWORD | __type_id_ = FUNC_PARA_TYPE_EMPTY | \
							__type_id_ = FUNC_PARA_TYPE_REGMM
							if regcount < 6
								regcount = regcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, r:regcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_REGISTER
									define __vararg.par#i.count r
									define __vararg.par#i.size qword
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
								end repeat
							else
								memcount = memcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, m:memcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_MEMORY
									define __vararg.par#i.count m
									define __vararg.par#i.size qword
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
								end repeat
							end if
						else if __type_id_ = FUNC_PARA_TYPE_REGDWORD | __type_id_ = FUNC_PARA_TYPE_NUMBER32 | \
							__type_id_ = FUNC_PARA_TYPE_SIGN32 | __type_id_ = FUNC_PARA_TYPE_FCDWORD | \
							__type_id_ = FUNC_PARA_TYPE_NULL | __type_id_ = FUNC_PARA_TYPE_BOOLEAN
							if regcount < 6
								regcount = regcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, r:regcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_REGISTER
									define __vararg.par#i.count r
									define __vararg.par#i.size dword
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
								end repeat
							else
								memcount = memcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, m:memcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_MEMORY
									define __vararg.par#i.count m
									define __vararg.par#i.size dword
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
								end repeat
							end if
						else if __type_id_ = FUNC_PARA_TYPE_REGXMM | __type_id_ = FUNC_PARA_TYPE_FLOAT | \
							__type_id_ = FUNC_PARA_TYPE_FCDOUBLE	; default float type is double (64-bit)
							if xmmcount < 8
								xmmcount = xmmcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, x:xmmcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_XMM
									define __vararg.par#i.count x
									define __vararg.par#i.size double
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
								end repeat
							else
								memcount = memcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, m:memcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_MEMORY
									define __vararg.par#i.count m
									define __vararg.par#i.size double
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
								end repeat
							end if
						else if __type_id_ = FUNC_PARA_TYPE_FCFLOAT
							if xmmcount < 8
								xmmcount = xmmcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, x:xmmcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_XMM
									define __vararg.par#i.count x
									define __vararg.par#i.size float
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
								end repeat
							else
								memcount = memcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, m:memcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_MEMORY
									define __vararg.par#i.count m
									define __vararg.par#i.size float
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
								end repeat
							end if
						else if __type_id_ = FUNC_PARA_TYPE_MEMORY | __type_id_ = FUNC_PARA_TYPE_PTR | \
							__type_id_ = FUNC_PARA_TYPE_PTRPTR
							if __type_size_ = 10	; handle as long double memory class
								ldhelper = memcount
								ldcount = ldcount + 1
								totalcount = totalcount + 1
								memcount = memcount + 2 + (memcount mod 2)
								repeat 1, i:%, m:memcount l:ldhelper
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_LDOUBLE
									define __vararg.par#i.count m
									define __vararg.par#i.size tword
									define __vararg.par#i.align l
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
								end repeat
							else if regcount < 6
								regcount = regcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, r:regcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_REGISTER
									define __vararg.par#i.count r
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
									if sizeof(__vararg.par#i.data) > 0
										__vararg.par#i.size equ sizeof(__vararg.par#i.data)
									else
										define __vararg.par#i.size qword
									end if
								end repeat
							else
								memcount = memcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, m:memcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_MEMORY
									define __vararg.par#i.count m
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
									if sizeof(__vararg.par#i.data) > 0
										__vararg.par#i.size equ sizeof(__vararg.par#i.data)
									else
										define __vararg.par#i.size qword
									end if
								end repeat
							end if
						else if __type_id_ = FUNC_PARA_TYPE_REGWORD | __type_id_ = FUNC_PARA_TYPE_FCWORD
							if regcount < 6
								regcount = regcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, r:regcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_REGISTER
									define __vararg.par#i.count r
									define __vararg.par#i.size word
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
								end repeat
							else
								memcount = memcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, m:memcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_MEMORY
									define __vararg.par#i.count m
									define __vararg.par#i.size word
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
								end repeat
							end if
						else if __type_id_ = FUNC_PARA_TYPE_REGLBYTE | __type_id_ = FUNC_PARA_TYPE_FCBYTE
							if regcount < 6
								regcount = regcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, r:regcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_REGISTER
									define __vararg.par#i.count r
									define __vararg.par#i.size byte
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
								end repeat
							else
								memcount = memcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, m:memcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_MEMORY
									define __vararg.par#i.count m
									define __vararg.par#i.size byte
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
								end repeat
							end if
						else if __type_id_ = FUNC_PARA_TYPE_EQUATION
							if regcount < 6
								regcount = regcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, r:regcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_REGISTER
									define __vararg.par#i.count r
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
									if argp eqtype ""	; now ("chars") parameter is accepted!
										repeat 1, val:argp
											if val <= 4294967295
												define __vararg.par#i.size dword
											else
												; display 27,"[1;31m","Check!",27,"[0m",10
												define __vararg.par#i.size qword
											end if
										end repeat
									else
										if argp <= 2147483647 & argp >= -2147483648
											define __vararg.par#i.size dword
										else
											define __vararg.par#i.size qword
										end if
									end if
								end repeat
							else
								memcount = memcount + 1
								totalcount = totalcount + 1
								repeat 1, i:%, m:memcount
									define __vararg.par#i.class SYSTEMV_PARA_CLASS_MEMORY
									define __vararg.par#i.count m
									define __vararg.par#i.align %
									__vararg.par#i.rawdata equ argp
									put_value __vararg.par#i.data, __type_para_
									put_value __vararg.par#i.type, __type_id_
									if argp eqtype ""	; ("chars") processed as a number
										repeat 1, val:argp
											if val <= 4294967295
												define __vararg.par#i.size dword
											else
												define __vararg.par#i.size qword
											end if
										end repeat
									else
										if argp <= 2147483647 & argp >= -2147483648
											define __vararg.par#i.size dword
										else
											define __vararg.par#i.size qword
										end if
									end if
								end repeat
							end if
						else if __type_id_ = FUNC_PARA_TYPE_REGFPU | __type_id_ = FUNC_PARA_TYPE_FCTWORD \
							| __type_id_ = FUNC_PARA_TYPE_PI_NUMBER
							ldhelper = memcount
							ldcount = ldcount + 1
							totalcount = totalcount + 1
							memcount = memcount + 2 + (memcount mod 2)
							repeat 1, i:%, m:memcount l:ldhelper
								define __vararg.par#i.class SYSTEMV_PARA_CLASS_LDOUBLE
								define __vararg.par#i.count m
								define __vararg.par#i.size tword
								define __vararg.par#i.align l
								__vararg.par#i.rawdata equ argp
								put_value __vararg.par#i.data, __type_para_
								put_value __vararg.par#i.type, __type_id_
							end repeat
						else
							display "Vararg: unsupported function by dynamic prototype.", 10
						end if
					end iterate
				end if
				indx %% - % + 1
				repeat 1, r:regcount, x:xmmcount, m:memcount, i: %% - % + 1 - func__.#func.par0.isVararg + 1
					__type_id_ = __vararg.par#i.type	; used by put_parameter
					__type_size_ = __vararg.par#i.size
					if __vararg.par#i.class = SYSTEMV_PARA_CLASS_REGISTER
						put_parameter2 r, SYSTEMV_PARA_CLASS_REGISTER, \
							__vararg.par#i.data, __vararg.par#i.size
						regcount = regcount - 1
					else if __vararg.par#i.class = SYSTEMV_PARA_CLASS_XMM
						put_parameter2 x, SYSTEMV_PARA_CLASS_XMM, __vararg.par#i.data, \
							__vararg.par#i.size
						xmmcount = xmmcount - 1
					else if __vararg.par#i.class = SYSTEMV_PARA_CLASS_MEMORY
						put_parameter2 m, SYSTEMV_PARA_CLASS_MEMORY, __vararg.par#i.data, \
							__vararg.par#i.size
						memcount = memcount - 1
					else if __vararg.par#i.class = SYSTEMV_PARA_CLASS_LDOUBLE
						put_parameter2 __vararg.par#i.align, SYSTEMV_PARA_CLASS_LDOUBLE, \
							__vararg.par#i.data, __vararg.par#i.size
						memcount = memcount - 2 - (__vararg.par#i.align and 1)
					end if
				end repeat
			end if
		end iterate
	end if
	if func__.#func.par0.mode
		if func__.#func.par0.jmp
			if func__.#func.par0.isVararg <= func__.#func.par0.attr
				if xmmargs > 0
					mov al, xmmargs
				else
					xor al, al
				end if
			end if
			if __fpu_ne_
				emms
			end if
			if defined func__.#func.par0.extern
				jmp [__imp.#func]
			else
				if func__.#func.par0.aliased
					jmp [func]
				else
					jmp [_#func]
				end if
			end if
		else
			if func__.#func.par0.isVararg <= func__.#func.par0.attr
				if xmmargs > 0
					mov al, xmmargs
				else
					xor al, al
				end if
			end if
			if __fpu_ne_
				emms
			end if
			if defined func__.#func.par0.extern
				call [__imp.#func]
			else
				if func__.#func.par0.aliased
					call [func]
				else
					call [_#func]
				end if
			end if
			if stackalloc > 0
				add rsp, stackalloc * 8
			end if
		end if
	else
		if func__.#func.par0.jmp
			if func__.#func.par0.isVararg <= func__.#func.par0.attr
				if xmmargs > 0
					mov al, xmmargs
				else
					xor al, al
				end if
			end if
			if __fpu_ne_
				emms
			end if
			if defined func__.#func.par0.extern
				jmp proto.func
			else
				if func__.#func.par0.aliased
					jmp func
				else
					jmp _#func
				end if
			end if
		else
			if func__.#func.par0.isVararg <= func__.#func.par0.attr
				if xmmargs > 0
					mov al, xmmargs
				else
					xor al, al
				end if
			end if
			if __fpu_ne_
				emms
			end if
			if defined func__.#func.par0.extern
				call proto.func
			else
				if func__.#func.par0.aliased
					call func
				else
					call _#func
				end if
			end if
			if stackalloc > 0
				add rsp, stackalloc * 8
			end if
		end if
	end if
end macro

; internal macro that unbound parameters and sets it to variables
macro put_value dest, src
	irpv curr, src			; NOTE: This problem on BETA2 is finally solved!
		indx %%
		dest equ curr
		break
	end irpv
end macro

; ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ### ###
; ###  Proto prototype function section
; ###  Supporting:
; ###
; ###  ext proto func specs: adds func to a list that can be parsed with irpv
; ###  to obtain external imported function names
; ###  -> __IMPORT_LIST_ equ func
; ###
; ###  noreturn proto func specs: function will be invoked with jmp func instead of call
; ###  -> jmp func
; ###
; ###  indirect proto func specs: a variable containing a pointer will be indirect
; ###  called -> call [func]
; ###
; ###  ext must be first, and can optionally be followed by noreturn proto to specify a jump
; ###  function, which is also added to external list. Also indirect as well.
; ###
; ###  indirect and noreturn can be combined in any order followed by proto definition
; ###
;
;  Examples:
;
;  proto internal_call, dword, dword qword  ; internal function with 3 parameters
;  ext proto puts, qword                    ; external function with 1 parameter
;  ext noreturn proto exit, dword           ; external jump function with 1 parameter
;  ext indirect proto g_print, qword, vararg; external call [g_print] var at import table (indirect)
;  											; with 1 fixed parameter, and vararg
;  indirect proto pluginptr, double, double ; indirect call variable with 2 64-bit float parameters
;  indirect noreturn proto nextblock, none  ; indirect jump variable with no parameters
;  ext proto printf, qword, vararg          ; external function with variable number of arguments
;                                           ; starting from parameter 2
;  noreturn indirect proto whichptr, tword  ; indirect jump variable with 1 80-bit float point parameter
;  ext proto __cxa_atexit, qword, alias atexit	; external __cxa_atexit aliased *only* as atexit()
;  												; with one qword parameter
;

define vararg -1
define none 0
define float 0.32
define double 0.64
define l_double tword
define float32 float
define float64 double
define float80 l_double

; External macro to define needed libraries
;
;   library 'libc.so.6'
;
macro library? &names&
	namespace __imp
		irp library, names
			define needed@dynamic library
		end irp
	end namespace
end macro

; internal macro to parse all imported data and functions
macro extern2_
	namespace __imp
		segment interpreter readable
		db '/lib64/ld-linux-x86-64.so.2', 0
		align 8									; This only accepts 0's as padding bytes, executable fails otherwise
		irpv xfunc, __IMPORT_LIST_
			display "Importing: ", `xfunc, 10
		end irpv
		importv __IMPORT_LIST_	; NEW!
	end namespace
end macro

; External ext macro (proto prefix)
__ext_dcount_ = 0
__ext_icount_ = 0
macro ext? line&
	match =proto? function=, specs, line
		if __ext_dcount_ = 0
			segment readable executable
		end if
		__ext_dcount_ = __ext_dcount_ + 1
		proto function, specs
		define func__.#function.par0.extern 1
		if used proto.#function
			proto.#function#: jmp [__imp.#function]
			define __IMPORT_LIST_ function
		end if
	else match =noreturn? =proto? function=, specs, line
		if __ext_dcount_ = 0
			segment readable executable
		end if
		__ext_dcount_ = __ext_dcount_ + 1
		proto function, specs
		define func__.#function.par0.extern 1
		define func__.#function.par0.jmp 1
		if used proto.#function
			proto.#function#: jmp [__imp.#function]
			define __IMPORT_LIST_ function
		end if
	else match =indirect? =proto? function=, specs, line
		__ext_icount_ = __ext_icount_ + 1
		proto function, specs
		define func__.#function.par0.extern 1
		define func__.#function.par0.mode 1
		if used __imp.#function
			define __IMPORT_LIST_ function
		end if
	else match =noreturn? =indirect? =proto? function=, specs, line
		__ext_icount_ = __ext_icount_ + 1
		proto function, specs
		define func__.#function.par0.extern 1
		define func__.#function.par0.jmp 1
		define func__.#function.par0.mode 1
		if used __imp.#function
			define __IMPORT_LIST_ function
		end if
	else match =indirect? =noreturn? =proto? function=, specs, line
		__ext_icount_ = __ext_icount_ + 1
		proto function, specs
		define func__.#function.par0.extern 1
		define func__.#function.par0.jmp 1
		define func__.#function.par0.mode 1
		if used __imp.#function
			define __IMPORT_LIST_ function
		end if
	else match =data?= impdata, line
		local temp
		define temp line
		match =data? list, temp
			iterate symbol, list
				if used symbol
					define __IMPORT_LIST_ symbol
					define symbol __imp.#symbol		; Allows symbol to reference __imp.symbol
				end if
			end iterate
		else
			err "Invalid extern argument. Usage: ext data symbol1, symbol2, ...", 10
		end match
	else
		ext line
	end match
end macro

; External indirect macro (proto prefix)
macro indirect? line&
	match =proto? function=, specs, line
		proto function, specs
		define func__.#function.par0.mode 1
	else match =noreturn? =proto? function=, specs, line
		proto function, specs
		define func__.#function.par0.jmp 1
		define func__.#function.par0.mode 1
	else
		indirect line
	end match
end macro

; External noreturn macro (proto prefix)
macro noreturn? line&
	match =proto? function=, specs, line
		proto function, specs
		define func__.#function.par0.jmp 1
	else match =indirect? =proto? function=, specs, line
		proto function, specs
		define func__.#function.par0.jmp 1
		define func__.#function.par0.mode 1
	else
		noreturn line
	end match
end macro

; External macro 'alias' allows to alias an ugly() function name with a beatiful() one
; (self explanatory ;))
; This macro preserves ugly(), and adds beautiful(), unlike proto 'alias' parameter
; that creates only the beautiful() name
macro alias? beautiful*, ugly*
	define func__.#ugly.par0.aliased 1
	if func__.#ugly.par0.attr > 0
		macro ?beautiful params&
			match (param), params
				fastcall ugly, param
			end match
		end macro
	else
		macro ?beautiful params&
			match (), params
				fastcall ugly
			end match
		end macro
	end if
	if ~ func__.#ugly.par0.mode	; aliased internal functions is freed from the same as label macro name!
		purge ugly
	end if
end macro

; External proto macro: the function prototyper, and fastcall hint creator
; This enables a function() to be called in C style, creating hints for
; fastcall macro that is unique to every function, and also
; setting function() macro itself to every function.
;
; Accepts: byte | word | dword | qword | float | double | l_double | tword | vararg | none
;
; WARNING: xword, yword and zword not done: I can't find any example that uses this so far.
; Send me a code example that uses, so I can analyze and create from it.
;
macro proto? func*, args&
	local xmmcnt, regcnt, memcnt, ldcnt, totalcnt, nsfunc, ldalign, aliased
	xmmcnt = 0
	regcnt = 0
	memcnt = 0
	ldalign = 0
	ldcnt = 0
	totalcnt = 0
	aliased = 0

	define func__.#func.par0.isVararg 0
	define func__.#func.par0.jmp 0
	define func__.#func.par0.mode 0

	iterate arg, args
		match =alias?= pretty, arg	; 'alias' should be the last parameter!
			aliased = 1				; Only pretty() is available as a macro here
			define func__.#func.par0.aliased 1
			if used __imp.func
				display "Alias: '", `func, "' as '", `pretty, "()'", 10
			end if
			macro ?pretty params&
				if totalcnt = 0
					match (), params
						fastcall func	; aliased resolve to func instead of _func
					end match
				else
					match (param), params
						fastcall func, param
					end match
				end if
			end macro
			break
		end match
		define func__.#func.#par#% arg
		if arg = qword | arg = dword | arg = word | arg = byte
			if regcnt <= 5
				totalcnt = totalcnt + 1
				regcnt = regcnt + 1
				repeat 1, i:totalcnt, j:regcnt, k:%
					define func__.#func.par#k.class SYSTEMV_PARA_CLASS_REGISTER
					define func__.#func.par#k.count j
					define func__.#func.par#k.size arg
					define func__.#func.regpar#j.size arg	; index regs separately
				end repeat
			else
				totalcnt = totalcnt + 1
				memcnt = memcnt + 1
				repeat 1, i:totalcnt, j:memcnt, k:%
					define func__.#func.par#k.class SYSTEMV_PARA_CLASS_MEMORY
					define func__.#func.par#k.count j
					define func__.#func.par#k.size arg
					define func__.#func.mempar#j.size arg	; index mems separately
				end repeat
			end if
		else if arg eq float | arg eq double
			if xmmcnt <= 7
				totalcnt = totalcnt + 1
				xmmcnt = xmmcnt + 1
				repeat 1, i:totalcnt, j:xmmcnt, k:%
					define func__.#func.par#k.class SYSTEMV_PARA_CLASS_XMM
					define func__.#func.par#k.count j
					define func__.#func.par#k.size arg
					define func__.#func.xmmpar#j.size arg	; index xmms separately
				end repeat
			else
				totalcnt = totalcnt + 1
				memcnt = memcnt + 1
				repeat 1, i:totalcnt, j:memcnt, k:%
					define func__.#func.par#k.class SYSTEMV_PARA_CLASS_MEMORY
					define func__.#func.par#k.count j
					define func__.#func.par#k.size arg
					define func__.#func.mempar#j.size arg
				end repeat
			end if
		else if arg eq tword
			totalcnt = totalcnt + 1
			ldalign = memcnt
			ldcnt = ldcnt + 1
			memcnt = memcnt + 2 + (memcnt mod 2)	; it must be 16 byte aligned
			repeat 1, i:totalcnt, j:ldcnt, k:%, l:memcnt, a:ldalign
				define func__.#func.par#k.class SYSTEMV_PARA_CLASS_LDOUBLE ; (THIS and 3) xor MEM = 0
				define func__.#func.par#k.count l
				define func__.#func.par#k.size arg
				define func__.#func.par#k.align a	; Previous value as align helper (reverse mode prediction)
				define func__.#func.ldpar#j.size arg
				define func__.#func.mempar#l.size arg
			end repeat
		else if arg eq vararg
			totalcnt = totalcnt + 1
			repeat 1, i:totalcnt, k:%
				define func__.#func.par#k.class SYSTEMV_PARA_CLASS_VARARG
				define func__.#func.par#k.count k
				define func__.#func.par#k.size vararg
				define func__.#func.par0.isVararg k	; index of vararg parameter
			end repeat
			if (% + 1) <= %%
				indx % + 1
				match =alias? gorgeous, arg
					aliased = 0
				else
					break
				end match
			else
				break
			end if
		else if arg eq none
			repeat 1, i:0 k:%
				define func__.#func.par#k.class SYSTEMV_PARA_CLASS_NONE
				define func__.#func.par#k.count 1
				define func__.#func.par#k.size none
			end repeat
			if (% + 1) <= %%
				indx % + 1
				match =alias? gorgeous, arg
					aliased = 0
				else
					break
				end match
			else
				break
			end if
		else
			err "Unsupported: ", `arg, 10
		end if
	end iterate
	define func__.#func.par0.attr totalcnt
	define func__.#func.par0.memcnt memcnt
	define func__.#func.par0.regcnt regcnt
	define func__.#func.par0.xmmcnt xmmcnt
	define func__.#func.par0.ldcnt ldcnt
	if func__.#func.par0.isVararg = 0
		func__.#func.par0.isVararg = totalcnt + 1	; vararg > total for no vararg
	end if
	if ~ aliased
		define func__.#func.par0.aliased 0
		macro ?func params&
			if totalcnt = 0
				match (), params
					fastcall func
				end match
			else
				match (param), params
					fastcall func, param		; See NOTE below
				end match
			end if
		end macro
	end if
end macro

; NOTE:
;
; Unlike fasm, fasmg does not allow reuse of defined names in backward reference mode, so
; it seems to be impossible to use the 'function()' that resolves to 'fastcall function',
; except if function is labeled as ?function.
; So far, one need to prefix all internal functions if using internal prototypes,
; preceding its names with '_' as follows:
;
;  proto internal_function, params
;  indirect proto intfunc2, params
;  noreturn proto intjmpfunc3, params
;  noreturn indirect proto intjmpfunc4, params
;
;  _intjmpfunc4 dq intjmpfunc4
;  _intfunc2	dq intfunc2
;
;  _internal_function:		; do stuff with params
;  							ret
;
;  intfunc2:				; do stuff with params
;  							ret
;  							;
;  _intjmpfunc3:			; do stuff with params
;							; continue
;							;
;  intjmpfunc4:				; do stuff with params
;  							; continue
;  							;
;
;  Not ideal, but this will work until a solution can be found.
;
;  Also, this is the reason why I decided to put imported functions within '__imp' namespace, and
;  also the reason why the jump table has 'proto.function: jmp [__imp.function]' statement for
;  every external function.
;
; NOTE(2): as of official version 1, you can now 'alias' an inline function to be called by a
; friendly name:
;
; proto dismissed, param, alias replace	; replace(param) will resolve to: call dismissed
; 										; in this approach dismissed(param) is unavailable as macro
;
;  -- or --
;
; proto dismissed, param
; alias replace, dismissed
;
