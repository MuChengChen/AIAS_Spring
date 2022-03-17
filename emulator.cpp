#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "cachesim.h"

#include "linenoise.hpp"

// 64 KB
#define MEM_BYTES 0x10000
#define TEXT_OFFSET 0
#define DATA_OFFSET 32768

#define MAX_LABEL_COUNT 128
#define MAX_LABEL_LEN 32
#define MAX_SRC_LEN (1024*1024)

typedef struct {
	char* src;
	int offset;
} source;

bool streq(char* s, const char* q) {
	if ( strcmp(s,q) == 0 ) return true;

	return false;
}

uint32_t signextend(uint32_t in, int bits) {
	if ( in & (1<<(bits-1)) ) return ((-1)<<bits)|in;
	return in;
}

void print_syntax_error(int line, const char* msg) {
	printf( "Line %4d: Syntax error! %s\n", line, msg );
	exit(1);
}

void print_regfile(uint32_t rf[32]) {
	for ( int i = 0; i < 32; i++ ) {
		printf( "x%02d:0x%08x ", i, rf[i] );
		if ( (i+1) % 8 == 0 ) printf( "\n" );
	}
}


typedef enum {
	UNIMPL = 0,
	//-----------wilson-----------//
	andn,
	clmul,
	clmulh,
	clmulr,
	clz,
	cpop,
	ctz,
	//-----------wilson-----------//



	//---------KAI HONG WANG-----------------------------------------------------------
    MUL, //! added
	MULH, //! added
	MULHSU, //! added
	MULHU, //! added
	DIV,  //! added
	DIVU, //! added
	REM,  //! added
	REMU, //! added

	MAX,   //! added
	MAXU, //! added
	MIN, //! added
	MINU, //! added
	ORCD, //! added-->orc.d
	ORN, //! added
	REV8, //! added-->rev8
//	SEXT_H,  //! added-->sext.h
//	SEXT_B,
	//---------KAI HONG WANG-----------------------------------------------------------
	
	
	//-----------culture0418-----------//
	BCLR,
	BCLRI,
	BEXT,
	BEXTI,
	BINV,
	BINVI,
	BSET,
	BSETI,
	//-----------culture0418-----------//
	
	//-----------song-fung-yu----------//
	BSETI,
	SEXTB,
	SEXTH,
	SH1ADD,
	SH2ADD,
	SH3ADD,
	//-----------song-fung-yu----------//
	
	


	ADD,
	ADDI,
	AND,
	ANDI,
	AUIPC,
	BEQ,
	BGE,
	BGEU,
	BLT,
	BLTU,
	BNE,
	JAL,
	JALR,
	LB,
	LBU,
	LH,
	LHU,
	LUI,
	LW,
	OR,
	ORI,
	SB,
	SH,
	SLL,
	SLLI,
	SLT,
	SLTI,
	SLTIU,
	SLTU,
	SRA,
	SRAI,
	SRL,
	SRLI,
	SUB,
	SW,
	XOR,
	XORI,
	HCF
} instr_type;

instr_type parse_instr(char* tok) {
	
	//-----------wilson-----------//
	if ( streq(tok, "andn") ) return andn;
	if ( streq(tok, "clmul") ) return clmul;
	if ( streq(tok, "clmulh") ) return clmulh;
	if ( streq(tok, "clmulr") ) return clmulr;
	if ( streq(tok, "clz") ) return clz;
	if ( streq(tok, "cpop") ) return cpop;
	if ( streq(tok, "ctz") ) return ctz;
	//-----------wilson-----------//


	//---------KAI-HONG-WANG-----------------------------------------------------------
    if ( streq(tok , "mul")) return MUL;   //! added
	if ( streq(tok , "mulh")) return MULH; //! added
	if ( streq(tok , "mulhsu")) return MULHSU; //! added
	if ( streq(tok , "mulhu")) return MULHU; //! added
	if ( streq(tok , "div")) return DIV; //! added
	if ( streq(tok , "divu")) return DIVU; //! added
	if ( streq(tok , "rem")) return REM; //! added
	if ( streq(tok , "remu")) return REMU; //! added

    if ( streq(tok , "max")) return MAX;   //! added
	if ( streq(tok , "maxu")) return MAXU; //! added
	if ( streq(tok , "min")) return MIN; //! added
	if ( streq(tok , "minu")) return MINU; //! added
	if ( streq(tok , "orc.d")) return ORCD; //! added
	if ( streq(tok , "orn")) return ORN; //! added
	if ( streq(tok , "rev8")) return REV8; //! added-->rev8-->8 bits
//	if ( streq(tok , "sext.h")) return SEXT_H; //! added-->sext.h
//	if ( streq(tok , "sext.b")) return SEXT_B; //! added-->sext.b
	//---------KAI-HONG-WANG-----------------------------------------------------------


	//-----------culture0418-----------//
	if ( streq(tok, "bclr") ) return BCLR;
	if ( streq(tok, "bclri") ) return BCLRI;
	if ( streq(tok, "bext") ) return BEXT;
	if ( streq(tok, "bexti") ) return BEXTI;
	if ( streq(tok, "binv") ) return BINV;
	if ( streq(tok, "binvi") ) return BINVI;
	if ( streq(tok, "bset") ) return BSET;
	if ( streq(tok, "bseti") ) return BSETI;

	//-----------culture0418-----------//
	
	//-----------song-fung-yu----------//
	if ( streq(tok, "bseti") )  return BSETI;
	if ( streq(tok, "sext.b") ) return SEXTB;
	if ( streq(tok, "sext.h") ) return SEXTH;
	if ( streq(tok, "sh1add") ) return SH1ADD;
	if ( streq(tok, "sh2add") ) return SH2ADD;
	if ( streq(tok, "sh3add") ) return SH3ADD;
	//-----------song-fung-yu----------//

	


	// 2r->1r
	if ( streq(tok, "add") ) return ADD;
	if ( streq(tok, "sub") ) return SUB;
	if ( streq(tok, "slt") ) return SLT;
	if ( streq(tok, "sltu") ) return SLTU;
	if ( streq(tok, "and") ) return AND;
	if ( streq(tok, "or") ) return OR;
	if ( streq(tok, "xor") ) return XOR;
	if ( streq(tok, "sll") ) return SLL;
	if ( streq(tok, "srl") ) return SRL;
	if ( streq(tok, "sra") ) return SRA;

	// 1r, imm -> 1r
	if ( streq(tok, "addi") ) return ADDI;
	if ( streq(tok, "slti") ) return SLTI;
	if ( streq(tok, "sltiu") ) return SLTIU;
	if ( streq(tok, "andi") ) return ANDI;
	if ( streq(tok, "ori") ) return ORI;
	if ( streq(tok, "xori") ) return XORI;
	if ( streq(tok, "slli") ) return SLLI;
	if ( streq(tok, "srli") ) return SRLI;
	if ( streq(tok, "srai") ) return SRAI;

	//load/store
	if ( streq(tok, "lb") ) return LB;
	if ( streq(tok, "lbu") ) return LBU;
	if ( streq(tok, "lh") ) return LH;
	if ( streq(tok, "lhu") ) return LHU;
	if ( streq(tok, "lw") ) return LW;
	if ( streq(tok, "sb") ) return SB;
	if ( streq(tok, "sh") ) return SH;
	if ( streq(tok, "sw") ) return SW;

	//branch
	if ( streq(tok, "beq") ) return BEQ;
	if ( streq(tok, "bge") ) return BGE;
	if ( streq(tok, "bgeu") ) return BGEU;
	if ( streq(tok, "blt") ) return BLT;
	if ( streq(tok, "bltu") ) return BLTU;
	if ( streq(tok, "bne") ) return BNE;

	// jal
	if ( streq(tok, "jal") ) return JAL;
	if ( streq(tok, "jalr") ) return JALR;

	// lui
	if ( streq(tok, "auipc") ) return AUIPC;
	if ( streq(tok, "lui") ) return LUI;

	// unimpl
	//if ( streq(tok, "unimpl") ) return UNIMPL;
	if ( streq(tok, "hcf") ) return HCF;
	return UNIMPL;
}

int parse_reg(char* tok, int line, bool strict = true) {
	if ( tok[0] == 'x' ) {
		int ri = atoi(tok+1);
		if ( ri < 0 || ri > 32 ) {
			if ( strict ) print_syntax_error(line, "Malformed register name");
			return -1;
		}
		return ri;
	}
	if ( streq(tok, "zero") ) return 0; 
	if ( streq(tok, "ra") ) return 1;
	if ( streq(tok, "sp") ) return 2;
	if ( streq(tok, "gp") ) return 3;
	if ( streq(tok, "tp") ) return 4;
	if ( streq(tok, "t0") ) return 5;
	if ( streq(tok, "t1") ) return 6;
	if ( streq(tok, "t2") ) return 7;
	if ( streq(tok, "s0") ) return 8;
	if ( streq(tok, "s1") ) return 9;
	if ( streq(tok, "a0") ) return 10;
	if ( streq(tok, "a1") ) return 11;
	if ( streq(tok, "a2") ) return 12;
	if ( streq(tok, "a3") ) return 13;
	if ( streq(tok, "a4") ) return 14;
	if ( streq(tok, "a5") ) return 15;
	if ( streq(tok, "a6") ) return 16;
	if ( streq(tok, "a7") ) return 17;
	if ( streq(tok, "s2") ) return 18;
	if ( streq(tok, "s3") ) return 19;
	if ( streq(tok, "s4") ) return 20;
	if ( streq(tok, "s5") ) return 21;
	if ( streq(tok, "s6") ) return 22;
	if ( streq(tok, "s7") ) return 23;
	if ( streq(tok, "s8") ) return 24;
	if ( streq(tok, "s9") ) return 25;
	if ( streq(tok, "s10") ) return 26;
	if ( streq(tok, "s11") ) return 27;
	if ( streq(tok, "t3") ) return 28;
	if ( streq(tok, "t4") ) return 29;
	if ( streq(tok, "t5") ) return 30;
	if ( streq(tok, "t6") ) return 31;

	if ( strict ) print_syntax_error(line, "Malformed register name");
	return -1;
}

