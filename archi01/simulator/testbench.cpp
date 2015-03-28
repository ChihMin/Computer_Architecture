#include "simulator.h"

namespace Simulator{
	void test_seed(){
		iimage_words = 1;
		ins[0].set_opcode(0);
		ins[0].set_rs(8);
		ins[0].set_rt(9);
		ins[0].set_rd(10);
		ins[0].set_funct(ADD);
		reg[8] = 2;
		reg[9] = 10;
	}
}
