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
				case HALT:
					return;
					break;

				case R_TYPE:
					R_Type_Calculator(cur_ins);				
					break;
					
				default:
					I_Type_and_J_Type_Calculator(cur_ins);
					printf("opcode = 0x%02X\n", opcode); 
			}
			if( is_halt )	return;
			
			print_dimage(mode);
			write_snapshot();
			update_VPC();
		}
	}
	
	u32 get_VPC(){
		return (PC - PC_Begin) / 4; 
	}

	void add_program_counter(){
		PC = PC + 4;	// Program Counter Point to next location
	}

	void update_VPC(){
		VPC = get_VPC();
	}
}	