uint32_t parse_imm(char* tok, int bits, int line, bool strict = true) {
	if ( !(tok[0]>='0'&&tok[0]<='9') && tok[0] != '-' && strict) {
		print_syntax_error(line, "Malformed immediate value" );
	}
	long int imml = strtol(tok, NULL, 0);


	if (imml > ((1<<bits)-1) || imml < -(1<<(bits-1)) ) {
		printf( "Syntax error at token %s\n", tok);
		exit(1);
	}
	uint64_t uv = *(uint64_t*)&imml;
	uint32_t hv = (uv&UINT32_MAX);

	return hv;
}

void parse_mem(char* tok, int* reg, uint32_t* imm, int bits, int line) {
	char* imms = strtok(tok, "(");
	char* regs = strtok(NULL, ")");
	*imm = parse_imm(imms, bits, line);
	*reg = parse_reg(regs, line);
}

uint32_t mem_flush_words = 0;
uint32_t mem_write_reqs = 0;
uint32_t cache_write_hits = 0;
uint32_t mem_read_reqs = 0;
uint32_t cache_read_hits = 0;


void mem_write(uint8_t* mem, uint32_t addr, uint32_t data, instr_type op) {
	//printf( "Storing %x to %d\n", data, addr );
	int bytes = 0;
	switch (op ) {
		case SB: bytes = 1; break;
		case SH: bytes = 2; break;
		case SW: bytes = 4; break;
	}
	if ( addr < MEM_BYTES && addr + bytes <= MEM_BYTES ) {
		mem_write_reqs ++;
		int way = cache_peek(addr,bytes);
		if ( way < 0 ) {
			cache_flush(addr, mem);
			uint32_t waddr = addr-(addr&((1<<(2+CACHE_LINE_WORD_SZ))-1));
			for ( int i = 0; i < CACHE_LINE_WORD; i++ ) {
				cache_update(waddr+(i*4), *(uint32_t*)&(mem[waddr+(i*4)]));
			}
			mem_flush_words += CACHE_LINE_WORD;
		} else {
			cache_write_hits ++;
		}
		cache_write(addr,data,bytes);
	} else if ( addr == MEM_BYTES ) {
		printf( "[System output]: 0x%x\n", data );
	} else {
		printf( "0x%x -- 0x%x\n", addr, data);
	}
}
uint32_t mem_read(uint8_t* mem, uint32_t addr, instr_type op) {
	uint32_t ret = 0;
	int bytes = 0;

	switch(op) {
		case LB: 
		case LBU: bytes = 1; break;
		case LH:
		case LHU: bytes = 2; break;
		case LW:  bytes = 4; break;
	}
	if ( addr + bytes <= MEM_BYTES ) {
		mem_read_reqs ++;
		int way = cache_peek(addr,bytes);
		if ( way < 0 ) {
			cache_flush(addr, mem);
			mem_flush_words += CACHE_LINE_WORD;
			uint32_t waddr = addr-(addr&((1<<(2+CACHE_LINE_WORD_SZ))-1));
			for ( int i = 0; i < CACHE_LINE_WORD; i++ ) {
				cache_update(waddr+(i*4), *(uint32_t*)&(mem[waddr+(i*4)]));
			}
		} else {
			cache_read_hits++;
			//printf( "%x %d--\n", addr,way);
		}
		uint32_t cr = cache_read(addr,bytes);
		switch(op) {
			case LB: ret = signextend(cr, 8); break;
			case LBU: ret = (cr&0xff); break;
			case LH: ret = signextend(cr,16); break;
			case LHU: ret = (cr&0xffff); break;
			case LW: ret = cr; break;
		}
	}
	//printf( "Reading %x from %d\n", ret, addr );

	return ret;
}

typedef enum {
	OPTYPE_NONE, // more like "don't care"
	OPTYPE_REG,
	OPTYPE_IMM,
	OPTYPE_LABEL,
} operand_type;
typedef struct {
	operand_type type = OPTYPE_NONE;
	char label[MAX_LABEL_LEN];
	int reg;
	uint32_t imm;

} operand;
typedef struct {
	instr_type op;
	operand a1;
	operand a2;
	operand a3;
	char* psrc = NULL;
	int orig_line=-1;
	bool breakpoint = false;
} instr;

void append_source(const char* op, const char* a1, const char* a2, const char* a3, source* src, instr* i) {
	char tbuf[128]; // not safe... static size... but should be okay since label length enforced
	if ( op && a1 && !a2 && !a3 ) {
		sprintf(tbuf, "%s %s", op, a1);
	} else if ( op && a1 && a2 && !a3 ) {
		sprintf(tbuf, "%s %s, %s", op, a1, a2);
	} else if ( op && a1 && a2 && a3 ) {
		sprintf(tbuf, "%s %s, %s, %s", op, a1, a2, a3);
	} else {
		return;
	}
	int slen = strlen(tbuf);
	if ( slen + src->offset < MAX_SRC_LEN ) {
		strncpy(src->src+src->offset, tbuf, strlen(tbuf));

		i->psrc = src->src+src->offset;
		src->offset += slen+1;
	}
}


typedef struct {
	char label[MAX_LABEL_LEN];
	int loc = -1;
} label_loc;

uint32_t label_addr(char* label , label_loc* labels, int label_count, int orig_line) {
	for ( int i = 0; i < label_count; i++ ) {
		if (streq(labels[i].label, label)) return labels[i].loc;
	}
	print_syntax_error(orig_line, "Undefined label" );
}



//typedef enum {SECTION_NONE, SECTION_TEXT, SECTION_DATA} sectionType;
int parse_data_element(int line, int size, uint8_t* mem, int offset) {
	while (char* t = strtok(NULL, " \t\r\n") ) {
		errno = 0;
		int64_t v = strtol(t, NULL, 0);
		int64_t vs = (v>>(size*8));
		if ( errno == ERANGE || (vs > 0 && vs != -1 ) ) {
			printf( "Value out of bounds at line %d : %s\n", line, t);
			exit(2);
		}
		//printf ( "parse_data_element %d: %d %ld %d %d\n", line, size, v, errno, sizeof(long int));
		memcpy(&mem[offset], &v, size);
		offset += size;
		//strtok(NULL, ",");
	}
	return offset;
}
int parse_data_zero(int line, uint8_t* mem, int offset) {
	char* t = strtok(NULL, " \t\r\n");
	int bytes = atoi(t);
	memset(&mem[offset], 0, bytes);

	return offset + bytes;
}
int parse_assembler_directive(int line, char* ftok, uint8_t* mem, int memoff) {
	//printf( "assembler directive %s\n", ftok );
	if ( 0 == memcmp(ftok, ".text", strlen(ftok) ) ) {
		if (strtok(NULL, " \t\r\n") ) {
			print_syntax_error(line, "Tokens after assembler directive");
		}
		//cur_section = SECTION_TEXT;
		memoff = TEXT_OFFSET;
		//printf( "starting text section\n" );
	} else if ( 0 == memcmp(ftok, ".data", strlen(ftok) ) ) {
		//cur_section = SECTION_TEXT;
		memoff = DATA_OFFSET;
		//printf( "starting data section\n" );
	} else if ( 0 == memcmp(ftok, ".byte", strlen(ftok)) ) memoff = parse_data_element(line, 1, mem, memoff);
	else if ( 0 == memcmp(ftok, ".half", strlen(ftok)) ) memoff = parse_data_element(line, 2, mem, memoff);
	else if ( 0 == memcmp(ftok, ".word", strlen(ftok)) ) memoff = parse_data_element(line, 4, mem, memoff);
	else if ( 0 == memcmp(ftok, ".zero", strlen(ftok)) ) memoff = parse_data_zero(line, mem, memoff);
	else {
		printf( "Undefined assembler directive at line %d: %s\n", line, ftok );
		//exit(3);
	}
	return memoff;
}

