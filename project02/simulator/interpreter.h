#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "definition.h"

#define	OPCODE_MASK	0xFC000000
#define	RS_MASK	0x03E00000
#define RT_MASK 0x001F0000
#define RD_MASK	0x0000F800
#define C_SHAMT_MASK 0x000007C0
#define FUNCT_MASK 0x0000003F
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
		
		u32 get_instruction();
			
		u32 get_opcode();	
		
		u32 get_rs();
		
		u32 get_rt();
		
		u32 get_rd();
		
		u32 get_C_shamt();
		
		u32 get_funct();
		
		short get_C_immediate();
		
		u32 get_C_address();
	
		bool is_nop();
		
		bool is_load_ins();
		
		bool is_rt_dist();
		
		bool is_rd_dist();	
		
		bool is_rt_source();

		bool is_rs_source();
		
		bool is_branch();

		bool is_jr();
	/*************************************/

	/***** TEST DIRECT SET INSTRUCTION ***/
	
		void set_opcode_t( u32 opcode );
		
		void set_rs_t( u32 rs );

		void set_rt_t( u32 rt );

		void set_rd_t( u32 rd );
		
		void set_C_shamt_t( u32 C_shamt );
		
		void set_funct_t( u32 funct );
		
		void set_C_immediate_t( short C_immediate );	
		
		void set_C_address_t(u32 C_address);
	
	/*************************************/

	private:
	
		u32 instruction;
				
		u32 opcode;
		
		u32 rs, rt, rd;
		
		u32 C_shamt;
		
		u32 funct;
		
		u32 C_address;
			
		short C_immediate;	
}; 
#endif
