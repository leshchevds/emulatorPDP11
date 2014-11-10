#define REG 0
#define IND_REG 1
#define AUTOINC 2
#define IND_AUTOINC 3
#define AUTODEC 4
#define IND_AUTODEC 5
#define INDEX 6
#define IND_INDEX 7
case REG:
    *ARG = (void*)reg;
    break;
case IND_REG:
    *ARG = (void*)(mem_ + *reg);
    break;
case AUTOINC:
    *ARG = (void*)(mem_ + *reg);
    #ifndef PC
    *reg += is_byte_instr ? 1 : 2;
    #endif
    #ifdef PC
    *reg += 2;
    opcode << "0x" << std::hex << *(uint16_t*)*ARG ;
    #endif
    break;
case IND_AUTOINC:
    *ARG = (*(uint16_t*)(mem_ + *reg)) + mem_;
    *reg+=2;
    #ifdef PC
    *reg += 2;
    opcode << "0x" << std::hex << *(uint16_t*)*ARG ;
    #endif
    break;
case AUTODEC:
    #ifndef PC
    *reg += is_byte_instr ? 1 : 2;
    #endif
    #ifdef PC
    *reg += 2;
    #endif
    *ARG = (void*)(mem_ + *reg);
    break;
case IND_AUTODEC:
    *reg -= 2;
    *ARG = (*(uint16_t*)(mem_ + *reg)) + mem_;
    break;
//TODO 67&77 modes
case INDEX:
    *ARG = (*(uint16_t*)(mem_ + pc_)) + mem_ + *reg;
    opcode << std::hex << *(uint16_t*)ARG << "]";
    pc_ += 2;
    break;
case IND_INDEX:
    *ARG = (*(uint16_t*)(mem_ + pc_)) + mem_ + *reg;
    opcode << std::hex << *(uint16_t*)ARG << "]";
    *ARG = (*(uint16_t*)(*ARG)) + mem_;
    pc_ += 2;
    break;
#undef REG
#undef IND_REG
#undef AUTOINC
#undef IND_AUTOINC
#undef AUTODEC
#undef IND_AUTODEC
#undef INDEX
#undef IND_INDEX