int parse_pseudoinstructions(int line, char* ftok, instr* imem, int ioff, label_loc* labels, char* o1, char* o2, char* o3, char* o4, source* src) {

	if ( streq(ftok, "li" ) ) {
		if ( !o1 || !o2 || o3 ) print_syntax_error(line, "Invalid format");

		int reg = parse_reg(o1, line);
		long int imml = strtol(o2, NULL, 0);


		if (reg < 0 || imml > UINT32_MAX || imml < INT32_MIN ) {
			printf( "Syntax error at line %d -- %lx, %x\n", line, imml, INT32_MAX);
			exit(1);
		}
		uint64_t uv = *(uint64_t*)&imml;
		uint32_t hv = (uv&UINT32_MAX);

		char areg[4]; sprintf(areg, "x%02d", reg);
		char immu[12]; sprintf(immu, "0x%08x" , (hv>>12));
		char immd[12]; sprintf(immd, "0x%08x" , (hv&((1<<12)-1)));


		instr* i = &imem[ioff];
		i->op = LUI;
		i->a1.type = OPTYPE_REG; i->a1.reg = reg;
		i->a2.type = OPTYPE_IMM; i->a2.imm = hv>>12;
		i->orig_line = line;
		append_source("lui", areg, immu, NULL, src, i);
		instr* i2 = &imem[ioff+1];

		i2->op = ADDI;
		i2->a1.type = OPTYPE_REG; i2->a1.reg = reg;
		i2->a2.type = OPTYPE_REG; i2->a2.reg = reg;
		i2->a3.type = OPTYPE_IMM; i2->a3.imm = (hv&((1<<12)-1)); 
		i2->orig_line = line;
		append_source("addi", areg, areg, immd, src, i2);
		//printf( ">> %d %x %d\n", reg, i->a2.imm, i->a2.imm );
		//printf( ">> %d %x %d\n", reg, i2->a3.imm, i2->a3.imm );
		return 2;
	}
	if ( streq(ftok, "la") || streq(ftok, "lla") ) {
		if ( !o1 || !o2 || o3 ) print_syntax_error(line, "Invalid format");

		int reg = parse_reg(o1, line);

		instr* i = &imem[ioff];
		i->op = LUI;
		i->a1.type = OPTYPE_REG; i->a1.reg = reg;
		i->a2.type = OPTYPE_LABEL; strncpy(i->a2.label, o2, MAX_LABEL_LEN);
		i->orig_line = line;
		//append_source(ftok, o1, o2, o3, src, i); // done in normalize
		instr* i2 = &imem[ioff+1];
		i2->op = ADDI;
		i2->a1.type = OPTYPE_REG; i2->a1.reg = reg;
		i2->a2.type = OPTYPE_REG; i2->a2.reg = reg;
		i2->a3.type = OPTYPE_LABEL; strncpy(i2->a3.label, o2, MAX_LABEL_LEN);
		i2->orig_line = line;
		//append_source(ftok, o1, o2, o3, src, i2); // done in normalize
		return 2;
	}
	if ( streq(ftok, "nop" )) {
		if ( o1 ) print_syntax_error(line, "Invalid format");

		instr* i = &imem[ioff];
		i->op = ADDI;
		i->a1.type = OPTYPE_REG; i->a1.reg = 0;
		i->a2.type = OPTYPE_REG; i->a2.reg = 0;
		i->a3.type = OPTYPE_IMM; i->a3.imm = 0;
		i->orig_line = line;
		append_source("nop", "zero", "zero", "0", src, i);
		return 1;
	}
	if ( streq(ftok, "ret" )) {
		if ( o1 ) print_syntax_error(line, "Invalid format");

		instr* i = &imem[ioff];
		i->op = JALR;
		i->a1.type = OPTYPE_REG; i->a1.reg = 0;
		i->a2.type = OPTYPE_REG; i->a2.reg = 1;
		i->a3.type = OPTYPE_IMM; i->a3.imm = 0;
		i->orig_line = line;
		append_source("jalr", "x0", "x1", "x0", src, i);
		return 1;
	}
	if ( streq(ftok, "jr" )) {
		if ( !o1 || o2 ) print_syntax_error(line, "Invalid format");

		instr* i = &imem[ioff];
		i->op = JALR;
		i->a1.type = OPTYPE_REG; i->a1.reg = 0;
		i->a2.type = OPTYPE_REG; i->a2.reg = parse_reg(o1, line);
		i->a3.type = OPTYPE_IMM; i->a3.imm = 0;
		i->orig_line = line;
		append_source("jalr", "x0", o1, "x0", src, i);
		return 1;
	}
	if ( streq(ftok, "j" )) {
		if ( !o1 || o2 ) print_syntax_error(line, "Invalid format");

		instr* i = &imem[ioff];
		i->op = JAL;
		i->a1.type = OPTYPE_REG; i->a1.reg = 0;
		i->a2.type = OPTYPE_LABEL; strncpy(i->a2.label, o1, MAX_LABEL_LEN);
		i->orig_line = line;
		append_source("j", "x0", o1, NULL, src, i);
		return 1;
	}
	if ( streq(ftok, "call" )) {
		if ( !o1 || o2 ) print_syntax_error(line, "Invalid format");

		instr* i = &imem[ioff];
		i->op = JAL;
		i->a1.type = OPTYPE_REG; i->a1.reg = 1;
		i->a2.type = OPTYPE_LABEL; strncpy(i->a2.label, o1, MAX_LABEL_LEN);
		i->orig_line = line;
		append_source("jal", "x1", o1, NULL, src, i);
		return 1;
	}
	if ( streq(ftok, "mv" )) {
		if ( !o1 || !o2 || o3 ) print_syntax_error(line, "Invalid format");
		instr* i = &imem[ioff];
		i->op = ADDI;
		i->a1.type = OPTYPE_REG; i->a1.reg = parse_reg(o1, line);
		i->a2.type = OPTYPE_REG; i->a2.reg = parse_reg(o2, line);
		i->a3.type = OPTYPE_IMM; i->a3.imm = 0;
		i->orig_line = line;
		append_source("addi",o1, o2, NULL, src, i);
		return 1;
	}
	if ( streq(ftok, "bnez" )) {
		if ( !o1 || !o2 || o3 ) print_syntax_error(line, "Invalid format");
		instr* i = &imem[ioff];
		i->op = BNE;
		i->a1.type = OPTYPE_REG; i->a1.reg = parse_reg(o1, line);
		i->a2.type = OPTYPE_REG; i->a2.reg = 0;
		i->a3.type = OPTYPE_LABEL; strncpy(i->a3.label, o2, MAX_LABEL_LEN);
		i->orig_line = line;
		append_source("bne", "x0", o1, o2, src, i);
		return 1;
	}
	if ( streq(ftok, "beqz" )) {
		if ( !o1 || !o2 || o3 ) print_syntax_error(line, "Invalid format");
		instr* i = &imem[ioff];
		i->op = BEQ;
		i->a1.type = OPTYPE_REG; i->a1.reg = parse_reg(o1, line);
		i->a2.type = OPTYPE_REG; i->a2.reg = 0;
		i->a3.type = OPTYPE_LABEL; strncpy(i->a3.label, o2, MAX_LABEL_LEN);
		i->orig_line = line;
		append_source("beq", "x0", o1, o2, src, i);
		return 1;
	}
	if ( streq(ftok, "bgt" )) {
		if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error(line, "Invalid format");
		instr* i = &imem[ioff];
		i->op = BLT;
		i->a1.type = OPTYPE_REG; i->a2.reg = parse_reg(o1, line);
		i->a2.type = OPTYPE_REG; i->a1.reg = parse_reg(o2, line);
		i->a3.type = OPTYPE_LABEL; strncpy(i->a3.label, o3, MAX_LABEL_LEN);
		i->orig_line = line;
		append_source("blt", o2, o1, o3, src, i);
		return 1;
	}
	if ( streq(ftok, "ble" )) {
		if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error(line, "Invalid format");
		instr* i = &imem[ioff];
		i->op = BGE;
		i->a1.type = OPTYPE_REG; i->a2.reg = parse_reg(o1, line);
		i->a2.type = OPTYPE_REG; i->a1.reg = parse_reg(o2, line);
		i->a3.type = OPTYPE_LABEL; strncpy(i->a3.label, o3, MAX_LABEL_LEN);
		i->orig_line = line;
		append_source("bge", o2, o1, o3, src, i);
		return 1;
	}
	return 0;
}

