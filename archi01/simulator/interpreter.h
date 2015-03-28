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

	/****** INSTRUCTION DECODE AND SET ******/
		
		void set_opcode( u32 ins );
		
		void set_rs( u32 ins );

		void set_rt( u32 ins );

		void set_rd( u32 ins );
		
		void set_C_shamt( u32 ins );
		
		void set_funct( u32 ins );
		
		void set_C_immediate( u32 ins );	
		
		void set_C_address(u32 ins);
	/**************************************/	
		void decode( u32 ins );

		void print();

	/*********** GET CONTENT **************/ 
	
		u32 get_opcode();	
		
		u32 get_rs();
		
		u32 get_rt();
		
		u32 get_rd();
		
		u32 get_C_shamt();
		
		u32 get_funct();
		
		u32 get_C_immediate();
		
		u32 get_C_address();
	
	/*************************************/

//	private:
	
		u32 instruction;
				
		u32 opcode;
		
		u32 rs, rt, rd;
		
		u32 C_shamt;
		
		u32 funct;
		
		u32 C_address;
			
		u32 C_immediate;	
}; 
#endif
