#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "definition.h"
#define OPCODE_MASK 0xFC000000
#define RS_MASK 

namespace Interpreter{

	uchar get_opcode(u32 ins);
}

class Instruction{
	
	public:
		
		Instruction();
		
		void set_opcode( u32 ins );
		
		void set_rs( u32 ins );

		void set_rt( u32 ins );

		void set_rd( u32 ins );
		
		void set_C_shamt( u32 ins );
		
		void set_funct( u32 ins );
		
		void set_C_immediate( u32 ins );	
		
		void decode( u32 ins );

		uchar get_opcode();	
		
		uchar get_rs();
		
		uchar get_rt();
		
		uchar get_rd();
		
		uchar get_C_shamt();
		
		uchar get_funct();
		
		short get_C_immediate();
			
	private:
		
		uchar opcode;
		
		uchar rs, rt, rd;
		
		uchar C_shamt;
		
		uchar funct;
		
		short C_immediate;	
}; 
#endif
