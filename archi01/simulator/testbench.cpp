#include "simulator.h"

namespace Simulator{
	void test_seed(){
		iimage_words = 10;
		ins[0].opcode = 0;
		ins[0].rs = 8;
		ins[0].rt = 9;
		ins[0].rd = 9;
		ins[0].funct = ADD;
		reg[8] = -1;
		reg[9] = -2147483646;

		for(int i = 1; i < iimage_words; ++i)
			ins[i] = ins[i-1];
	}
}
