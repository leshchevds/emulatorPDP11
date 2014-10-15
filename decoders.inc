#ifndef DECODERS_INC
#define DECODERS_INC

std::string decode_zero_op(u_int16_t* pc);
std::string decode_one_op(u_int16_t* pc);
std::string decode_oNh_op(u_int16_t* pc);
std::string decode_two_op(u_int16_t* pc);
std::string decode_half_op(u_int16_t* pc);
std::string decode_branch(u_int16_t* pc);
std::string decode_traps(u_int16_t* pc);
std::string decode_one_pl(u_int16_t* pc);
std::string decode_sob(u_int16_t* pc);
std::string decode_xor(u_int16_t* pc);
std::string decode_mark(u_int16_t* pc);
#endif // DECODERS_INC
