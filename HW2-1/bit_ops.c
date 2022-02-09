#include <stdio.h>
#include <stdint.h>

typedef enum{
    LUI,
    AUIPC,
    JAL,
    JALR,
    BEQ,
    BNE,
    BLT,
    BGE,
    BLTU,
    BGEU,
    LB,
    LH,
    LW,
    LBU,
    LHU,
    SB,
    SH,
    SW,
    ADDI,
    SLTI,
    SLTIU,
    XORI,
    ORI,
    ANDI,
    SLLI,
    SRLI,
    SRAI,
    ADD,
    SUB,
    SLL,
    SLT,
    SLTU,
    XOR,
    SRL,
    SRA,
    OR,
    AND,
    FENCE,
    FENCEI,
    ECALL,
    EBREAK,
    CSRRW,
    CSRRS,
    CSRRC,
    CSRRWI,
    CSRRSI,
    CSRRCI,
    UNDEFINED
}OPCODE;

// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x,
                 unsigned n) {
    // YOUR CODE HERE
    // Returning -1 is a placeholder (it makes
    // no sense, because get_bit only returns 
    // 0 or 1)
    return -1;
}
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned * x,
             unsigned n,
             unsigned v) {
    // YOUR CODE HERE
}
// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned * x,
              unsigned n) {
    // YOUR CODE HERE
}

//Encoding the instruction
OPCODE decode_riscv_inst(uint32_t inst){
    // YOUR CODE HERE
    return -1;
}


/*
 * YOU CAN IGNORE THE REST OF THIS FILE
 */

void test_get_bit(unsigned x,
                  unsigned n,
                  unsigned expected) {
    unsigned a = get_bit(x, n);
    if(a!=expected) {
        printf("get_bit(0x%08x,%u): 0x%08x, expected 0x%08x\n",x,n,a,expected);
    } else {
        printf("get_bit(0x%08x,%u): 0x%08x, correct\n",x,n,a);
    }
}
void test_set_bit(unsigned x,
                  unsigned n,
                  unsigned v,
                  unsigned expected) {
    unsigned o = x;
    set_bit(&x, n, v);
    if(x!=expected) {
        printf("set_bit(0x%08x,%u,%u): 0x%08x, expected 0x%08x\n",o,n,v,x,expected);
    } else {
        printf("set_bit(0x%08x,%u,%u): 0x%08x, correct\n",o,n,v,x);
    }
}
void test_flip_bit(unsigned x,
                   unsigned n,
                   unsigned expected) {
    unsigned o = x;
    flip_bit(&x, n);
    if(x!=expected) {
        printf("flip_bit(0x%08x,%u): 0x%08x, expected 0x%08x\n",o,n,x,expected);
    } else {
        printf("flip_bit(0x%08x,%u): 0x%08x, correct\n",o,n,x);
    }
}
_Bool test_decode_riscv_inst(){
    uint32_t inst;
    inst = 0x37;
    if(decode_riscv_inst(inst)!=LUI) return 0;
    inst = 0x00010597;
    if(decode_riscv_inst(inst)!=AUIPC) return 0;
    inst = 0x054000ef;
    if(decode_riscv_inst(inst)!=JAL) return 0;
    inst = 0x00008067;
    if(decode_riscv_inst(inst)!=JALR) return 0;
    inst = 0x0262e863;
    if(decode_riscv_inst(inst)!=BLTU) return 0;
    inst = 0x00012403;
    if(decode_riscv_inst(inst)!=LW) return 0;
    inst = 0xffe40c23;
    if(decode_riscv_inst(inst)!=SB) return 0;
    inst = 0x2013;
    if(decode_riscv_inst(inst)!=SLTI) return 0;
    inst = 0x1f093;
    if(decode_riscv_inst(inst)!=ANDI) return 0;
    inst = 0xd113;
    if(decode_riscv_inst(inst)!=SRAI) return 0;
    inst = 0x005303b3;
    if(decode_riscv_inst(inst)!=ADD) return 0;
    inst = 0x40638333;
    if(decode_riscv_inst(inst)!=SUB) return 0;
    inst = 0x0062b2b3;
    if(decode_riscv_inst(inst)!=SLTU) return 0;
    inst = 0x0062c2b3;
    if(decode_riscv_inst(inst)!=XOR) return 0;
    inst = 0x0110000f;
    if(decode_riscv_inst(inst)!=FENCE) return 0;
    inst = 0x300332f3;
    if(decode_riscv_inst(inst)!=CSRRC) return 0;
    inst = 0x11110000;
    if(decode_riscv_inst(inst)!=UNDEFINED) return 0;

    return 1;

}
int main(int argc,
         const char * argv[]) {
    
    printf("\nTesting get_bit()\n\n");
    test_get_bit(0b1001110,0,0);
    test_get_bit(0b1001110,1,1);
    test_get_bit(0b1001110,5,0);
    test_get_bit(0b11011,3,1);
    test_get_bit(0b11011,2,0);
    test_get_bit(0b11011,9,0);
    printf("\nTesting set_bit()\n\n");
    test_set_bit(0b1001110,2,0,0b1001010);
    test_set_bit(0b1101101,0,0,0b1101100);
    test_set_bit(0b1001110,2,1,0b1001110);
    test_set_bit(0b1101101,0,1,0b1101101);
    test_set_bit(0b1001110,9,0,0b1001110);
    test_set_bit(0b1101101,4,0,0b1101101);
    test_set_bit(0b1001110,9,1,0b1001001110);
    test_set_bit(0b1101101,7,1,0b11101101);
    printf("\nTesting flip_bit()\n\n");
    test_flip_bit(0b1001110,0,0b1001111);
    test_flip_bit(0b1001110,1,0b1001100);
    test_flip_bit(0b1001110,2,0b1001010);
    test_flip_bit(0b1001110,5,0b1101110);
    test_flip_bit(0b1001110,9,0b1001001110);
    printf("\n");

    printf("\nTesting decode_riscv_inst()\n\n");
    if(test_decode_riscv_inst()) printf("Your decode function is correct.\n");
    else printf("Your decode function may have something wrong.\n");

    return 0;
}
