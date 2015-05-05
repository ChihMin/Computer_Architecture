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
			}

			if(i == 3 && entry.get_error(3)){
				error_dump_output(3);
				is_terminated = true;
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
	
	void handle_stall(){
		/******* STALL DETECTION *****
			Must handle NOP instruction
			For 2 parts : 'Branch' and 'NOT Branch'
			LW in EX, LW in DM detect ID stage
			
		*****************************/

		Instruction ID = stage.get_entry(1).get_ins();
		Instruction EX = stage.get_entry(2).get_ins();
		Instruction DM = stage.get_entry(3).get_ins();
		
		if(ID.is_nop())	return;	
		if(!EX.is_nop()){
			int target = -1;
			if(EX.is_rt_dist())	
				target = EX.get_rt();

			else if(EX.is_rd_dist())
				target = EX.get_rd();

			if(target != -1){
				if(ID.is_branch()){
					if(ID.is_rs_source() && ID.get_rs() == target)
						is_stall = true;
					
					if(ID.is_rt_source() && ID.get_rt() == target)
						is_stall = true;			
				}
				else if(EX.is_load_ins()){
					if(ID.is_rs_source() && ID.get_rs() == target)
						is_stall = true;
					
					if(ID.is_rt_source() && ID.get_rt() == target)
						is_stall = true;			
				}
			}
		}
		
		if(DM.is_load_ins() && ID.is_branch()){
			if(ID.get_rs() == DM.get_rt())
				is_stall = true;
			
			else if(ID.get_rt() == DM.get_rt())
				is_stall = true;			
		}
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
		Instruction DM = stage.get_entry(3).get_ins();
		get_ins_string(ins_str, ID.get_ins());	
		fprintf(SNAP, "ID: %s", ins_str);
		
		if(is_stall){
			fprintf(SNAP, " to_be_stalled");	
		}
		else if(ID.get_ins().is_branch() && !DM.is_nop()){
			int tar = -1;
			u32 rs = ID.get_ins().get_rs();
			u32 rt = ID.get_ins().get_rt();
			if(DM.is_rd_dist())
				tar = DM.get_rd();

			else if(DM.is_rt_dist())
				tar = DM.get_rt();
			
			if(tar != 0 && rs == tar)
				fprintf(SNAP, " fwd_EX-DM_rs_$%d", rs);

			if(tar != 0 && rt == tar)
				fprintf(SNAP, " fwd_EX-DM_rt_$%d", rt);
		}
		else if(ID.get_ins().is_branch() && DM.get_opcode() == JAL){
			u32 rs = ID.get_ins().get_rs();
			u32 rt = ID.get_ins().get_rt();
			if(rs == 31)
				fprintf(SNAP, " fwd_EX-DM_rs_$%d", rs);

			if(rt == 31)
				fprintf(SNAP, " fwd_EX-DM_rt_$%d", rt);
		}
		fprintf(SNAP, "\n");
	
	}

	void print_EX(Entry EX){
		FILE *SNAP = IOfunction::snapshot;
		char ins_str[10];
		
		Instruction DM = stage.get_entry(3).get_ins();
		Instruction WB = stage.get_entry(4).get_ins();
		
		get_ins_string(ins_str, EX.get_ins());	
		fprintf(SNAP, "EX: %s", ins_str);
		
		if(!is_stall && !EX.get_ins().is_nop() && !EX.get_ins().is_branch()){
			if(EX.get_ins().is_rs_source()){
				u32 rs = EX.get_ins().get_rs();

				int tar = -1;
				bool is_fwd = false;
				if(!DM.is_nop()){			
					if(DM.is_rd_dist())
						tar = DM.get_rd();

					else if(DM.is_rt_dist())
						tar = DM.get_rt();
					
					if(tar != 0 && tar == rs){
						fprintf(SNAP, " fwd_EX-DM_rs_$%d", rs);	
						is_fwd = true;
					}
				}
				if(!is_fwd && !WB.is_nop()){
					if(WB.is_rd_dist())
						tar = WB.get_rd();

					else if(WB.is_rt_dist())
						tar = WB.get_rt();
					
					if(tar != 0 && tar == rs){
						fprintf(SNAP, " fwd_DM-WB_rs_$%d", rs);	
						is_fwd = true;
					}
				}

				if(WB.get_opcode() == JAL){
					if(31 == rs)
						fprintf(SNAP, " fwd_DM-WB_rs_$%d", rs);	
				}
				
			}
			if(EX.get_ins().is_rt_source()){
				u32 rt = EX.get_ins().get_rt();

				int tar = -1;
				bool is_fwd = false;
				if(!DM.is_nop()){			
					if(DM.is_rd_dist())
						tar = DM.get_rd();

					else if(DM.is_rt_dist())
						tar = DM.get_rt();
					
					if(tar != 0 && tar == rt){
						fprintf(SNAP, " fwd_EX-DM_rt_$%d", rt);	
						is_fwd = true;
					}
				}
				if(!is_fwd && !WB.is_nop()){
					if(WB.is_rd_dist())
						tar = WB.get_rd();

					else if(WB.is_rt_dist())
						tar = WB.get_rt();
					
					if(tar != 0 && tar == rt){
						fprintf(SNAP, " fwd_DM-WB_rt_$%d", rt);	
						is_fwd = true;
					}
				}
				if(WB.get_opcode() == JAL){
					if(31 == rt)
						fprintf(SNAP, " fwd_DM-WB_rs_$%d", rt);	
				}
			}
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
		fprintf(SNAP, "\n");
	}

	
	void handle_forward(u32 ){
		Instruction ID = stage.get_entry(1).get_ins();
		Instruction EX = stage.get_entry(2).get_ins();
		Instruction DM = stage.get_entry(3).get_ins();
		Instruction WB = stage.get_entry(4).get_ins();
	
				
	}
	 
	void print_stage_state(){
		stage.update_error(error);
		stage.update_reg(reg);
	
		Entry IF = stage.get_entry(0);
		Entry ID = stage.get_entry(1);
		Entry EX = stage.get_entry(2);
		Entry DM = stage.get_entry(3);
		Entry WB = stage.get_entry(4);
		
		handle_stall();
			
		/* IF Stage */
		print_IF(IF);
		print_ID(ID);
		print_EX(EX);
		print_DM(DM);
		print_WB(WB);
/*
	next have to do forwarding
*/
		
		if(!is_stall && to_be_flushed)
			stage.flush_replace();
		detect_halt();
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
