format ELF64 executable 3 at 100000h
entry Start

; :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

; A simple struct/ends structure macro that allows to use
;   struct NAME.child as displacement, and also gets size
;   information based on NAME
;
; Example:      mov eax, [rsi+CPUDATA.clkMax]
;               add r10, sizeof(CPUDATA)
;
macro struct? name
     define __ACTUAL__ name
     esc struc name
     label . : .size - .
end macro

macro ends?!
     .size:
     esc end struc
     virtual at 0
          match a, __ACTUAL__
               a a
          end match
     end virtual
end macro
;
; :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
include 'fastcall_v1.inc'
include 'anon_label.inc'

library 'libc.so.6'

; Prototypes
ext proto close, dword
ext noreturn proto exit, dword
ext proto fputs, qword, qword
ext proto free, qword
ext proto fstat, dword, qword
ext proto malloc, qword
ext proto open, qword, dword, dword
ext proto perror, qword
ext proto read, dword, qword, qword
ext proto snprintf, qword, qword, qword, vararg
ext proto write, dword, qword, qword
ext proto __errno_location, none, alias errno
ext data stdin, stdout, stderr

struct CPUDATA
  .clkMin       dd ?
  .clkMax       dd ?
  .off_clkProf  dd ?
  .off_enProf   dd ?
  .flags        db ?
                rb 7
ends

struct FILEHEADER
  .NumProcs      dd ?
  .globalMinClk  dd ?
  .globalMaxClk  dd ?
  .OffsetGov     dd ?
  .OffsetEnp     dd ?
  .OffsetCPUData dd ?
ends

struct STAT
  .st_dev       dq ?
  .st_ino       dq ?
  .st_nlink     dq ?
  .st_mode      dd ?
  .st_uid       dd ?
  .st_gid       dd ?
                dd ?
  .st_rdev      dq ?
  .st_size      dq ?
  .st_blksize   dq ?
  .st_blocks    dq ?
  .statim       TIMESPEC
  .stmtim       TIMESPEC
  .stctim       TIMESPEC
ends

struct TIMESPEC
  .tv_sec       dq ?
  .tv_nsec      dq ?
ends

MAX_FILE_SIZE = 65535

O_RDONLY = 0o
O_WRONLY = 1o

