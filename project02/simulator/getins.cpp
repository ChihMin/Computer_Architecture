#include "interpreter.h"

u32 Instruction::get_opcode(){
	return this->opcode;
}
		
u32 Instruction::get_rs(){
	return this->rs;
}
		
u32 Instruction::get_rt(){
	return this->rt;
}
		
u32 Instruction::get_rd(){
	return this->rd;
}
		
u32 Instruction::get_C_shamt(){
	return this->C_shamt;
}
		
u32 Instruction::get_funct(){
	return this->funct;
}
		
short Instruction::get_C_immediate(){
	return this->C_immediate;
}

u32 Instruction::get_C_address(){
	return this->C_address;
}

u32 Instruction::get_instruction(){
	return this->instruction;
}

bool Instruction::is_load_ins(){
	const u32 LW = 0x23;
	const u32 LH = 0x21;
	const u32 LHU = 0x25;
	const u32 LB = 0x20;
	const u32 LBU = 0x24;
	u32 x = this->opcode;
	return x == LW || x == LH || x == LB ||
		   x == LHU || x == LBU ;
}

bool Instruction::is_rt_source(){
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
	const u32 BEQ = 0x04;
	const u32 BNE = 0x05;
	
	u32 x = this->opcode;
	u32 y = this->funct;
	if(x == R_TYPE){
		return  y == ADD || y == SUB || y == AND ||
				y == OR  || y == XOR || y == NOR ||
				y == NAND|| y == SLT || y == SLL ||
				y == SRL || y == SRA ;
	}
	return x ==  BNE || x == BEQ;		
}

bool Instruction::is_rs_source(){
	const u32 R_TYPE = 0x00;
	const u32 ADD = 0x20;
	const u32 SUB = 0x22;
	const u32 AND = 0x24;
	const u32 OR =  0x25;
	const u32 XOR = 0x26;
	const u32 NOR = 0x27;
	const u32 NAND = 0x28;
	const u32 SLT = 0x2A;
	
	const u32 J = 0x02;
	const u32 JAL = 0x03;
	const u32 HALT = 0x3F;
	const u32 LUI = 0x0F;

	u32 x = this->opcode;
	u32 y = this->funct;

	if(x == R_TYPE){
		return  y == ADD || y == SUB || y == AND ||
				y == OR  || y == XOR || y == NOR ||
				y == NAND|| y == SLT;
	}
	return x != J && x != JAL && x != HALT && x != LUI;
}

bool Instruction::is_rd_dist(){
	return this->opcode == 0 &&
		   this->funct != 0x08; 
}

bool Instruction::is_rt_dist(){
	const u32 RType = 0x00;
	const u32 BEQ = 0x04;
	const u32 BNE = 0x05;
	const u32 HALT = 0x3F;
	const u32 J = 0x02;
	const u32 JAL = 0x03;
	const u32 SW = 0x2B;
	const u32 SH = 0x29;
	const u32 SB = 0x28;
	return this->opcode != 0 &&	
		   this->opcode != BEQ &&
		   this->opcode != BNE &&
		   this->opcode != HALT &&
		   this->opcode != J &&
		   this->opcode != JAL && 
		   this->opcode != SW &&
		   this->opcode != SH &&
		   this->opcode != SB;
}

bool Instruction::is_branch(){
	const u32 BEQ = 0x04;
	const u32 BNE = 0x05;
	
	return this->opcode == BEQ ||
		   this->opcode == BNE;
}

bool Instruction::is_nop(){
	return 
		this->opcode == 0 &&
		this->rd == 0 &&
		this->rt == 0 &&
		this->C_shamt == 0 &&
		this->funct == 0; 
}
