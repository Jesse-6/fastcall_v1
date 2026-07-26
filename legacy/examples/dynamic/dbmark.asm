format ELF64

include 'fastcall.inc'
include 'stdmacros.inc'
include 'stdio.inc'

TEST_CYCLES = 400000000       ; Number of iterations within test loop

_bss
          buffer1                  rb 512
          buffer2                  rb 512

_code     align 32
          pAffinity                ddq 1

          align 32
          Start entry:             endbr64
                                   fputs("Setting priority for 1 core only... ", *stdout);
                                   fflush(*stdout);
                                   errno();
                                   mov       rbx, rax
                                   sched_setaffinity(NULL, sizeof(pAffinity), &pAffinity);
                                   test      eax, eax
                                   jz        @f
                                   perror("fail");
                                   jmp       @f2
                              @@   perror(NULL);
                              @@   mov       [rbx], dword 0
                                   setpriority(PRIO_PROCESS, NULL, PRIO_HIGHEST);
                                   mov       edx, [rbx]
                                   test      edx, edx
                                   jz        @f
                                   perror("Error elevating priority");
                                   jmp       @f2
                              @@   perror("Setting priority");
                              @@   puts(<27,"[0;35mStarting...",27,"[0m",0>);
                                   fflush(*stdout);
                                   mov       rbx, TEST_CYCLES
                                   mov       r12, rbx

                                   ; **********************************
                                   ; ***    Start Benchmark code    ***

                                   lfence
                                   rdtsc
                                   push      rdx
                                   push      rax

                                   ; ### Tested code goes here ###
                              @@@  call      Dummy1
                                   ; ### End tested code       ###

                                   dec       r12
                                   jnz       @@b

                              @@   mfence
                                   rdtsc
                                   pop       rbp
                                   pop       rcx

                                   ; ***     End Benchmark code     ***
                                   ; **********************************

                                   sub       eax, ebp
                                   sbb       edx, ecx
                                   shrd      r15, rax, 32
                                   shrd      r15, rdx, 32
                                   mov       rax, r15
                                   cqo
                                   xor       esi, esi
                                   div       rbx
                                   shld      rsi, r15, 32
                                   printf(<"TSC run length: %08X:%08X.",10,\
                                        "Iteration average: %u cycles.",10, \
                                        "Total iteration: %lu loops.",10,0>, \
                                        esi, r15d, eax, rbx);
                                   exit(0);

          Dummy0:                  endbr64
                                   push      rbp
                                   mov       rbp, rsp
                                   sub       rsp, 128
                                   xor       eax, eax
                                   leave
                                   ret

          Dummy1:                  endbr64
                                   enter     128, 0
                                   xor       eax, eax
                                   leave
                                   ret
