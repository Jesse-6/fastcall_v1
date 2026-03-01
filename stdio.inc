if ~ defined __STDIO_INC_INCLUDED__
	define __STDIO_INC_INCLUDED__
	define __STDIO_INC_INCLUDED__

	library 'libc.so.6'

	define AF_UNIX          1
	define AF_INET          2
	define AF_INET6         10

    define CLOCK_REALTIME           0
    define CLOCK_MONOTONIC          1
    define CLOCK_PROCESS_CPUTIME_ID 2
    define CLOCK_THREAD_CPUTIME_ID  3
    define CLOCK_MONOTONIC_RAW      4
    define CLOCK_REALTIME_COARSE    5
    define CLOCK_MONOTONIC_COARSE   6
    define CLOCK_BOOTTIME           7
    define CLOCK_REALTIME_ALARM     8
    define CLOCK_BOOTTIME_ALARM     9
    define CLOCK_SGI_CYCLE          10
    define CLOCK_TAI                11

	define	EPERM		 1	; Operation not permitted
	define	ENOENT		 2	; No such file or directory
	define	ESRCH		 3	; No such process
	define	EINTR		 4	; Interrupted system call
	define	EIO		 	 5	; I/O error
	define	ENXIO		 6	; No such device or address
	define	E2BIG		 7	; Argument list too long
	define	ENOEXEC		 8	; Exec format error
	define	EBADF		 9	; Bad file number
	define	ECHILD		10	; No child processes
	define	EAGAIN		11	; Try again
	define	ENOMEM		12	; Out of memory
	define	EACCES		13	; Permission denied
	define	EFAULT		14	; Bad address
	define	ENOTBLK		15	; Block device required
	define	EBUSY		16	; Device or resource busy
	define	EEXIST		17	; File exists
	define	EXDEV		18	; Cross-device link
	define	ENODEV		19	; No such device
	define	ENOTDIR		20	; Not a directory
	define	EISDIR		21	; Is a directory
	define	EINVAL		22	; Invalid argument
	define	ENFILE		23	; File table overflow
	define	EMFILE		24	; Too many open files
	define	ENOTTY		25	; Not a typewriter
	define	ETXTBSY		26	; Text file busy
	define	EFBIG		27	; File too large
	define	ENOSPC		28	; No space left on device
	define	ESPIPE		29	; Illegal seek
	define	EROFS		30	; Read-only file system
	define	EMLINK		31	; Too many links
	define	EPIPE		32	; Broken pipe
	define	EDOM		33	; Math argument out of domain of func
	define	ERANGE		34	; Math result not representable

	define	EDEADLK		35	; Resource deadlock would occur
	define	ENAMETOOLONG	36	; File name too long
	define	ENOLCK		37	; No record locks available
	define	ENOSYS		38	; Invalid system call number
	define	ENOTEMPTY	39	; Directory not empty
	define	ELOOP		40	; Too many symbolic links encountered
	define	EWOULDBLOCK	EAGAIN	; Operation would block
	define	ENOMSG		42	; No message of desired type
	define	EIDRM		43	; Identifier removed
	define	ECHRNG		44	; Channel number out of range
	define	EL2NSYNC	45	; Level 2 not synchronized
	define	EL3HLT		46	; Level 3 halted
	define	EL3RST		47	; Level 3 reset
	define	ELNRNG		48	; Link number out of range
	define	EUNATCH		49	; Protocol driver not attached
	define	ENOCSI		50	; No CSI structure available
	define	EL2HLT		51	; Level 2 halted
	define	EBADE		52	; Invalid exchange
	define	EBADR		53	; Invalid request descriptor
	define	EXFULL		54	; Exchange full
	define	ENOANO		55	; No anode
	define	EBADRQC		56	; Invalid request code
	define	EBADSLT		57	; Invalid slot
	define	EDEADLOCK	EDEADLK
	define	EBFONT		59	; Bad font file format
	define	ENOSTR		60	; Device not a stream
	define	ENODATA		61	; No data available
	define	ETIME		62	; Timer expired
	define	ENOSR		63	; Out of streams resources
	define	ENONET		64	; Machine is not on the network
	define	ENOPKG		65	; Package not installed
	define	EREMOTE		66	; Object is remote
	define	ENOLINK		67	; Link has been severed
	define	EADV		68	; Advertise error
	define	ESRMNT		69	; Srmount error
	define	ECOMM		70	; Communication error on send
	define	EPROTO		71	; Protocol error
	define	EMULTIHOP	72	; Multihop attempted
	define	EDOTDOT		73	; RFS specific error
	define	EBADMSG		74	; Not a data message
	define	EOVERFLOW	75	; Value too large for defined data type
	define	ENOTUNIQ	76	; Name not unique on network
	define	EBADFD		77	; File descriptor in bad state
	define	EREMCHG		78	; Remote address changed
	define	ELIBACC		79	; Can not access a needed shared library
	define	ELIBBAD		80	; Accessing a corrupted shared library
	define	ELIBSCN		81	; .lib section in a.out corrupted
	define	ELIBMAX		82	; Attempting to link in too many shared libraries
	define	ELIBEXEC	83	; Cannot exec a shared library directly
	define	EILSEQ		84	; Illegal byte sequence
	define	ERESTART	85	; Interrupted system call should be restarted
	define	ESTRPIPE	86	; Streams pipe error
	define	EUSERS		87	; Too many users
	define	ENOTSOCK	88	; Socket operation on non-socket
	define	EDESTADDRREQ	89	; Destination address required
	define	EMSGSIZE	90	; Message too long
	define	EPROTOTYPE	91	; Protocol wrong type for socket
	define	ENOPROTOOPT	92	; Protocol not available
	define	EPROTONOSUPPORT	93	; Protocol not supported
	define	ESOCKTNOSUPPORT	94	; Socket type not supported
	define	EOPNOTSUPP	95	; Operation not supported on transport endpoint
	define	EPFNOSUPPORT	96	; Protocol family not supported
	define	EAFNOSUPPORT	97	; Address family not supported by protocol
	define	EADDRINUSE	98	; Address already in use
	define	EADDRNOTAVAIL	99	; Cannot assign requested address
	define	ENETDOWN	100	; Network is down
	define	ENETUNREACH	101	; Network is unreachable
	define	ENETRESET	102	; Network dropped connection because of reset
	define	ECONNABORTED	103	; Software caused connection abort
	define	ECONNRESET	104	; Connection reset by peer
	define	ENOBUFS		105	; No buffer space available
	define	EISCONN		106	; Transport endpoint is already connected
	define	ENOTCONN	107	; Transport endpoint is not connected
	define	ESHUTDOWN	108	; Cannot send after transport endpoint shutdown
	define	ETOOMANYREFS	109	; Too many references: cannot splice
	define	ETIMEDOUT	110	; Connection timed out
	define	ECONNREFUSED	111	; Connection refused
	define	EHOSTDOWN	112	; Host is down
	define	EHOSTUNREACH	113	; No route to host
	define	EALREADY	114	; Operation already in progress
	define	EINPROGRESS	115	; Operation now in progress
	define	ESTALE		116	; Stale file handle
	define	EUCLEAN		117	; Structure needs cleaning
	define	ENOTNAM		118	; Not a XENIX named type file
	define	ENAVAIL		119	; No XENIX semaphores available
	define	EISNAM		120	; Is a named type file
	define	EREMOTEIO	121	; Remote I/O error
	define	EDQUOT		122	; Quota exceeded
	define	ENOMEDIUM	123	; No medium found
	define	EMEDIUMTYPE	124	; Wrong medium type
	define	ECANCELED	125	; Operation Canceled
	define	ENOKEY		126	; Required key not available
	define	EKEYEXPIRED	127	; Key has expired
	define	EKEYREVOKED	128	; Key has been revoked
	define	EKEYREJECTED	129	; Key was rejected by service

	; for robust mutexes
	define	EOWNERDEAD	130	; Owner died
	define	ENOTRECOVERABLE	131	; State not recoverable
	define ERFKILL		132	; Operation not possible due to RF-kill
	define EHWPOISON	133	; Memory page has hardware error

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

	define ICMP_ECHOREPLY		0	; Echo Reply
	define ICMP_DEST_UNREACH	3	; Destination Unreachable
	define ICMP_SOURCE_QUENCH	4	; Source Quench
	define ICMP_REDIRECT		5	; Redirect (change route)
	define ICMP_ECHO			8	; Echo Request

	define ICMP_TIME_EXCEEDED	11	; Time Exceeded
	define ICMP_PARAMETERPROB	12	; Parameter Problem
	define ICMP_TIMESTAMP		13	; Timestamp Request
	define ICMP_TIMESTAMPREPLY	14	; Timestamp Reply
	define ICMP_INFO_REQUEST	15	; Information Request
	define ICMP_INFO_REPLY		16	; Information Reply
	define ICMP_ADDRESS			17	; Address Mask Request
	define ICMP_ADDRESSREPLY	18	; Address Mask Reply
	define ICMP_NET_UNREACH		0	; Network Unreachable
	define ICMP_HOST_UNREACH	1	; Host Unreachable
	define ICMP_PROT_UNREACH	2	; Protocol Unreachable
	define ICMP_PORT_UNREACH	3	; Port Unreachable
	define ICMP_FRAG_NEEDED		4	; Fragmentation Needed/DF set
	define ICMP_SR_FAILED		5	; Source Route failed
	define ICMP_NET_UNKNOWN		6
	define ICMP_HOST_UNKNOWN	7
	define ICMP_HOST_ISOLATED	8
	define ICMP_NET_ANO			9
	define ICMP_HOST_ANO		10
	define ICMP_NET_UNR_TOS		11
	define ICMP_HOST_UNR_TOS	12
	define ICMP_PKT_FILTERED	13	; Packet filtered
	define ICMP_PREC_VIOLATION	14	; Precedence violation
	define ICMP_PREC_CUTOFF		15	; Precedence cut off

	define ICMPV6_ROUTER_PREF_LOW		0x3
	define ICMPV6_ROUTER_PREF_MEDIUM	0x0
	define ICMPV6_ROUTER_PREF_HIGH		0x1
	define ICMPV6_ROUTER_PREF_INVALID	0x2

	define ICMPV6_DEST_UNREACH		1
	define ICMPV6_PKT_TOOBIG		2
	define ICMPV6_TIME_EXCEED		3
	define ICMPV6_PARAMPROB			4

	define ICMPV6_ERRMSG_MAX		127

	define ICMPV6_INFOMSG_MASK		0x80

	define ICMPV6_ECHO_REQUEST		128
	define ICMPV6_ECHO_REPLY		129
	define ICMPV6_MGM_QUERY			130
	define ICMPV6_MGM_REPORT       	131
	define ICMPV6_MGM_REDUCTION    	132

	define ICMPV6_NI_QUERY			139
	define ICMPV6_NI_REPLY			140

	define ICMPV6_MLD2_REPORT		143

	define ICMPV6_DHAAD_REQUEST		144
	define ICMPV6_DHAAD_REPLY		145
	define ICMPV6_MOBILE_PREFIX_SOL	146
	define ICMPV6_MOBILE_PREFIX_ADV	147

	define ICMPV6_MRDISC_ADV		151
	define ICMPV6_MRDISC_SOL		152

	define ICMPV6_MSG_MAX			255

	;	Codes for Destination Unreachable

	define ICMPV6_NOROUTE			0
	define ICMPV6_ADM_PROHIBITED	1
	define ICMPV6_NOT_NEIGHBOUR		2
	define ICMPV6_ADDR_UNREACH		3
	define ICMPV6_PORT_UNREACH		4
	define ICMPV6_POLICY_FAIL		5
	define ICMPV6_REJECT_ROUTE		6

	;
	;	Codes for Time Exceeded

	define ICMPV6_EXC_HOPLIMIT		0
	define ICMPV6_EXC_FRAGTIME		1

	;
	;	Codes for Parameter Problem

	define ICMPV6_HDR_FIELD			0
	define ICMPV6_UNK_NEXTHDR		1
	define ICMPV6_UNK_OPTION		2
	define ICMPV6_HDR_INCOMP		3

	; Codes for EXT_ECHO (PROBE)
	define ICMPV6_EXT_ECHO_REQUEST	160
	define ICMPV6_EXT_ECHO_REPLY	161
	;
	;	constants for (set|get)sockopt

	define ICMPV6_FILTER			1

	;
	;	ICMPV6 filter

	define ICMPV6_FILTER_BLOCK			1
	define ICMPV6_FILTER_PASS			2
	define ICMPV6_FILTER_BLOCKOTHERS	3
	define ICMPV6_FILTER_PASSONLY		4

	;	Definitions for MLDv2

	define MLD2_MODE_IS_INCLUDE		1
	define MLD2_MODE_IS_EXCLUDE		2
	define MLD2_CHANGE_TO_INCLUDE	3
	define MLD2_CHANGE_TO_EXCLUDE	4
	define MLD2_ALLOW_NEW_SOURCES	5
	define MLD2_BLOCK_OLD_SOURCES	6

	define IP_TOS					1
	define IP_TTL					2
	define IP_HDRINCL				3
	define IP_OPTIONS				4
	define IP_ROUTER_ALERT			5
	define IP_RECVOPTS				6
	define IP_RETOPTS				7
	define IP_PKTINFO				8
	define IP_PKTOPTIONS			9
	define IP_MTU_DISCOVER			10
	define IP_RECVERR				11
	define IP_RECVTTL				12
	define IP_MTU					14
	define IP_FREEBIND				15
	define IP_IPSEC_POLICY			16
	define IP_XFRM_POLICY			17
	define IP_PASSSEC				18
	define IP_TRANSPARENT			19
	define IP_RECVRETOPTS			IP_RETOPTS
	define IP_ORIGDSTADDR			20
	define IP_RECVORIGDSTADDR		IP_ORIGDSTADDR
	define IP_MINTTL       			21
	define IP_NODEFRAG     			22
	define IP_CHECKSUM				23
	define IP_BIND_ADDRESS_NO_PORT	24
	define IP_RECVFRAGSIZE			25
	define IP_RECVERR_RFC4884		26


	define IPPROTO_IP       0
	define IPPROTO_ICMP     1
	define IPPROTO_TCP      6
	define IPPROTO_UDP      17
	define IPPROTO_GRE      47
	define IPPROTO_ICMPV6   58

	define ITIMER_REAL     0
	define ITIMER_VIRTUAL  1
	define ITIMER_PROF     2

	define LC_ALL          6

	define	MSG_OOB			0x01	; Process out-of-band data.
	define	MSG_PEEK		0x02	; Peek at incoming messages.
	define	MSG_DONTROUTE	0x04	; Don't use local routing.
	define	MSG_TRYHARD		MSG_DONTROUTE
	define	MSG_CTRUNC		0x08	; Control data lost before delivery.
	define	MSG_PROXY		0x10	; Supply or ask second address.
	define	MSG_TRUNC		0x20
	define	MSG_DONTWAIT	0x40 ; Nonblocking IO.
	define	MSG_EOR			0x80 ; End of record.
	define	MSG_WAITALL		0x100 ; Wait for a full request.
	define	MSG_FIN			0x200
	define	MSG_SYN			0x400
	define	MSG_CONFIRM		0x800 ; Confirm path validity.
	define	MSG_RST			0x1000
	define	MSG_ERRQUEUE	0x2000 ; Fetch message from error queue.
	define	MSG_NOSIGNAL	0x4000 ; Do not generate SIGPIPE.
	define	MSG_MORE		0x8000  ; Sender will send more.
	define	MSG_WAITFORONE	0x10000 ; Wait for at least one packet to return.
	define	MSG_BATCH		0x40000 ; sendmmsg: more messages coming.
	define	MSG_SOCK_DEVMEM	0x2000000 ; Receive devmem skbs as cmsg.
	define	MSG_ZEROCOPY	0x4000000 ; Use user data in kernel path.
	define	MSG_FASTOPEN	0x20000000 ; Send data in TCP SYN.
	define	MSG_CMSG_CLOEXEC 0x40000000	; Set close_on_exit for file

	define NI_NUMERICHOST	1	; Don't try to look up hostname.
	define NI_NUMERICSERV	2	; Don't convert port number to name.
	define NI_NOFQDN		4	; Only return nodename portion.
	define NI_NAMEREQD		8	; Don't return numeric addresses.
	define NI_DGRAM			16	; Look up UDP service rather than TCP.

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

	define POLLIN			0001h
	define POLLERR			0008h

	define PRIO_PROCESS    0
	define PRIO_PGRP       1
	define PRIO_USER       2
	define PRIO_MIN        -20
	define PRIO_MAX        20
	define PRIO_HIGHEST    PRIO_MIN
	define PRIO_LOWEST     PRIO_MAX


	define PTHREAD_PRIO_NONE		0
	define PTHREAD_PRIO_INHERIT		1
	define PTHREAD_PRIO_PROTECT		2

	define PTHREAD_INHERIT_SCHED	0
	define PTHREAD_EXPLICIT_SCHED	1

	define THREAD_SCOPE_SYSTEM		0
	define  PTHREAD_SCOPE_PROCESS	1

	define PTHREAD_PROCESS_PRIVATE	0
	define PTHREAD_PROCESS_SHARED	1

	define PTHREAD_CANCEL_ENABLE	0
	define PTHREAD_CANCEL_DISABLE	1

	define PTHREAD_CANCEL_DEFERRED		0
	define PTHREAD_CANCEL_ASYNCHRONOUS	1

	define PTHREAD_CANCELED			-1

	define PTHREAD_ONCE_INIT		0


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

	define SO_EE_ORIGIN_NONE		0
	define SO_EE_ORIGIN_LOCAL		1
	define SO_EE_ORIGIN_ICMP		2
	define SO_EE_ORIGIN_ICMP6		3
	define SO_EE_ORIGIN_TXSTATUS	4
	define SO_EE_ORIGIN_ZEROCOPY	5
	define SO_EE_ORIGIN_TXTIME		6
	define SO_EE_ORIGIN_TIMESTAMPING SO_EE_ORIGIN_TXSTATUS

	define SO_RCVTIMEO      20
	define SO_SNDTIMEO      21
	define SO_TIMESTAMP_OLD 29

	define SOCK_STREAM      1
	define SOCK_DGRAM       2
	define SOCK_RAW         3

	define SOL_IP           0
	define SOL_SOCKET       1
	define SOL_TCP          6
	define SOL_UDP          17
	define SOL_IPV6         41
	define SOL_ICMPV6       58

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
	ext proto __h_errno_location, none, alias h_errno
	ext proto asctime, qword                        ; rdi = *TM structure; rax = *strtime
	ext proto calloc, qword, qword                  ; rdi = n, rsi = size
	ext proto cfmakeraw, qword                      ; rdi = *TERMIOS filled structure
	ext proto chdir, qword
	ext proto clearerr, qword                       ; rdi = * FILE
	ext proto clock_getres, dword, qword            ; edi = clockid, rsi = * timespec
	ext proto clock_gettime, dword, qword           ;
	ext proto clock_settime, dword, qword           ;
	ext proto close, dword                          ; edi = int file descriptor
	ext proto closedir, qword                       ; rdi = directory descriptor
	ext proto ctime, qword                          ; rdi = *TIMEP structure; rax = *strtime
	ext proto dprintf, dword, qword, vararg         ; edi = fd, rsi, *format, ...
	ext proto dlclose, qword
	ext proto dlerror, none
	ext proto dlopen, qword, dword
	ext proto dlsym, qword, qword
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
	ext proto get_current_dir_name, none
	ext proto getcwd, qword, dword
	ext proto gethostbyaddr, qword, dword, dword    ;
	ext proto gethostbyname, qword
	ext proto gethostbyname2, qword, dword			; * name, AF
	ext proto getitimer, dword, qword               ; edi = which timer, rsi = *itimerval current settings
	ext proto getline, qword, qword, qword
	ext proto getnameinfo, qword, dword, qword, dword, qword, dword, dword
	ext proto getpass, qword
	ext proto getpid, none
	ext proto getpriority, dword, dword
	ext proto getpwuid, dword                       ; edi = user ID
	ext proto getsockname, dword, qword, qword		; fd, * sockaddr, * size
	ext proto getsockopt, dword, dword, dword, qword, qword	; socket, level, option, *value, *size
	ext proto gettimeofday, qword, qword            ; *TIMEVAL structure, *TIMEZONE struct
	ext proto grantpt, dword                        ; edi = int file descriptor
	ext proto hstrerror, dword						; edi = int h_errno
	ext proto ioctl, dword, vararg                  ; edi = int file descriptor
	ext proto inet_aton, qword, qword				; rdi = *cp, rsi = *in_addr
	ext proto inet_ntoa, dword						; edi = in_addr
	ext proto inet_ntop, dword, qword, qword, dword	; af, src, dst, size
	ext proto inet_pton, dword, qword, qword		; af, src, dst
	ext proto localtime, qword                      ; rdi = *POSIX TIME variable
	ext proto malloc, qword                        ; rdi = number of bytes to allocate
	ext proto mkdir, qword, dword
	ext proto mkfifo, qword, dword                  ; rdi = *pathname, esi = mode
	ext proto mkstemp, qword                        ; rdi = template name; returns eax = int file descriptor
	ext proto nanosleep, qword, qword
	ext proto open, qword, dword, dword     ; rdi = pathname, esi = flags, edx = mode
	ext proto opendir, qword                        ; rdi = *dirpath
	ext proto perror, qword                         ; rdi = *string before error string (can be NULL)
	ext proto poll, qword, qword, dword				; * pollfd, num x pollfd, timeout ms
	ext proto posix_openpt, dword                   ; edi = flags. eax = pts lowest number available
	ext proto printf, qword, vararg
	ext proto pthread_attr_destroy, qword
	ext proto pthread_attr_init, qword
	ext proto pthread_cancel, qword
	ext proto _pthread_cleanup_pop, qword, dword, alias pthread_cleanup_pop            ; unverified! CAUTION
	ext proto _pthread_cleanup_push, qword, qword, qword, alias pthread_cleanup_push   ; unverified! CAUTION
	ext proto pthread_create, qword, qword, qword, qword
	ext noreturn proto pthread_exit, qword
	ext proto pthread_getname_np, qword, qword, dword
	ext proto pthread_join, qword, qword
	ext proto pthread_self, none
	ext proto pthread_setcancelstate, dword, qword
	ext proto pthread_setcanceltype, dword, qword
	ext proto pthread_setname_np, qword, qword
	ext proto pthread_test_cancel, none
	ext proto pthread_yield, none
	ext proto ptsname, dword                        ; edi = int file descriptor. rax = str PTS name
	ext proto putchar, dword
	ext proto puts, qword
	ext proto putwchar, dword
	ext proto read, dword, qword, qword            ; edi = int file desc, rsi = *buffer, rdx = size
	ext proto readdir, qword
	ext proto realloc, qword, qword
	ext proto reallocarray, qword, dword, dword
	ext proto recvfrom, dword, qword, qword, dword, qword, qword
	ext proto recvmsg, dword, qword, dword
	ext proto remove, qword                         ; rdi = *filepath
	ext proto rewind, qword
	ext proto scanf, qword, vararg
	ext proto sched_getaffinity, dword, dword, qword
	ext proto sched_getscheduler, dword
	ext proto sched_setaffinity, dword, dword, qword
	ext proto sched_setscheduler, dword, dword, qword
	ext proto sched_yield, none
	ext proto select, dword, qword, qword, qword, qword
	ext proto sendmsg, dword, qword, dword
	ext proto sendto, dword, qword, qword, dword, qword, dword
	ext proto setegid, dword
	ext proto setenv, qword, qword, dword
	ext proto seteuid, dword
	ext proto setitimer, dword, qword, qword        ; edi = which timer, rsi = *itimerval new, rdx = *itimerval old
	ext proto setlocale, dword, qword               ; edi = flags; rsi = *locale
	ext proto setpriority, dword, dword, dword
	ext proto setsockopt, dword, dword, dword, qword, dword	; socket, level, option, *value, size
	ext proto setuid, dword
	ext proto signal, dword, qword                  ; edi = sig, rsi = *handler
	ext proto sleep, dword                          ; edi = seconds to sleep
	ext proto snprintf, qword, qword, qword, vararg ; rdi = *buffer, rsi = size, rdx = format, ...
	ext proto socket, dword, dword, dword           ; edi = domain, esi, type, edx = protocol
	ext proto sprintf, qword, qword, vararg         ; rdi = *buffer; rsi = *format; ...
	ext proto stat, qword, qword
	ext proto strcmp, qword, qword
	ext proto strerror, dword
	ext proto strerrordesc_np, dword
	ext proto strerrorname_np, dword
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
	ext proto thrd_current, none
	ext proto thrd_detach, qword
	ext proto thrd_equal, qword, qword
	ext noreturn proto thrd_exit, dword
	ext proto thrd_join, qword, qword
	ext proto thrd_sleep, qword, qword
	ext proto thrd_yield, none
	ext proto time, qword                           ; rdi = *time_t (may be null); rax = Posix Time (Epoch based)
	ext proto tmpfile, none                         ; rax = returns a file pointer to temporary file
	ext proto unlink, qword                         ; rdi = char path filename to be removed
	ext proto unlockpt, dword                       ; edi = int file descriptor
	ext proto usleep, qword                         ; edi = microsseconds to sleep
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

	; This call is always the same (with fastcall macro). So, to simplify:
	;

	macro libc.StartMain mainproc
		match (mainptr), mainproc
			__libc_start_main(mainptr, [rsp+8], &rsp+16, NULL, NULL, rdx, rsp);
		else
			err "Invalid syntax.", 10
		end match
	end macro

else
	err "Duplicated inclusion of 'stdio.inc' file.", 10
end if

; Just use:
;
;     libc.StartMain(&MyMainProc);
;
;:::::::::::::::::::::::::::::::::::::
;:::::::::::::::::::::::::::::::::::::

alias pthread_getname, pthread_getname_np
alias pthread_setname, pthread_setname_np
