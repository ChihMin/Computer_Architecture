#include "simulator.h"

namespace Simulator{
	
	u32 PC_Begin; 
	void execute(bool mode){
			
		PC_Begin = PC;		
		VPC = get_VPC();
		
		Instruction ins_nop;
		ins_nop.decode(0);

		/* Initialize five stages */
		stage = Stage(Entry(ins_nop, 0, reg, error));


		while(true){
			memset(error, 0, sizeof(error));
			int *output_reg = stage.get_entry(4).get_reg();
			write_snapshot(output_reg);

			cycle++ ;	// CPU Cycle
				
			/* Push the instruction to IF NO stall happends */	
			if(!is_stall){
				to_be_flushed = false;
				stage.push_ins(Entry(ins[VPC], reg, error));
			
				/* Execute the instruction in ID */ 
				Instruction cur_ins = stage.get_entry(1).get_ins();
				u32 opcode = cur_ins.get_opcode();
			
				switch(opcode){
					case R_TYPE:
						R_Type_Calculator(cur_ins);				
						break;
						
					default:
						I_Type_and_J_Type_Calculator(cur_ins);
				}
				is_stall = false;
				print_stage_state();
				if(!to_be_flushed && !is_stall)
					add_program_counter();
			}
			else{
				stage.insert_nop();
				is_stall = false;
				print_stage_state();
				if(!to_be_flushed && !is_stall)
					add_program_counter();
			}


			if( is_terminated )	return;
			
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
	

}	
