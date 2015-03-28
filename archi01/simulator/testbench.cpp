#include "simulator.h"

namespace Simulator{
	void test_seed(){
		iimage_words = 1;
		ins[0].opcode = 0;
		ins[0].rs = 8;
		ins[0].rt = 9;
		ins[0].rd = 9;
		ins[0].funct = SUB;
		reg[9] = 1;
		reg[8] = -2147483648;
	}
}
