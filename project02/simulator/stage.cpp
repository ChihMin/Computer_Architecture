#include "stage.h"

Entry::Entry(const Instruction &_ins, u32 _fake_ins, const int _reg[], const bool _error[]){
	this->ins = _ins;
	this->fake_ins = _fake_ins;
	for(int i = 0; i < 32; ++i)
		this->reg[i] = _reg[i];
	for(int i = 0; i < 4; ++i)
		this->error[i] = _error[i];
}

Entry::Entry(){}

Instruction Entry::get_ins(){
	return this->ins;
}

u32 Entry::get_fake_ins(){
	return this->fake_ins;
}

bool Entry::get_error(int i){
	return this->error[i];
}

int *Entry::get_reg(){
	return this->reg;
}

void Entry::set_reg(const int _reg[]){
	for(int i = 0; i < 32; ++i)
		this->reg[i] = _reg[i];
}

void Entry::set_ins(const Instruction &ins){
	this->ins = ins;
}


void Entry::set_fake_ins(u32 ins){
	this->fake_ins = ins;
}

Stage::Stage(){}

Stage::Stage(const Entry &NOP){
	for(int i = 0; i < 5; ++i)
		this->stage[i] = NOP;	// Set NOP Entry
	this->NOP.decode(0);		// Set NOP Instruction
}

void Stage::push_ins(const Entry &ins){
	for(int i = 4; i >= 1; i--)
		this->stage[i] = this->stage[i-1];	// Shift the state
	this->stage[0] = ins;					// push ins
}

void Stage::insert_nop(){
	this->stage[4] = this->stage[3];		// right shift stage
	this->stage[3] = this->stage[2];		// right shift stage
	this->stage[2].set_ins(this->NOP);		// Conserve and insert NOP to EX
}

void Stage::flush_replace(const Entry &ins){
	for(int i = 4; i >=2; i--)
		this->stage[i] = this->stage[i-1];	
	this->stage[1].set_ins(NOP);
	this->stage[0].set_fake_ins(
		this->stage[0].get_ins().get_instruction()
	);
}

Entry Stage::get_entry(int current){
	return stage[current];
}
