#ifndef TAB_INC
#define TAB_INC
#pragma GCC diagnostic ignored "-Wwrite-strings"
    typedef std::string (EmulatorPDP11::*d_func)(void** ,void**);
    typedef void (EmulatorPDP11::*e_func)(void* ,void*);

    struct instr_t {
        u_int16_t opcode;
        char* instr;
        d_func decoder;
        e_func callback;
    };
    //DISCUSS? decode_zero_op -> NULL

    instr_t tab[86] = {
        {0000000,   "halt", &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_halt},
        {0000001,   "wait", &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_wait},
        {0000002,   "rti",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_rti},
        {0000003,   "bpt",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_bpt},
        {0000004,   "iot",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_iot},
        {0000005,   "reset",&EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_reset},
        {0000006,   "rtt",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_rtt},
        {0000100,   "jmp",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_jmp},
        {0000200,   "rts",  &EmulatorPDP11::decode_half_op, &EmulatorPDP11::op_rts},
        {0000230,   "spl",  &EmulatorPDP11::decode_half_op, &EmulatorPDP11::op_spl},
        {0000240,   "nop",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_nop},
        {0000241,   "clc",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_clc},
        {0000242,   "clv",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_clv},
        {0000244,   "clz",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_clz},
        {0000250,   "cln",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_cln},
        {0000257,   "ccc",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_ccc},
        {0000261,   "sec",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_sec},
        {0000262,   "sev",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_sev},
        {0000264,   "sez",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_sez},
        {0000270,   "sen",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_sen},
        {0000277,   "scc",  &EmulatorPDP11::decode_zero_op, &EmulatorPDP11::op_scc},
        {0000300,   "swab", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_swab},
        {0x0100,    "br",   &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_br},
        {0x0200,    "bne",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bne},
        {0x0300,    "beq",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_beq},
        {0x0400,    "bge",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bge},
        {0x0500,    "blt",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_blt},
        {0x0600,    "bgt",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bgt},
        {0x0700,    "ble",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_ble},
        {0004000,   "jsr",  &EmulatorPDP11::decode_oNh_op,  &EmulatorPDP11::op_jsr},
        {0005000,   "clr",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_clr},
        {0005100,   "com",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_com},
        {0005200,   "inc",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_inc},
        {0005300,   "dec",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_dec},
        {0005400,   "neg",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_neg},
        {0005500,   "adc",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_adc},
        {0005600,   "sbc",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_sbc},
        {0005700,   "tst",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_tst},
        {0006000,   "ror",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_ror},
        {0006100,   "rol",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_rol},
        {0006200,   "asr",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_asr},
        {0006300,   "asl",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_asl},
        {0006400,   "mark", &EmulatorPDP11::decode_one_pl,  &EmulatorPDP11::op_mark},
        {0006500,   "mfpi", &EmulatorPDP11::decode_one_pl,  &EmulatorPDP11::op_mfpi},
        {0006600,   "mtpi", &EmulatorPDP11::decode_one_pl,  &EmulatorPDP11::op_mtpi},
        {0006700,   "sxt",  &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_sxt},
        {0010000,   "mov",  &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_mov},
        {0020000,   "cmp",  &EmulatorPDP11::decode_two_op_no_check,  &EmulatorPDP11::op_cmp},
        {0030000,   "bit",  &EmulatorPDP11::decode_two_op_no_check,  &EmulatorPDP11::op_bit},
        {0040000,   "bic",  &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_bic},
        {0050000,   "bis",  &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_bis},
        {0060000,   "add",  &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_add},
        {0070000,   "mul",  &EmulatorPDP11::decode_oNh_op,  &EmulatorPDP11::op_mul},
        {0071000,   "div",  &EmulatorPDP11::decode_oNh_op,  &EmulatorPDP11::op_div},
        {0072000,   "ash",  &EmulatorPDP11::decode_oNh_op,  &EmulatorPDP11::op_ash},
        {0073000,   "ashc", &EmulatorPDP11::decode_oNh_op,  &EmulatorPDP11::op_ashc},
        {0074000,   "xor",  &EmulatorPDP11::decode_xor,     &EmulatorPDP11::op_xor},
        {0077000,   "sob",  &EmulatorPDP11::decode_sob,     &EmulatorPDP11::op_sob},    //077Rnn R - register nn - uint6
        {0x8000,    "bpl",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bpl},
        {0x8100,    "bmi",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bmi},
        {0x8200,    "bhi",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bhi},
        {0x8300,    "blos", &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_blos},
        {0x8400,    "bvc",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bvc},
        {0x8500,    "bvs",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bvs},
        {0x8600,    "bcc",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bcc},
        {0x8700,    "bcs",  &EmulatorPDP11::decode_branch,  &EmulatorPDP11::op_bcs},
        {0x8800,    "emt",  &EmulatorPDP11::decode_traps,   &EmulatorPDP11::op_emt},
        {0x8900,    "sys",  &EmulatorPDP11::decode_traps,   &EmulatorPDP11::op_sys},
        {0105000,   "clrb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_clrb},
        {0105100,   "comb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_comb},
        {0105200,   "incb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_incb},
        {0105300,   "decb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_decb},
        {0105400,   "negb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_negb},
        {0105500,   "adcb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_adcb},
        {0105600,   "sbcb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_sbcb},
        {0105700,   "tstb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_tstb},
        {0106000,   "rorb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_rorb},
        {0106100,   "rolb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_rolb},
        {0106200,   "asrb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_asrb},
        {0106300,   "aslb", &EmulatorPDP11::decode_one_op,  &EmulatorPDP11::op_aslb},
        //{0106400,   "mtps", decode_one_op,  op_mtps},
        //{0106500,   "mfpd", decode_one_op,  op_mfpd},
        //{0106600,   "mtpd", decode_one_op,  op_mtpd},
        //{0106700,   "mfps", decode_one_op,  op_mfpd},
        {0110000,   "movb", &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_movb},
        {0120000,   "cmpb", &EmulatorPDP11::decode_two_op_no_check,  &EmulatorPDP11::op_cmpb},
        {0130000,   "bitb", &EmulatorPDP11::decode_two_op_no_check,  &EmulatorPDP11::op_bitb},
        {0140000,   "bicb", &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_bicb},
        {0150000,   "bisb", &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_bisb},
        {0160000,   "sub",  &EmulatorPDP11::decode_two_op,  &EmulatorPDP11::op_sub}
    };//86 lines



#endif // TAB_INC
