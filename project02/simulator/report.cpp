#include "simulator.h"

namespace Simulator{
	void print_stage_state(){
		stage.update_error(error);
		stage.update_reg(reg);
		for(int i = 0; i < 4; ++i)
			if(error[i])
				error_dump_output(i);

		for(int i = 0; i < 5; ++i){
			Entry entry = stage.get_entry(i);
			printf("stage %d ::::: ", i);
			stage.get_entry(i).get_ins().print(); 
		}
/*
		for(int i = 4; i >= 2; i--){
			
			Instruction temp = entry.get_ins();
			if(temp.is_nop()){	
				//printf("stage = %d, opcode = %d\n", i, temp.get_opcode());
				continue;
			}
			printf("cycle %d\n", cycle);	
			if(i == 4 && entry.get_error(0))
				error_dump_output(0);

			if(i == 3 && entry.get_error(2))
				error_dump_output(2);

			if(i == 3 && entry.get_error(3))
				error_dump_output(3);

			if(i == 2 && entry.get_error(1))
				error_dump_output(1);
		}
*/
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
