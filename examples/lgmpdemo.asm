; Multiple Precision Arithmetic Library libgmp demo
; Or big number libgmp demo, as it is popularly known
; Using the reusable header 'gmp.inc'
; And, yes: this is assembly! 8)
; It's the power of fastcall macro toolkit!
format ELF64 executable 3

include 'anon_label.inc'
include 'fastcall_v1.inc'
include 'stdio.inc'
include 'gmp.inc'

_bss align 32
        result          mpz_t
        op1             mpz_t
        op2             mpz_t
        op3             mpz_t
        op4             mpz_t

_code align 8
        entry $
                        endbr64
                        mpz_inits(&result, &op1, &op2, &op3, &op4, NULL);
                        getpid();
                        mov         r15d, eax
                        puts(<27,"[1mIP x IPv6 statistic and ",27,"[1;38;5;228mlibgmp",27,\
                            "[0;1m demo example.",27,"[0m",0>);
                        gmp_printf(<27,"[2;3mProcess PID: %u says:",27,"[0m",10,0>, r15d);
                        mpz_ui_pow_ui(&op1, 2, 32);
                        gmp_printf(<10,"There are ",27,"[38;5;214m%Zd",27,\
                            "[0m possible IPv4 addresses, %s. %s.",10,0>, &op1, \
                            "including private, public, reserved and unused IPs",\
                            <10,"A typical home user has ",27,"[38;5;253m256",27, \
                            "[0m private IPs, which do not communicate directly",\
                            " on the internet",0>);
                        mpz_mul(&op2, &op1, &op1);
                        gmp_printf(<"In a single /64 SLAAC IPv6 subnet, there are ",10,27,  \
                            "[38;5;83m%Zd",27,"[0m possible IPv6 addresses.",10,"%s",10,"%s",\
                            10,0>, &op2, "This is one single LAN for a typical domestic ISP user.", \
                            "And they're all public IPs!");
                        mpz_set_str(&op3, "2001 0000 0000 0000 0000 0000 0000 0000", 16);
                        mpz_set_str(&op4, "3FFF FFFF FFFF FFFF FFFF FFFF FFFF FFFF", 16);
                        mpz_sub(&result, &op4, &op3);
                        gmp_printf(<"The total IPv6 addresses for the whole internet on",   \
                            " Earth contains nearly",10,27,"[1;38;5;46m%Zd",27,"[0m unique public",\
                            " IPv6 addresses, ",10," %s.",10,0>, &result, \
                            <"not excluding any bogons in the range ",10," 2000::/3, of course",0>);
                        mpz_pow_ui(&result, &op2, 2);
                        gmp_printf(<"To conclude, there are ",27,"[1;4;38;5;50m%Zd",10,27,"[0m",\
                            " possible IPv6 addresses in the whole address space, against",\
                            10,32,27,"[38;5;203m%Zd",27,"[0m in IPv4 address space.",10,0>, \
                            &result, &op1);
                        puts(<"Then comes the question: why are ISPs still strongly relying on ",  \
                            "the obsolete and stagnated IPv4 address so much, instead of IPv6?!",10,\
                            27,"[1;6;38;5;212mAsk your ISP for your IPv6 now",27,"[0m, if you don't ", \
                            "have it. It's your right!",10,0>);
                        mpz_clears(&result, &op1, &op2, &op3, &op4, NULL);
                        exit(EXIT_SUCCESS);
