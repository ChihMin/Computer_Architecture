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


		while( PC < 1024){
			memset(error, 0, sizeof(error));
			to_be_flushed = false;
			int *output_reg = stage.get_entry(4).get_reg();
			
			if(mode){
				Instruction cur_ins = stage.get_entry(4).get_ins();
				fprintf(IOfunction::snapshot, "opcode = %X rd = %d rs = %d rt = %d funct = %X C_shamt = %X\n", cur_ins.get_opcode(), cur_ins.get_rd(), cur_ins.get_rs(), cur_ins.get_rt(), cur_ins.get_funct(), cur_ins.get_C_shamt());	
			}
			write_snapshot(output_reg);

			cycle++ ;	// CPU Cycle
				
			/* Push the instruction to IF NO stall happends */	
			
			//printf("cycle = %d, now PC = 0x%08X, VPC = %d\n", cycle-1, PC, VPC);
			if(!is_stall){
				stage.push_ins(Entry(ins[VPC], reg, error));
			
				/* Execute the instruction in ID */ 
				Instruction cur_ins = stage.get_entry(1).get_ins();
				u32 opcode = cur_ins.get_opcode();
				

			
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
				if(!to_be_flushed)
					add_program_counter();
			}
			is_stall = false;
			print_stage_state();

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
	

}	
