#include "simulator.h"

namespace Simulator{
	
	u32 PC_Begin; 
	void execute(bool mode){
			
		PC_Begin = PC;		
		VPC = get_VPC();
		
		Instruction ins_nop;
		ins_nop.decode(0);

		/* Initialize five stages */
		Stage stage = Stage(Entry(ins_nop, 0, reg, error));


		while( PC < 1024){
			memset(error, 0, sizeof(error));
			int *output_reg = stage.get_entry(4).get_reg();
			write_snapshot(output_reg);

			cycle++ ;	// CPU Cycle
				
			/* Push the instruction to IF*/	
			stage.push_ins(Entry(ins[VPC], reg, error));
			
			/* Execute the instruction in ID */ 
			Instruction cur_ins = stage.get_entry(1).get_ins();
			u32 opcode = cur_ins.get_opcode();
			add_program_counter();

			if(mode){
				fprintf(IOfunction::snapshot, "opcode = %X rd = %d rs = %d rt = %d funct = %X C_shamt = %X\n", cur_ins.get_opcode(), cur_ins.get_rd(), cur_ins.get_rs(), cur_ins.get_rt(), cur_ins.get_funct(), cur_ins.get_C_shamt());	
			}
		
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

			print_stage_state();
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
