#include "simulator.h"

namespace Simulator{

	void detect_stage_error(){
		/*********** DETECT ERRORS *************/
		for(int i = 4; i >= 2; i--){
			Entry entry = stage.get_entry(i);	
			Instruction temp = entry.get_ins();
			if(temp.is_nop()){	
				//printf("stage = %d, opcode = %d\n", i, temp.get_opcode());
				continue;
			}
			//printf("cycle %d\n", cycle);	
			if(i == 4 && entry.get_error(0))
				error_dump_output(0);

			if(i == 3 && entry.get_error(2))
				error_dump_output(2);

			if(i == 3 && entry.get_error(3))
				error_dump_output(3);

			if(i == 2 && entry.get_error(1))
				error_dump_output(1);
		}

		/***************************************/
	}

	void print_stage_state(){
		stage.update_error(error);
		stage.update_reg(reg);
	
		u32 opcode = stage.get_entry(1).get_ins().get_opcode();
		u32 funct = stage.get_entry(1).get_ins().get_opcode();
		
		
		//printf("cicle = %d\n", cycle);	
		for(int i = 0; i < 5; ++i){
			u32 opcode = stage.get_entry(i).get_ins().get_opcode();
			u32 funct = stage.get_entry(i).get_ins().get_funct();
			fprintf(IOfunction::snapshot, "stage %d = op : %X, funct : %X\n", i, opcode, funct);
		}
		fprintf(IOfunction::snapshot, "\n");
		if(to_be_flushed){
			fprintf(IOfunction::snapshot, "flushed!!\n");
			stage.flush_replace();
		}
				
	}
	
	void error_dump_output(int i){
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
