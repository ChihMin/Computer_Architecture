#include "stage.h"


Entry::Entry(const Instruction &_ins, u32 _fake_ins, bool _error[]){
	this->ins = _ins;
	this->fake_ins = _fake_ins;
	for(int i = 0; i < 4; ++i)
		this->error[i] = _error[i];
}

Instruction Entry::get_ins(){
	return this->ins;
}

u32 Entry::get_fake_ins(){
	return this->fake_ins;
}

bool Entry::get_error(int i){
	return this->error;
}

int *Entry::get_reg(){
	return this->reg;
}

void Entry::set_reg(const int _reg[]){
	for(int i = 0; i < 32; ++i)
		this->reg[i] = _reg[i];
}

void Entry::set_instruciton(const Instruction &ins){
	this->ins = ins;
}
