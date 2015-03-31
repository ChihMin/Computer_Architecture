#include "simulator.h"

namespace Simulator{
	void I_Type_and_J_Type_Calculator(Instruction cur_ins){
		u32 opcode = cur_ins.get_opcode();
		u32 rs = cur_ins.get_rs();
		u32 rt = cur_ins.get_rt();
		short C = cur_ins.get_C_immediate();
		
		write_to_reg_zero_detect(cur_ins);
		switch(opcode){
			case ADDI:
				addi_funct(rt, rs, C);
				break;
			
			case LW:
				lw_funct(rt, rs, C);
				break;			
		}
	}

	void addi_funct(u32 rt, u32 rs, short C){
		s64 sum = (s64)reg[rs] + (s64)C;
		detect_overflow(sum, reg[rs], (int)C);
		if( rt != 0 )	reg[rt] = sum; 	
	}

	void lw_funct(u32 rt, u32 rs, short C){
		int s = reg[rs];
		s64 sum = (s64)s + (s64)C;
		detect_overflow(sum, s, (int)C);
		detect_memory_address_overflow(sum);
		
		if( sum % 4 != 0 )	
			data_misaligned(sum);
		
		printf("cycle %d address sum = %lld\n", cycle, sum);
		if( is_halt )	return;
		if( rt != 0 )	reg[rt] = dimage[sum/4];			
	}
}
