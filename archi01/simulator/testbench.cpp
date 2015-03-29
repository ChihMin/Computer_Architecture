#include "simulator.h"
#include "testbench.h"

namespace Simulator{
	void test_seed(){
		iimage_words = 1;
		ins[0].opcode = 0;
		ins[0].rs = 8;
		ins[0].rt = 9;
		ins[0].rd = 9;
		ins[0].funct = ADD;
		reg[9] = -1;
		reg[8] = -2147483647;
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
