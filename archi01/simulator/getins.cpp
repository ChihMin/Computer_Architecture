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
		
u32 Instruction::get_C_immediate(){
	return this->C_immediate;
}

u32 Instruction::get_C_address(){
	return this->C_address;
}
