#include <stdio.h>
#include <stdint.h>
#define BIT_MASK(n)     ((((uint32_t)1)<< (n)) -1)
#define BIT_MASKS(start, end) (BIT_MASK(start) & ~BIT_MASK(end))
#define GET_INST_BITS(inst, start, end)  ((inst) & BIT_MASKS(start, end)) 
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
    x=x>>n;
    return x&1;
    
}
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned * x,
             unsigned n,
             unsigned v) {
    // YOUR CODE HERE
    v=v<<n;
    unsigned a=1<<n;
    *x=(*x|a)^v^a;
    //*x=*x^v;
    ////*x=*x^a;
}
// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned * x,
              unsigned n) {
    // YOUR CODE HERE
    unsigned a=1<<n;
    *x=*x^a;
}

//Encoding the instruction
OPCODE decode_riscv_inst(uint32_t inst){
    // YOUR CODE HERE
    printf("%u\n",GET_INST_BITS(inst,7,0));
    if(GET_INST_BITS(inst,7,0)==55){
	    printf("LUI is correct\n");
	    return LUI;
    }
    else if(GET_INST_BITS(inst,7,0)==23){
            printf("AUIPC is correct\n");
            return AUIPC;
    }
    else if(GET_INST_BITS(inst,7,0)==111){
	    printf("JAL is correct\n");
	    return JAL;
    }
    else if(GET_INST_BITS(inst,7,0)==103){
	    printf("JALR is correct\n");
	    return JALR;
    }
    else if(GET_INST_BITS(inst,7,0)==99){
	    printf("%u\n",GET_INST_BITS(inst,15,12)>>12);
	    if(GET_INST_BITS(inst,15,12)>>12==0){
		    printf("BEQ is correct\n");
		    return BEQ;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==1){
		    printf("BNE is correct\n");
		    return BNE;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==4){
		    printf("BLT is correct\n");
		    return BLT;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==5){
		    printf("BGE is correct\n");
		    return BGE;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==6){
		    printf("BLTU is correct\n");
		    return BLTU;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==7){
		    printf("BGEU is correct\n");
		    return BGEU;
	    }
    }
    else if(GET_INST_BITS(inst,7,0)==3){
	    printf("%u\n",GET_INST_BITS(inst,15,12)>>12);
	    if(GET_INST_BITS(inst,15,12)>>12==0){
		    printf("LB is correct\n");
		    return LB;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==1){
		    printf("LH is correct\n");
		    return LH;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==2){
		    printf("LW is correct\n");
		    return LW;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==4){
		    printf("LBU is correct\n");
		    return LBU;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==5){
		    printf("LHU is correct\n");
		    return LHU;
	    }
    }
    else if(GET_INST_BITS(inst,7,0)==35){
	    printf("%u\n",GET_INST_BITS(inst,15,12)>>12);
	    if(GET_INST_BITS(inst,15,12)>>12==0){
		    printf("SB is correct\n");
		    return SB;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==1){
		    printf("SH is correct\n");
		    return SH;
            }
	    else if(GET_INST_BITS(inst,15,12)>>12==2){
		    printf("SW is correct\n");
		    return LW;
	    }
    }
    else if(GET_INST_BITS(inst,7,0)==19){
	    printf("%u\n",GET_INST_BITS(inst,15,12)>>12);
	    if(GET_INST_BITS(inst,15,12)>>12==0){
		    printf("ADDI is correct\n");
		    return ADDI;
	    }
            else if(GET_INST_BITS(inst,15,12)>>12==2){
		    printf("SLTI is correct\n");
		    return SLTI;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==3){
		    printf("SLTIU is correct\n");
		    return SLTIU;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==4){
		    printf("XORI is correct\n");
		    return XORI;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==6){
		    printf("ORI is correct\n");
		    return ORI;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==7){
		    printf("ANDI is correct\n");
		    return ANDI;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==1){
		    printf("SLLI is correct\n");
		    return SLLI;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==5){
		    if(GET_INST_BITS(inst,31,25)>>25==0){
			    printf("SRLI is correct\n");
			    return SRLI;
		    }
		    else{
			    printf("SRAI is correct\n");
			    return SRAI;
		    }
	    }
    }
    else if(GET_INST_BITS(inst,7,0)==51){
	    printf("%u\n",GET_INST_BITS(inst,15,12)>>12);
	    if(GET_INST_BITS(inst,15,12)>>12==0){
		    if(GET_INST_BITS(inst,31,25)>>25==0){
			    printf("ADD is correct\n");
			    return ADD;
		    }
		    else{
			    printf("SUB is correct\n");
			    return SUB;
		    }
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==1){
		    printf("SLL is correct\n");
		    return SLL;
	    }
            else if(GET_INST_BITS(inst,15,12)>>12==2){
		    printf("SLT is correct\n");
		    return SLT;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==3){
		    printf("SLTU is correct\n");
		    return SLTU;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==4){
		    printf("XOR is correct\n");
		    return XOR;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==5){
		    if(GET_INST_BITS(inst,31,25)>>25==0){
			    printf("SRL is correct\n");
			    return SRL;
		    }
		    else{
			    printf("SRA is correct\n");
			    return SRA;
		    }
	    }
            else if(GET_INST_BITS(inst,15,12)>>12==6){
		    printf("OR is correct\n");
		    return OR;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==7){
		    printf("AND is correct\n");
		    return AND;
	    }
    }
    else if(GET_INST_BITS(inst,7,0)==15){
	    printf("%u\n",GET_INST_BITS(inst,15,12)>>12);
            if(GET_INST_BITS(inst,15,12)>>12==0){
		    printf("FENCE is correct\n");
		    return FENCE;
	    }
	    else{
		    printf("FENCE.I is correct\n");
		    return FENCEI;
	    }
    }
    else if(GET_INST_BITS(inst,7,0)==115){
	    printf("%u\n",GET_INST_BITS(inst,15,12)>>12);
            if(GET_INST_BITS(inst,15,12)>>12==0){
		    if(GET_INST_BITS(inst,31,25)>>25==0){
			    printf("ECALL is correct\n");
			    return ECALL;
		    }
		    else{
			    printf("EBREAK is correct\n");
			    return EBREAK;
		    }
	    }
            else if(GET_INST_BITS(inst,15,12)>>12==1){
		    printf("CSRRW is correct\n");
		    return CSRRW;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==2){
		    printf("CSRRS is correct\n");
		    return CSRRS;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==3){
		    printf("CSRRC is correct\n");
		    return CSRRC;
	    }
            else if(GET_INST_BITS(inst,15,12)>>12==5){
		    printf("CSRRWI is correct\n");
		    return CSRRWI;
	    }
	    else if(GET_INST_BITS(inst,15,12)>>12==6){
		    printf("CSRRSI is correct\n");
		    return CSRRSI;
	    }
            else if(GET_INST_BITS(inst,15,12)>>12==7){
		    printf("CSRRCI is correct\n");
		    return CSRRCI;
	    }
    }
    return UNDEFINED;
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
    if(decode_riscv_inst(inst)!=SRLI) return 0;
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
