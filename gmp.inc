if ~ defined __LIBGMP_INC_INCLUDED__
	define __LIBGMP_INC_INCLUDED__
	define __LIBGMP_INC_INCLUDED__

    library 'libgmp.so.10'

    ; Labeled macroinstructions for variables
    struc mpz_t
        label . : 16
        emit 16, ?
    end struc

    struc mpq_t
        label . : 32
        emit 32, ?
    end struc

    struc mpf_t
        label . : 24
        emit 24, ?
    end struc

    struc gmp_randstate_t
        label . : 32
        emit 32, ?
    end struc

    struc gmp_randalg_t
        label . : 4
        emit 4, ?
    end struc

    ; Initialization Functions
    ext proto __gmpz_init, qword, alias mpz_init
    ext proto __gmpz_inits, qword, vararg, alias mpz_inits
    ext proto __gmpz_init2, qword, qword, alias mpz_init2
    ext proto __gmpz_clear, qword, alias mpz_clear
    ext proto __gmpz_clears, qword, vararg, alias mpz_clears
    ext proto __gmpz_realloc2, qword, qword, alias mpz_realloc2

    ; Assignment Functions
    ext proto __gmpz_set, qword, qword, alias mpz_set
    ext proto __gmpz_set_ui, qword, qword, alias mpz_set_ui
    ext proto __gmpz_set_si, qword, qword, alias mpz_set_si
    ext proto __gmpz_set_d, qword, double, alias mpz_set_d
    ext proto __gmpz_set_q, qword, qword, alias mpz_set_q
    ext proto __gmpz_set_f, qword, qword, alias mpz_set_f
    ext proto __gmpz_set_str, qword, qword, dword, alias mpz_set_str
    ext proto __gmpz_swap, qword, qword, alias mpz_swap

    ; Combined Initialization and Assignment Functions
    ext proto __gmpz_init_set, qword, qword, alias mpz_init_set
    ext proto __gmpz_init_set_ui, qword, qword, alias mpz_init_set_ui
    ext proto __gmpz_init_set_si, qword, qword, alias mpz_init_set_si
    ext proto __gmpz_init_set_d, qword, double, alias mpz_init_set_d
    ext proto __gmpz_init_set_str, qword, qword, dword, alias mpz_init_set_str

    ; Conversion Functions
    ext proto __gmpz_get_ui, qword, alias mpz_get_ui
    ext proto __gmpz_get_si, qword, alias mpz_get_si
    ext proto __gmpz_get_d, qword, alias mpz_get_d
    ext proto __gmpz_get_d_2exp, qword, qword, alias mpz_get_d_2exp
    ext proto __gmpz_get_str, qword, dword, qword, alias mpz_get_str

    ; Arithmetic Functions
    ext proto __gmpz_add, qword, qword, qword, alias mpz_add
    ext proto __gmpz_add_ui, qword, qword, qword, alias mpz_add_ui
    ext proto __gmpz_sub, qword, qword, qword, alias mpz_sub
    ext proto __gmpz_sub_ui, qword, qword, qword, alias mpz_sub_ui
    ext proto __gmpz_ui_sub, qword, qword, qword, alias mpz_ui_sub
    ext proto __gmpz_mul, qword, qword, qword, alias mpz_mul
    ext proto __gmpz_mul_si, qword, qword, qword, alias mpz_mul_si
    ext proto __gmpz_mul_ui, qword, qword, qword, alias mpz_mul_ui
    ext proto __gmpz_addmul, qword, qword, qword, alias mpz_addmul
    ext proto __gmpz_addmul_ui, qword, qword, qword, alias mpz_addmul_ui
    ext proto __gmpz_submul, qword, qword, qword, alias mpz_submul
    ext proto __gmpz_submul_ui, qword, qword, qword, alias mpz_submul_ui
    ext proto __gmpz_mul_2exp, qword, qword, qword, alias mpz_mul_2exp
    ext proto __gmpz_neg, qword, qword, alias mpz_neg
    ext proto __gmpz_abs, qword, qword, alias mpz_abs

    ; Division Functions
    ext proto __gmpz_cdiv_q, qword, qword, qword, alias mpz_cdiv_q
    ext proto __gmpz_cdiv_r, qword, qword, qword, alias mpz_cdiv_r
    ext proto __gmpz_cdiv_qr, qword, qword, qword, qword, alias mpz_cdiv_qr
    ext proto __gmpz_cdiv_q_ui, qword, qword, qword, alias mpz_cdiv_q_ui
    ext proto __gmpz_cdiv_r_ui, qword, qword, qword, alias mpz_cdiv_r_ui
    ext proto __gmpz_cdiv_qr_ui, qword, qword, qword, qword, alias mpz_cdiv_qr_ui
    ext proto __gmpz_cdiv_ui, qword, qword, alias mpz_cdiv_ui
    ext proto __gmpz_cdiv_q_2exp, qword, qword, qword, alias mpz_cdiv_q_2exp
    ext proto __gmpz_cdiv_r_2exp, qword, qword, qword, alias mpz_cdiv_r_2exp
    ext proto __gmpz_fdiv_q, qword, qword, qword, alias mpz_fdiv_q
    ext proto __gmpz_fdiv_r, qword, qword, qword, alias mpz_fdiv_r
    ext proto __gmpz_fdiv_qr, qword, qword, qword, qword, alias mpz_fdiv_qr
    ext proto __gmpz_fdiv_q_ui, qword, qword, qword, alias mpz_fdiv_q_ui
    ext proto __gmpz_fdiv_r_ui, qword, qword, qword, alias mpz_fdiv_r_ui
    ext proto __gmpz_fdiv_qr_ui, qword, qword, qword, qword, alias mpz_fdiv_qr_ui
    ext proto __gmpz_fdiv_ui, qword, qword, alias mpz_fdiv_ui
    ext proto __gmpz_fdiv_q_2exp, qword, qword, qword, alias mpz_fdiv_q_2exp
    ext proto __gmpz_fdiv_r_2exp, qword, qword, qword, alias mpz_fdiv_r_2exp
    ext proto __gmpz_tdiv_q, qword, qword, qword, alias mpz_tdiv_q
    ext proto __gmpz_tdiv_r, qword, qword, qword, alias mpz_tdiv_r
    ext proto __gmpz_tdiv_qr, qword, qword, qword, qword, alias mpz_tdiv_qr
    ext proto __gmpz_tdiv_q_ui, qword, qword, qword, alias mpz_tdiv_q_ui
    ext proto __gmpz_tdiv_r_ui, qword, qword, qword, alias mpz_tdiv_r_ui
    ext proto __gmpz_tdiv_qr_ui, qword, qword, qword, qword, alias mpz_tdiv_qr_ui
    ext proto __gmpz_tdiv_ui, qword, qword, alias mpz_tdiv_ui
    ext proto __gmpz_tdiv_q_2exp, qword, qword, qword, alias mpz_tdiv_q_2exp
    ext proto __gmpz_tdiv_r_2exp, qword, qword, qword, alias mpz_tdiv_r_2exp
    ext proto __gmpz_mod, qword, qword, qword, alias mpz_mod
    ext proto __gmpz_mod_ui, qword, qword, qword, alias mpz_mod_ui
    ext proto __gmpz_divexact, qword, qword, qword, alias mpz_divexact
    ext proto __gmpz_divexact_ui, qword, qword, qword, alias mpz_divexact_ui
    ext proto __gmpz_divisible_p, qword, qword, alias mpz_divisible_p
    ext proto __gmpz_divisible_ui_p, qword, qword, alias mpz_divisible_ui_p
    ext proto __gmpz_divisible_2exp_p, qword, qword, alias mpz_divisible_2exp_p
    ext proto __gmpz_congruent_p, qword, qword, qword, alias mpz_congruent_p
    ext proto __gmpz_congruent_ui_p, qword, qword, qword, alias mpz_congruent_ui_p
    ext proto __gmpz_congruent_2exp_p, qword, qword, qword, alias mpz_congruent_2exp_p

    ; Exponentiation Functions
    ext proto __gmpz_powm, qword, qword, qword, qword, alias mpz_powm
    ext proto __gmpz_powm_ui, qword, qword, qword, qword, alias mpz_powm_ui
    ext proto __gmpz_powm_sec, qword, qword, qword, qword, alias mpz_powm_sec
    ext proto __gmpz_pow_ui, qword, qword, qword, alias mpz_pow_ui
    ext proto __gmpz_ui_pow_ui, qword, qword, qword, alias mpz_ui_pow_ui

    ; Root Extraction Functions
    ext proto __gmpz_root, qword, qword, qword, alias mpz_root
    ext proto __gmpz_rootrem, qword, qword, qword, qword, alias mpz_rootrem
    ext proto __gmpz_sqrt, qword, qword, alias mpz_sqrt
    ext proto __gmpz_sqrtrem, qword, qword, qword, alias mpz_sqrtrem
    ext proto __gmpz_perfect_power_p, qword, alias mpz_perfect_power_p
    ext proto __gmpz_perfect_square_p, qword, alias mpz_perfect_square_p

    ; Number Theorectic Functions
    ; TBD

    ; Comparison Functions
    ext proto __gmpz_cmp, qword, qword, alias mpz_cmp
    ext proto __gmpz_cmp_d, qword, double, alias mpz_cmp_d
    ext proto __gmpz_cmp_si, qword, qword, alias mpz_cmp_si
    ext proto __gmpz_cmp_ui, qword, qword, alias mpz_cmp_ui
    ext proto __gmpz_cmpabs, qword, qword, alias mpz_cmpabs
    ext proto __gmpz_cmpabs_d, qword, double, alias mpz_cmpabs_d
    ext proto __gmpz_cmpabs_ui, qword, qword, alias mpz_cmpabs_ui

    ; Logical and Bit Manipulation Functions
    ext proto __gmpz_and, qword, qword, qword, alias mpz_and
    ext proto __gmpz_ior, qword, qword, qword, alias mpz_ior
    ext proto __gmpz_xor, qword, qword, qword, alias mpz_xor
    ext proto __gmpz_com, qword, qword, alias mpz_com
    ext proto __gmpz_popcount, qword, alias mpz_popcount
    ext proto __gmpz_hamdist, qword, qword, alias mpz_hamdist
    ext proto __gmpz_scan0, qword, qword, alias mpz_scan0
    ext proto __gmpz_scan1, qword, qword, alias mpz_scan1
    ext proto __gmpz_setbit, qword, qword, alias mpz_setbit
    ext proto __gmpz_clrbit, qword, qword, alias mpz_clrbit
    ext proto __gmpz_combit, qword, qword, alias mpz_combit
    ext proto __gmpz_tstbit, qword, qword, alias mpz_tstbit

    ; Input and Output Functions
    ext proto __gmpz_out_str, qword, dword, qword, alias mpz_out_str
    ext proto __gmpz_inp_str, qword, dword, alias mpz_inp_str
    ext proto __gmpz_out_raw, qword, qword, alias mpz_out_raw
    ext proto __gmpz_inp_raw, qword, qword, alias mpz_inp_raw

    ; Random Number Functions
    ext proto __gmpz_urandomm, qword, qword, qword, alias mpz_urandomm
    ext proto __gmpz_rrandomb, qword, qword, qword, alias mpz_rrandomb
    ext proto __gmpz_random, qword, qword, alias mpz_random
    ext proto __gmpz_random2, qword, qword, alias mpz_random2

    ; Integer Import and Export
    ext proto __gmpz_import, qword, qword, dword, qword, dword, qword, qword, alias mpz_import
    ext proto __gmpz_export, qword, qword, dword, qword, dword, qword, qword, alias mpz_export

    ; Miscellaneous Functions
    ext proto __gmpz_fits_ulong_p, qword, alias mpz_fits_ulong_p
    ext proto __gmpz_fits_slong_p, qword, alias mpz_fits_slong_p
    ext proto __gmpz_fits_uint_p, qword, alias mpz_fits_uint_p
    ext proto __gmpz_fits_sint_p, qword, alias mpz_fits_sint_p
    ext proto __gmpz_fits_ushort_p, qword, alias mpz_fits_ushort_p
    ext proto __gmpz_fits_sshort_p, qword, alias mpz_fits_sshort_p
    ext proto __gmpz_odd_p, qword, alias mpz_odd_p
    ext proto __gmpz_even_p, qword, alias mpz_even_p
    ext proto __gmpz_sizeinbase, qword, alias mpz_sizeinbase

    ; Special Functions
    ; TBD

    ; Random Number Functions
    ext proto __gmp_randinit_default, qword, alias gmp_randinit_default
    ext proto __gmp_randinit_mt, qword, alias gmp_randinit_mt
    ext proto __gmp_randinit_lc_2exp, qword, qword, qword, qword, alias gmp_randinit_lc_2exp
    ext proto __gmp_randinit_lc_2exp_size, qword, qword, alias gmp_randinit_lc_2exp_size
    ext proto __gmp_randinit_set, qword, qword, alias gmp_randinit_set
    ext proto __gmp_randinit, qword, dword, vararg, alias gmp_randinit
    ext proto __gmp_randclear, qword, alias gmp_randclear

    ; Random State Miscellaneous
    ext proto __gmp_urandomb_ui, qword, qword, alias gmp_urandomb_ui
    ext proto __gmp_urandomm_ui, qword, qword, alias gmp_urandomm_ui

    ; Format Strings
    ext proto __gmp_printf, qword, vararg, alias gmp_printf
    ext proto __gmp_vprintf, qword, qword, alias gmp_vprintf
    ext proto __gmp_fprintf, qword, qword, vararg, alias gmp_fprintf
    ext proto __gmp_vfprintf, qword, qword, qword, alias gmp_vfprintf
    ext proto __gmp_sprintf, qword, qword, vararg, alias gmp_sprintf
    ext proto __gmp_vsprintf, qword, qword, qword, alias gmp_vsprintf
    ext proto __gmp_snprintf, qword, qword, qword, vararg, alias gmp_snprintf
    ext proto __gmp_vsnprintf, qword, qword, qword, qword, alias gmp_vsnprintf
    ext proto __gmp_asprintf, qword, qword, vararg, alias gmp_asprintf
    ext proto __gmp_vasprintf, qword, qword, qword, alias gmp_vasprintf
    ext proto __gmp_obstack_printf, qword, qword, vararg, alias gmp_obstack_printf
    ext proto __gmp_obstack_vprintf, qword, qword, qword, alias gmp_obstack_vprintf
else
	err "Duplicated inclusion: of 'gmp.inc' file.", 10
end if

