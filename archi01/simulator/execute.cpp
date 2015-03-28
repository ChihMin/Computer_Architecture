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
					//R_Type_Calculator(cur_ins);				
					break;
				default:
					printf("opcode = 0x%02X\n", opcode); 
			}
			write_snapshot();
		}
	}
	
	u32 get_VPC(){
		return (PC - PC_Begin) / 4; 
	}

	void add_program_counter(){
		PC = PC + 4;	// Program Counter Point to next location
		VPC = get_VPC();
	}
}
