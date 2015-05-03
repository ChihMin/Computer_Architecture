#include "simulator.h"
#include <string>

namespace Simulator{
	
	void get_ins_string(char ins_str[], Instruction ins){
		std::string INS;
		u32 opcode = ins.get_opcode();
		u32 funct = ins.get_funct();
		
		if(ins.is_nop())
			INS = "NOP";
		else if(opcode == R_TYPE){
			switch(funct){
				case ADD:
					INS = "ADD";
					break;

				case SUB:
					INS = "SUB";
					break;
				case AND:
					INS = "AND";
					break;

				case OR:
					INS = "OR";
					break;
			
				case XOR:
					INS = "XOR";
					break;
			
				case NOR:
					INS = "NOR";
					break;
				
				case NAND:
					INS = "NAND";
					break;

				case SLT:
					INS = "SLT";
					break;

				case SLL:
					INS = "SLL";
					break;
				
				case SRL:
					INS = "SRL";
					break;
					
				case SRA:
					INS = "SRA";
					break;
					
				case JR:
					INS = "JR";
					break;	 
			}
		}

		else{
			switch(opcode){
				case ADDI:
					INS = "ADDI";
					break;
				
				case LW:
					INS = "LW";
					break;
				
				case LH:
					INS = "LH";
					break;				
			
				case LHU:
					INS = "LHU";
					break;

				case LB:
					INS = "LB";
					break;
				
				case LBU:
					INS = "LBU";
					break;
				
				case SW:
					INS  = "SW";
					break;

				case SH:
					INS = "SH";
					break;
				
				case SB:
					INS = "SB";
					break;

				case LUI:
					INS = "LUI";
					break;

				case ANDI:
					INS = "ANDI";
					break;

				case ORI:
					INS = "ORI";
					break;
				
				case NORI:
					INS = "NORI";
					break;

				case SLTI:
					INS = "SLTI";
					break;
				
				case BEQ:
					INS = "BEQ";
					break;

				case BNE:
					INS = "BNE";
					break;
				/* J TYPE */
				
				case J:
					INS = "J";
					break;

				case JAL:
					INS = "JAL";
					break;
				case HALT:
					INS = "HALT";
					break;
			}		
		}
		int len = INS.length();
		for(int i = 0; i < len; ++i)
			ins_str[i] = INS[i];
		ins_str[len] = '\0';
	}
}
