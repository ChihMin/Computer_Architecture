#include "simulator.h"

namespace Simulator{
	void test_seed(){
		iimage_words = 1;
		ins[0].opcode = 0;
		ins[0].rs = 8;
		ins[0].rt = 9;
		ins[0].rd = 10;;
		ins[0].funct = ADD;
		reg[8] = (1<<30);
		reg[9] = (1<<30)+123;
	}
}
