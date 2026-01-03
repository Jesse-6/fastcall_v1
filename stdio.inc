library 'libc.so.6'

define AF_UNIX          1
define AF_INET          2
define AF_INET6         10

define EAGAIN          11
define EACCES          13
define EINVAL          22

define ECHO            0x00008
define ECHOE           0x00010
define ECHOK           0x00020
define ECHONL          0x00040
define ECHOCTL         0x00200
define ECHOPRT         0x00400
define ECHOKE          0x00800

define EXIT_FAILURE    1
define EXIT_SUCCESS    0

define FALSE           0

define F_GETLK         5
define F_SETLK         6
define F_SETLKW        7

define F_RDLCK         0
define F_WRLCK         1
define F_UNLCK         2

define ICANON          0x00002

define IPPROTO_ICMP     1
define IPPROTO_TCP      6
define IPPROTO_UDP      17
define IPPROTO_GRE      47
define IPPROTO_ICMPV6   58

define ITIMER_REAL     0
define ITIMER_VIRTUAL  1
define ITIMER_PROF     2

define LC_ALL          6

define NULL            0

define O_CLOEXEC       2000000o
define O_CREAT         100o
define O_DIRECTORY     200000o
define O_DSYNC         10000o
define O_EXCL          200o
define O_NOCTTY        400o
define O_NONBLOCK      4000o
define O_SYNC          (4000000o + O_DSYNC)
define O_RDONLY        0o
define O_RDWR          2o
define O_TMPFILE       (20000000o + O_DIRECTORY)
define O_TRUNC         1000o
define O_WRONLY        1o

define PRIO_PROCESS    0
define PRIO_PGRP       1
define PRIO_USER       2
define PRIO_MIN        -20
define PRIO_MAX        20
define PRIO_HIGHEST    PRIO_MIN
define PRIO_LOWEST     PRIO_MAX

define S_IRWXU  00700o  ; user (file owner) has read, write, and execute permission
define S_IRUSR  00400o  ; user has read permission
define S_IWUSR  00200o  ; user has write permission
define S_IXUSR  00100o  ; user has execute permission
define S_IRWXG  00070o  ; group has read, write, and execute permission
define S_IRGRP  00040o  ; group has read permission
define S_IWGRP  00020o  ; group has write permission
define S_IXGRP  00010o  ; group has execute permission
define S_IRWXO  00007o  ; others have read, write, and execute permission
define S_IROTH  00004o  ; others have read permission
define S_IWOTH  00002o  ; others have write permission
define S_IXOTH  00001o  ; others have execute permission

define S_ISUID  0004000o
define S_ISGID  0002000o
define S_ISVTX  0001000o

define SEEK_SET        0
define SEEK_CUR        1
define SEEK_END        2
define SEEK_DATA       3
define SEEK_HOLE       4

define SIGHUP          1
define SIGINT          2
define SIGQUIT         3
define SIGILL          4
define SIGTRAP         5
define SIGABRT         6
define SIGIOT          6
define SIGBUS          7
define SIGFPE          8
define SIGKILL         9
define SIGUSR1         10
define SIGSEGV         11
define SIGUSR2         12
define SIGPIPE         13
define SIGALRM         14
define SIGTERM         15
define SIGSTKFLT       16
define SIGCHLD         17
define SIGCONT         18
define SIGSTOP         19
define SIGTSTP         20
define SIGTTIN         21
define SIGTTOU         22
define SIGURG          23
define SIGXCPU         24
define SIGXFSZ         25
define SIGVTALRM       26
define SIGPROF         27
define SIGWINCH        28
define SIGIO           29
define SIGPOLL         SIGIO
define SIGLOST         29
define SIGPWR          30
define SIGSYS          31

define SOCK_STREAM      1
define SOCK_DGRAM       2
define SOCK_RAW         3

define STDIN_FILENO    0
define STDOUT_FILENO   1
define STDERR_FILENO   2

define TCIFLUSH        0    ;  Discard data received but not yet read
define TCOFLUSH        1    ;  Discard data written but not yet sent
define TCIOFLUSH       2    ;  Discard all pending data

define TCSANOW         0
define TCSADRAIN       1
define TCSAFLUSH       2

define thrd_success    0
define thrd_busy       1
define thrd_error      2
define thrd_nomem      3
define thrd_timedout   4

