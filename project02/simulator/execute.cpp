#include "simulator.h"

namespace Simulator{
	
	u32 PC_Begin; 
	void execute(bool mode){
			
		PC_Begin = PC;		
		VPC = get_VPC();
		while( PC < 1024){
			memset(error, 0, sizeof(error));	
			write_snapshot();
			//printf("PC = 0x%08X\n",PC);

			cycle++ ;	// CPU Cycle
			Instruction cur_ins = ins[VPC];
			if(mode){
				fprintf(IOfunction::snapshot, "opcode = %X rd = %d rs = %d rt = %d funct = %X C_shamt = %X\n", cur_ins.get_opcode(), cur_ins.get_rd(), cur_ins.get_rs(), cur_ins.get_rt(), cur_ins.get_funct(), cur_ins.get_C_shamt());	
			}


			u32 opcode = cur_ins.get_opcode();
			add_program_counter();

			switch(opcode){
				case HALT:
					return;
					break;

				case R_TYPE:
					R_Type_Calculator(cur_ins);				
					break;
					
				default:
					I_Type_and_J_Type_Calculator(cur_ins);
					//printf("opcode = 0x%02X\n", opcode); 
			}
			/**** PRINT ERROR DUMP ****/	
			for(int i = 0; i < 4; ++i)
				error_dump_output(i);
			/**************************/

			if( is_halt )	return;
			
			print_dimage(mode);
			update_VPC();
		}
	}
	
	u32 get_VPC(){
		return (PC) / 4; 
	}

	void add_program_counter(){
		PC = PC + 4;	// Program Counter Point to next location
	}

	void update_VPC(){
		VPC = get_VPC();
	}
	
	void error_dump_output(int i){
		if(!error[i])	return;
		if(i == 0)	
			fprintf(ERR, "In cycle %d: Write $0 Error\n", cycle);		
		
		if(i == 1)
			fprintf(ERR, "In cycle %d: Number Overflow\n", cycle);

		if(i == 2)
			fprintf(ERR, "In cycle %d: Address Overflow\n", cycle);

		if(i == 3)
			fprintf(ERR, "In cycle %d: Misalignment Error\n", cycle);
	}
}	
