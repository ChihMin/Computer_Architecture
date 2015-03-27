#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "definition.h"

#define	OPCODE_MASK	0xFC000000
#define	RS_MASK	0x03E00000
#define RT_MASK 0x001F0000
#define RD_MASK	0x0000F800
#define C_SHAMT_MASK 0x000003E0
#define FUNCT_MASK 0x0000001F
#define C_IMMEDIATE_MASK 0x0000FFFF
#define C_ADDRESS_MASK 0x03FFFFFF

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
		
		void set_C_address(u32 ins);
		
		void decode( u32 ins );

		void print();

		uchar get_opcode();	
		
		uchar get_rs();
		
		uchar get_rt();
		
		uchar get_rd();
		
		uchar get_C_shamt();
		
		uchar get_funct();
		
		short get_C_immediate();
			
	private:
	
		u32 instruction;
				
		u32 opcode;
		
		u32 rs, rt, rd;
		
		u32 C_shamt;
		
		u32 funct;
		
		u32 C_address;
			
		u32 C_immediate;	
}; 
#endif
