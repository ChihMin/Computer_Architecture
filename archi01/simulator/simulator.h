#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <iomanip>

#include "IOfunction.h"

namespace Simulator{

	const s64 MAX = 2147483647;
	const s64 MIN = -2147483648;
	
	/* R Type Instruction */
	const u32 R_TYPE = 0x00;
	const u32 ADD = 0x20;
	const u32 SUB = 0x22;
	const u32 AND = 0x24;
	const u32 OR =  0x25;
	const u32 XOR = 0x26;
	const u32 NOR = 0x27;
	const u32 NAND = 0x28;
	const u32 SLT = 0x2A;
	const u32 SLL = 0x00;
	const u32 SRL = 0x02;
	const u32 SRA = 0x03;
	const u32 JR = 0x08; 

	extern u32 PC, VPC, cycle;
	extern u32 iimage_words;
	extern u32 dimage_words;
	
	extern FILE *ERR;
		
	extern u32 iimage[];
	extern u32 dimage[]; 
	
	extern int reg[];
	extern Instruction ins[]; 

/******** HOST CPU PROCESS ******/
	void initialize();
	void run();
	void execute(bool mode);
	void test_seed();
	void decode_instruction();
	void check_image();
	void write_snapshot();
	void destruct();
/*******************************/


/******* EXEXUTION PROCESS *****/
	void R_Type_Calculator(Instruction cur_ins);
	void add_program_counter();
	u32 get_VPC();
/******************************/


/******* R_TYPE_FUNCTION ******/
	void add_funct(u32 rd, u32 rs, u32 rt);
	void sub_funct(u32 rd, u32 rs, u32 rt);
	void and_funct(u32 rd, u32 rs, u32 rt);
	void or_funct(u32 rd, u32 rs, u32 rt);
	void xor_funct(u32 rd, u32 rs, u32 rt);
	void nor_funct(u32 rd, u32 rs, u32 rt);
	void nand_funct(u32 rd, u32 rs, u32 rt);
	void slt_funct(u32 rd, u32 rs, u32 rt);
	void sll_funct(u32 rd, u32 rt, u32 C_shamt);
	void srl_funct(u32 rd, u32 rt, u32 C_shamt);
	void sra_funct(u32 rd, u32 rt, u32 C_shamt);
	void jr_funct(u32 rs);
/******************************/

/********** ERROR DETECT ******/
	bool write_to_reg_zero_detect(Instruction ins);
	void detect_overflow(s64 sum, int x, int y);
/******************************/

}

#endif
