#include "simulator.h"

namespace Simulator{
	
	void detect_overflow(s64 sum, int x, int y){
		if( x < 0 && y < 0 && sum < MIN)
			fprintf(ERR, "In cycle %d: Number Overflow\n", cycle);
		else if( x > 0 && y > 0 && sum > MAX)
			fprintf(ERR, "In cycle %d: Number Overflow\n", cycle);
		else if( x >= 0 && y <= 0 && sum > MAX)
			fprintf(ERR, "In cycle %d: Number Overflow\n", cycle);
		else if( x <= 0 && y >= 0 && sum < MIN)
			fprintf(ERR, "In cycle %d: Number Overflow\n", cycle);

	}

	bool detect_memory_address_overflow(s64 address){
		if( address >= 1024 ||  address < 0 ){
			fprintf(ERR, "In cycle %d: Address Overflow\n", cycle);
			is_halt = true;
			return true;
		}
		return false;
	}

	void data_misaligned(s64 address){
		fprintf(ERR, "In cycle %d: Misalignment Error\n", cycle);	
		is_halt = true;
	}

	bool write_to_reg_zero_detect(Instruction cur_ins){
		u32 opcode = cur_ins.get_opcode();
		u32 rs = cur_ins.get_rs();
		u32 rt = cur_ins.get_rt();
		u32 rd = cur_ins.get_rd();
		u32 C_shamt = cur_ins.get_C_shamt();
		
		u32 funct = cur_ins.get_funct();
	
		if( opcode == 0 ){
			if( funct == JR )	return false;
			if( rd == 0 ){
				if( funct == SLL && rt == 0 && rs == 0 )
					return false;
				fprintf(ERR, "In cycle %d: Write $0 Error\n", cycle);
				return true;
			}
		}
		else{
			if( opcode == SW )	return false;
			if( opcode == SH )	return false;
			if( opcode == SB )	return false;	
			if( opcode == BEQ )	return false;
			if( opcode == BNE )	return false; 
			if( opcode == J )	return false;
			if( opcode == JAL )	return false;
	
			if( rt == 0 ){
				fprintf(ERR, "In cycle %d: Write $0 Error\n", cycle);
				return true;
			}
		}
		return false;
	}

}
