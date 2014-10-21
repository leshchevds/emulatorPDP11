#ifndef MODES_SELECTOR_INC
#define MODES_SELECTOR_INC

case 0:
    *ARG = (void*)reg;
    break;
case 1:
    *ARG = (void*)(mem_+*reg);
    break;
case 2:
    *ARG = (void*)(mem_+*reg);
    *reg+=is_byte_instr?1:2;
    break;
case 3:
    *ARG = (*(u_int16_t*)(mem_+*reg))+mem_;
    *reg+=2;
    break;
case 4:
    *reg-=is_byte_instr?1:2;
    *ARG = (void*)(mem_+*reg);
    break;
case 5:
    *reg-=2;
    *ARG = (*(u_int16_t*)(mem_+*reg))+mem_;
    break;
case 6:
    *ARG = (*(u_int16_t*)(mem_+pc_))+mem_+*reg;
    opcode << std::hex << *(u_int16_t*)ARG;
    pc_+=2;
    break;
case 7:
    *ARG = (*(u_int16_t*)(mem_+pc_))+mem_+*reg;
    opcode << std::hex << *(u_int16_t*)ARG;
    *ARG = (*(u_int16_t*)(*ARG))+mem_;
    pc_+=2;
    break;
#endif // MODES_SELECTOR_INC