int parse_instr(int line, char* ftok, instr* imem, int memoff, label_loc* labels, source* src) {
	if ( memoff +4 > DATA_OFFSET ) {
		printf( "Instructions in data segment! Line %d\n", line );
		exit(1);
	}

	char* o1 = strtok(NULL, " \t\r\n,");
	char* o2 = strtok(NULL, " \t\r\n,");
	char* o3 = strtok(NULL, " \t\r\n,");
	char* o4 = strtok(NULL, " \t\r\n,");

	int ioff = memoff/4;
	int pscnt = parse_pseudoinstructions(line, ftok, imem, ioff, labels, o1, o2, o3, o4, src);
	if ( pscnt > 0 ) {
		return pscnt;
	} else {
		instr* i = &imem[ioff];
		instr_type op = parse_instr(ftok);
		i->op = op;
		i->orig_line = line;
		append_source(ftok, o1, o2, o3, src, i);

		switch( op ) {
			//-----------wilson-----------//
			case andn:
				if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line,  "Invalid format" );
        			i->a1.reg = parse_reg(o1 , line);
			        i->a2.reg = parse_reg(o2 , line);
			        i->a3.reg = parse_reg(o3 , line);
        			return 1;
			case clmul:
                                if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line,  "Invalid format" );
                                i->a1.reg = parse_reg(o1 , line);
                                i->a2.reg = parse_reg(o2 , line);
                                i->a3.reg = parse_reg(o3 , line);
                                return 1;
			case clmulh:
                                if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line,  "Invalid format" );
                                i->a1.reg = parse_reg(o1 , line);
                                i->a2.reg = parse_reg(o2 , line);
                                i->a3.reg = parse_reg(o3 , line);
                                return 1;
			case clmulr:
                                if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line,  "Invalid format" );
                                i->a1.reg = parse_reg(o1 , line);
                                i->a2.reg = parse_reg(o2 , line);
                                i->a3.reg = parse_reg(o3 , line);
                                return 1;
			case clz:
                                if ( !o1 || !o2 || o3 || o4 ) print_syntax_error( line,  "Invalid format" );
                                i->a1.reg = parse_reg(o1 , line);
                                i->a2.reg = parse_reg(o2 , line);
                                return 1;
			case cpop:
                                if ( !o1 || !o2 || o3 || o4 ) print_syntax_error( line,  "Invalid format" );
                                i->a1.reg = parse_reg(o1 , line);
                                i->a2.reg = parse_reg(o2 , line);
                                return 1;
			case ctz:
                                if ( !o1 || !o2 || o3 || o4 ) print_syntax_error( line,  "Invalid format" );
                                i->a1.reg = parse_reg(o1 , line);
                                i->a2.reg = parse_reg(o2 , line);
				return 1;
			//-----------wilson-----------//




			//---------KAI-HONG-WANG-----------------------------------------------------------
			//TODO: instruction added
			 case MUL: //! added
			    if ( !o1 || !o2 || !o3 || o4 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為MUL為R系列指令，有rd、rs1、rs2，所以要找有o1、o2、o3的
				//printf("hi 160\n");
				//printf("o1: %s\to2: %s\to3: %s\to4: %s\n", o1, o2, o3, o4); //hi 10
			 	i->a1.reg = parse_reg(o1 , line);
			 	i->a2.reg = parse_reg(o2 , line);
			 	i->a3.reg = parse_reg(o3 , line);
			     return 1; //vital

			 case MULH: //! added
			    if ( !o1 || !o2 || !o3 || o4 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為MULH為R系列指令，有rd、rs1、rs2，所以要找有o1、o2、o3的
			 	i->a1.reg = parse_reg(o1 , line);
			 	i->a2.reg = parse_reg(o2 , line);
			 	i->a3.reg = parse_reg(o3 , line);
			     return 1;

			 case MULHSU: //! added
			    if ( !o1 || !o2 || !o3 || o4 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為MULHSU為R系列指令，有rd、rs1、rs2，所以要找有o1、o2、o3的
			 	i->a1.reg = parse_reg(o1 , line);
			 	i->a2.reg = parse_reg(o2 , line);
			 	i->a3.reg = parse_reg(o3 , line);
			     return 1;

			 case MULHU: //! added
			    if ( !o1 || !o2 || !o3 || o4 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為MULHU為R系列指令，有rd、rs1、rs2，所以要找有o1、o2、o3的
			 	i->a1.reg = parse_reg(o1 , line);
			 	i->a2.reg = parse_reg(o2 , line);
			 	i->a3.reg = parse_reg(o3 , line);
			     return 1;

			 case DIV: //! added
			    if ( !o1 || !o2 || !o3 || o4 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為DIV為R系列指令，有rd、rs1、rs2，所以要找有o1、o2、o3的
			 	i->a1.reg = parse_reg(o1 , line);
			 	i->a2.reg = parse_reg(o2 , line);
			 	i->a3.reg = parse_reg(o3 , line);
			     return 1;

			 case DIVU: //! added
			    if ( !o1 || !o2 || !o3 || o4 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為DIVU有rd、rs1、rs2，所以要找有o1、o2、o3的
			 	i->a1.reg = parse_reg(o1 , line);
			 	i->a2.reg = parse_reg(o2 , line);
			 	i->a3.reg = parse_reg(o3 , line);
			     return 1;

			 case REM: //! added
			    if ( !o1 || !o2 || !o3 || o4 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為REM為R系列指令，有rd、rs1、rs2，所以要找有o1、o2、o3的
			 	i->a1.reg = parse_reg(o1 , line);
			 	i->a2.reg = parse_reg(o2 , line);
			 	i->a3.reg = parse_reg(o3 , line);
			     return 1;

			 case REMU: //! added
			    if ( !o1 || !o2 || !o3 || o4 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為REMU為R系列指令，有rd、rs1、rs2，所以要找有o1、o2、o3的
			 	i->a1.reg = parse_reg(o1 , line);
			 	i->a2.reg = parse_reg(o2 , line);
			 	i->a3.reg = parse_reg(o3 , line);
			     return 1;

			 case MAX: //! added
			    if ( !o1 || !o2 || !o3 || o4 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為REMU為R系列指令，有rd、rs1、rs2，所以要找有o1、o2、o3的
			 	i->a1.reg = parse_reg(o1 , line);
			 	i->a2.reg = parse_reg(o2 , line);
			 	i->a3.reg = parse_reg(o3 , line);
			     return 1;			

			 case MAXU: //! added
			    if ( !o1 || !o2 || !o3 || o4 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為REMU為R系列指令，有rd、rs1、rs2，所以要找有o1、o2、o3的
			 	i->a1.reg = parse_reg(o1 , line);
			 	i->a2.reg = parse_reg(o2 , line);
			 	i->a3.reg = parse_reg(o3 , line);
			     return 1;

			 case MIN: //! added
			    if ( !o1 || !o2 || !o3 || o4 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為REMU為R系列指令，有rd、rs1、rs2，所以要找有o1、o2、o3的
			 	i->a1.reg = parse_reg(o1 , line);
			 	i->a2.reg = parse_reg(o2 , line);
			 	i->a3.reg = parse_reg(o3 , line);
			     return 1;			

			 case MINU: //! added
			    if ( !o1 || !o2 || !o3 || o4 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為REMU為R系列指令，有rd、rs1、rs2，所以要找有o1、o2、o3的
			 	i->a1.reg = parse_reg(o1 , line);
			 	i->a2.reg = parse_reg(o2 , line);
			 	i->a3.reg = parse_reg(o3 , line);
			     return 1;

			 case ORN: //! added
			    if ( !o1 || !o2 || !o3 || o4 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為REMU為R系列指令，有rd、rs1、rs2，所以要找有o1、o2、o3的
				//printf("hi 170\n");
				//printf("o1: %s\to2: %s\to3: %s\to4: %s\n", o1, o2, o3, o4); //hi 10
			 	i->a1.reg = parse_reg(o1 , line);
			 	i->a2.reg = parse_reg(o2 , line);
			 	i->a3.reg = parse_reg(o3 , line);
			     return 1;

			//ORC_D、REV8--->較特別
			case ORCD: //! added--->格式參考mv指令(同樣都是7.5.3.5.12，且同樣都是只有2個暫存器參與)
			    if ( !o1 || !o2 || o3 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為ORC_D為orc_d rd, rs，有rd、rs，所以要找有o1、o2、但無o3的
			 	i->a1.type = OPTYPE_REG; i->a1.reg = parse_reg(o1 , line); //operand 1 為 register，長line-bits
			 	i->a2.type = OPTYPE_REG; i->a2.reg = parse_reg(o2 , line); //operand 2 為 register，長line-bits
				i->a3.type = OPTYPE_IMM; i->a3.imm = 0; //operand 3 不存在(故設為imm=0，並且下方函式的a3欄位以NULL作為參數傳入)，長line-bits
				//append_source("orcd",o1, o2, NULL, src, i); //FIXME:這樣寫對嗎?還是要註解掉? hi bad
			    return 1;

			case REV8: //! added--->格式參考mv指令(同樣都是7.5.3.5.12，且同樣都是只有2個暫存器參與)
				//printf("\n\no1: %s\to2: %s\to3: %s\to4: %s\n\n", o1, o2, o3, o4); //hi 10
			    if ( !o1 || !o2 || o3 ) 
					print_syntax_error( line,  "Invalid format" ); //!因為REMU為rev8 rd, rs，有rd、rs，所以要找有o1、o2、但無o3的
			 	i->a1.type = OPTYPE_REG; i->a1.reg = parse_reg(o1 , line);
			 	i->a2.type = OPTYPE_REG; i->a2.reg = parse_reg(o2 , line);
				i->a3.type = OPTYPE_IMM; i->a3.imm = 0;
				//append_source("rev",o1, o2, NULL, src, i); //FIXME:這樣寫對嗎?還是要註解掉? hi bad
			    return 1;



//			case SEXT_H: //! added-----Sign-extend halfword-----X(rd) = EXTS(X(rs)[15..0]);------sext.h rd, rs
//				//FIXME: 注意，雖然指令格式為(7, 5, 5, 3, 5, 7)，
//				//但因為此為sext.h rd, rs，
//				//所以這裡要排除掉有o3的情況!!
//				//所以不能用 if ( !o1 || !o2 || !o3 )
//				//要用 if ( !o1 || !o2 || o3 )  才可以
//			    if ( !o1 || !o2 || o3 ) 
//					print_syntax_error( line,  "Invalid format" ); //!因為REMU為rev8 rd, rs，有rd、rs，所以要找有o1、o2、但無o3的
//			 	i->a1.type = OPTYPE_REG; i->a1.reg = parse_reg(o1 , line);
//			 	i->a2.type = OPTYPE_REG; i->a2.reg = parse_reg(o2 , line);
//				i->a3.type = OPTYPE_IMM; i->a3.imm = 0;
//				//append_source("sext.h",o1, o2, NULL, src, i);
//			     return 1;
//
//			case SEXT_B: //! added-----Sign-extend halfword-----X(rd) = EXTS(X(rs)[7..0]);------sext.b rd, rs
//				//FIXME: 注意，雖然指令格式為(7, 5, 5, 3, 5, 7)，
//				//但因為此為sext.b rd, rs，
//				//所以這裡要排除掉有o3的情況!!
//				//所以不能用 if ( !o1 || !o2 || !o3 )
//				//要用 if ( !o1 || !o2 || o3 )  才可以
//			    if ( !o1 || !o2 || o3 ) 
//					print_syntax_error( line,  "Invalid format" ); //!因為REMU為rev8 rd, rs，有rd、rs，所以要找有o1、o2、但無o3的
//			 	i->a1.type = OPTYPE_REG; i->a1.reg = parse_reg(o1 , line);
//			 	i->a2.type = OPTYPE_REG; i->a2.reg = parse_reg(o2 , line);
//				i->a3.type = OPTYPE_IMM; i->a3.imm = 0;
//				//append_source("sext.b",o1, o2, NULL, src, i); 
//			     return 1;
			//---------KAI-HONG-WANG-----------------------------------------------------------

			//-----------culture0418-----------//
			case BCLR:{ // bclr rd, rs1, rs2
				if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line,  "Invalid format" );
				    i->a1.reg = parse_reg(o1 , line);
				    i->a2.reg = parse_reg(o2 , line);
				    i->a3.reg = parse_reg(o3 , line);
			    return 1;
			}

			case BCLRI:{ // bclri rd, rs1, shamt
				if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line,  "Invalid format" );
				    i->a1.reg = parse_reg(o1 , line);
				    i->a2.reg = parse_reg(o2 , line);
				    i->a3.imm = parse_imm(o3, 5, line);
			    return 1;
			}
			

			case BEXT:{ // bext rd, rs1, rs2
				if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line,  "Invalid format" );
				    i->a1.reg = parse_reg(o1 , line);
				    i->a2.reg = parse_reg(o2 , line);
				    i->a3.reg = parse_reg(o3 , line);
			    return 1;
			}

			case BEXTI:{ // bexti rd, rs1, shamt
				if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line,  "Invalid format" );
				    i->a1.reg = parse_reg(o1 , line);
				    i->a2.reg = parse_reg(o2 , line);
				    i->a3.imm = parse_imm(o3, 5, line);
			    return 1;
			}

			case BINV:{ // binv rd, rs1, rs2
				if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line,  "Invalid format" );
				    i->a1.reg = parse_reg(o1 , line);
				    i->a2.reg = parse_reg(o2 , line);
				    i->a3.reg = parse_reg(o3 , line);
			    return 1;
			}

			case BINVI:{  // binvi rd, rs1, shamt
				if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line,  "Invalid format" );
				    i->a1.reg = parse_reg(o1 , line);
				    i->a2.reg = parse_reg(o2 , line);
				    i->a3.imm = parse_imm(o3, 5, line);
			    return 1;
			}

			case BSET:{
				if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line,  "Invalid format" );
				    i->a1.reg = parse_reg(o1 , line);
				    i->a2.reg = parse_reg(o2 , line);
				    i->a3.reg = parse_reg(o3 , line);
			    return 1;
			}

			case BSETI:{
				if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line,  "Invalid format" );
				    i->a1.reg = parse_reg(o1 , line);
				    i->a2.reg = parse_reg(o2 , line);
				    i->a3.imm = parse_imm(o3, 5, line);
			    return 1;
			}

			//-----------culture0418-----------//
			
	//-----------song-fung-yu----------//
			case SEXTB: case SEXTH: 
				if ( !o1 || !o2 || o3 || o4 ) print_syntax_error( line, "Invalid format" );
				i->a1.reg = parse_reg(o1, line);
				i->a2.reg = parse_reg(o2, line);
				return 1;
			case SH1ADD: case SH2ADD: case SH3ADD: 
				if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line, "Invalid format" );
				i->a1.reg = parse_reg(o1, line);
				i->a2.reg = parse_reg(o2, line);
				i->a3.reg = parse_reg(o3, line);
				return 1;
			case BSETI:
				if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line, "Invalid format" );
				i->a1.reg = parse_reg(o1, line);
				i->a2.reg = parse_reg(o2, line);
				i->a3.imm = parse_imm(o3, 5, line);
				return 1;
	//-----------song-fung-yu----------//


			case UNIMPL: return 1;
			case JAL:
				if ( o2 ) { // two operands, reg, label
					if ( !o1 || !o2 || o3 || o4 ) print_syntax_error( line, "Invalid format" );
					i->a1.type = OPTYPE_REG; i->a1.reg = parse_reg(o1, line);
					i->a2.type = OPTYPE_LABEL; strncpy(i->a2.label, o2, MAX_LABEL_LEN);
				} else { // one operand, label
					if ( !o1 || o2 || o3 || o4 ) print_syntax_error( line, "Invalid format" );

					i->a1.type = OPTYPE_REG; i->a1.reg = 1;
					i->a2.type = OPTYPE_LABEL; strncpy(i->a2.label, o1, MAX_LABEL_LEN);
				}
				return 1;
			case JALR:
				if ( !o1 || !o2 || o3 || o4 ) print_syntax_error( line, "Invalid format" );
				i->a1.reg = parse_reg(o1, line);
				parse_mem(o2, &i->a2.reg, &i->a3.imm, 12, line);
				return 1;
			case ADD: case SUB: case SLT: case SLTU: case AND: case OR: case XOR: case SLL: case SRL: case SRA:
				if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line, "Invalid format" );
				i->a1.reg = parse_reg(o1, line);
				i->a2.reg = parse_reg(o2, line);
				i->a3.reg = parse_reg(o3, line);
				return 1;
			case LB: case LBU: case LH: case LHU: case LW: case SB: case SH: case SW:
				if ( !o1 || !o2 || o3 || o4 ) print_syntax_error( line, "Invalid format" );
				i->a1.reg = parse_reg(o1, line);
				parse_mem(o2, &i->a2.reg, &i->a3.imm, 12, line);
				return 1;
			case ADDI: case SLTI: case SLTIU: case ANDI: case ORI: case XORI: case SLLI: case SRLI: case SRAI:
				if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line, "Invalid format" );

				i->a1.reg = parse_reg(o1, line);
				i->a2.reg = parse_reg(o2, line);
				i->a3.imm = signextend(parse_imm(o3, 12, line), 12);
				return 1;
			case BEQ: case BGE: case BGEU: case BLT: case BLTU: case BNE:
				if ( !o1 || !o2 || !o3 || o4 ) print_syntax_error( line, "Invalid format" );
				i->a1.reg = parse_reg(o1, line);
				i->a2.reg = parse_reg(o2, line);
				i->a3.type = OPTYPE_LABEL; strncpy(i->a3.label, o3, MAX_LABEL_LEN);
				return 1;
			case LUI: 
			case AUIPC: // how to deal with LSB correctly? FIXME
				if ( !o1 || !o2 || o3 || o4 ) print_syntax_error( line, "Invalid format" );
				i->a1.reg = parse_reg(o1, line);
				i->a2.imm = (parse_imm(o2, 20, line));
				return 1;
			case HCF: return 1;
		}

	}
	return 1;
}

