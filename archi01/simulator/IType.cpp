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
			
			case LH:
				lh_funct(rt, rs, C);
				break;				
		
			case LHU:
				lhu_funct(rt, rs, C);
				break;

			case LB:
				lb_funct(rt, rs, C);
				break;
		}
	}
	
	char get_char(s64 address){
		if( address % 4 == 0 )
			return (char)((dimage[address/4] & 0xFF000000) >> 24);
		
		else if(address % 4 == 1)
			return (char)((dimage[address/4] & 0x00FF0000) >> 16);
		
		else if(address % 4 == 2)
			return (char)((dimage[address/4] & 0x0000FF00) >> 8);
		
		return (char)((dimage[address/4] & 0x000000FF));
	}

	short get_short(s64 address){
		if( address % 4 == 0)	
			return (short)((dimage[address/4] & 0xFFFF0000) >> 16);	
		return (short)(dimage[address/4] & 0x0000FFFF);
	}
	
	s64 compute_location(u32 rt, u32 rs, short C){
		int s = reg[rs];
		s64 sum = (s64)s + (s64)C;
		detect_overflow(sum, s, (int)C);
		detect_memory_address_overflow(sum);
		return sum;
	}
		
	void addi_funct(u32 rt, u32 rs, short C){
		s64 sum = (s64)reg[rs] + (s64)C;
		detect_overflow(sum, reg[rs], (int)C);
		if( rt != 0 )	reg[rt] = sum; 	
	}

	void lw_funct(u32 rt, u32 rs, short C){
		s64 sum = compute_location(rt, rs, C);
		if( sum % 4 != 0 )	
			data_misaligned(sum);
		
		if( is_halt )	return;
		if( rt != 0 )	reg[rt] = dimage[sum/4];			
	}

	void lh_funct(u32 rt, u32 rs, short C){
		s64 sum = compute_location(rt, rs, C);
		if( sum % 2 != 0 )	
			data_misaligned(sum);
		
		if( is_halt )	return;
		if( rt != 0 )	reg[rt] = get_short(sum);	
	}

	void lhu_funct(u32 rt, u32 rs, short C){
		s64 sum = compute_location(rt, rs, C);
		if( sum % 2 != 0 )	
			data_misaligned(sum);
		
		if( is_halt )	return;
		if( rt != 0 )	reg[rt] = (u16)get_short(sum);	
	}
	
	void lb_funct(u32 rt, u32 rs, short C){
		s64 sum = compute_location(rt, rs, C);
		if( is_halt )	return;
		if( rt != 0 )	reg[rt] = get_char(sum);	
	}
}
