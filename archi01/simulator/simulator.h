#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <iomanip>

#include "IOfunction.h"

namespace Simulator{

	const s64 MAX = 2147483647;
	const s64 MIN = -2147483648;
	
/*********** R Type Instruction ***********/
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
/*****************************************/

/*********** I Type Instruction **********/
	const u32 ADDI = 0x08;
	const u32 LW = 0x23;
	const u32 LH = 0x21;
	const u32 LHU = 0x25;
	const u32 LB = 0x20;
	const u32 LBU = 0x24;
	const u32 SW = 0x2B;
	const u32 SH = 0x29;
	const u32 SB = 0x28;
	const u32 LUI = 0x0F;
	const u32 ANDI = 0x0C;
	const u32 ORI = 0x0D;
	const u32 NORI = 0x0E;
	const u32 SLTI = 0x0A;
	const u32 BEQ = 0x04;
	const u32 BNE = 0x05;
/*****************************************/

/************* J TYPE & HALT ************/
	const u32 J = 0x02;
	const u32 JAL = 0x03;
	const u32 HALT = 0x3F;
/****************************************/

/********* REQUIRE COMPONENT ************/	
	extern u32 PC, VPC, cycle;
	extern u32 iimage_words;
	extern u32 dimage_words;
	
	extern FILE *ERR;
		
	extern u32 iimage[];
	extern u32 dimage[]; 
	
	extern int reg[];
	extern Instruction ins[]; 
	extern bool isHalt;
/***************************************/

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
	void I_Type_and_J_Type_Calculator(Instruction cur_ins);
	void add_program_counter();
	void update_VPC();
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

/******* I_TYPE_FUNCTION ******/
	void addi_funct(u32 rt, u32 rs, short C);	
	void lw_funct(u32 rt, u32 rs, short C);	
	void lh_funct(u32 rt, u32 rs, short C);	
	void lhu_funct(u32 rt, u32 rs, short C);	
	void lb_funct(u32 rt, u32 rs, short C);	
	void lbu_funct(u32 rt, u32 rs, short C);	
	void sw_funct(u32 rt, u32 rs, short C);	
	void sh_funct(u32 rt, u32 rs, short C);	
	void sb_funct(u32 rt, u32 rs, short C);	
	void lui_funct(u32 rt, short C);	
	void andi_funct(u32 rt, u32 rs, short C);	
	void ori_funct(u32 rt, u32 rs, short C);	
	void nori_funct(u32 rt, u32 rs, short C);	
	void slti_funct(u32 rt, u32 rs, short C);	
	void beq_funct(u32 rs, u32 rt, short C);	
	void bne_funct(u32 rs, u32 rt, short C);	
/******************************/

/****** J_TYPE_FUNCTION *******/
	void j_funct(u32 C_address);
	void jal_funct(u32 C_address);
/******************************/


/********** ERROR DETECT ******/
	bool write_to_reg_zero_detect(Instruction ins);
	void detect_overflow(s64 sum, int x, int y);
/******************************/

}

#endif
