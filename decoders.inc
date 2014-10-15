#ifndef DECODERS_INC
#define DECODERS_INC

std::string decode_zero_op(void* a, void* b);
std::string decode_one_op(void* a, void* b);
std::string decode_oNh_op(void* a, void* b);
std::string decode_two_op(void* a, void* b);
std::string decode_two_op_no_check(void* a, void* b);
std::string decode_half_op(void* a, void* b);
std::string decode_branch(void* a, void* b);
std::string decode_traps(void* a, void* b);
std::string decode_one_pl(void* a, void* b);
std::string decode_sob(void* a, void* b);
std::string decode_xor(void* a, void* b);
std::string decode_mark(void* a, void* b);
#endif // DECODERS_INC