define TIOCGWINSZ      0x5413

define TRUE            1

ext data stdin, stdout, stderr

ext proto __cxa_atexit, qword, alias atexit
ext proto __errno_location, none, alias errno   ; rax = errno ptr
ext proto asctime, qword                        ; rdi = *TM structure; rax = *strtime
ext proto calloc, qword, qword                  ; rdi = n, rsi = size
ext proto cfmakeraw, qword                      ; rdi = *TERMIOS filled structure
ext proto clearerr, qword                       ; rdi = * FILE
ext proto close, dword                          ; edi = int file descriptor
ext proto closedir, qword                       ; rdi = directory descriptor
ext proto ctime, qword                          ; rdi = *TIMEP structure; rax = *strtime
ext proto dprintf, dword, qword, vararg         ; edi = fd, rsi, *format, ...
ext proto dup, dword                            ; edi = int file descriptor
ext proto dup2, dword, dword                    ; esi = new file descriptor
ext proto dup3, dword, dword, dword             ; edx = flags
ext proto execve, qword, qword, qword           ; rdi = *path, rsi = **arg, rdx = **envp
ext proto execvpe, qword, qword, qword          ; same as above
ext noreturn proto exit, dword                  ; edi = exit code
ext proto fclose, qword                         ; rdi = file descriptor
ext proto fcntl, dword, dword, vararg           ; edi = int file desc, esi = command, ...
ext proto fdopen, dword, qword                  ; edi = fd, rsi = char *mode
ext proto feof, qword
ext proto ferror, qword
ext proto fflush, qword                         ; rdi = file descriptor
ext proto fgetc, qword                          ; rdi = file descriptor
ext proto fgets, qword, dword, qword
ext proto fileno, qword                         ; rdi = *file stream
ext proto fopen, qword, qword                   ; rdi = *filepath; rsi = *mode
ext proto fork, none
ext proto fprintf, qword, vararg                ; rdi = *File stream, RSI = format, ...
ext proto fputc, dword, qword                   ; edi = int char, rsi = *File stream
ext proto fputs, qword, qword
ext proto fputwc, dword, qword
ext proto fread, qword, qword, qword, qword     ; rdi = *data, rsi = size, rdx = num elements, rcx = *file stream
ext proto free, qword
ext proto freeaddrinfo, qword
ext proto fseek, qword, qword, dword
ext proto fstat, qword, qword
ext proto ftell, qword
ext proto ftruncate, dword, dword               ; edi = fd, esi = length
ext proto fwrite, qword, qword, qword, qword    ; Same as fread()
ext proto gai_strerror, dword
ext proto get_nprocs, none                      ; number of processors in the system
ext proto get_nprocs_conf, none                 ; number of processors online
ext proto getaddrinfo, qword, qword, qword, qword
ext proto getchar, none
ext proto getenv, qword                         ; rdi = *environment string
ext proto geteuid, none
ext proto getgrgid, dword                       ; edi = Group ID
ext proto gethostbyaddr, qword, dword, dword    ; 
ext proto gethostbyname, qword
ext proto getitimer, dword, qword               ; edi = which timer, rsi = *itimerval current settings
ext proto getline, qword, qword, qword
ext proto getnameinfo, qword, dword, qword, dword, qword, dword, dword
ext proto getpass, qword
ext proto getpid, none
ext proto getpriority, dword, dword
ext proto getpwuid, dword                       ; edi = user ID
ext proto gettimeofday, qword, qword            ; *TIMEVAL structure, *TIMEZONE struct
ext proto grantpt, dword                        ; edi = int file descriptor
ext proto ioctl, dword, vararg                  ; edi = int file descriptor
ext proto localtime, qword                      ; rdi = *POSIX TIME variable
ext proto malloc, qword                        ; rdi = number of bytes to allocate
ext proto mkdir, qword, dword
ext proto mkfifo, qword, dword                  ; rdi = *pathname, esi = mode
ext proto mkstemp, qword                        ; rdi = template name; returns eax = int file descriptor
ext proto nanosleep, qword, qword
ext proto open, qword, dword, dword     ; rdi = pathname, esi = flags, edx = mode
ext proto opendir, qword                        ; rdi = *dirpath
ext proto perror, qword                         ; rdi = *string before error string (can be NULL)
ext proto posix_openpt, dword                   ; edi = flags. eax = pts lowest number available
ext proto printf, qword, vararg
ext proto ptsname, dword                        ; edi = int file descriptor. rax = str PTS name
ext proto putchar, dword
ext proto puts, qword
ext proto putwchar, dword
ext proto read, dword, qword, qword            ; edi = int file desc, rsi = *buffer, rdx = size
ext proto readdir, qword
ext proto realloc, qword, qword
ext proto reallocarray, qword, dword, dword
ext proto remove, qword                         ; rdi = *filepath
ext proto rewind, qword
ext proto scanf, qword, vararg
ext proto sched_getaffinity, dword, dword, qword
ext proto sched_getscheduler, dword
ext proto sched_setaffinity, dword, dword, qword
ext proto sched_setscheduler, dword, dword, qword
ext proto setegid, dword
ext proto seteuid, dword
ext proto setitimer, dword, qword, qword        ; edi = which timer, rsi = *itimerval new, rdx = *itimerval old
ext proto setlocale, dword, qword               ; edi = flags; rsi = *locale
ext proto setpriority, dword, dword, dword
ext proto setuid, dword
ext proto signal, dword, qword                  ; edi = sig, rsi = *handler
ext proto sleep, dword                          ; edi = seconds to sleep
ext proto snprintf, qword, qword, qword, vararg ; rdi = *buffer, rsi = size, rdx = format, ...
ext proto socket, dword, dword, dword           ; edi = domain, esi, type, edx = protocol
ext proto sprintf, qword, qword, vararg         ; rdi = *buffer; rsi = *format; ...
ext proto stat, qword, qword
ext proto strcmp, qword, qword
ext proto strftime, qword, dword, qword, qword  ; *buffer; max-size; *format; *TM structure
ext proto strtod, qword, qword                  ; see below ¹
ext proto strtol, qword, qword, dword           ; *nptr, *endptr (or NULL), base ²
ext proto strtold, qword, qword                 ; ¹ *buffer; **nbuffer (variable which receives character pointer next to converted string
ext proto strtoll, qword, qword, dword          ; same as ². Returns long long
ext proto strtoul, qword, qword, dword          ; same as ². Returns unsigned long
ext proto strtoull, qword, qword, dword         ; same as ². Returns unsigned long long
ext proto system, qword                         ; rdi = *cmdline
ext proto tcdrain, dword                        ; edi = int file descriptor
ext proto tcflush, dword, dword                 ; edi = int file descriptor, esi = queue selector
ext proto tcgetattr, dword, qword               ; FILENO, *TERMIOS structure
ext proto tcsetattr, dword, dword, qword        ; FILENO, when, *TERMIOS structure
ext proto thrd_create, qword, qword, qword
ext proto thrd_detach, qword
ext proto thrd_join, qword, qword
ext proto time, qword                           ; rdi = *time_t (may be null); rax = Posix Time (Epoch based)
ext proto tmpfile, none                         ; rax = returns a file pointer to temporary file
ext proto unlink, qword                         ; rdi = char path filename to be removed
ext proto unlockpt, dword                       ; edi = int file descriptor
ext proto usleep, dword                         ; edi = microsseconds to sleep
ext proto write, dword, qword, qword            ; edi = int file desc, rsi = buffer, edx = size

;:::::::::::::::::::::::::::::::::::::
;:::::::::::::::::::::::::::::::::::::
; This is how a libc main program starts the main callback
; For (still) unknown reason, linker ld-linux-x86-64.so.2
; passes its destructor pointer into rdx before jump into
; _start.
;
; Parameters:
; rdi = ptr* main function
; esi = argc
; rdx = ptr* argv
; rcx = ptr* init function (which in libc probably initializes
;       some internals
; r8  = pre* fini function (probably function to destroy
;       this program allocations)
; r9  = ptr* rtld_fini (the misterious pointer passed by
;       the linker in rdx must be inserted here!)
; [rsp] = ptr *stack end address (usually, rsp value at _start

ext noreturn proto __libc_start_main, qword, dword, qword, qword, qword, qword, qword

;:::::::::::::::::::::::::::::::::::::
;:::::::::::::::::::::::::::::::::::::