void parse(FILE* fin, uint8_t* mem, instr* imem, int& memoff, label_loc* labels, int& label_count, source* src) {
	int line = 0;

	printf( "Parsing input file\n" );

	//sectionType cur_section = SECTION_NONE;

	char rbuf[1024];
	while(!feof(fin)) {
		if ( !fgets(rbuf, 1024, fin) ) break;
		for (char* p = rbuf; *p; ++p) *p = tolower(*p);
		line++;

		char* ftok = strtok(rbuf, " \t\r\n");
		if ( !ftok ) continue;

		if ( ftok[0] == '#' ) continue;

		if ( ftok[strlen(ftok)-1] == ':' ) {
			ftok[strlen(ftok)-1] = 0;
			if ( strlen(ftok) >= MAX_LABEL_LEN ) {
				printf( "Exceeded maximum length of label: %s\n", ftok );
				exit(3);
			}
			if ( label_count >= MAX_LABEL_COUNT ) {
				printf( "Exceeded maximum number of supported labels" );
				exit(3);
			}
			strncpy(labels[label_count].label, ftok, MAX_LABEL_LEN);
			labels[label_count].loc = memoff;
			label_count++;
			//printf( "Parsing label %s at mem %x\n", ftok, memoff );

			char* ntok = strtok(NULL, " \t\r\n");
			// there is more code after label
			if ( ntok ) {
				if ( ntok[0] == '.' ) {
					memoff = parse_assembler_directive(line, ntok, mem, memoff);
				} else {
					int count = parse_instr(line, ntok, imem, memoff, labels, src);
					for ( int i = 0; i < count; i++ ) *(uint32_t*)&mem[memoff+(i*4)] = 0xcccccccc;
					memoff += count*4;
				}
			}
		} else if ( ftok[0] == '.' ) {
			memoff = parse_assembler_directive(line, ftok, mem, memoff);
		} else {
			int count = parse_instr(line, ftok, imem, memoff, labels, src);
			for ( int i = 0; i < count; i++ ) *(uint32_t*)&mem[memoff+(i*4)] = 0xcccccccc;
			memoff += count*4;
		}
	}
}

