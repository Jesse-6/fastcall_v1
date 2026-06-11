include 'lxcpud.inc'

_data
        banner                  db 'Starting lxcpud daemon version '
        version                 db '0.0 build: '
                                db '0-fasm2'
                                db 10, 0
        cfgFile                 db 'cpudaemon.data', 0
        cpufreqPath             db '/sys/devices/system/cpu/cpu%u/cpufreq/%s', 0
        num2str                 db '%u', 0

_bss
        fdata                   STAT
        tmpBuff                 rb 1024

_code
        Start:                  endbr64
                                cmp     [rsp], dword 2
                                jne     @f
                                mov     r10, [rsp+16]
                                test    r10, r10
                                jz      @f
                                test    [r10+6], byte -1
                                jnz     @f
                                mov     rdx, [r10]
                                mov     rcx, '-write'
                                mov     rax, 0#0000#FFFF#FFFF#FFFFh
                                and     rdx, rax
                                cmp     rdx, rcx
                                je      @f2
                        @@      fputs(<"Hello, I'm a daemon!",10,0>, **stderr);
                                exit(1);
                                
                        @@      fputs(&banner, **stdout);
                                open(&cfgFile, O_RDONLY,.);
                                test    eax, eax
                                js      .errdaemon1
                                mov     ebp, eax
                                fstat(eax, &fdata);
                                test    eax, eax
                                jz      @f
                .errdaemon2:    close(ebp);
                                jmp     .errdaemon1
                        @@      mov     rbx, [fdata.st_size]
                                cmp     rbx, MAX_FILE_SIZE
                                jbe     @f
                .errdaemon3:    close(ebp);
                                fputs(<"Invalid data file.",10,0>, **stderr);
                                exit(1);
                        @@      mov     r14, rbx
                                malloc(rbx);
                                test    rax, rax
                                jz      .errdaemon2
                                mov     r15, rax
                                mov     r13, rax
                        @@@     read(ebp, r13, rbx);
                                test    rax, rax
                                jns     @f
                                free(r15);
                                jmp     .errdaemon2
                        @@      cmp     rax, rbx
                                jae     @f
                                add     r13, rax
                                sub     rbx, rax
                                jnle    @@b
                        @@      cmp     [r15+r14-4], dword 'CPUD'
                                je      @f
                .errdaemon4:    free(r15);
                                jmp     .errdaemon3
                        @@      mov     edx, [r15]
                                cmp     edx, 2000
                                ja      .errdaemon4
                                imul    ecx, edx, sizeof(CPUDATA)
                                add     ecx, sizeof(FILEHEADER)+4
                                cmp     ecx, r14d
                                ja      .errdaemon4
                                mov     r11d, [r15+FILEHEADER.globalMaxClk]
                                mov     r10d, [r15+FILEHEADER.globalMinClk]
                                cmp     r11d, r10d
                                jbe     .errdaemon4
                                mov     r12d, edx
                                mov     ebx, [r15+FILEHEADER.OffsetCPUData]
                                lea     r9, [r15+r14]
                                lea     r8, [r15+rbx]
                        @@@     cmp     r8, r9
                                jae     .errdaemon4
                                mov     eax, [r8+CPUDATA.clkMin]
                                mov     ecx, [r8+CPUDATA.clkMax]
                                cmp     eax, r10d
                                jb      .errdaemon4
                                cmp     ecx, r11d
                                ja      .errdaemon4
                                add     r8, sizeof(CPUDATA)
                                dec     r12d
                                jnz     @@b
                                nop
                                nop
                                mov     r12d, edx
                                xor     r13d, r13d
                                
                        @@@     snprintf(&tmpBuff, 1024, &cpufreqPath, r13d, "scaling_max_freq");
                                open(&tmpBuff, O_WRONLY,.);
                                test    eax, eax
                                js      @f7
                                push    rbx
                                push    r13
                                mov     r13d, eax
                                snprintf(&tmpBuff+512, 512, &num2str, dd [r15+rbx+CPUDATA.clkMax]);
                                lea     r11, [tmpBuff+512]
                                mov     [r11+rax], word 0Ah
                                write(r13d, &tmpBuff+512, dd &eax+2);
                                close(r13d);
                                
                                snprintf(&tmpBuff, 1024, &cpufreqPath, dd [rsp], \
                                        "scaling_min_freq");
                                open(&tmpBuff, O_WRONLY,.);
                                test    eax, eax
                                js      @f6
                                mov     r13d, eax
                                snprintf(&tmpBuff+512, 512, &num2str, \
                                        dd [r15+rbx+CPUDATA.clkMin]);
                                lea     r11, [tmpBuff+512]
                                mov     [r11+rax], word 0Ah
                                write(r13d, &tmpBuff+512, dd &eax+2);
                                close(r13d);
                                
                                test    [r15+rbx+CPUDATA.flags], byte 1b
                                jz      @f3
                                snprintf(&tmpBuff, 1024, &cpufreqPath, \
                                        dd [rsp], "scaling_governor");
                                open(&tmpBuff, O_WRONLY,.);
                                test    eax, eax
                                js      @f6
                                mov     r13d, eax
                                mov     esi, [r15+rbx+CPUDATA.off_clkProf]
                                lea     rdi, [tmpBuff+512]
                                lea     rsi, [r15+rsi]
                                mov     ah, 0Ah
                                xor     edx, edx
                        @@      lodsb
                                test    al, al
                                jz      @f
                                stosb
                                inc     edx
                                jmp     @b
                        @@      xchg    ah, al
                                stosw
                                inc     edx
                                write(r13d, &tmpBuff+512, edx);
                                close(r13d);
                                
                        @@      test    [r15+rbx+CPUDATA.flags], byte 10b
                                jz      @f3
                                snprintf(&tmpBuff, 1024, &cpufreqPath, dd [rsp], \
                                        "energy_performance_preference");
                                open(&tmpBuff, O_WRONLY,.);
                                test    eax, eax
                                js      @f3
                                mov     r13d, eax
                                mov     esi, [r15+rbx+CPUDATA.off_enProf]
                                lea     rdi, [tmpBuff+512]
                                lea     rsi, [r15+rsi]
                                mov     ah, 0Ah
                                xor     edx, edx
                        @@      lodsb
                                test    al, al
                                jz      @f
                                stosb
                                inc     edx
                                jmp     @b
                        @@      xchg    ah, al
                                stosw
                                inc     edx
                                write(r13d, &tmpBuff+512, edx);
                                close(r13d);
                                
                        @@      nop
                                pop     r13
                                pop     rbx
                        @@      inc     r13d
                                add     ebx, sizeof(CPUDATA)
                                dec     r12d
                                jnz     @@b
                                
                                nop
                                nop
                .end:           free(r15);
                                close(ebp);
                                test    eax, eax
                                js      .errdaemon1
                                mov     r14d, eax
                                fputs(<"Service lxcpud is done. All successfully.",10,0>, **stdout);
                                exit(r14d);
                                
                .errdaemon1:    errno();
                                mov     r14d, [rax]
                                perror("Service lxcpud unsuccessfull");
                                exit(r14d);
