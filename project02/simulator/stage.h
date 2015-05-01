#ifndef STAGE_H
#define STAGE_H

#include "interpreter.h"

class Entry{

public :
	
	Entry();	
	Entry(const Instruction &_ins, u32 _fake_ins, const int _reg[], const bool _error[]);
	Instruction get_ins();
	u32 get_fake_ins();
	bool get_error(int i);
	int *get_reg();
	void set_reg(const int reg[]);
	void set_ins(const Instruction &ins);
	void set_fake_ins(u32 ins);

private :
	
	Instruction ins;
	u32 fake_ins;
	int reg[40];
	bool error[5];
};

class Stage{

public :
	
	Stage();	
	Stage(const Entry &NOP);
	void push_ins(const Entry &ins);
	void insert_nop();
	void flush_replace(const Entry &ins);
	Entry get_entry(int current);
private :
	
	Entry stage[6];
	Instruction NOP;
};

#endif