void execute(uint8_t* mem, instr* imem, label_loc* labels, int label_count, bool start_immediate) {
	uint32_t rf[32];
	uint32_t rf_mirror[32];
	uint32_t pc = 0;
	uint32_t inst_cnt = 0;
	for ( int i = 0; i < 32; i++ ) {
		rf[i] = 0;
		rf_mirror[i] = 0;
	}

	bool stepping = !start_immediate;
	int stepcnt = 0;
	char keybuf[128];
	char* kbp = keybuf;


	bool dexit = false;
	while(!dexit) {
		uint32_t iid = pc/4;
		instr i = imem[iid];
		inst_cnt ++;

		if ( stepping || i.breakpoint ) {
			if ( stepcnt > 0 ) {
				stepcnt -= 1;
			} 

			if ( stepcnt == 0 || i.breakpoint ) {
				stepping = true;
				printf( "\n" );
				if ( i.psrc ) printf( "Next: %s\n", i.psrc );
				while (true) {
					printf( "[inst: %6d pc: %6d, src line %4d]\n", inst_cnt, pc, i.orig_line );

					std::string linebuf;
					fflush(stdout);
					linenoise::Readline(">>", linebuf);
					memcpy(keybuf, linebuf.c_str(), 128);
					linenoise::AddHistory(linebuf.c_str());
					//while ((kbp = linenoise?::Readline(">>")) == NULL);
					//fgets(keybuf, 128, stdin);


					for ( int i = 0; i < strlen(keybuf); i++ ) if (keybuf[i] == '\n') keybuf[i] = '\0';

					if ( keybuf[0] == 'q' ) {
						printf( "Quit command input! Exiting...\n" );
						exit(0);
					}
					if ( keybuf[0] == 'c' ) {
						stepping = false;
						break;
					}
					if ( strlen(keybuf) == 0 ) {
						break;
					}
					if ( keybuf[0] == 's' ) {
						stepcnt = parse_imm(keybuf+1, 16, 0, false);
						break;
					}
					if ( keybuf[0] == 'b' ) { // todo breakpoint!
						uint32_t break_line = parse_imm(keybuf+1, 16, 0, false);
						if ( strlen(keybuf+1) == 0 ) {
							for ( int i = 0; i < DATA_OFFSET/4; i++ ) {
								if ( imem[i].breakpoint ) printf( "Break at line %d: %s\n", imem[i].orig_line, imem[i].psrc );
							}
						} else {
							for ( int i = 0; i < DATA_OFFSET/4; i++ ) {
								if ( imem[i].orig_line >= break_line ) {
									printf( "Break point added to line %d\n", break_line );
									imem[i].breakpoint = true;
									break;
								}
							}
						}
					}
					if ( keybuf[0] == 'B' ) { // breakpoint remove
						uint32_t break_line = parse_imm(keybuf+1, 16, 0, false);
						for ( int i = 0; i < DATA_OFFSET/4; i++ ) {
							if ( imem[i].orig_line == break_line && imem[i].breakpoint ) {
								printf( "Break point removed from line %d\n", break_line );
								imem[i].breakpoint = false;
								break;
							}
						}
					}
					if ( keybuf[0] == 'r' ) {
						int reg = parse_reg(keybuf+1, 0, false);
						if ( reg >= 0 ) printf( "rf[%2d] = 0x%x\n", reg, rf[reg] );
						if ( reg < 0 ) print_regfile(rf);
					}
					if ( keybuf[0] == 'm' ) {
						uint32_t addr = parse_imm(keybuf+1, 31, 0, false); // just for simplicity
						int cnt = 1;
						char* ftok = strtok(keybuf, " \t\r\n");
						ftok = strtok(NULL, " \t\r\n");
						if ( ftok ) {
							cnt = parse_imm(ftok, 16, 0, false);
						}

						for ( int w = 0; w < cnt; w++ ) {
							printf( "0x%04x: ", addr+(w*4) );
							for ( int i = 0; i < 4; i++ ) {
								printf( "%02x ", mem[addr+(w*4)+i] );
							}
							printf( "\n" );
						}
					}
					if ( keybuf[0] == 'l' ) {
						printf( "Listing compiled isntructions\n" );
						printf( " srcline : Compiled instruction\n" );
						for ( int i = 0; i < DATA_OFFSET/4; i++ ) {
							instr* ii = &imem[i];
							if ( ii->orig_line >= 0 && ii->psrc ) {
								printf( "%9d: %s\n", ii->orig_line, ii->psrc );
							}
						}
					}
				}
			}
		}
		
		int pc_next = pc + 4;
		switch (i.op) {

			//-----------wilson-----------//
			//andn clmul clmulh clmulr clz cpop ctz
			case andn:
				rf[i.a1.reg] = rf[i.a2.reg] & ~rf[i.a3.reg];
				break;
			case clmul:
                                for (int j = 0; j < 32; j++){
					if(rf[i.a3.reg] >> j & 1){
						rf[i.a1.reg] = rf[i.a1.reg] ^ rf[i.a2.reg] << j;
					}
				}
                                break;
			case clmulh:
                                for (int j = 1; j < 32; j++){
                                        if(rf[i.a3.reg] >> j & 1){
                                                rf[i.a1.reg] = rf[i.a1.reg] ^ rf[i.a2.reg] >> (32 - j);
                                        }
                                }
				break;
			case clmulr:
                                for (int j = 0; j < 31; j++){
                                        if(rf[i.a3.reg] >> j & 1){
                                                rf[i.a1.reg] = rf[i.a1.reg] ^ rf[i.a2.reg] >> (31 - j);
                                        }
                                }
				break;
			case clz:
				rf[i.a1.reg] = 0;
                                for (int j = 0; j < 32; j++){
					if ((rf[i.a2.reg] << j & 0x80000000) >> 31)
						break;
					rf[i.a1.reg] = j + 1;
				}
                                break;
			case cpop:
				rf[i.a1.reg] = 0;
				for (int j = 0; j < 32; j++){
					if (rf[i.a2.reg] >> j & 1)
						rf[i.a1.reg] += 1;
				}
                                break;
			case ctz:
				rf[i.a1.reg] = 0;
                                for (int j = 0; j < 32; j++){
                                        if (rf[i.a2.reg] >> j & 1)
                                                break;
                                        rf[i.a1.reg] = j + 1;
                                }
                                break;
			//-----------wilson-----------//







			//---------KAI-HONG-WANG-----------------------------------------------------------
			//TODO: instruction added
			//32*32 mul get 64 bit 
			
			//unsigned * unsigned   取 lowest 32-bit 
			//把unsigned_32相乘，乘積為unsigned_64 (因unsigned，所以"左邊都補零")，
			//接著轉為unsigned_32(會留右邊的32-bits)的方式傳給a1
			//! added  mul: 最低 XLEN-bit
      		case MUL:{
				uint64_t t1 = rf[i.a2.reg]; 
                uint64_t t2 = rf[i.a3.reg]; 
				uint64_t result_temp = t1 * t2; //u * u---->mul
				rf[i.a1.reg] = (uint32_t)result_temp;							
				break;
			} 
		
		
			//signed * signed   取 highest 32-bit 
			//FIXME:把signed_32便signed_64，然後相乘，乘積為signed_64，
			//FIXME:再以"左邊按照正負補0、1"的方式往右shift 32 bit，接著轉為signed_32的方式傳給a1
			//! added 
			case MULH: {
				int64_t t1 = (int32_t)rf[i.a2.reg]; 
                int64_t t2 = (int32_t)rf[i.a3.reg]; 
				uint64_t result_temp =  t1 * t2;//s * s---->mulh
				rf[i.a1.reg] = (result_temp>>32); 	
				break; 
			}

			//FIXME:signed * unsigned   取 highest 32-bit ，然後相乘，乘積為unsigned_64(也可以是signed???)
			//FIXME:
      		case MULHSU: {
				int64_t t1 = (int32_t)rf[i.a2.reg]; 
                uint64_t t2 = rf[i.a3.reg]; 
				uint64_t result_temp = t1 * t2;//s * u---->mulhsu
				rf[i.a1.reg] = (result_temp>>32); 	
				break; 
			}
      		
			//unsigned x unsigned  取 highest 32-bit 
			//FIXME:把unsigned_32便unsigned_64，然後相乘，乘積為unsigned_64，
			//FIXME:再以"左邊都補零"的方式往右shift 32 bit，接著轉為unsigned_32的方式傳給a1
			case MULHU:{ 
				uint64_t t1 = rf[i.a2.reg]; 
                uint64_t t2 = rf[i.a3.reg]; 
				uint64_t result_temp = t1 * t2;//u * u---->mulhu
				rf[i.a1.reg] = (result_temp>>32); 	
				break; 
			}

      		case DIV: {
				int64_t t1 = (int32_t)rf[i.a2.reg]; 
                int64_t t2 = (int32_t)rf[i.a3.reg]; 
				uint64_t result_temp = 0; 
   
				result_temp = t1 / t2; //u / u---->divu
				rf[i.a1.reg] = result_temp;							
				printf("divu: %x\n", rf[i.a1.reg]); //divu
			  	break; //! added	
			}

      		case DIVU:{ 
				uint64_t t1 = rf[i.a2.reg]; 
                uint64_t t2 = rf[i.a3.reg]; 
				uint64_t result_temp = 0; 
   
				result_temp = t1 / t2; //u / u---->divu
				rf[i.a1.reg] = result_temp;							
				printf("divu: %x\n", rf[i.a1.reg]); //divu
			  	break; //! added
			}

      		case REM:{ 

				int64_t t1 = (int32_t)rf[i.a2.reg]; 
                int64_t t2 = (int32_t)rf[i.a3.reg]; 
				uint64_t result_temp = 0; 

				result_temp = t1/t2; //s / s---->rem
				result_temp = result_temp * t2;
				result_temp = (~(result_temp) + 1); //2's complement
				result_temp = t1 + result_temp;
				rf[i.a1.reg] = result_temp;							
			  	break; //! added
			}

      		case REMU: {
				uint64_t t1 = rf[i.a2.reg]; 
                uint64_t t2 = rf[i.a3.reg]; 
				uint64_t result_temp = 0; 

				result_temp = t1/t2; //u / u---->remu
				result_temp = result_temp * t2;
				result_temp = (~(result_temp) + 1); //2's complement
				result_temp = t1 + result_temp;
				rf[i.a1.reg] = result_temp;							
			  	break; //! added
			}

      		case MAX: {
				int32_t t1 = (int32_t)rf[i.a2.reg]; 
                int32_t t2 = (int32_t)rf[i.a3.reg]; 
				uint32_t result_temp = 0;
				//printf("\n\nrf[i.a2.reg]: %x", rf[i.a2.reg]);	
				//printf("\nrf[i.a3.reg]: %x", rf[i.a3.reg]);

				result_temp = (t1 < t2) ? t2 : t1; //s/s-->max
				rf[i.a1.reg] = result_temp;
				//printf("\nrf[i.a1.reg]: %x\n\n", rf[i.a1.reg]);	
			  	break; //! added
			}

      		case MAXU: {
				uint32_t t1 = rf[i.a2.reg]; 
                uint32_t t2 = rf[i.a3.reg]; 
				uint32_t result_temp = 0;
				//printf("\n\nrf[i.a2.reg]: %x", rf[i.a2.reg]);	
				//printf("\nrf[i.a3.reg]: %x", rf[i.a3.reg]);

				result_temp = (t1 < t2) ? t2 : t1; //u/u-->maxu
				rf[i.a1.reg] = result_temp;			
				//printf("\nrf[i.a1.reg]: %x\n\n", rf[i.a1.reg]);				
			  	break; //! added
			}

      		case MIN: {
				int32_t t1 = (int32_t)rf[i.a2.reg]; 
                int32_t t2 = (int32_t)rf[i.a3.reg]; 
				uint32_t result_temp = 0;
				//printf("\n\nrf[i.a2.reg]: %x", rf[i.a2.reg]);	
				//printf("\nrf[i.a3.reg]: %x", rf[i.a3.reg]);

				result_temp = (t1 < t2) ? t1 : t2;  //s/s-->min
				rf[i.a1.reg] = result_temp;		
				//printf("\nrf[i.a1.reg]: %x\n\n", rf[i.a1.reg]);					
			  	break; //! added					
			}

      		case MINU: {
				uint32_t t1 = rf[i.a2.reg]; 
                uint32_t t2 = rf[i.a3.reg]; 
				uint32_t result_temp = 0;
				//printf("\n\nrf[i.a2.reg]: %x", rf[i.a2.reg]);	
				//printf("\nrf[i.a3.reg]: %x", rf[i.a3.reg]);

				result_temp = (t1 < t2) ? t1 : t2; //u/u-->minu
				rf[i.a1.reg] = result_temp;				
				//printf("\nrf[i.a1.reg]: %x\n\n", rf[i.a1.reg]);		
			  	break; //! added
			}

      		case ORN: { //orn:  X(rd) = X(rs1) | (~X(rs2));
				//printf("\n\nrf[i.a2.reg]: %x", rf[i.a2.reg]);	
				//printf("\nrf[i.a3.reg]: %x", rf[i.a3.reg]);

				uint32_t result_temp = (rf[i.a2.reg] | (~(rf[i.a3.reg])));
				rf[i.a1.reg] = result_temp;		
				//printf("\nrf[i.a1.reg]: %x\n\n", rf[i.a1.reg]);	//orn: X(rd) = X(rs1) | (~X(rs2))			
			  	break; //! added
			}

			//rev8:  reverse byte--8 bits----應該只有 rf[i.a1.reg]--rd     rf[i.a2.reg]--rs ??
			//rev8 rd, rs
			//input:   0x de  ad  be  ef
			//output:  0x ef  be  ad  de
      		case REV8: { //orn:  X(rd) = X(rs1) | (~X(rs2));
				uint32_t temp_1 = 0x000000ff; //filter
				uint32_t temp_2 = 0x0000ff00; //filter
				uint32_t temp_3 = 0x00ff0000; //filter
				uint32_t temp_4 = 0xff000000; //filter
				uint32_t result_temp = 0;
				//printf("\n\nrf[i.a2.reg]: %x", rf[i.a2.reg]);			

				//temp = filter & rs      
				temp_1 = (temp_1 & rf[i.a2.reg]); //[7:0]    
				temp_2 = (temp_2 & rf[i.a2.reg]);  //[15:8]    
				temp_3 = (temp_3 & rf[i.a2.reg]);  //[23:16]   
				temp_4 = (temp_4 & rf[i.a2.reg]); //[31:24]  

				//temp = temp-shift
				temp_1 = (temp_1<<24); //[7:0]-->[31:24]
				temp_2 = (temp_2<<8);  //[15:8]-->[23:16]
				temp_3 = (temp_3>>8);  //[23:16]-->[15:8]
				temp_4 = (temp_4>>24); //[31:24]-->[7:0]

				result_temp = (temp_1 | temp_2 | temp_3 | temp_4);  //or all temps
				rf[i.a1.reg] = result_temp;		
				//printf("\nrf[i.a1.reg]: %x\n\n", rf[i.a1.reg]);	
			  	break; //! added
			}

//			//sext.h:  Sign-extend halfword--8 bits
//			//sext.h rd, rs
//			//X(rd) = EXTS(X(rs)[15..0]);
//			//input:   0x 0011 1100 1000 0001 1000 0111 1111 0000  ----32   0x3c8187f0
//			//TEMP :   0x 1000 0111 1111 0000					   ----16   0x87f0
//			//output:  0x 1111 1111 1111 1111 1000 0111 1111 0000  ----32   0xffff87f0
//      		case SEXT_H: {
//				uint16_t temp_1 = 0; //COLLECT LOW 16-bit
//				uint32_t result_temp = 0;
//				uint32_t HALF_FULL = 0xffff0000;
//				uint32_t ZERO = 0;
//				//rf[i.a2.reg] = 0x3c8137f0;
//				//printf("\n\nrf[i.a2.reg]: %x", rf[i.a2.reg]);			
//
//				temp_1 = (rf[i.a2.reg]); //temp = LOW_16_bit(rs)      [31:0]----->[15:0]   
//
//				//temp_1做signed extension
//				if((temp_1>>15)==1){  //if((temp_1>>15)==1) ---->[31...16]補1
//					result_temp = (HALF_FULL | ((uint32_t)temp_1));
//				}
//				else{  //if((temp_1>>15)==0) ---->[31...16]補0
//					result_temp = (ZERO | ((uint32_t)temp_1));
//				}
//
//				rf[i.a1.reg] = result_temp;		
//				//printf("\nrf[i.a1.reg]: %x\n\n", rf[i.a1.reg]);	
//			  	break; //! added
//			}
//
//
//			//sext.b:  Sign-extend byte
//			//sext.b rd, rs
//			//X(rd) = EXTS(X(rs)[7..0]);
//			//input:   0x 0011 1100 1000 0001 1000 0111 1111 0000  ----32   0x3c8187f0
//			//TEMP :   0x 1111 0000					   ----16   0xf0
//			//output:  0x 1111 1111 1111 1111 1111 1111 1111 0000  ----32   0xfffffff0
//      		case SEXT_B: {
//				uint8_t temp_1 = 0; //COLLECT LOW 8-bit
//				uint32_t result_temp = 0;
//				uint32_t HALF_FULL = 0xffffff00;
//				uint32_t ZERO = 0;
//				//rf[i.a2.reg] = 0x3c8137f0;
//				//printf("\n\nrf[i.a2.reg]: %x", rf[i.a2.reg]);			
//
//				temp_1 = (rf[i.a2.reg]); //temp = LOW_8_bit(rs)      [31:0]----->[7:0]   
//
//				//temp_1做signed extension
//				if((temp_1>>7)==1){  //if((temp_1>>7)==1) ---->[31...8]補1
//					result_temp = (HALF_FULL | ((uint32_t)temp_1));
//				}
//				else{  //if((temp_1>>7)==0) ---->[31...8]補0
//					result_temp = (ZERO | ((uint32_t)temp_1));
//				}
//
//				rf[i.a1.reg] = result_temp;		
//				//printf("\nrf[i.a1.reg]: %x\n\n", rf[i.a1.reg]);	
//			  	break; //! added
//			}



			//orc_d:  orc.b rd, rs   
			//Bitwise OR-Combine, byte granule
			//rs的第i個byte為 0b 00000000 (裡面沒有任何1)--->則設rd的第i個byte為 0b 00000000
    		//rs的第i個byte不為 0b 00000000 (裡面出現至少1個1)--->則設rd的第i個byte為 0b 11111111
      		case ORCD:{		
				uint32_t temp_1 = 0x000000ff; //filter
				uint32_t temp_2 = 0x0000ff00; //filter
				uint32_t temp_3 = 0x00ff0000; //filter
				uint32_t temp_4 = 0xff000000; //filter				
				uint32_t result_temp = 0;
				//printf("\n\nrf[i.a2.reg]: %x", rf[i.a2.reg]);	

				//filter & rs    temp = temp-shift
				temp_1 = (temp_1 & rf[i.a2.reg]);               // [7:0]   -->[7:0]
				temp_2 = ( (temp_2 & rf[i.a2.reg]) >> 8 );      // [15:8]  -->[7:0]
				temp_3 = ( (temp_3 & rf[i.a2.reg]) >> 16 );     // [23:16] -->[7:0]
				temp_4 = ( (temp_4 & rf[i.a2.reg]) >> 24 );     // [31:24] -->[7:0]

				temp_1 = ((temp_1==0) ? (0x00): (0xff));         // [7:0] -->[7:0]
				temp_2 = (((temp_2==0) ? (0x00): (0xff)) << 8 ); // [7:0] -->[15:8]
				temp_3 = (((temp_3==0) ? (0x00): (0xff)) << 16); // [7:0] -->[23:16]
				temp_4 = (((temp_4==0) ? (0x00): (0xff)) << 24); // [7:0] -->[31:24]

				result_temp = (temp_1 | temp_2 | temp_3 | temp_4);  //or all temps
				//printf("\nrf[i.a1.reg]: %x\n\n", rf[i.a1.reg]);	
				rf[i.a1.reg] = result_temp;
				break; //! added
			} 
			//---------KAI-HONG-WANG-----------------------------------------------------------


			//-----------culture0418-----------//
			case BCLR:{ // bclr rd, rs1, rs2
				unsigned rs1_tmp = rf[i.a2.reg];
				unsigned n = rf[i.a3.reg];
				unsigned tmp1 = 1;
				rs1_tmp = (rs1_tmp) &  ~(tmp1 << n);
				rf[i.a1.reg] = rs1_tmp; 
				
				// printf("rf[i.a1.reg]: %lx\n", rf[i.a1.reg]); 
				break;
			}

			case BCLRI:{ // bclri rd, rs1, shamt
				unsigned rs1_tmp = rf[i.a2.reg];
				unsigned n = i.a3.imm;
				unsigned tmp1 = 1;

				rs1_tmp = rs1_tmp & ~(tmp1 << n);
				rf[i.a1.reg] = rs1_tmp;
				// printf("rf[i.a1.reg]: %lx\n", rf[i.a1.reg]); 
				break;
			}

			case BEXT:{ // bext rd, rs1, rs2
				unsigned rs1_tmp = rf[i.a2.reg];
				unsigned n = rf[i.a3.reg];
				unsigned tmp1 = 1;

				rs1_tmp = (rs1_tmp >> (n)) & tmp1;
				rf[i.a1.reg] = rs1_tmp;
				// printf("rf[i.a1.reg]: %lx\n", rf[i.a1.reg]); 
				break;
			}

			case BEXTI:{ // bexti rd, rs1, shamt
				unsigned rs1_tmp = rf[i.a2.reg];
				unsigned n = i.a3.imm;
				unsigned tmp_len = 31;
				unsigned tmp1 = 1;
				
				n = n & tmp_len;
				rs1_tmp = (rs1_tmp >> n) & tmp1;
				rf[i.a1.reg] = rs1_tmp;
				// printf("rf[i.a1.reg]: %lx\n", rf[i.a1.reg]); 
				break;
			}

			case BINV:{ // binv rd, rs1, rs2
				unsigned rs1_tmp = rf[i.a2.reg];
				unsigned n = rf[i.a3.reg];
				unsigned tmp_len = 31;
				unsigned tmp1 = 1;

				n = n & tmp_len;
				rs1_tmp = rs1_tmp ^ (tmp1 << n);
				rf[i.a1.reg] = rs1_tmp;
				// printf("rf[i.a1.reg]: %lx\n", rf[i.a1.reg]); 
				break;
			}

			case BINVI	:{ // binvi rd, rs1, shamt
				unsigned rs1_tmp = rf[i.a2.reg];
				unsigned n = i.a3.imm;
				unsigned tmp_len = 31;
				unsigned tmp1 = 1;

				n = n & tmp_len;
				rs1_tmp = rs1_tmp ^ (tmp1 << n);
				rf[i.a1.reg] = rs1_tmp;
				// printf("rf[i.a1.reg]: %lx\n", rf[i.a1.reg]); 
				break;
			}

			case BSET:{ // bset rd, rs1,rs2
				unsigned rs1_tmp = rf[i.a2.reg];
				unsigned n = rf[i.a3.reg];
				unsigned tmp_len = 31;
				unsigned tmp1 = 1;

				n = n & tmp_len;
				rs1_tmp = rs1_tmp | (tmp1 << n);
				rf[i.a1.reg] = rs1_tmp;
				// printf("rf[i.a1.reg]: %lx\n", rf[i.a1.reg]); 
				break;
			}

			//-----------culture0418-----------//
			
			
			//-----------song-fung-yu----------//
			case BSETI:{
				int index= (i.a3.imm & 31);
				rf[i.a1.reg] = rf[i.a2.reg] | ((uint32_t)1<< index);
				break;
			}
			case SEXTB:{
				uint32_t x = rf[i.a2.reg];
				uint32_t result = ((int32_t)(x << 24))>>24;
				rf[i.a1.reg] =  result ;
				break;
			}
			case SEXTH:{
				uint32_t x = rf[i.a2.reg];
				uint32_t result = ((int32_t)(x << 16)) >> 16;
				rf[i.a1.reg] =  result ;
				break;
			}
			case SH1ADD:{
				rf[i.a1.reg] =( rf[i.a2.reg] << 1) + rf[i.a3.reg]; 
				break;
			} 
			case SH2ADD:{
				rf[i.a1.reg] =( rf[i.a2.reg] << 2) + rf[i.a3.reg]; 
				break;
			}
			case SH3ADD:{
				rf[i.a1.reg] =( rf[i.a2.reg] << 3) + rf[i.a3.reg]; 
				break;
			}
			//-----------song-fung-yu----------//
			
			
			

			case ADD: rf[i.a1.reg] = rf[i.a2.reg] + rf[i.a3.reg]; break;
			case SUB: rf[i.a1.reg] = rf[i.a2.reg] - rf[i.a3.reg]; break;
			case SLT: rf[i.a1.reg] = (*(int32_t*)&rf[i.a2.reg]) < (*(int32_t*)&rf[i.a3.reg]) ? 1 : 0; break;
			case SLTU: rf[i.a1.reg] = rf[i.a2.reg] + rf[i.a3.reg]; break;
			case AND: rf[i.a1.reg] = rf[i.a2.reg] & rf[i.a3.reg]; break;
			case OR: rf[i.a1.reg] = rf[i.a2.reg] | rf[i.a3.reg]; break;
			case XOR: rf[i.a1.reg] = rf[i.a2.reg] ^ rf[i.a3.reg]; break;
			case SLL: rf[i.a1.reg] = rf[i.a2.reg] << rf[i.a3.reg]; break;
			case SRL: rf[i.a1.reg] = rf[i.a2.reg] >> rf[i.a3.reg]; break;
			case SRA: rf[i.a1.reg] = (*(int32_t*)&rf[i.a2.reg]) >> rf[i.a3.reg]; break;


			case ADDI: rf[i.a1.reg] = rf[i.a2.reg] + i.a3.imm; break;
			case SLTI: rf[i.a1.reg] = (*(int32_t*)&rf[i.a2.reg]) < (*(int32_t*)&(i.a3.imm)) ? 1 : 0; break;
			case SLTIU: rf[i.a1.reg] = rf[i.a2.reg] < i.a3.imm ? 1 : 0; break;
			case ANDI: rf[i.a1.reg] = rf[i.a2.reg] & i.a3.imm; break;
			case ORI: rf[i.a1.reg] = rf[i.a2.reg] | i.a3.imm; break;
			case XORI: rf[i.a1.reg] = rf[i.a2.reg] ^ i.a3.imm; break;
			case SLLI: rf[i.a1.reg] = rf[i.a2.reg] << i.a3.imm; break;
			case SRLI: rf[i.a1.reg] = rf[i.a2.reg] >> i.a3.imm; break;
			case SRAI: rf[i.a1.reg] = (*(int32_t*)&rf[i.a2.reg]) >> i.a3.imm; break;

			case LB:
			case LBU: 
			case LH:
			case LHU:
			case LW: rf[i.a1.reg] = mem_read(mem, rf[i.a2.reg]+i.a3.imm, i.op); break;
			
			case SB: 
			case SH: 
			case SW: mem_write(mem, rf[i.a2.reg]+i.a3.imm, rf[i.a1.reg], i.op); break;
			/*

			case SB: mem[rf[i.a2.reg]+i.a3.imm] = *(uint8_t*)&(rf[i.a1.reg]); break;
			case SH: *(uint16_t*)&(mem[rf[i.a2.reg]+i.a3.imm]) = *(uint16_t*)&(rf[i.a1.reg]); break;
			case SW: 
				*(uint32_t*)&(mem[rf[i.a2.reg]+i.a3.imm]) = rf[i.a1.reg]; 
				//printf( "Writing %x to addr %x\n", rf[i.a1.reg], rf[i.a2.reg]+i.a3.imm );
			break;
			*/

			case BEQ: if ( rf[i.a1.reg] == rf[i.a2.reg] ) pc_next = i.a3.imm; break;
			case BGE: if ( *(int32_t*)&rf[i.a1.reg] >= *(int32_t*)&rf[i.a2.reg] ) pc_next = i.a3.imm; break;
			case BGEU: if ( rf[i.a1.reg] >= rf[i.a2.reg] ) pc_next = i.a3.imm; 
				break;
			case BLT: if ( *(int32_t*)&rf[i.a1.reg] < *(int32_t*)&rf[i.a2.reg] ) pc_next = i.a3.imm; break;
			case BLTU: if ( rf[i.a1.reg] < rf[i.a2.reg] ) pc_next = i.a3.imm; break;
			case BNE: if ( rf[i.a1.reg] != rf[i.a2.reg] ) pc_next = i.a3.imm; break;

			case JAL:
				rf[i.a1.reg] = pc + 4;
				pc_next = i.a2.imm;
				//printf( "jal %d %x\n", pc+4, pc_next );
				break;
			case JALR:
				rf[i.a1.reg] = pc + 4;
				pc_next = rf[i.a2.reg] + i.a3.imm;
				//printf( "jalr %d %d(%d)\n", i.a1.reg, i.a3.imm, i.a2.reg );
				break;
			case AUIPC:
				rf[i.a1.reg] = pc + (i.a2.imm<<12);
				//printf( "auipc %x \n", rf[i.a1.reg] );
				break;
			case LUI:
				rf[i.a1.reg] = (i.a2.imm<<12);
				//printf( "lui %x \n", rf[i.a1.reg] );
				break;
			
			case HCF:
				printf( "\n\n----------\n\n" );
				printf( "Reached Halt and Catch Fire instruction!\n" );
				printf( "inst: %6d pc: %6d src line: %d\n", inst_cnt, pc, i.orig_line );
				print_regfile(rf);
				printf( "Cache read %d/%d Cache write %d/%d\n", cache_read_hits, mem_read_reqs, cache_write_hits, mem_write_reqs );
				printf( "Cache flush words: %d\n", mem_flush_words);
				dexit = true;
				break;
			case UNIMPL:
			default:
				printf( "Reached an unimplemented instruction!\n" );
				if ( i.psrc ) printf( "Instruction: %s\n", i.psrc );
				printf( "inst: %6d pc: %6d src line: %d\n", inst_cnt, pc, i.orig_line );
				print_regfile(rf);
				dexit = true;
				break;
		}
		pc = pc_next % MEM_BYTES;
		rf[0] = 0;// cleaner way to do this?
		if ( stepping ) {
			for ( int i = 0; i < 32; i++ ) {
				if ( rf[i] != rf_mirror[i] ) printf( ">> rf[x%02d] %x -> %x\n", i, rf_mirror[i], rf[i] );
				rf_mirror[i] = rf[i];
			}
		}

		//printf( "reg dst %d -> %x %d\n", i.a1.reg, rf[i.a1.reg], rf[i.a1.reg] );

		fflush(stdout);
		
	}
}

