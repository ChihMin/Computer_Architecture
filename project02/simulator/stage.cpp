#include "stage.h"

/*********** Entry Class **************/

Entry::Entry(const Instruction &_ins, u32 _fake_ins, const int _reg[], const bool _error[]){
	this->ins = _ins;
	this->fake_ins = _fake_ins;
	for(int i = 0; i < 32; ++i)
		this->reg[i] = _reg[i];
	for(int i = 0; i < 4; ++i)
		this->error[i] = _error[i];
	this->insert = false;
}
Entry::Entry(Instruction _ins, const int _reg[], const bool _error[]){
	this->ins = _ins;
	for(int i = 0; i < 32; ++i)
		this->reg[i] = _reg[i];
	for(int i = 0; i < 4; ++i)
		this->error[i] = _error[i];
	this->insert = false;
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

bool Entry::is_insert(){
	return this->insert;
}

int *Entry::get_reg(){
	return this->reg;
}

void Entry::set_reg(const int _reg[]){
	for(int i = 0; i < 32; ++i)
		this->reg[i] = _reg[i];
}

void Entry::set_error(const bool _error[]){
	for(int i = 0; i < 4; ++i)
		this->error[i] = _error[i];
}

void Entry::set_ins(Instruction ins){
	this->ins = ins;
}


void Entry::set_insert(){
	this->insert = true;
}

void Entry::set_fake_ins(u32 ins){
	this->fake_ins = ins;
}

/********** STAGE CLASS ***********/

Stage::Stage(){}

Stage::Stage(Entry NOP){
	for(int i = 0; i < 5; ++i)
		this->stage[i] = NOP;	// Set NOP Entry
	this->NOP.decode(0);		// Set NOP Instruction
}

void Stage::push_ins(Entry ins){
	Instruction tmp = ins.get_ins();
	for(int i = 4; i >= 1; i--)
		this->stage[i] = this->stage[i-1];	// Shift the state
	this->stage[0] = ins;					// push ins
/*	
	for(int i = 0; i < 5; ++i)
		printf("%d -> %X & %p\n", i, this->stage[i].get_ins().get_opcode(), &this->stage[i]);
*/
}

void Stage::insert_nop(){
	this->stage[4] = this->stage[3];		// right shift stage
	this->stage[3] = this->stage[2];		// right shift stage
	this->stage[2].set_ins(this->NOP);		// Conserve and insert NOP to EX
}

void Stage::flush_replace(){
	this->stage[0].set_ins(NOP);
	this->stage[0].set_insert();
}

void Stage::update_reg(const int reg[]){
	stage[1].set_reg(reg);
}

void Stage::update_error(const bool error[]){
	stage[1].set_error(error);
}

Entry Stage::get_entry(int current){
	//printf("get_entry_location : %d -----> %p\n",current,  &this->stage[current]);
	return this->stage[current];
}

Instruction Stage::get_NOP(){
	return this->NOP;
}

