#ifndef STAGE_H
#define STAGE_H

#include "interpreter.h"

class Entry{

public :
	
	Entry();	
	Entry(const Instruction &_ins, u32 _fake_ins, const int _reg[], const bool _error[]);
	Entry(Instruction _ins, const int _reg[], const bool _error[]);
	Instruction get_ins();
	u32 get_fake_ins();
	bool get_error(int i);
	bool is_insert();
	int *get_reg();
	void set_reg(const int _reg[]);
	void set_error(const bool _error[]);
	void set_ins(Instruction ins);
	void set_insert();
	void set_fake_ins(u32 ins);
private :
	
	bool insert;
	Instruction ins;
	u32 fake_ins;
	int reg[40];
	bool error[5];
};

class Stage{

public :
	
	Stage();	
	Stage(Entry NOP);
	void push_ins(Entry ins);
	void update_reg(const int reg[]);
	void update_error(const bool error[]);
	void insert_nop();
	void flush_replace();
	Entry get_entry(int current);
	Instruction get_NOP();
private :
		
	Entry stage[6];
	Instruction NOP;
};

#endif