void normalize_labels(instr* imem, label_loc* labels, int label_count, source* src) {
	for ( int i = 0; i < DATA_OFFSET/4; i++ ) {
		instr* ii = &imem[i];
		if ( ii->op == UNIMPL ) continue;

		if ( ii->a1.type == OPTYPE_LABEL ) {
			ii->a1.type = OPTYPE_IMM;
			ii->a1.imm = label_addr(ii->a1.label, labels, label_count, ii->orig_line);
		}
		if ( ii->a2.type == OPTYPE_LABEL ) {
			ii->a2.type = OPTYPE_IMM;
			ii->a2.imm = label_addr(ii->a2.label, labels, label_count, ii->orig_line);
			switch (ii->op) {
				case LUI: {
					ii->a2.imm = (ii->a2.imm>>12); 
					char areg[4]; sprintf(areg, "x%02d", ii->a1.reg);
					char immu[12]; sprintf(immu, "0x%08x" , ii->a2.imm);
					//printf( "LUI %d 0x%x %s\n", ii->a1.reg, ii->a2.imm, immu );
					append_source("lui", areg, immu, NULL, src, ii);
					break;
				}
				case JAL:
				int pc = (i*4);
				int target = ii->a3.imm;
				int diff = pc - target;
				if ( diff < 0 ) diff = -diff;

				if ( diff >= (1<<21) ) {
					printf( "JAL instruction target out of bounds\n" );
					exit(3);
				}
				break;
			}
		}
		if ( ii->a3.type == OPTYPE_LABEL ) {
			ii->a3.type = OPTYPE_IMM;
			ii->a3.imm = label_addr(ii->a3.label, labels, label_count, ii->orig_line);
			switch(ii->op) {
				case ADDI: {
					ii->a3.imm = ii->a3.imm&((1<<12)-1);
					char a1reg[4]; sprintf(a1reg, "x%02d", ii->a1.reg);
					char a2reg[4]; sprintf(a2reg, "x%02d", ii->a2.reg);
					char immd[12]; sprintf(immd, "0x%08x" , ii->a3.imm);
					//printf( "ADDI %d %d 0x%x %s\n", ii->a1.reg, ii->a2.reg, ii->a3.imm, immd );
					append_source("addi", a1reg, a2reg, immd, src, ii);
					break;
				}
				case BEQ: case BGE: case BGEU: case BLT: case BLTU: case BNE: {
					int pc = (i*4);
					int target = ii->a3.imm;
					int diff = pc - target;
					if ( diff < 0 ) diff = -diff;

					if ( diff >= (1<<13) ) {
						printf( "Branch instruction target out of bounds\n" );
						exit(3);
					}
					break;
				}
			}
		}
	}
}

