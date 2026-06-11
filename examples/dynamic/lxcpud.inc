format ELF64

include 'fastcall.inc'
include 'stdmacros.inc'

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
end struct

struct FILEHEADER
  .NumProcs      dd ?
  .globalMinClk  dd ?
  .globalMaxClk  dd ?
  .OffsetGov     dd ?
  .OffsetEnp     dd ?
  .OffsetCPUData dd ?
end struct

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
                rq 3
end struct

struct TIMESPEC
  .tv_sec       dq ?
  .tv_nsec      dq ?
end struct

MAX_FILE_SIZE = 65535

O_RDONLY = 0o
O_WRONLY = 1o

