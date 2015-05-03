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

			if(i == 3 && entry.get_error(2)){
				error_dump_output(2);
				is_terminated = true;
				printf("here!!!\n");
			}

			if(i == 3 && entry.get_error(3)){
				error_dump_output(3);
				is_terminated = true;
				printf("here !!!\n");
			}

			if(i == 2 && entry.get_error(1))
				error_dump_output(1);
		}

		/***************************************/
	}
	
	void detect_halt(){
		int halt_cnt = 0;
		for(int i = 0; i < 5; ++i){
			u32 opcode = stage.get_entry(i).get_ins().get_opcode();
			if(opcode == HALT)
				halt_cnt++;
		}
		if(halt_cnt == 5)
			is_terminated = true;
	}

	void print_IF(Entry IF){	
		FILE *SNAP = IOfunction::snapshot;
		fprintf(SNAP, "IF: 0x%08X", IF.get_ins().get_instruction());
		
		if(is_stall)
			fprintf(SNAP, " to_be_stalled");	
		
		else if(to_be_flushed)
			fprintf(SNAP, " to_be_flushed");
			
					
		fprintf(SNAP, "\n");
	}

	void print_ID(Entry ID){
		FILE *SNAP = IOfunction::snapshot;
		char ins_str[10];
		get_ins_string(ins_str, ID.get_ins());	

		fprintf(SNAP, "ID: %s", ins_str);
		if(is_stall){
			fprintf(SNAP, " to_be_stalled");	
		}

		fprintf(SNAP, "\n");
	
	}

	void print_EX(Entry EX){
		FILE *SNAP = IOfunction::snapshot;
		char ins_str[10];
		get_ins_string(ins_str, EX.get_ins());	

		fprintf(SNAP, "EX: %s", ins_str);
		if(is_stall){
			fprintf(SNAP, " to_be_stalled");	
		}

		fprintf(SNAP, "\n");
	
	}
	void print_DM(Entry DM){
		FILE *SNAP = IOfunction::snapshot;
		char ins_str[10];
		get_ins_string(ins_str, DM.get_ins());	

		fprintf(SNAP, "DM: %s", ins_str);

		fprintf(SNAP, "\n");
	}
	void print_WB(Entry WB){
		FILE *SNAP = IOfunction::snapshot;
		char ins_str[10];
		get_ins_string(ins_str, WB.get_ins());	

		fprintf(SNAP, "WB: %s", ins_str);
		if(is_stall){
			fprintf(SNAP, " to_be_stalled");	
		}
		fprintf(SNAP, "\n");
	}

	void print_stage_state(){
		stage.update_error(error);
		stage.update_reg(reg);
	
		Entry IF = stage.get_entry(0);
		Entry ID = stage.get_entry(1);
		Entry EX = stage.get_entry(2);
		Entry DM = stage.get_entry(3);
		Entry WB = stage.get_entry(4);
		
		/* IF Stage */
		print_IF(IF);
		print_ID(ID);
		print_EX(EX);
		print_DM(DM);
		print_WB(WB);
/*
	next have to do forwarding
*/
		detect_halt();
		if(to_be_flushed)
			stage.flush_replace();
		detect_stage_error();
		fprintf(IOfunction::snapshot, "\n\n");
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
