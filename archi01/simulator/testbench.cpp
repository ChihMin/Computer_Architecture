#include "simulator.h"
#include "testbench.h"

namespace Simulator{
	void test_seed(){
		
		dimage_words = 256;	
		for(int i = 0; i < 300; ++i)	dimage[i] = 0;

		dimage[0] = 0xFFFFFFFF;
		dimage[1] = 0x00001111;
			
		PC = 0;
		iimage_words = 3;
		ins[0].set_opcode_t(ADDI);
		ins[0].set_rs_t(8);
		ins[0].set_rt_t(9);
		ins[0].set_C_immediate_t(-1);
		reg[8] = 2147483647;
		reg[9] = -1;
		
		
		for(int i = 1; i < iimage_words; ++i)
			ins[i] = ins[i-1];
		ins[1].set_rt_t(0);
		

		reg[10] = 1020;
		
		dimage[255] = 0xC234F678;	
		ins[2].set_opcode_t(LBU);
		ins[2].set_C_immediate_t(0);
		ins[2].set_rs_t(10);
		ins[2].set_rt_t(11);
			
	/*	
		PC = 0;
		iimage_words = 6;
		ins[0].set_opcode_t(R_TYPE);
		ins[0].set_rs_t(8);
		ins[0].set_rt_t(9);
		ins[0].set_rd_t(0);
		ins[0].set_funct_t(ADD);
		reg[8] = 2147483647;
		reg[9] = 1;
		
	
		for(int i =1; i <iimage_words; ++i)	ins[i] = ins[i-1];

		ins[1].set_funct_t(SLL);
		ins[2].set_funct_t(ADD);
		ins[3].set_funct_t(NOR);

		ins[4].set_rs_t(0);
		ins[4].set_rt_t(0);
		ins[4].set_rd_t(0);
		ins[4].set_funct_t(SLL);
		
		ins[5].set_rs_t(11);
		ins[5].set_rt_t(12);
		ins[5].set_rd_t(0);

		reg[11] = 0;
		reg[12] = -2147483648;
		ins[5].set_funct_t(JR);
		ins[5].set_rs_t(11);
	*/
	}

	void testbench(){
		int d[100][2] = {{MAX, -MAX},{MIN, -MIN}};
		for(int i = 0; i < 2; ++i){
	
			int x = d[i][0], y = d[i][1];
			u32 rs = 8, rt = 9, rd = 10;
		
			reg[rs] = x, reg[rt] = y;
		
			printf("AND :");
			and_funct(rd, rs, rt);
			judge(x & y, reg[rd]);
		
			printf("OR :");
			or_funct(rd, rs, rt);
			judge(x | y, reg[rd]);
		
			printf("XOR :");
			xor_funct(rd, rs, rt);	
			judge(x ^ y, reg[rd]);
		
			printf("NAND :");
			nand_funct(rd, rs, rt);
			judge( ~(x & y), reg[rd]);

			printf("SLT : ");
			slt_funct(rd, rs, rt);
			judge( x < y, reg[rd]);
		}
	}

	void judge(int x, int y){
		if( x == y )	printf(" same\n");
		else	printf("%d vs %d is different\n", x, y);
	}
}
