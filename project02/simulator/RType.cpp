#include "simulator.h"

namespace Simulator{
	void R_Type_Calculator(Instruction cur_ins){
		u32 rs = cur_ins.get_rs();
		u32 rt = cur_ins.get_rt();
		u32 rd = cur_ins.get_rd();
		u32 C_shamt = cur_ins.get_C_shamt();
		u32 funct = cur_ins.get_funct();
	
//		printf("funct %02X vs %d\n", funct, ADD);
		
		write_to_reg_zero_detect(cur_ins);
		switch(funct){
			case ADD:
				add_funct(rd, rs, rt);
				break;

			case SUB:
				sub_funct(rd ,rs, rt);
				break;
			case AND:
				and_funct(rd, rs, rt);
				break;

			case OR:
				or_funct(rd, rs, rt);
				break;
		
			case XOR:
				xor_funct(rd, rs, rt);
				break;
		
			case NOR:
				nor_funct(rd, rs, rt);
				break;
			
			case NAND:
				nand_funct(rd, rs, rt);
				break;

			case SLT:
				slt_funct(rd, rs, rt);
				break;

			case SLL:
				sll_funct(rd, rt, C_shamt);
				break;
			
			case SRL:
				srl_funct(rd, rt, C_shamt);
				break;
				
			case SRA:
				sra_funct(rd, rt, C_shamt);
				break;
				
			case JR:
				jr_funct(rs);
				break;	 
		}
	}

	void add_funct(u32 rd, u32 rs, u32 rt){
		s64 sum = (s64)reg[rs] + (s64)reg[rt];;
		detect_overflow(reg[rs], reg[rt]);
		if( rd != 0 )	reg[rd] = sum;
	}

	void sub_funct(u32 rd, u32 rs, u32 rt){
		s64 sum = (s64)reg[rs] - (s64)reg[rt];
		detect_overflow(reg[rs], -reg[rt]);
		if( rd != 0 )	reg[rd] = sum;
	}

	void and_funct(u32 rd, u32 rs, u32 rt){
		if(rd == 0)	return;
		reg[rd] = reg[rs] & reg[rt];	
	}

	void or_funct(u32 rd, u32 rs, u32 rt){
		if(rd == 0)	return;
		reg[rd] = reg[rs] | reg[rt];	
	}

	void xor_funct(u32 rd, u32 rs, u32 rt){
		if(rd == 0)	return;
		reg[rd] = reg[rs] ^ reg[rt];	
	}

	void nor_funct(u32 rd, u32 rs, u32 rt){	
		if(rd == 0)	return;
		reg[rd] = ~(reg[rs] | reg[rt]);	
	}

	void nand_funct(u32 rd, u32 rs, u32 rt){
		if(rd == 0)	return;
		reg[rd] = ~(reg[rs] & reg[rt]);	
	}

	void slt_funct(u32 rd, u32 rs, u32 rt){
		if(rd == 0)	return;
		reg[rd] = (reg[rs] < reg[rt]);
	}
		
	void sll_funct(u32 rd, u32 rt, u32 C_shamt){
		if(rd == 0)	return;
		reg[rd] = (reg[rt] << C_shamt); 	
	}

	void srl_funct(u32 rd, u32 rt, u32 C_shamt){
		if(rd == 0)	return;
		reg[rd] = ((u32)reg[rt] >> C_shamt);
	}

	void sra_funct(u32 rd, u32 rt, u32 C_shamt){
		if(rd == 0)	return;
		reg[rd] = (reg[rt] >> C_shamt);	
	}

	void jr_funct(u32 rs){
		to_be_flushed = true;
		PC = reg[rs];		
	}
}
