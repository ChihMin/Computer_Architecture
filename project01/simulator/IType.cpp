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
			
			case LBU:
				lbu_funct(rt, rs, C);
				break;
			
			case SW:
				sw_funct(rt, rs, C);
				break;

			case SH:
				sh_funct(rt, rs ,C);
				break;
			
			case SB:
				sb_funct(rt, rs, C);
				break;

			case LUI:
				lui_funct(rt, C);
				break;

			case ANDI:
				andi_funct(rt, rs, C);
				break;

			case ORI:
				ori_funct(rt, rs, C);
				break;
			
			case NORI:
				nori_funct(rt, rs, C);
				break;

			case SLTI:
				slti_funct(rt, rs, C);
				break;
			
			case BEQ:
				beq_funct(rs, rt, C);
				break;

			case BNE:
				bne_funct(rs, rt, C);
				break;
			/* J TYPE */
			
			case J:
				j_funct(C);
				break;

			case JAL:
				jal_funct(C);
				break;
		}	
	}
	
		
	s64 compute_location(u32 rt, u32 rs, short C, s64 bytes){
		int s = reg[rs];
		s64 sum = (s64)s + (s64)C;
		detect_overflow(sum, s, (int)C);
		detect_memory_address_overflow(sum + bytes - 1);
		return sum;
	}
		
	void addi_funct(u32 rt, u32 rs, short C){
		s64 sum = (s64)reg[rs] + (s64)C;
		detect_overflow(reg[rs], (int)C);
		if( rt != 0 )	reg[rt] = sum; 	
	}

	void lw_funct(u32 rt, u32 rs, short C){
		s64 sum = compute_location(rt, rs, C, 4);
		if( sum % 4 != 0 )	
			data_misaligned(sum);
		
		if( is_halt )	return;
		if( rt != 0 )	reg[rt] = dimage[sum/4];			
	}

	void lh_funct(u32 rt, u32 rs, short C){
		s64 sum = compute_location(rt, rs, C, 2);
		if( sum % 2 != 0 )	
			data_misaligned(sum);
		
		if( is_halt )	return;
		if( rt != 0 )	reg[rt] = get_short(sum);	
	}

	void lhu_funct(u32 rt, u32 rs, short C){
		s64 sum = compute_location(rt, rs, C, 2);
		if( sum % 2 != 0 )	
			data_misaligned(sum);
		
		if( is_halt )	return;
		if( rt != 0 )	reg[rt] = (u16)get_short(sum);	
	}
	
	void lb_funct(u32 rt, u32 rs, short C){
		s64 sum = compute_location(rt, rs, C, 1);
		if( is_halt )	return;
		if( rt != 0 )	reg[rt] = get_char(sum);	
	}

	void lbu_funct(u32 rt, u32 rs, short C){
		s64 sum = compute_location(rt, rs, C, 1);
		if( is_halt )	return;
		if( rt != 0 )	reg[rt] = (uchar)get_char(sum);	
	}
	
	void sw_funct(u32 rt, u32 rs, short C){
		s64 sum = compute_location(rt, rs, C, 4);
		if( sum % 4 != 0 )	
			data_misaligned(sum);
		
		if( is_halt )	return;
		dimage[sum/4] = reg[rt];
	}

// here is used to save half world	
	void sh_funct(u32 rt, u32 rs, short C){
		s64 sum = compute_location(rt, rs, C, 2);
		if( sum % 2 != 0 )	
			data_misaligned(sum);
		
		if( is_halt )	return;
		save_short(sum, rt);
	}

	void sb_funct(u32 rt, u32 rs, short C){
		s64 sum = compute_location(rt, rs, C, 1);
		if( is_halt )	return;
		save_char(sum, rt);	
	}
	
	void lui_funct(u32 rt, short C){
		if(rt != 0)	reg[rt] = C << 16;
	}

	void andi_funct(u32 rt, u32 rs, short C){
		if(rt != 0)	reg[rt] = reg[rs] & (u16)C;
	}

	void ori_funct(u32 rt, u32 rs, short C){
		if(rt != 0)	reg[rt] = reg[rs] | (u16)C;
	}

	void nori_funct(u32 rt, u32 rs, short C){
		if(rt != 0)	reg[rt] = ~(reg[rs] | (u16)C);
	}

	void slti_funct(u32 rt, u32 rs, short C){
		if(rt != 0)	reg[rt] = reg[rs] < C;
	}
	
	void beq_funct(u32 rs, u32 rt, short C){
		if(reg[rs] == reg[rt])
			PC = PC + 4 * (int)C;
	}

	void bne_funct(u32 rs, u32 rt, short C){
		if(reg[rs] != reg[rt])
			PC = PC + 4 * (int)C;
	}

	void j_funct(u32 C){
		PC &= 0xF0000000;	
		PC = PC | (C << 2);
	}

	void jal_funct(u32 C){
		reg[31] = PC;
		j_funct(C);
	}
}
