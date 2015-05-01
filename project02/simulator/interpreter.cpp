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
	this->C_shamt = (ins & C_SHAMT_MASK) >> 6;
}

void Instruction::set_funct( u32 ins ){
	this->funct = (ins & FUNCT_MASK);
}

void Instruction::set_C_immediate(u32 ins){
	this->C_immediate = (ins & C_IMMEDIATE_MASK);
}

void Instruction::set_C_address(u32 ins){
	this->C_address = (ins & C_ADDRESS_MASK);
}


void Instruction::set_opcode_t( u32 opcode ){
	this->opcode = opcode;
}
		
void Instruction::set_rs_t( u32 rs ){
	this->rs = rs;
}

void Instruction::set_rt_t( u32 rt ){
	this->rt = rt;
}

void Instruction::set_rd_t( u32 rd ){
	this->rd = rd;
}
		
void Instruction::set_C_shamt_t( u32 C_shamt ){
	this->C_shamt = C_shamt;
}
		
void Instruction::set_funct_t( u32 funct ){
	this->funct = funct;
}
		
void Instruction::set_C_immediate_t( short C_immediate ){
	this->C_immediate = C_immediate;
}
		
void Instruction::set_C_address_t(u32 C_address){
	this->C_address = C_address;
}

void Instruction::operator=(Instruction TEMP){
	this->instruction = TEMP.get_instruction();
	this->opcode = TEMP.get_opcode();
	this->rs = TEMP.get_rs();
	this->rt = TEMP.get_rt();
	this->rd = TEMP.get_rd();
	this->C_shamt = TEMP.get_C_shamt();
	this->funct = TEMP.get_funct();
	this->C_address = TEMP.get_C_address();
	this->C_immediate = TEMP.get_C_immediate();
}

void Instruction::decode( u32 ins ){
	this->instruction = ins;
	this->set_opcode(ins);
	this->set_rs(ins);
	this->set_rt(ins);
	this->set_rd(ins);
	this->set_C_shamt(ins);
	this->set_funct(ins);
	this->set_C_immediate(ins);
	this->set_C_address(ins);
}

void Instruction::print(){
	//std::cout << instruction << '\t'
	std::cout << std::hex << get_opcode() << '\t'
	<< get_rs() << '\t' 
	<< get_rt() << '\t'
	<< get_rd() << '\t'
	<< get_C_shamt() << '\t'
	<< get_funct() << '\t'
	<< get_C_immediate() << '\t'
	<< get_C_address() << std::endl;
}

