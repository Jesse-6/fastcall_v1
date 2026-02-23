; Hello World multi language example using libsmlproto and its SMLP specification.
; Available at: https://github.com/Jesse-6/libsmlproto
;

format ELF64 executable 3

include 'fastcall_v1.inc'
include 'stdmacros.inc'
include 'stdio.inc'
include 'smlp.inc'

_rdata  locales:                db 'af_ZA', 0, 0, 0
                                db 'am_ET', 0, 0, 0
                                db 'ar_SA', 0, 0, 0
                                db 'az_AZ', 0, 0, 0
                                db 'be_BY', 0, 0, 0
                                db 'bg_BG', 0, 0, 0
                                db 'bn_BD', 0, 0, 0
                                db 'bs_BA', 0, 0, 0
                                db 'ca_ES', 0, 0, 0
                                db 'cs_CZ', 0, 0, 0
                                db 'cy_GB', 0, 0, 0
                                db 'da_DK', 0, 0, 0
                                db 'de_DE', 0, 0, 0
                                db 'el_GR', 0, 0, 0
                                db 'en_US', 0, 0, 0
                                db 'en_GB', 0, 0, 0
                                db 'eo_EO', 0, 0, 0
                                db 'es_ES', 0, 0, 0
                                db 'es_MX', 0, 0, 0
                                db 'et_EE', 0, 0, 0
                                db 'eu_ES', 0, 0, 0
                                db 'fa_IR', 0, 0, 0
                                db 'fi_FI', 0, 0, 0
                                db 'fr_FR', 0, 0, 0
                                db 'ga_IE', 0, 0, 0
                                db 'gl_ES', 0, 0, 0
                                db 'gu_IN', 0, 0, 0
                                db 'he_IL', 0, 0, 0
                                db 'hi_IN', 0, 0, 0
                                db 'hr_HR', 0, 0, 0
                                db 'hu_HU', 0, 0, 0
                                db 'hy_AM', 0, 0, 0
                                db 'id_ID', 0, 0, 0
                                db 'is_IS', 0, 0, 0
                                db 'it_IT', 0, 0, 0
                                db 'ja_JP', 0, 0, 0
                                db 'ka_GE', 0, 0, 0
                                db 'kk_KZ', 0, 0, 0
                                db 'km_KH', 0, 0, 0
                                db 'kn_IN', 0, 0, 0
                                db 'ko_KR', 0, 0, 0
                                db 'lt_LT', 0, 0, 0
                                db 'lv_LV', 0, 0, 0
                                db 'mk_MK', 0, 0, 0
                                db 'ml_IN', 0, 0, 0
                                db 'mn_MN', 0, 0, 0
                                db 'mr_IN', 0, 0, 0
                                db 'ms_MY', 0, 0, 0
                                db 'mt_MT', 0, 0, 0
                                db 'nb_NO', 0, 0, 0
                                db 'ne_NP', 0, 0, 0
                                db 'nl_NL', 0, 0, 0
                                db 'nn_NO', 0, 0, 0
                                db 'pa_IN', 0, 0, 0
                                db 'pl_PL', 0, 0, 0
                                db 'pt_BR', 0, 0, 0
                                db 'pt_PT', 0, 0, 0
                                db 'ro_RO', 0, 0, 0
                                db 'ru_RU', 0, 0, 0
                                db 'si_LK', 0, 0, 0
                                db 'sk_SK', 0, 0, 0
                                db 'sl_SI', 0, 0, 0
                                db 'sq_AL', 0, 0, 0
                                db 'sr_RS', 0, 0, 0
                                db 'sv_SE', 0, 0, 0
                                db 'sw_KE', 0, 0, 0
                                db 'ta_IN', 0, 0, 0
                                db 'te_IN', 0, 0, 0
                                db 'th_TH', 0, 0, 0
                                db 'tr_TR', 0, 0, 0
                                db 'uk_UA', 0, 0, 0
                                db 'ur_PK', 0, 0, 0
                                db 'uz_UZ', 0, 0, 0
                                db 'vi_VN', 0, 0, 0
                                db 'zh_CN', 0, 0, 0
                                db 'zh_TW', 0, 0, 0
                                db 'zu_ZA', 0, 0, 0
                                db -1

_code   Start entry:            endbr64
                                sub         rsp, 32

                                lea         r15, [locales]
                        @@      snprintf(rsp, 32, "%s.UTF-8", r15);
                                setenv("LANG", rsp, TRUE);

                                SMLP_InitLanguage("lang/hello/", "hello_world.", ".txt", 640);
                                test        rax, rax
                                jz          .err
                                mov         rbx, rax
                                mov         rbp, rdx

                                SMLP_ParseEscapedString([rax], [rax]);

                                fprintf(**stdout, [rbx], rbp, [rbx+8]);

                                add         r15, 8
                                cmp         [r15], byte -1
                                je          @f

                                SMLP_Cleanup(TRUE);
                                usleep(250000);
                                jmp         @b

                        @@      SMLP_Cleanup(FALSE);

                                exit(0);

            .err:               exit(1);