int
main(int argc, char** argv) {
	if ( argc < 2 ) {
		printf( "usage: %s asmfile\n", argv[0] );
		exit(1);
	}

	FILE* fin = fopen(argv[1], "r" );
	if ( !fin ) {
		printf( "%s: No such file\n", argv[1] );
		exit(2);
	}

	bool start_immediate = false;
	if ( argc >= 3 ) {
		start_immediate = true;
	}


	//ProcessorState* ps = new ProcessorState();
	
	int memoff = 0;
	uint8_t* mem = (uint8_t*)malloc(MEM_BYTES);
	instr* imem = (instr*)malloc(DATA_OFFSET*sizeof(instr)/4);
	label_loc* labels = (label_loc*)malloc(MAX_LABEL_COUNT*sizeof(label_loc));
	int label_count = 0;
	source src;
	src.offset = 0;
	src.src = (char*)malloc(sizeof(char)*MAX_SRC_LEN);

	if ( !mem || !labels || !imem || !src.src ) {
		printf( "Memory allocation failed\n" );
		exit(2);
	}

	for ( int i = 0; i < DATA_OFFSET/4; i++ ) {
		imem[i].op = UNIMPL;
		imem[i].a1.type = OPTYPE_NONE;
		imem[i].a2.type = OPTYPE_NONE;
		imem[i].a3.type = OPTYPE_NONE;
	}

	parse(fin, mem, imem, memoff, labels, label_count, &src);
	normalize_labels(imem, labels, label_count, &src);
	
	execute(mem, imem, labels, label_count, start_immediate);

	printf( "Execution done!\n" );
	exit(0);

}
