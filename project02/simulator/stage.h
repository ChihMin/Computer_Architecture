#ifndef STAGE_H
#define STAGE_H

#include "interpreter.h"

class Entry{

public :
	
	Entry(const Instruction &_ins, u32 _fake_ins, bool _error[]);
	Instruction get_ins();
	u32 get_fake_ins();
	bool get_error(int i);
	int *get_reg();
	void set_reg(const int reg[]);
	void set_instruciton(const Instruction &ins);

private :
	
	Instruction ins;
	u32 fake_ins;
	int reg[40];
	bool error[5];
};

class Stage{

public :
	
	Stage(const Instruction &NOP);
	void push_ins(const Instruction &ins);
	void insert_nop();
	void flush_replace(const Instruction &ins);

private :
	
	Entry stage[6];
};

#endif
