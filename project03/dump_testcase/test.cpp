#include "simulator.h"
#include <iostream>
#include <bitset>

using namespace Simulator;

int main(){
	
	initialize();

	int x = -2147483648;
	u32 rd = 10, rt = 9, C = 15;
	reg[rt] = x;

	
	std::cout << std::bitset<32>(reg[rt]) << std::endl;	

	sll_funct(rd, rt, C);
	std::cout << std::bitset<32>(reg[rd]) << std::endl;	
	

	srl_funct(rd, rt, C);
	std::cout << std::bitset<32>(reg[rd]) << std::endl;	

	sra_funct(rd, rt, C);
	std::cout << std::bitset<32>(reg[rd]) << std::endl;	
	
	return 0;
}
