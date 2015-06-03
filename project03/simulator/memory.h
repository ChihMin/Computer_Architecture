#ifndef MEMORY_H
#define MEMORY_H

#include "interpreter.h"

class Memory{

	public:

		Memory();
		void set_time(u32 time);
		void set_VA(u32 VA);
		void set_VP(u32 VP);
		void set_PP(u32 PP);
		void set_PA(u32 PA);
		void set_valid(bool valid);
		void set_ins(Instruction ins);
		
		u32 get_time();
		u32 get_VA();
		u32 get_VP();
		u32 get_PA();
		u32 get_PP();
		bool is_valid();
		Instruction get_ins();

	private:

		u32 Time;
		u32 VirtualAddress;
		u32 VirtualPage;
		u32 PhysicalPage;
		u32 PhysicalAddress;
		bool valid;
		Instruction ins;
};

#endif
