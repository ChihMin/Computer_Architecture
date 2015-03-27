#include "simulator.h"

namespace Simulator{
	u32 PC;
	u32 iimage_words;
	u32 dimage_words;
	
	Instruction ins[300];
	u32 iimage[300];
	u32 dimage[300];
	char iimagePath[] = "../testcase/branch/iimage.bin";
	char dimagePath[] = "../testcase/branch/dimage.bin";

	void initialize(){
		PC = INF;
		memset(iimage, 0, sizeof( iimage ) );
		memset(dimage, 0, sizeof( dimage ) );
	}

	void run(){
		initialize();

		IOfunction::load_binary(iimage, iimagePath, dimage, dimagePath);
		IOfunction::dump_instruction(PC, iimage_words, iimage, ins); 	
	
		decode_instruction();	
		check_image();	
	}

	void check_image(){
		/*
		printf("PC = %d %X\n", PC, iimage[0]);	
		for(int i = 0; i < iimage_words; ++i){
			printf("opcode = %X ", ins[i].get_opcode());	
			std::cout << std::hex << std::setfill('0') << std::setw(8) << iimage[i+2] << std::endl; 
		}*/

		for(int i = 0; i < iimage_words; ++i)
			ins[i].print();
	} 
	void decode_instruction(){
		for(int i = 0; i < iimage_words; ++i)
			ins[i].decode(iimage[i+2]);
	}
}
