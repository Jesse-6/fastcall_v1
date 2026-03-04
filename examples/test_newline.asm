; This demo shows all supported \n feature formats
; included with fastcall_v1 macro.
; I cover most usage scenarios. For anything else,
; <string,10,0> or its variants should be used.
;
; ATTENTION: I noticed a strange behavior on how
; fasmg interprets string tokens when one mess up with it
; a little (like this feature code), which leads to
; weirdness when you try \n"String" or \n'String' variants.
; A space is needed in between \n and the next
; string token (so far) for this feature
; to function properly.
;
; Example:
;
; fputs(\n"This doesn't work", *stdout);
; fputs("Neither this"\n" one here"\n, *stdout);
; fputs(\n "But this"\n "is perfectly fine."\n, *stdout);
; fputs(\n "As well as" \n "this one" \n, *stdout);
;
format ELF64 executable 3

include 'fastcall_v1.inc'
include 'stdmacros.inc'
include 'stdio.inc'

_code   Start entry         endbr64

                            mov         rsi, [stdout]
                            push        [rsi]
                            pop         [stdout]

                            fputs("The most common usage case."\n, [stdout]);
                            fputs(\n "A not so common format, ", [stdout]);
                            fputs("and another uncommon one"\n "here.", *stdout);
                            fputs(\n "But this one should occur quite often."\n, [stdout]);
                            fputs("And this too..."\n\n, [stdout]);
                            fputs(\n\n "Although this one not.", [stdout]);
                            fputs(\n "This one is"\n "quite complex.", [stdout]);
                            fputs\
                            (\n "But the most complex possible variation"\n "is this."\n, \
                                [stdout]);
                            fputs("A common usage with"\n "two '\n' chars."\n, *stdout);
                            fputs\
                            (\n "This is the" \n "safest approach possible", *stdout);
                            fputs(" as pointed at" \n "comments." \n, [stdout]);
                            fputs(<"For all other uses, ", \
                                "and for other special characters, ", \
                                "one should use the classic literal ", \
                                27,"[33m","<""Anything else", \
                                """,""format."",10,0>",27,"[0m.",10,0>, *stdout);
                            exit(0);