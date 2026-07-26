format ELF64

include 'fastcall3.inc'
include 'stdio.inc'

TEST_CYCLES = 400000000       ; Number of iterations within test loop

_bss
          buffer1:                 rd 128    ; by reference address type label
          buffer2                  rd 128    ; by value data type label

_code     align 32
          pAffinity                ddq 1     ; ¹ NOTE: this is a data label...

          align 32
          Start entry:             endbr64
                                   fputs("Setting priority for 1 core only... ", stdout);
                                   fflush(stdout);
                                   errno();
                                   mov       rbx, rax
                                   sched_setaffinity(NULL, sizeof(pAffinity), &pAffinity);
                                   test      eax, eax  ; The '&' is needed above, because 'pAffinity'
                                   jz        @f        ; is a declared data label, so, it will the
                                   perror("fail");     ; interpreted as [data] type by default.
                                   jmp       @f2       ; &pAffinity enforces pAffinity as address here,
                              @@   perror(NULL);       ; which is how this function expects it.
                              @@   mov       [rbx], dword 0
                                   setpriority(PRIO_PROCESS, NULL, PRIO_HIGHEST);
                                   mov       edx, [rbx]
                                   test      edx, edx
                                   jz        @f
                                   perror("Error elevating priority");
                                   jmp       @f2
                              @@   perror("Setting priority");
                              @@   puts(<27,"[0;35mStarting...",27,"[0m",0>);
                                   fflush(stdout);
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
                                        
                                   mov       [buffer2+32], 988352567
                                   printf(\n "Variable %u address: 0x%lX"\n, 1, buffer1+32);
                                   printf("Variable %u data: %u"\n, 2, buffer2+32);
                                        
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

; To compile: > ./build dbmark
