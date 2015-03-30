#include "simulator.h"

namespace Simulator{
	
	u32 PC_Begin; 
	void execute(bool mode){
			
		PC_Begin = PC;		
		VPC = get_VPC();
		while( VPC < iimage_words && PC < 1024){

			printf("PC = 0x%08X\n",PC);

			cycle++ ;	// CPU Cycle
			
			Instruction cur_ins = ins[VPC];
			u32 opcode = cur_ins.get_opcode();
			add_program_counter();

			switch(opcode){
				case R_TYPE:
					R_Type_Calculator(cur_ins);				
					break;
				default:
					printf("opcode = 0x%02X\n", opcode); 
			}
			write_snapshot();
			VPC = get_VPC();	// update VPC
		}
	}
	
	u32 get_VPC(){
		return (PC - PC_Begin) / 4; 
	}

	void add_program_counter(){
		PC = PC + 4;	// Program Counter Point to next location
		VPC = get_VPC();
	}

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
		return false;
	}
}	
