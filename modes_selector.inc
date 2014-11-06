
case 0:
    *ARG = (void*)reg;
    break;
case 1:
    *ARG = (void*)(mem_ + *reg);
    break;
case 2:
    *ARG = (void*)(mem_ + *reg);
    #ifndef PC
    *reg += is_byte_instr ? 1 : 2;
    #endif
    #ifdef PC
    *reg += 2;
    opcode << "0x" << std::hex << *(uint16_t*)*ARG ;
    #endif
    break;
case 3:
    *ARG = (*(uint16_t*)(mem_ + *reg)) + mem_;
    *reg+=2;
    #ifdef PC
    *reg += 2;
    opcode << "0x" << std::hex << *(uint16_t*)*ARG ;
    #endif
    break;
case 4:
    #ifndef PC
    *reg += is_byte_instr ? 1 : 2;
    #endif
    #ifdef PC
    *reg += 2;
    #endif
    *ARG = (void*)(mem_ + *reg);
    break;
case 5:
    *reg -= 2;
    *ARG = (*(uint16_t*)(mem_ + *reg)) + mem_;
    break;
//TODO 67&77 modes
case 6:
    *ARG = (*(uint16_t*)(mem_ + pc_)) + mem_ + *reg;
    opcode << std::hex << *(uint16_t*)ARG << "]";
    pc_ += 2;
    break;
case 7:
    *ARG = (*(uint16_t*)(mem_ + pc_)) + mem_ + *reg;
    opcode << std::hex << *(uint16_t*)ARG << "]";
    *ARG = (*(uint16_t*)(*ARG)) + mem_;
    pc_ += 2;
    break;

