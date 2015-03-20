#include "interpreter.h"

namespace Interpreter{
	uchar get_opcode(u32 ins){
		return ( ins & OPCODE_MASK ) >> 26;
	}

}

Instruction::Instruction(){}

void Instruction::set_opcode(u32 ins){
	this->opcode = ( ins & OPCODE_MASK ) >> 26;
}

void Instruction::set_rs( u32 ins ){
	this->rs = ( ins & RS_MASK ) >> 21;
}

void Instruction::set_rt( u32 ins ){
	this->rt = ( ins & RT_MASK ) >> 16;

}

void Instruction::set_rd( u32 ins ){
	this->rd = ( ins & RD_MASK ) >> 11;

}

void Instruction::set_C_shamt( u32 ins ){

}

void Instruction::set_C_immediate( u32 ins ){

}

void decode( u32 ins ){

}

uchar Instruction::get_opcode(){
	return this->opcode;
}
