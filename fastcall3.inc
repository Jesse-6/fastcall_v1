if defined __FASTCALL_v1_INCLUDED__
	err "fastcall version 1 cannot the used together with version 3"
else if defined __FASTCALL_v2_INCLUDED__
	err "fastcall version 2 cannot the used together with version 3"
else if ~ defined __FASTCALL_v3_INCLUDED__		; ### ### START OF FASTCALL3 CODE ### ### ###

	define __FASTCALL_v3_INCLUDED__
	define __FASTCALL_v3_INCLUDED__

	if ~ defined UNDO_SHOW_VERSION	; to hide version string at command line: -i'define UNDO_SHOW_VERSION'
		display 27, "[93mUsing 'fastcall' macro package version 3.0+", 27, "[0m", 10
	end if

	if defined ELF.SECTION_NAME
		define __ELF_MODE_DYNAMIC__		; dynamic PIE ELF type: .o object file
	else
		define __ELF_MODE_STATIC__		; static address ELF type: self linked
	end if



	define __ROOT_LABEL_NAMESPACE__		; variable to track last defined root label

	; Label interceptor to track label namespace and also append a property to 'labels:'
	; to be recognized as address pointer type labels
	calminstruction (name) ? line&
				; local		text
				; arrange		text, name line
				; stringify	text
				; display 	27 bappend "[1;35mCatch: " bappend 27 bappend "[0m" bappend text bappend 10
				local		cmd, instructions
				match		:= instructions?, line
				arrange		cmd, name line
				assemble	cmd
				jyes		append
				match		:, line
				jyes		append
				exit
		append: local		property, empty, symbol, color
				arrange		color, 36
				arrange		empty,
				match		.symbol, name
				jno			ns_switch
				arrange		property, =default.=type.=address.__ROOT_LABEL_NAMESPACE__.symbol
				publish		property, empty
				exit
	 ns_switch: match		?symbol, name
				jno			default
		 strip: arrange		property, =default.=type.=address.symbol
				call		lns_attach_to_root, color, symbol
				jump		ns_end
	   default: arrange		property, =default.=type.=address.name
				call		lns_attach_to_root, color, name
		ns_end: publish		property, empty
	end calminstruction



	; Data interceptors that switch label namespace tracking when a root label is defined
	iterate a, db, dw, dd, dq, dt, ddq, dqq, ddqq, \
				emit, rb, rw, rd, rt, rq, rdq, rqq, rdqq, dbx

		calminstruction (dest) a? tail*&
					local		symbol, command
					match		.symbol, dest
					jyes		skip
					match		., dest
					jyes		skip
		 ns_switch: local		color
					arrange		color, 35
					match		?symbol, dest
					jno			default
			 strip: call		lns_attach_to_root, color, symbol
					jump		ns_end
		   default: call		lns_attach_to_root, color, dest
			ns_end:
			  skip: arrange		command, dest =a tail
					assemble	command
		end calminstruction

	end iterate



	purge struct?
	purge end?.struct?

	; Simple track label namespace writer that does not stack names
	__AT_VIRTUAL_OFFSET_CREATE__ = 0    ; flag used within end struct macro

	calminstruction lns_attach_to_root color*, name*    ; set tracked label namespace
				check		__AT_VIRTUAL_OFFSET_CREATE__
				jyes		skip
	 ns_switch: arrange		__ROOT_LABEL_NAMESPACE__, name
				local		text
				arrange		text, name
				stringify	text
				stringify	color
				display		27 bappend "[" bappend color bappend "mSwitch label namespace to: " \
							bappend 27 bappend "[32m" bappend text bappend 27 bappend "[0m" bappend 10
		  skip:
	end calminstruction



	define __STRUCT_CURRENT_FQEN__

	calminstruction sns_current_pop
			local		closed
			take		closed, __STRUCT_CURRENT_FQEN__
			stringify	closed
			display		27 bappend "[94mStruct end: " bappend 27 bappend "[32m" bappend closed \
						bappend 27 bappend "[0m" bappend 10
	end calminstruction

	calminstruction sns_current_push name
			local		opened
			arrange		opened, name
			take		__STRUCT_CURRENT_FQEN__, name
			stringify	opened
			display		27 bappend "[33mStruct start at: " bappend 27 bappend "[32m" bappend opened \
						bappend 27 bappend "[0m" bappend 10
	end calminstruction



	macro struct? definition&   ; Beautiful and flexible structure definition...

		match name= params, definition
			define __STRUCT_OPENED__ name
		else
			define __STRUCT_OPENED__ definition
		end match
		esc struc (lb) definition
		if ~ __AT_VIRTUAL_OFFSET_CREATE__
			match .symbol, lb       ; Making a hint for the variable name to be handled as addressable by default
				match a, __ROOT_LABEL_NAMESPACE__
					define default.type.address.a.symbol
					match b, __STRUCT_CURRENT_FQEN__
						define default.type.address.a.symbol
						display "  -> Create property address to: ", `lb, " at: ", `b, 10
						sns_current_push b.symbol
					else
						define default.type.address.b.symbol
						display "  -> Create property address to: ", `lb, " at: ", `a, 10
						sns_current_push a.symbol
					end match
				end match
			else
				define default.type.address.lb
				lns_attach_to_root 94, lb
				sns_current_push lb
			end match
		end if
		label . : .___sizeof_ - .
		if ~ __AT_VIRTUAL_OFFSET_CREATE__
			struc (lbl) ? line&     ; Trap every struct line to set address property wherever needed
				display "--> Mount: ", `lbl, " ", `line, 10
				match a, __STRUCT_CURRENT_FQEN__
					match := rem, line
						define default.type.address.a#lbl
						display "  -> Create property address to: ", `lbl, " at: ", `a, 10
					else match :, line
						define default.type.address.a#lbl
						display "  -> Create property address to: ", `lbl, " at: ", `a, 10
					end match
				end match
				lbl line
			end struc
		end if

	end macro



	; 'end struct&' creates offset symbol with struct name
	; 'end struct' only the structure definition
	macro end?.struct?! flag

		if ~ __AT_VIRTUAL_OFFSET_CREATE__
			restruc ?
			sns_current_pop
		end if
		.___sizeof_:
		esc end struc
		match &, flag
			virtual at 0
				__AT_VIRTUAL_OFFSET_CREATE__ = 1    ; just a signaling variable
				match a, __STRUCT_OPENED__
					a a
				end match
			end virtual
		end match
		restore __STRUCT_OPENED__
		__AT_VIRTUAL_OFFSET_CREATE__ = 0

	end macro



	FUNC_PARA_TYPE_UNKNOWN  := 0_FFFF_FFFFh
	FUNC_PARA_TYPE_EMPTY	:= 0
	FUNC_PARA_TYPE_MEMORY   := 1
	FUNC_PARA_TYPE_PTRPTR   := 2
	FUNC_PARA_TYPE_ADDR     := 3
	FUNC_PARA_TYPE_PTR      := 4
	FUNC_PARA_TYPE_EQUATION := 5
	FUNC_PARA_TYPE_SIGN32   := 6
	FUNC_PARA_TYPE_SIGN64   := 7
	FUNC_PARA_TYPE_FCBYTE   := 8
	FUNC_PARA_TYPE_FCWORD   := 9
	FUNC_PARA_TYPE_FCDWORD  := 10
	FUNC_PARA_TYPE_FCQWORD  := 11
	FUNC_PARA_TYPE_FCTWORD  := 12
	; FUNC_PARA_TYPE_TOPSC    := 13
	FUNC_PARA_TYPE_BOOLEAN  := 14
	FUNC_PARA_TYPE_NULL     := 15
	FUNC_PARA_TYPE_FLOAT    := 16
	FUNC_PARA_TYPE_STRING   := 17
	FUNC_PARA_TYPE_NUMBER32 := 18
	FUNC_PARA_TYPE_NUMBER64 := 19
	FUNC_PARA_TYPE_REGLBYTE := 20
	FUNC_PARA_TYPE_REGHBYTE := 21
	FUNC_PARA_TYPE_REGWORD  := 22
	FUNC_PARA_TYPE_REGDWORD := 23
	FUNC_PARA_TYPE_REGQWORD := 24
	FUNC_PARA_TYPE_REGXMM   := 25
	FUNC_PARA_TYPE_REGYMM   := 26
	FUNC_PARA_TYPE_REGZMM   := 27
	FUNC_PARA_TYPE_REGMM    := 28
	FUNC_PARA_TYPE_REGFPU   := 29
	FUNC_PARA_TYPE_REGCRX   := 30
	FUNC_PARA_TYPE_REGDRX   := 31
	; FUNC_PARA_TYPE_LABEL    := 32
	FUNC_PARA_TYPE_XSTRING	:= 33
	FUNC_PARA_TYPE_FCFLOAT	:= 34	; df parameter
	FUNC_PARA_TYPE_FCDOUBLE := 35	; dp parameter
	FUNC_PARA_TYPE_PI_NUMBER := 36	; number PI (TT or π parameter)
	FUNC_PARA_TYPE_STRINGN  := 37    ; New at 2026-02-25: "string"n as a \n terminated string

	; ::: "System V ABI parameter classes"
	SYSTEMV_PARA_CLASS_NONE		:= 0
	SYSTEMV_PARA_CLASS_REGISTER := 1
	SYSTEMV_PARA_CLASS_XMM      := 2
	SYSTEMV_PARA_CLASS_MEMORY   := 3
	SYSTEMV_PARA_CLASS_VARARG	:= 4   ; Special type for handling vararg paramter
	SYSTEMV_PARA_CLASS_LDOUBLE	:= SYSTEMV_PARA_CLASS_MEMORY + 8	; Special type for handling fpu float type



	if defined __ELF_MODE_STATIC__

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
			DT_RUNPATH = 29

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
				if defined __LIB_RUNPATH__
					dq DT_RUNPATH,strtab.runpath-strtab
				end if
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
				if defined __LIB_RUNPATH__
					match path, __LIB_RUNPATH__
						strtab.runpath db path,0
					end match
				end if
				strsz = $-strtab
				ptrtab:
				align 8, 255
				irpv name, definitions
					?name dq 0
				end irpv
			end macro
		end namespace

	end if



	__RDATA_ONLINE__ = 0
	__DATA_ONLINE__ = 0
	__CODE_ONLINE__ = 0
	__BSS_ONLINE__ = 0
	__V_SECTION_OPEN__ = 0

	__SECTION_OP_MODE__ = 0		; Reserved: for future usage regarding section recognition

	if defined __ELF_MODE_STATIC__

		macro _rdata &line&  ; Read only initialized data segment
			if __ext_dcount_ > 0 | __ext_icount_ > 0 & ~ (__RDATA_ONLINE__ or __DATA_ONLINE__ \
				or __CODE_ONLINE__ or __BSS_ONLINE__)
				extern2_
			end if
			__SECTION_OP_MODE__ = 2
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

		macro _data &line&   ; Read/write initialized data segment
			if __ext_dcount_ > 0 | __ext_icount_ > 0 & ~ (__RDATA_ONLINE__ or __DATA_ONLINE__ \
				or __CODE_ONLINE__ or __BSS_ONLINE__)
				extern2_
			end if
			__SECTION_OP_MODE__ = 3
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

		macro _bss &line&	; Read/write uninitialized data segment
			if __ext_dcount_ > 0 | __ext_icount_ > 0 & ~ (__RDATA_ONLINE__ or __DATA_ONLINE__ \
				or __CODE_ONLINE__ or __BSS_ONLINE__)
				extern2_
			end if
			__SECTION_OP_MODE__ = 4
			if __BSS_ONLINE__ = 0
				if __CODE_ONLINE__
					err "_bss section macro must be placed before any _code statement!", 10
				end if
				if __V_SECTION_OPEN__
					esc end virtual
				end if
				__V_SECTION_OPEN__ = 0
				segment readable writeable
				__BSS_ONLINE__ = 1
				postpone
					if __V_SECTION_OPEN__
						esc end virtual
					end if
					__V_SECTION_OPEN__ = 0
					virtual __bss_ptr
						__BSS_SIZE_ALLOCATE__ = $-$@
						; repeat 1, sz:$-$@
						; 	display "BSS size allocation: ",`sz,10
						; end repeat
					end virtual
				end postpone
				match =align?= any, line
					line
					virtual at $
						__bss_ptr::
					end virtual
					if __BSS_SIZE_ALLOCATE__ <> 0
						emit __BSS_SIZE_ALLOCATE__, ?
					end if
					esc virtual __bss_ptr
					__V_SECTION_OPEN__ = 1
				else
					align 64
					virtual at $
						__bss_ptr::
					end virtual
					if __BSS_SIZE_ALLOCATE__ <> 0
						emit __BSS_SIZE_ALLOCATE__, ?
					end if
					esc virtual __bss_ptr
						line
					__V_SECTION_OPEN__ = 1
				end match
			else
				if __V_SECTION_OPEN__
					esc end virtual
				end if
				esc virtual __bss_ptr
					line
				__V_SECTION_OPEN__ = 1
			end if
		end macro

		macro _code &line&   ; Code segment
			if __ext_dcount_ > 0 | __ext_icount_ > 0 & ~ (__RDATA_ONLINE__ or __DATA_ONLINE__ \
				or __CODE_ONLINE__ or __BSS_ONLINE__)
				extern2_
			end if
			__SECTION_OP_MODE__ = 1
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
										; before the code in the same section.
				match =rwx?= any, line
					match =align?= value, any
						any
					else
						align 4, 90h
						match label: instr, line
							label:
							instr
						else
							line
						end match
					end match
				else match =rwx?, line
					align 4, 90h
				else
					match =align?= any, line
						line
					else
						align 4, 90h
						match label: instr, line
							label:
							instr
						else
							line
						end match
					end match
				end match
				__V_SECTION_OPEN__ = 0
			else
				if __V_SECTION_OPEN__
					esc end virtual
				end if
				match label: instr, line
					label:
					instr
				else
					line
				end match
				__V_SECTION_OPEN__ = 0
			end if
		end macro

	else if defined __ELF_MODE_DYNAMIC__

		macro _rdata &line&  ; Read only initialized data segment
			__SECTION_OP_MODE__ = 2
			if __RDATA_ONLINE__ = 0
				if __V_SECTION_OPEN__
					esc end virtual
				end if
				match =align?= any, line
					section '.rdata' align any
				else
					section '.rdata' align 64
				end match
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
					else
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

		macro _data &line&   ; Read/write initialized data segment
			__SECTION_OP_MODE__ = 3
			if __DATA_ONLINE__ = 0
				if __V_SECTION_OPEN__
					esc end virtual
				end if
				match =align?= any, line
					section '.data' writeable align any
				else
					section '.data' writeable align 64
				end match
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
					else
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

		macro _bss &line&	; NOTE: Beta stage: now it can be reused!
			__SECTION_OP_MODE__ = 4
			if __BSS_ONLINE__ = 0
				if __CODE_ONLINE__
					err "_bss section macro must be placed before any _code statement!", 10
				end if
				if __V_SECTION_OPEN__
					esc end virtual
				end if
				__V_SECTION_OPEN__ = 0
				match =align?= any, line
					section '.bss' writeable align any
				else
					section '.bss' writeable align 64
				end match
				__BSS_ONLINE__ = 1
				virtual at $
					__bss_ptr::
				end virtual
				postpone
					if __V_SECTION_OPEN__
						esc end virtual
					end if
					__V_SECTION_OPEN__ = 0
					virtual __bss_ptr
						__BSS_SIZE_ALLOCATE__ = $-$@
					end virtual
				end postpone
				virtual __bss_ptr
					match =align? any, line
					else
						line
					end match
				end virtual
				if __BSS_SIZE_ALLOCATE__ <> 0
					emit __BSS_SIZE_ALLOCATE__, ?
				end if
				esc virtual __bss_ptr
				__V_SECTION_OPEN__ = 1
			else
				if __V_SECTION_OPEN__
					esc end virtual
				end if
				esc virtual __bss_ptr
					line
				__V_SECTION_OPEN__ = 1
			end if
		end macro

		macro _code &line&   ; Code segment
			__SECTION_OP_MODE__ = 1
			if __CODE_ONLINE__ = 0
				if __V_SECTION_OPEN__
					esc end virtual
				end if
				match =rwx?= any, line
					match =align? val, any
						section '.text' writeable executable align val
					else
						section '.text' writeable executable align 16
					end match
				else match =rwx?, line
					section '.text' writeable executable align 16
				else
					match =align?= any, line
						section '.text' executable align any
					else
						section '.text' executable align 16
					end match
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
				db __code_ptr.contents	; If there's only a _code section, anonymous data will be placed
										; before the code in the same section.
				align 4, 90h
				match =align? val, line
				else match =rwx? code, line
					match =align? val, line
					else
						match label: instr, code
							label:
							instr
						else
							code
						end match
					end match
				else match =rwx?, line
				else
					match label: instr, line
						label:			; Ensure namespace switching to 'label' prior to 'instr'
						instr
					else
						line
					end match
				end match
				__V_SECTION_OPEN__ = 0
			else
				if __V_SECTION_OPEN__
					esc end virtual
				end if
				match label: instr, line
					label:
					instr
				else
					line
				end match
				__V_SECTION_OPEN__ = 0
			end if
		end macro

	end if



	macro @bss line*&
		_bss line
		_code
	end macro

	macro @data line*&
		_data line
		_code
	end macro

	macro @rdata line*&
		_rdata line
		_code
	end macro



	if defined __ELF_MODE_DYNAMIC__

		; Macro 'extrn' based on the original Tomasz Grysztar's fasm2 header elf64.inc macro:
		; Slightly modified here, to also pass size attribute to GOT.label
		;
		purge extrn?

		macro extrn? declaration*
			namespace ELF
				local sym,gsym,psym
				element sym : relocatable * (-1) + SYMBOL_INDEX
				element gsym : GOT + SYMBOL_INDEX
				element psym : PLT + SYMBOL_INDEX
				match str =as? name:size, declaration
					label name:size at sym
					label GOT.name:size at gsym
					label PLT.name at psym
					SYMBOL_NAME = string str
					SYMBOL_SIZE = size
				else match name:size, declaration
					label name:size at sym
					label GOT.name:size at gsym
					label PLT.name at psym
					SYMBOL_NAME = `name
					SYMBOL_SIZE = size
				else match str =as? name, declaration
					label name at sym
					label GOT.name:8 at gsym
					label PLT.name at psym
					SYMBOL_NAME = string str
					SYMBOL_SIZE = 0
				else
					label declaration at sym
					label GOT.declaration:8 at gsym
					label PLT.declaration at psym
					SYMBOL_NAME = `declaration
					SYMBOL_SIZE = 0
				end match
				store STRING_POSITION at symbol_table : Elf64_Sym.st_name + SYMBOL_INDEX * sizeof Elf64_Sym
				store SYMBOL_NAME : lengthof SYMBOL_NAME at string_table:STRING_POSITION
				STRING_POSITION = STRING_POSITION + lengthof SYMBOL_NAME + 1
				store SYMBOL_SIZE at symbol_table : Elf64_Sym.st_size + SYMBOL_INDEX * sizeof Elf64_Sym
				store STT_NOTYPE + STB_GLOBAL shl 4 at symbol_table : Elf64_Sym.st_info + SYMBOL_INDEX * sizeof Elf64_Sym
				SYMBOL_INDEX = SYMBOL_INDEX + 1
			end namespace
		end macro

	end if




	define __q_reg

	iterate <ID,reg>, 0,rax, 1,rcx, 2,rdx, 3,rbx, 4,rsp, 5,rbp, 6,rsi, 7,rdi
		calminstruction get_reg_id_#ID
			compute __q_reg, reg
		end calminstruction
	end iterate

	repeat 8, ID:8
		calminstruction get_reg_id_#ID
			arrange reg, =r#ID
			compute __q_reg, reg
		end calminstruction
	end repeat

	calminstruction get_q_register register*
		local RegID, info, class, select
		compute info, register metadata 1
		compute class, info metadata 1
		check class relativeto x86.reg
		jyes next
		error:
			err "register not found or unknown/unsupported type"
			exit
		next:
			compute RegID, 0 scaleof info
			arrange select, =get_reg_id_#RegID
			assemble select
	end calminstruction



	define __type_id_
	define __type_para_
	define __type_size_

	calminstruction testtype &dest&
			local tmp1, tmp2
			arrange tmp1, dest
			stringify tmp1
			display "Probing: "
			arrange __type_id_, FUNC_PARA_TYPE_UNKNOWN
			arrange __type_para_, -1
			compute __type_size_, 10101010
			transform dest
		force:
			match =db? a, dest
			jyes fb
			match =dw? a, dest
			jyes fw
			match =dd? a, dest
			jyes fd
			match =dq? a, dest
			jyes fq
			match =dt? a, dest
			jyes ft
			match =df? a, dest
			jyes ff
			match =dp? a, dest
			jyes fg
		start:
			; match i:macro, dest, :			; to ease error handling (maybe being disabled)
			; jyes invalid
			; match i:struc, dest, :			; to ease error handling (maybe being disabled)
			; jyes invalid
			match i:area, dest, :			; to ease error handling (maybe being disabled)
			jyes invalid
			match i:equ, dest, :			; catch variables made with 'define' and 'equ'
			jyes type_variable
			; match i:name.branch, dest, :	; catch hierarchical labels
			; jyes type_named
			match i:name+branch, dest, :	; catch label or register + offset
			jyes type_namep
			match i:name-branch, dest, :	; catch label or register - offset
			jyes type_namen
			match ., dest
			jyes empty1
			match i:name, dest, :			; catch single named tokens
			jyes type_name
			match i:number, dest, :			; catch explicit numbers (integer or float point)
			jyes type_number
			match +i:number, dest, :		; catch positive signed (integer or float point) explicit numbers
			jyes type_numberpsign
			match -i:number, dest, :		; catch negative signed (integer or float point) explicit numbers
			jyes type_numbernsign
			match i:quoted, dest, :			; catch single token quoted strings
			jyes type_stringz
			match i:expression, dest, :		; catch any remaining computable expressions
			jyes type_numericx

			; From here, the remaining ones are: [this], &this, *this, **this, \n this, <this,one>, ., ,
		xstring:
			match first=,last, dest
			jno stringn1
			arrange __type_id_, FUNC_PARA_TYPE_XSTRING
			arrange __type_para_, first,last
			compute __type_size_, 8
			jump _end
		stringn1:
			match \=n str1 \=n str2 \=n, dest
			jno stringn2
			arrange __type_id_, FUNC_PARA_TYPE_STRINGN
			arrange __type_para_, dest
			compute __type_size_, 8
			jump _end
		stringn2:
			match \=n str1 \=n str2, dest
			jno stringn3
			arrange __type_id_, FUNC_PARA_TYPE_STRINGN
			arrange __type_para_, dest
			compute __type_size_, 8
			jump _end
		stringn3:
			match str1 \=n str2 \=n, dest
			jno stringn4
			arrange __type_id_, FUNC_PARA_TYPE_STRINGN
			arrange __type_para_, dest
			compute __type_size_, 8
			jump _end
		stringn4:
			match \=n str1 \=n, dest
			jno stringn5
			arrange __type_id_, FUNC_PARA_TYPE_STRINGN
			arrange __type_para_, dest
			compute __type_size_, 8
			jump _end
		stringn5:
			match str1 \=n str2, dest
			jno stringn6
			arrange __type_id_, FUNC_PARA_TYPE_STRINGN
			arrange __type_para_, dest
			compute __type_size_, 8
			jump _end
		stringn6:
			match \=n \=n str1, dest
			jno stringn7
			arrange __type_id_, FUNC_PARA_TYPE_STRINGN
			arrange __type_para_, dest
			compute __type_size_, 8
			jump _end
		stringn7:
			match str1 \=n \=n, dest
			jno stringn8
			arrange __type_id_, FUNC_PARA_TYPE_STRINGN
			arrange __type_para_, dest
			compute __type_size_, 8
			jump _end
		stringn8:
			match \=n str1, dest
			jno stringn9
			arrange __type_id_, FUNC_PARA_TYPE_STRINGN
			arrange __type_para_, dest
			compute __type_size_, 8
			jump _end
		stringn9:
			match str1 \=n, dest
			jno empty2
			arrange __type_id_, FUNC_PARA_TYPE_STRINGN
			arrange __type_para_, dest
			compute __type_size_, 8
			jump _end
		empty2:
			match , dest
			jno remaining
		empty1:
			arrange __type_id_, FUNC_PARA_TYPE_EMPTY
			arrange __type_para_, .
			compute __type_size_, 8
			jump _end
		remaining:
			match [i], dest
			jyes type_memory
			match **i, dest
			jyes type_ptrptr
			match *i, dest
			jyes type_memory
			match &i, dest
			jyes type_address
			match (i), dest
			jyes type_numericx
			; match one= two, dest
			; jyes type_forced
			err "'testtype' error: something slips too deep in the chained flow"

		type_address:
			; display 27 bappend "[1;31m Here at 'type_address'" bappend 27 bappend "[0m "
			arrange __type_id_, FUNC_PARA_TYPE_ADDR
			arrange __type_para_, i
			compute __type_size_, 8
			local info, class
			compute info, 1 metadataof i
			compute class, 1 metadataof info
			check class relativeto x86.reg
			jno _end
			compute __type_size_, 0 scaleof class
			jump _end
		type_forced:
			; display 27 bappend "[1;31m Here at 'type_forced'" bappend 27 bappend "[0m "
			; fcbyte:
			; 	match =db? a, dest
			; 	jno fcword
			fb:	arrange __type_id_, FUNC_PARA_TYPE_FCBYTE
				arrange __type_para_, a
				compute __type_size_, 1
				jump _end
			; fcword:
			; 	match =dw? a, dest
			; 	jno fcdword
			fw:	arrange __type_id_, FUNC_PARA_TYPE_FCWORD
				arrange __type_para_, a
				compute __type_size_, 2
				jump _end
			; fcdword:
			; 	match =dd? a, dest
			; 	jno fcqword
			fd:	arrange __type_id_, FUNC_PARA_TYPE_FCDWORD
				arrange __type_para_, a
				compute __type_size_, 4
				jump _end
			; fcqword:
			; 	match =dq? a, dest
			; 	jno fctword
			fq:	arrange __type_id_, FUNC_PARA_TYPE_FCQWORD
				arrange __type_para_, a
				compute __type_size_, 8
				jump _end
			; fctword:
			; 	match =dt? a, dest
			; 	jno fcfloat
			ft:	arrange __type_id_, FUNC_PARA_TYPE_FCTWORD
				arrange __type_para_, a
				compute __type_size_, 10
				jump _end
			; fcfloat:
			; 	match =df? a, dest
			; 	jno fcdouble
			ff:	arrange __type_id_, FUNC_PARA_TYPE_FCFLOAT
				arrange __type_para_, a
				compute __type_size_, 4
				jump _end
			; fcdouble:
			; 	match =dp? a, dest
			; 	jno nx_ret
			fg:	arrange __type_id_, FUNC_PARA_TYPE_FCDOUBLE
				arrange __type_para_, a
				compute __type_size_, 8
				jump _end
		type_memory:
			; display 27 bappend "[1;31m Here at 'type_memory'" bappend 27 bappend "[0m "
			arrange __type_id_, FUNC_PARA_TYPE_MEMORY
			arrange __type_para_, i
			mem_add:
				match some + thing, i
				jno mem_sub
				compute __type_size_, sizeof(i)
				jump _end
			mem_sub:
				match some - thing, i
				jno mem_reg
				compute __type_size_, sizeof(i)
				jump _end
			mem_reg:
				compute __type_size_, 0
				local info, class
				compute info, 1 metadataof i
				compute class, 1 metadataof info
				check class relativeto x86.reg
				jyes mem_next
				compute __type_size_, sizeof(i)
			mem_next:
				jump _end
		type_name:
			boolean1:
				match =TRUE, dest
				jno boolean0
				arrange __type_id_, FUNC_PARA_TYPE_BOOLEAN
				arrange __type_para_, 1
				compute __type_size_, 0
				jump _end
			boolean0:
				match =FALSE, dest
				jno null
				arrange __type_id_, FUNC_PARA_TYPE_BOOLEAN
				arrange __type_para_, 0
				compute __type_size_, 0
				jump _end
			null:
				match =NULL, dest
				jno num_pi
				arrange __type_id_, FUNC_PARA_TYPE_NULL
				arrange __type_para_, 0
				compute __type_size_, 0
				jump _end
			num_pi:
				match =π, dest
				jno num_TT
				arrange __type_id_, FUNC_PARA_TYPE_PI_NUMBER
				arrange __type_para_, 3.1415926535897932385
				compute __type_size_, 10
				jump _end
			num_TT:
				match =TT, dest
				jno tn_other
				arrange __type_id_, FUNC_PARA_TYPE_PI_NUMBER
				arrange __type_para_, 3.1415926535897932385
				compute __type_size_, 10
				jump _end
			tn_other:
				; display 27 bappend "[1;31m Here at 'type_name'" bappend 27 bappend "[0m "
				; check defined i
				; jno invalid
				local symbol, size, ssym
				match .ssym, i
				jno tn_root
				arrange symbol, =default.=type.=address.__ROOT_LABEL_NAMESPACE__.ssym
				jump tn_next
			tn_root:
				arrange symbol, =default.=type.=address.i
			tn_next:
				check defined symbol
				jyes type_address
				compute size, sizeof(i)
				check size > 0
				jyes type_memory
				local info, class
				compute info, 1 metadataof dest
				compute class, 1 metadataof info
				check class relativeto x86.reg
				jyes x86_reg
				check info relativeto SSE.reg
				jyes sse_reg
				check info relativeto MMX.reg
				jyes mmx_reg
				check info relativeto st
				jyes st_reg
				check info relativeto AVX.reg
				jyes avx_reg
				check info relativeto AVX_512.reg
				jyes avx512_reg
				check info relativeto x86.sreg
				jyes x86_sreg
				check info relativeto x86.crx
				jyes x86_creg
				check info relativeto x86.drx
				jyes x86_dreg
				check defined __ELF_MODE_DYNAMIC__
				jno type_number
				check info relativeto PLT
				jyes type_address
				check info relativeto GOT
				jyes type_memory
				jump type_number
		; type_named:
		; 	display 27 bappend "[1;31m Here at 'type_named'" bappend 27 bappend "[0m "
		; 	arrange i, name.branch
		; 	jump tn_other
		type_namen:
			; display 27 bappend "[1;31m Here at 'type_namen'" bappend 27 bappend "[0m "
			check defined i
			jno invalid
			local symbol, size, ssym
			match .ssym, i
			jno tnn_root
			arrange symbol, =default.=type.=address.__ROOT_LABEL_NAMESPACE__.ssym
			jump tnn_next
		tnn_root:
			arrange symbol, =default.=type.=address.i
		tnn_next:
			local j
			arrange j, i
			arrange i, i-branch
			check defined symbol
			jyes type_address
			compute size, sizeof(j)		; TODO: to be tested and enchanced
			check size > 0
			jyes type_memory
			local info, class
			compute info, 1 metadataof dest
			compute class, 1 metadataof info
			check class relativeto x86.reg
			jyes type_address
			match i:expression, dest, :
			jyes type_numericx
			; TODO: if something get here
			jump _end
		type_namep:
			; display 27 bappend "[1;31m Here at 'type_namep'" bappend 27 bappend "[0m "
			check defined i
			jno invalid
			local symbol, size, ssym
			match .ssym, i
			jno tnp_root
			arrange symbol, =default.=type.=address.__ROOT_LABEL_NAMESPACE__.ssym
			jump tnp_next
		tnp_root:
			arrange symbol, =default.=type.=address.i
		tnp_next:
			local j
			arrange j, i
			arrange i, i+branch
			check defined symbol
			jyes type_address
			compute size, sizeof(j)		; TODO: to be tested and enchanced
			check size > 0
			jyes type_memory
			local info, class
			compute info, 1 metadataof dest
			compute class, 1 metadataof info
			check class relativeto x86.reg
			jyes type_address
			match i:expression, dest, :
			jyes type_numericx
			; TODO: if something get here
			jump _end
		type_number:
			; display 27 bappend "[1;31m Here at 'type_number'" bappend 27 bappend "[0m "
			abs_float:
				check dest eqtype 0.0
				jno abs_number32
				arrange __type_para_, dest
				arrange __type_id_, FUNC_PARA_TYPE_FLOAT
				compute __type_size_, 8
				jump _end
			abs_number32:
				check dest >= 0 & dest <= 4'294'967'295
				jno abs_number64
				arrange __type_para_, dest
				arrange __type_id_, FUNC_PARA_TYPE_NUMBER32
				compute __type_size_, 4
				jump _end
			abs_number64:
				check dest <= 0_FFFF_FFFF_FFFF_FFFFh
				jno unknown
				arrange __type_para_, dest
				arrange __type_id_, FUNC_PARA_TYPE_NUMBER64
				compute __type_size_, 8
				jump _end
			unknown:
				arrange __type_para_, 255
				arrange __type_id_, FUNC_PARA_TYPE_UNKNOWN
				compute __type_size_, 255
				jump _end
		type_numbernsign:
			n2m_float:
				check i eqtype 0.0
				jno n2m_sign32
				arrange __type_id_, FUNC_PARA_TYPE_FLOAT
				arrange __type_para_, dest
				compute __type_size_, 8
				jump _end
			n2m_sign32:
				check i >= 1 & i <= 8000_0000h
				jno n2m_sign64
				arrange __type_id_, FUNC_PARA_TYPE_SIGN32
				arrange __type_para_, dest
				compute __type_size_, 4
				jump _end
			n2m_sign64:
				check i > 8000_0000h & i <= 7FFF_FFFF_FFFF_FFFFh
				jno invalid
				arrange __type_id_, FUNC_PARA_TYPE_SIGN64
				arrange __type_para_, dest
				compute __type_size_, 8
				jump _end
		type_numberpsign:
			n1p_float:
				check i eqtype 0.0
				jno n1p_sign32
				arrange __type_id_, FUNC_PARA_TYPE_FLOAT
				arrange __type_para_, dest
				compute __type_size_, 8
				jump _end
			n1p_sign32:
				check i >= 1 & i <= 7FFF_FFFFh
				jno n1p_sign64
				arrange __type_id_, FUNC_PARA_TYPE_SIGN32
				arrange __type_para_, dest
				compute __type_size_, 4
				jump _end
			n1p_sign64:
				check i >= 7FFF_FFFFh & i <= 7FFF_FFFF_FFFF_FFFFh
				jno invalid
				arrange __type_id_, FUNC_PARA_TYPE_SIGN64
				arrange __type_para_, dest
				compute __type_size_, 8
				jump _end
			jump _end
		type_numericx:
			; display 27 bappend "[1;31m Here at 'type_numericx'" bappend 27 bappend "[0m "
			; match one= two, dest			; complex type for forced size parameters
			; jyes type_forced
			nx_ret:
				arrange __type_id_, FUNC_PARA_TYPE_EQUATION
				compute __type_size_, 0
				local tmpresult
				compute tmpresult, + (i)
			eq_type_float:
				check tmpresult eqtype 0.0
				jno eq_type_str
				arrange __type_id_, FUNC_PARA_TYPE_FLOAT
				arrange __type_para_, i
				compute __type_size_, 8
				jump _end
			eq_type_str:
				check i eqtype ''
				jno eq_type_reg
				compute i, i
				arrange __type_para_, tmpresult
				jump _end
			eq_type_reg:
				local info, class
				compute info, 1 metadataof dest
				compute class, 1 metadataof info
				check class relativeto x86.reg
				jyes type_address
				arrange __type_para_, i
				jump _end
			jump _end
		type_other:
			; display 27 bappend "[1;31m Here at 'type_other'" bappend 27 bappend "[0m "
			jump _end
		type_ptrptr:
			arrange __type_id_, FUNC_PARA_TYPE_PTRPTR
			arrange __type_para_, i
			compute __type_size_, 0
			jump _end
		type_x86_reg:
			; display 27 bappend "[1;31m Here at 'type_x86_reg'" bappend 27 bappend "[0m "
			x86_reg:
				check class relativeto x86.reg
				jno sse_reg
				arrange __type_para_, dest
				compute __type_size_, 0 scaleof class
				regq:
					check __type_size_ = 8
					jno regd
					arrange __type_id_, FUNC_PARA_TYPE_REGQWORD
					jump _end
				regd:
					check __type_size_ = 4
					jno regw
					arrange __type_id_, FUNC_PARA_TYPE_REGDWORD
					jump _end
				regw:
					check __type_size_ = 2
					jno regb
					arrange __type_id_, FUNC_PARA_TYPE_REGWORD
					jump _end
				regb:
					check __type_size_ = 1
					jno regend
					arrange __type_id_, FUNC_PARA_TYPE_REGLBYTE
				regend:
					jump _end
			sse_reg:
				check info relativeto SSE.reg
				jno mmx_reg
				arrange __type_para_, dest
				arrange __type_id_, FUNC_PARA_TYPE_REGXMM
				compute __type_size_, 16
				jump _end
			mmx_reg:
				check info relativeto MMX.reg
				jno st_reg
				arrange __type_para_, dest
				arrange __type_id_, FUNC_PARA_TYPE_REGMM
				compute __type_size_, 8
				jump _end
			st_reg:
				check info relativeto st
				jno avx_reg
				arrange __type_para_, dest
				arrange __type_id_, FUNC_PARA_TYPE_REGFPU
				compute __type_size_, 10
				jump _end
			avx_reg:
				check info relativeto AVX.reg
				jno avx512_reg
				arrange __type_para_, dest
				arrange __type_id_, FUNC_PARA_TYPE_REGYMM
				compute __type_size_, 32
				jump _end
			avx512_reg:
				check info relativeto AVX_512.reg
				jno x86_sreg
				arrange __type_para_, dest
				arrange __type_id_, FUNC_PARA_TYPE_REGZMM
				compute __type_size_, 64
				jump _end
			x86_sreg:
				check info relativeto x86.sreg
				jno x86_creg
				arrange __type_para_, dest
				arrange __type_id_, FUNC_PARA_TYPE_REGDWORD
				compute __type_size_, 4
				jump _end
			x86_creg:
				check info relativeto x86.crx
				jno x86_dreg
				arrange __type_para_, dest
				arrange __type_id_, FUNC_PARA_TYPE_REGQWORD
				compute __type_size_, 8
				jump _end
			x86_dreg:
				check info relativeto x86.drx
				jno _end
				arrange __type_para_, dest
				arrange __type_id_, FUNC_PARA_TYPE_REGQWORD
				compute __type_size_, 8
				jump _end
			jump _end
		type_stringz:
			; display 27 bappend "[1;31m Here at 'type_stringz'" bappend 27 bappend "[0m "
			arrange __type_para_, dest
			arrange __type_id_, FUNC_PARA_TYPE_STRING
			compute __type_size_, 8
			jump _end
		type_variable:
			; display 27 bappend "[1;31m Here at 'type_variable'" bappend 27 bappend "[0m "
			transform dest
			jyes tv_symbolic
			local i, symbol
			arrange i, dest
			compute i, i
			jump type_number
			tv_symbolic:
				arrange i, dest
				arrange symbol, =default.=type.=address.i
				check defined symbol
				jyes type_address
				check i relativeto x86.reg
				jyes type_other
				jump type_numericx
			jump _end
		invalid:
			; display 27 bappend "[1;31m Here at 'invalid'" bappend 27 bappend "[0m "
			check defined dest
			jno i_invalidate
			match complex= expr, dest
			jno type_other
			i_invalidate:
				arrange __type_id_, FUNC_PARA_TYPE_UNKNOWN
				arrange __type_para_, 65535
				compute __type_size_, 65535
			; jump _end
		_end:
			local sz, id, param
			arrange param, __type_para_
			compute sz, __type_size_
			arrange id, __type_id_
			stringify param
			arrange sz, sz
			stringify sz
			stringify id
			display 1B27h bappend "[38;5;224m" bappend tmp1 bappend 27 bappend "[0m" \
				bappend "' size: " bappend sz bappend " type: " bappend 27 bappend "[38;5;219m"
			call show_parameter_type_name, __type_id_
			display 27 bappend "[0m" bappend 10
	end calminstruction

	calminstruction show_parameter_type_name id*
			transform	id
			local		ID
			arrange		ID, id
			compute		ID, ID
		N0:	check		ID = 0
			jno			N1
			display		'empty'
			exit
		N1:	check		ID = 1
			jno			N2
			display		'memory data'
			exit
		N2:	check		ID = 2
			jno			N3
			display		'recursive pointer to data'
			exit
		N3:	check		ID = 3
			jno			N5
			display		'effective address'
			exit
		N5:	check		ID = 5
			jno			N6
			display		'numeric expression'
			exit
		N6:	check		ID = 6
			jno			N7
			display		'signed 32-bit number'
			exit
		N7:	check		ID = 7
			jno			N8
			display		'signed 64-bit number'
			exit
		N8:	check		ID = 8
			jno			N9
			display		'foced byte'
			exit
		N9:	check		ID = 9
			jno			N10
			display		'forced word'
			exit
	   N10:	check		ID = 10
			jno			N11
			display		'forced dword'
			exit
	   N11:	check		ID = 11
			jno			N12
			display		'forced qword'
			exit
	   N12:	check		ID = 12
			jno			N14
			display		'forced tword'
			exit
	   N14:	check		ID = 14
			jno			N15
			display		'boolean'
			exit
	   N15:	check		ID = 15
			jno			N16
			display		'numeric NULL'
			exit
	   N16:	check		ID = 16
			jno			N17
			display		'float point number'
			exit
	   N17:	check		ID = 17
			jno			N18
			display		'string'
			exit
	   N18:	check		ID = 18
			jno			N19
			display		'32-bit number'
			exit
	   N19:	check		ID = 19
			jno			N20
			display		'64-bit number'
			exit
	   N20:	check		ID = 20
			jno			N22
			display		'byte register'
			exit
	   N22:	check		ID = 22
			jno			N23
			display		'word register'
			exit
	   N23:	check		ID = 23
			jno			N24
			display		'dword register'
			exit
	   N24:	check		ID = 24
			jno			N25
			display		'qword register'
			exit
	   N25:	check		ID = 25
			jno			N26
			display		'XMM register'
			exit
	   N26:	check		ID = 26
			jno			N27
			display		'YMM register'
			exit
	   N27:	check		ID = 27
			jno			N28
			display		'ZMM register'
			exit
	   N28:	check		ID = 28
			jno			N29
			display		'MMX register'
			exit
	   N29:	check		ID = 29
			jno			N30
			display		'FPU register'
			exit
	   N30:	check		ID = 30
			jno			N31
			display		'Control register'
			exit
	   N31:	check		ID = 31
			jno			N33
			display		'Debug register'
			exit
	   N33:	check		ID = 33
			jno			N34
			display		'complex string'
			exit
	   N34:	check		ID = 34
			jno			N35
			display		'forced float'
			exit
	   N35:	check		ID = 35
			jno			N36
			display		'forced double'
			exit
	   N36:	check		ID = 36
			jno			N37
			display		'FPU π constant'
			exit
	   N37:	check		ID = 37
			jno			NZZ
			display		'escaped string'
			exit
	   NZZ:	display		'parameter type error'
	end calminstruction



	PUT_ANON_DATA_STRING	:= 9
	PUT_ANON_DATA_STRINGZ	:= 7
	PUT_ANON_DATA_STRINGN   := 11
	__anon_data_count_		= 0
	define _anon_data_curr_

	calminstruction put_anon_data dtype*, data*&
		_start:
			local cmd1, cmd2, cmd3, i
			check __RDATA_ONLINE__
			jno _nextD
			arrange cmd1, =virtual =__rdata_ptr
			jump _put_data
		_nextD:
			check __DATA_ONLINE__
			jno _nextC
			arrange cmd1, =virtual =__data_ptr
			jump _put_data
		_nextC:
			check __CODE_ONLINE__
			jno _err_context
			arrange cmd1, =virtual =__code_ptr
			jump _put_data
		_err_context:
			err "undefined anonymous data context: needed _code, _rdata or _data to work"
			exit

		_put_data:
			arrange cmd3, =end =virtual
			assemble cmd1
			arrange i, __anon_data_count_
			transform data
		_data_strz:
			check dtype = PUT_ANON_DATA_STRINGZ
			jno _data_str
			arrange cmd2, ..=_anon_data_#i =db data, 0
			jump _end
		_data_str:
			check dtype = PUT_ANON_DATA_STRING
			jno _data_strn
			arrange cmd2, ..=_anon_data_#i =db data
			jump _end
		_data_strn:
			check dtype = PUT_ANON_DATA_STRINGN
			jno _data_dd
			_3n2s:
				match \=n str1 \=n str2 \=n, data
				jno _2n2s
				arrange cmd2, ..=_anon_data_#i =db 10, str1, 10, str2, 10, 0
				jump _end
			_2n2s:
				match \=n str1 \=n str2, data
				jno _2n1s
				arrange cmd2, ..=_anon_data_#i =db 10, str1, 10, str2, 0
				jump _end
			_2n1s:
				match \=n str1 \=n, data
				jno _2s2n
				arrange cmd2, ..=_anon_data_#i =db 10, str1, 10, 0
				jump _end
			_2s2n:
				match str1 \=n str2 \=n, data
				jno _nn1s
				arrange cmd2, ..=_anon_data_#i =db str1, 10, str2, 10, 0
				jump _end
			_nn1s:
				match \=n \=n str1, data
				jno _1snn
				arrange cmd2, ..=_anon_data_#i =db 10, 10, str1, 0
				jump _end
			_1snn:
				match str1 \=n \=n, data
				jno _2s1n
				arrange cmd2, ..=_anon_data_#i =db str1, 10, 10, 0
				jump _end
			_2s1n:
				match str1 \=n str2, data
				jno _1n1s
				arrange cmd2, ..=_anon_data_#i =db str1, 10, str2, 0
				jump _end
			_1n1s:
				match \=n str1, data
				jno _1s1n
				arrange cmd2, ..=_anon_data_#i =db 10, str1, 0
				jump _end
			_1s1n:
				match str1 \=n, data
				jno _snerr
				arrange cmd2, ..=_anon_data_#i =db str1, 10, 0
				jump _end
			_snerr:
				err "unsupported string \n pattern"
				exit
		_data_dd:
			check dtype eq dword
			jno _data_dq
			arrange cmd1, =align 4
			arrange cmd2, ..=_anon_data_#i =dd data
			jump _end
		_data_dq:
			check dtype eq qword
			jno _data_dt
			arrange cmd1, =align 8
			arrange cmd2, ..=_anon_data_#i =dq data
			jump _end
		_data_dt:
			check dtype eq tword
			jno _dataerr
			arrange cmd1, =align 8
			arrange cmd2, ..=_anon_data_#i =dt data
			jump _end
		_dataerr:
			err "unsupported anonymous data type"
			exit

		_end:
			match =align val, cmd1
			jno _no_align
			assemble cmd1
			_no_align:
				assemble cmd2
				arrange cmd1, =_anon_data_curr_ == ..=_anon_data_#i
				assemble cmd1
			assemble cmd3
			compute __anon_data_count_, __anon_data_count_ + 1
	end calminstruction



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
            else if __type_id_ = FUNC_PARA_TYPE_STRINGN
				if psize = qword
					put_anon_data PUT_ANON_DATA_STRINGN, parameter
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
            else if __type_id_ = FUNC_PARA_TYPE_STRINGN
				if psize = qword
					put_anon_data PUT_ANON_DATA_STRINGN, parameter
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
		; irpv param, parameter
		; 	indx %%
		; 	display "parameter '", `param, "' "
		; 	irpv size, psize
		; 		indx %%
		; 		display "passed with psize: ", `size, 32
		; 		irpv ts, __type_size_
		; 			indx %%
		; 			if ts eqtype 0
		; 				repeat 1, val:ts
		; 					 display "type size: ", `val, 10
		; 				end repeat
		; 			else
		; 				display "type size: ", `ts, 10
		; 			end if
		; 			break
		; 		end irpv
		; 		break
		; 	end irpv
		; 	break
		; end irpv
	end macro



	; internal fastcall macro itself
	macro fastcall func, args&
		local stackalloc, xmmcount, memcount, regcount, xmmargs
		stackalloc	= 0

		regcount = func__.func.par0.regcnt
		xmmcount = func__.func.par0.xmmcnt
		memcount = func__.func.par0.memcnt
		__mexpect_ = func__.func.par0.memcnt	; Memory class expected memory "parameter counter"
												; (error control)
		xmmargs = 0		; vararg number of xmm arguments
		__fpu_ne_ = 0	; signal to issue emms prior to call function

		if func__.func.par0.isVararg > func__.func.par0.attr
			if (memcount mod 2)
				if func__.func.par0.jmp
					stackalloc = memcount
				else
					sub rsp, 8
					stackalloc = memcount + 1
				end if
			else
				if func__.func.par0.jmp
					sub rsp, 8
					stackalloc = memcount + 1
				else
					stackalloc = memcount
				end if
			end if
		end if
		if func__.func.par0.attr > 0
			iterate arg, args	; ATTENTION: iterate decapsulates '<>' off parameter!
				if % = 1
					if func__.func.par0.isVararg > func__.func.par0.attr ; no vararg condition
						if %% <> func__.func.par0.attr
							err "Function '", `func, "()' number of passed parameters is wrong.", 10
						end if
					end if
				end if
				if (%% - % + 1) < func__.func.par0.isVararg
					indx %% - % + 1
					repeat 1, r:regcount, x:xmmcount, m:memcount, i: %% - % + 1
						if func__.func.par#i.class = SYSTEMV_PARA_CLASS_REGISTER
							testtype arg
							put_parameter2 r, SYSTEMV_PARA_CLASS_REGISTER, \
								__type_para_, func__.#func.par#i.size
							regcount = regcount - 1
						else if func__.func.par#i.class = SYSTEMV_PARA_CLASS_XMM
							testtype arg
							put_parameter2 x, SYSTEMV_PARA_CLASS_XMM, __type_para_, \
								func__.func.par#i.size
							xmmcount = xmmcount - 1
						else if func__.func.par#i.class = SYSTEMV_PARA_CLASS_MEMORY
							testtype arg
							put_parameter2 m, SYSTEMV_PARA_CLASS_MEMORY, __type_para_, \
								func__.func.par#i.size
							memcount = memcount - 1
						else if func__.func.par#i.class = SYSTEMV_PARA_CLASS_LDOUBLE
							testtype arg
							put_parameter2 func__.func.par#i.align, SYSTEMV_PARA_CLASS_LDOUBLE, \
								__type_para_, func__.func.par#i.size
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
								__type_id_ = FUNC_PARA_TYPE_REGMM | __type_id_ = FUNC_PARA_TYPE_STRINGN
								if regcount < 6
									regcount = regcount + 1
									totalcount = totalcount + 1
									repeat 1, i:%, r:regcount
										define __vararg.par#i.class SYSTEMV_PARA_CLASS_REGISTER
										define __vararg.par#i.count r
										if __type_id_ = FUNC_PARA_TYPE_ADDR
											__vararg.par#i.size = __type_size_	; trust testtype parameter
										else
											define __vararg.par#i.size qword
										end if
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
										if __type_id_ = FUNC_PARA_TYPE_ADDR
											__vararg.par#i.size = __type_size_	; correctly detects 32|64 address size
										else
											define __vararg.par#i.size qword
										end if
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
		if func__.func.par0.mode
			if func__.func.par0.jmp
				if func__.func.par0.isVararg <= func__.func.par0.attr
					if xmmargs > 0
						mov al, xmmargs
					else
						xor al, al
					end if
				end if
				if __fpu_ne_
					emms
				end if
				if defined func__.func.par0.extern
					if defined __ELF_MODE_STATIC__
						jmp [__imp.func]
					else if defined __ELF_MODE_DYNAMIC__
						jmp [GOT.func]
					end if
				else
						jmp [func]
				end if
			else
				if func__.func.par0.isVararg <= func__.func.par0.attr
					if xmmargs > 0
						mov al, xmmargs
					else
						xor al, al
					end if
				end if
				if __fpu_ne_
					emms
				end if
				if defined func__.func.par0.extern
					if defined __ELF_MODE_STATIC__
						call [__imp.func]
					else if defined __ELF_MODE_DYNAMIC__
						call [GOT.func]
					end if
				else
					call [func]
				end if
				if stackalloc > 0
					add rsp, stackalloc * 8
				end if
			end if
		else
			if func__.func.par0.jmp
				if func__.func.par0.isVararg <= func__.func.par0.attr
					if xmmargs > 0
						mov al, xmmargs
					else
						xor al, al
					end if
				end if
				if __fpu_ne_
					emms
				end if
				if defined func__.func.par0.extern
					if defined __ELF_MODE_STATIC__
						jmp proto.func
					else if defined __ELF_MODE_DYNAMIC__
						jmp PLT.func
					end if
				else
					jmp func
				end if
			else
				if func__.func.par0.isVararg <= func__.func.par0.attr
					if xmmargs > 0
						mov al, xmmargs
					else
						xor al, al
					end if
				end if
				if __fpu_ne_
					emms
				end if
				if defined func__.func.par0.extern
					if defined __ELF_MODE_STATIC__
						call proto.func
					else if defined __ELF_MODE_DYNAMIC__
						call PLT.func
					end if
				else
					call func
				end if
				if stackalloc > 0
					add rsp, stackalloc * 8
				end if
			end if
		end if
	end macro

	; internal macro that unbind parameters and sets it to variables
	calminstruction put_value dest, src
			transform	src
			jyes 		symbolic
			compute		src, src
	 symbolic:
			publish		dest, src
	end calminstruction



	if defined __ELF_MODE_STATIC__

		; External macro to define needed libraries
		macro library? &names&
			namespace __imp
				irp library, names
					define needed@dynamic library
				end irp
			end namespace
		end macro

		; External macro to add a custom library path to load libraries from
		__RUNPATH_COUNT__ = 0
		macro libpath? &path
			__RUNPATH_COUNT__ = __RUNPATH_COUNT__ + 1
			if __RUNPATH_COUNT__ > 1
				err "only one custom library path is valid"
			else
				namespace __imp
					define __LIB_RUNPATH__ path
				end namespace
			end if
		end macro

		; internal macro to parse all imported data and functions
		macro extern2_
			namespace __imp
				segment interpreter readable
				db '/lib64/ld-linux-x86-64.so.2', 0
				align 8				; This only accepts 0's as padding bytes, executable fails otherwise
				irpv xfunc, __IMPORT_LIST_
					display "Importing: ", `xfunc, 10
				end irpv
				importv __IMPORT_LIST_
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
				define func__.function.par0.extern 1
				if used proto.function
					proto.function: jmp [__imp.function]
					define __IMPORT_LIST_ function
				end if
			else match =noreturn? =proto? function=, specs, line
				if __ext_dcount_ = 0
					segment readable executable
				end if
				__ext_dcount_ = __ext_dcount_ + 1
				proto function, specs
				define func__.function.par0.extern 1
				define func__.function.par0.jmp 1
				if used proto.function
					proto.function: jmp [__imp.function]
					define __IMPORT_LIST_ function
				end if
			else match =indirect? =proto? function=, specs, line
				__ext_icount_ = __ext_icount_ + 1
				proto function, specs
				define func__.function.par0.extern 1
				define func__.function.par0.mode 1
				if used __imp.function
					define __IMPORT_LIST_ function
				end if
			else match =noreturn? =indirect? =proto? function=, specs, line
				__ext_icount_ = __ext_icount_ + 1
				proto function, specs
				define func__.function.par0.extern 1
				define func__.function.par0.jmp 1
				define func__.function.par0.mode 1
				if used __imp.function
					define __IMPORT_LIST_ function
				end if
			else match =indirect? =noreturn? =proto? function=, specs, line
				__ext_icount_ = __ext_icount_ + 1
				proto function, specs
				define func__.function.par0.extern 1
				define func__.function.par0.jmp 1
				define func__.function.par0.mode 1
				if used __imp.function
					define __IMPORT_LIST_ function
				end if
			else match =data?= impdata, line
				local temp
				define temp line
				match =data? list, temp
					iterate symbol, list
						if used symbol
							define __IMPORT_LIST_ symbol
							define symbol __imp.symbol		; Allows symbol to reference __imp.symbol
						end if
					end iterate
				else
					err "Invalid extern argument. Usage: ext data symbol1, symbol2, ...", 10
				end match
			else
				ext line
			end match
		end macro

	else if defined __ELF_MODE_DYNAMIC__

		macro ext? line&
			match =proto? function=, specs, line
				proto function, specs
				define func__.function.par0.extern 1
				if used PLT?.function
					extrn function:8
					display "Importing: ", `function, 10
				else if used GOT?.function
					extrn function:8
					display "Importing: ", `function, 10
				else if used function
					extrn function:8
					display "Importing: ", `function, 10
				end if
			else match =noreturn? =proto? function=, specs, line
				proto function, specs
				define func__.function.par0.extern 1
				define func__.function.par0.jmp 1
				if used PLT?.function
					extrn function:8
					display "Importing: ", `function, 10
				else if used GOT?.function
					extrn function:8
					display "Importing: ", `function, 10
				else if used function
					extrn function:8
					display "Importing: ", `function, 10
				end if
			else match =indirect? =proto? function=, specs, line
				proto function, specs
				define func__.function.par0.extern 1
				define func__.function.par0.mode 1
				if used GOT?.function
					extrn function:8
					display "Importing: ", `function, 10
				else if used function
					extrn function:8
					display "Importing: ", `function, 10
				end if
			else match =noreturn? =indirect? =proto? function=, specs, line
				proto function, specs
				define func__.function.par0.extern 1
				define func__.function.par0.jmp 1
				define func__.function.par0.mode 1
				if used GOT?.function
					extrn function:8
					display "Importing: ", `function, 10
				else if used function
					extrn function:8
					display "Importing: ", `function, 10
				end if
			else match =indirect? =noreturn? =proto? function=, specs, line
				proto function, specs
				define func__.function.par0.extern 1
				define func__.function.par0.jmp 1
				define func__.function.par0.mode 1
				if used GOT?.function
					extrn function:8
					display "Importing: ", `function, 10
				else if used function
					extrn function:8
					display "Importing: ", `function, 10
				end if
			else match =data?= impdata, line
				local temp
				define temp line
				match =data? list, temp
					iterate symbol, list
						match sym:size, symbol
							if used sym
								extrn sym:size
								display "Importing: ", `sym, 10
							else if used GOT?.sym
								extrn sym:size
								display "Importing: ", `sym, 10
							end if
						else
							if used symbol
								extrn symbol
								display "Importing: ", `symbol, 10
							else if used GOT?.symbol
								extrn symbol
								display "Importing: ", `symbol, 10
							end if
						end match
					end iterate
				else
					err "Invalid extern argument. Usage: ext data symbol1, symbol2, ...", 10
				end match
			else
				ext line
			end match
		end macro

	end if

	macro indirect? line&
		match =proto? function=, specs, line
			proto function, specs
			define func__.function.par0.mode 1
		else match =noreturn? =proto? function=, specs, line
			proto function, specs
			define func__.function.par0.jmp 1
			define func__.function.par0.mode 1
		else
			indirect line
		end match
	end macro

	macro noreturn? line&
		match =proto? function=, specs, line
			proto function, specs
			define func__.function.par0.jmp 1
		else match =indirect? =proto? function=, specs, line
			proto function, specs
			define func__.function.par0.jmp 1
			define func__.function.par0.mode 1
		else
			noreturn line
		end match
	end macro

	macro alias? beautiful*, ugly*
		define func__.ugly.par0.aliased 1
		if func__.ugly.par0.attr > 0
			macro ?beautiful params&
				match (param), params
					fastcall ugly, param
				else
					err "fastcall syntax error: ", `beautiful, " ", `params
				end match
			end macro
		else
			macro ?beautiful params&
				match (), params
					fastcall ugly
				else
					err "fastcall syntax error: ", `beautiful, " ", `params
				end match
			end macro
		end if
		if ~ func__.ugly.par0.mode	; aliased internal function is freed from the same as label macro name!
			purge ugly
		end if
	end macro



	define vararg -1
	define none 0
	define float 0.32
	define double 0.64
	define l_double tword
	define float32 float
	define float64 double
	define float80 l_double

	macro proto? func*, args&
		local xmmcnt, regcnt, memcnt, ldcnt, totalcnt, nsfunc, ldalign, aliased
		xmmcnt = 0
		regcnt = 0
		memcnt = 0
		ldalign = 0
		ldcnt = 0
		totalcnt = 0
		aliased = 0

		define func__.func.par0.isVararg 0
		define func__.func.par0.jmp 0
		define func__.func.par0.mode 0

		iterate arg, args
			match =alias?= pretty, arg	; 'alias' should be the last parameter!
				aliased = 1				; Only pretty() is available as a macro here
				define func__.func.par0.aliased 1
				if defined __ELF_MODE_STATIC__
					if used __imp.func
						display "Alias: '", `func, "' as '", `pretty, "()'", 10
					end if
				else if defined __ELF_MODE_DYNAMIC__
					if used __imp.func
						display "Alias: '", `func, "' as '", `pretty, "()'", 10
					end if
				end if
				macro ?pretty params&
					if totalcnt = 0
						match (), params
							fastcall func	; aliased resolve to func instead of _func
						else
							err "fastcall syntax error: ", `func, " ", `params
						end match
					else
						match (param), params
							fastcall func, param
						else
							err "fastcall syntax error: ", `func, " ", `params
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
						define func__.func.par#k.class SYSTEMV_PARA_CLASS_REGISTER
						define func__.func.par#k.count j
						define func__.func.par#k.size arg
						define func__.func.regpar#j.size arg	; index regs separately
					end repeat
				else
					totalcnt = totalcnt + 1
					memcnt = memcnt + 1
					repeat 1, i:totalcnt, j:memcnt, k:%
						define func__.func.par#k.class SYSTEMV_PARA_CLASS_MEMORY
						define func__.func.par#k.count j
						define func__.func.par#k.size arg
						define func__.func.mempar#j.size arg	; index mems separately
					end repeat
				end if
			else if arg eq float | arg eq double
				if xmmcnt <= 7
					totalcnt = totalcnt + 1
					xmmcnt = xmmcnt + 1
					repeat 1, i:totalcnt, j:xmmcnt, k:%
						define func__.func.par#k.class SYSTEMV_PARA_CLASS_XMM
						define func__.func.par#k.count j
						define func__.func.par#k.size arg
						define func__.func.xmmpar#j.size arg	; index xmms separately
					end repeat
				else
					totalcnt = totalcnt + 1
					memcnt = memcnt + 1
					repeat 1, i:totalcnt, j:memcnt, k:%
						define func__.func.par#k.class SYSTEMV_PARA_CLASS_MEMORY
						define func__.func.par#k.count j
						define func__.func.par#k.size arg
						define func__.func.mempar#j.size arg
					end repeat
				end if
			else if arg eq tword
				totalcnt = totalcnt + 1
				ldalign = memcnt
				ldcnt = ldcnt + 1
				memcnt = memcnt + 2 + (memcnt mod 2)	; it must be 16 byte aligned
				repeat 1, i:totalcnt, j:ldcnt, k:%, l:memcnt, a:ldalign
					define func__.func.par#k.class SYSTEMV_PARA_CLASS_LDOUBLE ; (THIS and 3) xor MEM = 0
					define func__.func.par#k.count l
					define func__.func.par#k.size arg
					define func__.func.par#k.align a	; Previous value as align helper (reverse mode prediction)
					define func__.func.ldpar#j.size arg
					define func__.func.mempar#l.size arg
				end repeat
			else if arg eq vararg
				totalcnt = totalcnt + 1
				repeat 1, i:totalcnt, k:%
					define func__.func.par#k.class SYSTEMV_PARA_CLASS_VARARG
					define func__.func.par#k.count k
					define func__.func.par#k.size vararg
					define func__.func.par0.isVararg k	; index of vararg parameter
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
					define func__.func.par#k.class SYSTEMV_PARA_CLASS_NONE
					define func__.func.par#k.count 1
					define func__.func.par#k.size none
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
		define func__.func.par0.attr totalcnt
		define func__.func.par0.memcnt memcnt
		define func__.func.par0.regcnt regcnt
		define func__.func.par0.xmmcnt xmmcnt
		define func__.func.par0.ldcnt ldcnt
		if func__.func.par0.isVararg = 0
			func__.func.par0.isVararg = totalcnt + 1	; vararg > total for no vararg
		end if
		if ~ aliased
			define func__.func.par0.aliased 0
			macro func params&
				if totalcnt = 0
					match (), params
						fastcall func
					else match := line, params	; At function itself, just
						func:
						line
					else						; do its stuff
						func params
					end match
				else
					match (param), params
						fastcall func, param
					else match := line, params
						func:
						line
					else
						func params
					end match
				end if
			end macro
		end if
	end macro

end if													; ### ### END OF FASTCALL3 CODE ### ### ###


; :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: :
; Below are some useful macros already bundled with this package:  ;
; :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: ;


if ~ defined __ANON_LABEL_INCLUDED__
	define __ANON_LABEL_INCLUDED__
	define __ANON_LABEL_INCLUDED__

	; All of those @@@, @@ and @x macros don't interact each other!
	; They can be used independently, adding choice and versatility.

	_desired_levels_ = 16			; number of available anon labels (both @xf/@xb or @fx @bx)



	; DEPRECATED (revised and updated anyways)
	; @@@ single level anonymous label macro: with its jump selectors:
	; @@b jump to the @@@ label above; @@f jump to the @@@ label below.
	__lbl_count_3@__ = 0
	macro @@@ line&
		local x
		x = __lbl_count_3@__
		repeat 1, i:x, j:x + 1
			@@b? equ ..@@@_UL_#i
			@@f? equ ..@@@_UL_#j
			__lbl_count_3@__ = j
			..@@@_UL_#i: line
		end repeat
	end macro
	@@@
	restore @@b?



	; @@ anonymous label macro: @bx jumps x @@ labels above, @fx jumps x @@ labels below
	; x ranges between 1 to 16, by default (_desired_levels_ controls this limit)
	; NOTE: @b = @b1 and @f = @f1, for added flexibility and beauty.
	__lbl_count_ = _desired_levels_

	calminstruction init_@fx
			local		i, j, fsym, fval

			compute		i, 1
			compute		j, __lbl_count_

			arrange		fsym, =@f?
			arrange		fval, ..=@@_UL_#j
			publish		fsym, fval

	  loop: arrange		fsym, =@f#i#?
			arrange		fval, ..=@@_UL_#j
			publish		fsym, fval
			compute		i, i + 1
			compute		j, j + 1
			check		i <= _desired_levels_
			jyes		loop
	end calminstruction

	calminstruction @@ line&
			local		h, i, j, sym, val

			compute		i, __lbl_count_ - (_desired_levels_ - 1)
			compute		h, _desired_levels_
			compute		j, 1

	 loopb: arrange		sym, =@b#h#?
			arrange		val, ..=@@_UL_#i
			publish		sym, val
			compute		h, h - 1
			compute		i, i + 1
			compute		j, j + 1
			check		_desired_levels_ >= j
			jyes		loopb

			arrange		sym, =@b?
			arrange		val, ..=@@_UL_#__lbl_count_
			publish		sym, val

			compute		h, i

			arrange		sym, =@f?
			arrange		val, ..=@@_UL_#i
			publish		sym, val

			compute		j, 1

	 loopf: arrange		sym, =@f#j#?
			arrange		val, ..=@@_UL_#i
			publish		sym, val
			compute		i, i + 1
			compute		j, j + 1
			check		j <= _desired_levels_
			jyes		loopf

			arrange		sym, ..=@@_UL_#__lbl_count_: line
			assemble	sym

			compute		__lbl_count_, h
	end calminstruction

	init_@fx
	purge init_@fx



	; Spawns @1 to @16 anonymous label macros, with its respectives:
	; @1b to @16b and @1f to @16f. Similar to original fasm2 @n extended macro.
	repeat _desired_levels_
		__lbl_count_#%#__ = 0
		calminstruction @#% line&
				local		i, sym, val
				compute		i, __lbl_count_#%#__
				arrange		sym, =@#%#=b?
				arrange		val, ..=@#%#=_UL_#i
				publish		sym, val
				compute		i, i + 1
				arrange		sym, =@#%#=f?
				arrange		val, ..=@#%#=_UL_#i
				publish		sym, val
				compute		__lbl_count_#%#__, i
				compute		i, i - 1
				arrange		sym, ..=@#%#=_UL_#i: line
				assemble	sym
		end calminstruction
		@#%
		restore @#%#b?
	end repeat

else
	err "duplicated inclusion of 'anon_label' statements"
end if



if ~ defined __STANDARD_MACRO_PACKAGE_INCLUDED__
	define __STANDARD_MACRO_PACKAGE_INCLUDED__
	define __STANDARD_MACRO_PACKAGE_INCLUDED__



	; A recent change at fasm2 headers (commit '2b683a2') add size checking
	; to push instruction: here, we preserve the previous behavior,
	; which is default qword to 64-bit mode (the only usage scenario
	; for this macro toolkit), when size isn't specified.
	;
	macro push? what*&
		match size [mem], what
			push size [mem]
		else match [mem], what
			push qword [mem]    ; now, default size is 'qword'
		else
			push what
		end match
	end macro



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
			struc (lb) nam? data*&
				align val
				match =* rsv, data
					. rtyp rsv
				else
					. typ data
				end match
				match .symbol, lb
				else match ., lb
				else match ?symbol, lb
					lns_attach_to_root 35, symbol
				else
					lns_attach_to_root 35, lb
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



	__ENTRY_COUNT__ = 0
	struc (point) entry? &line&   ; Allow: '_code Start entry endbr64' as entry point
		match .symbol, point
			err "for the sake of stability, do not use subordinate label at entry point"
		end match
		if __ENTRY_COUNT__
			err "more than one entry point is not allowed"
		else
			if defined __ELF_MODE_STATIC__
				entry point
			else if defined __ELF_MODE_DYNAMIC__
				public point as '_start' ; don't need to specify '-e <entryname>' to linker anymore
			else
				entry point
			end if
			match := instruction, line
				point:
				instruction
			else match :, line
				point:
			else
				point:
				line
			end match
			__ENTRY_COUNT__ = __ENTRY_COUNT__ + 1
			lns_attach_to_root 93, point
			define default.type.address.point	; mark entry name as address type label
		end if
	end struc

	; entry macro wrapper to support this statement in both dynamic and static ELF
	macro entry? point*
		if __ENTRY_COUNT__
			err "more than one entry point is not allowed"
		else
			match .symbol, point
				err "for the sake of stability, do not use subordinate label at entry point"
			else match $, point
				Default_User_Space_Fallback_Root_Label:
				if defined __ELF_MODE_DYNAMIC__
					public $ as '_start'
				else if defined __ELF_MODE_STATIC__
					entry $
				end if
			else
				if defined __ELF_MODE_DYNAMIC__
					public point as '_start'
				else if defined __ELF_MODE_STATIC__
					entry point
				end if
			end match
			__ENTRY_COUNT__ = __ENTRY_COUNT__ + 1
		end if
	end macro

	macro Main line&        ; self align Main label to be used with libc.StartMain
		align 4
		match := code, line
			?Main:
			code
		else match :, line
			?Main:
		else
			err "syntax error"
		end match
	end macro



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
	macro enum? start, names&
		match =step= val, start
			define __ENUM_STEP__ val
		else
			if ~ start eqtype 0
				err "invalid 'enum' enumeration macro usage"
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



else
	err "duplicated inclusion of 'stdmacros' statements"
end if
