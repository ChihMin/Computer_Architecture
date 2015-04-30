#include "simulator.h"
#include "testbench.h"
#include <iostream>

namespace Simulator{
	FILE *ERR;
	bool is_halt = 0;
	bool error[4] = {0};
	u32 PC, SP, cycle, VPC;
	u32 iimage_words;
	u32 dimage_words;
	
	Instruction ins[300];
	u32 iimage[300];
	u32 dimage[300];

	int reg[40];

	char iimagePath[] = "iimage.bin";
	char dimagePath[] = "dimage.bin";

	void initialize(){
		IOfunction::snapshot = fopen("snapshot.rpt", "w");
		IOfunction::error_dump = fopen("error_dump.rpt", "w");
		ERR = IOfunction::error_dump;
		
		PC = INF;
		memset(reg, 0, sizeof( reg ) );
		memset(iimage, 0, sizeof( iimage ) );
		memset(dimage, 0, sizeof( dimage ) );
		memset(ins, 0, sizeof(Instruction));
	}

	void run(){
		initialize();

		IOfunction::load_binary(iimage, iimagePath, dimage, dimagePath);
		IOfunction::dump_instruction(PC, iimage_words, iimage, ins); 	
		IOfunction::dump_data(reg[29], dimage_words, dimage);	
			
		decode_instruction();	

		
	/********** WARNING !!!!! This Block is used to TEST ***********/
		//check_image();
		//testbench();
		//test_seed();  // seed mode 
		bool test_mode = false;
	/***************************************************************/
		execute(test_mode);

		destruct();	
	}
	
	void write_snapshot(){
		FILE *W = IOfunction::snapshot;
		fprintf(W, "cycle %d\n", cycle);
		for(int i = 0; i < 32; ++i)
			fprintf(W, "$%02d: 0x%08X\n",i, reg[i]);
		fprintf(W, "PC: 0x%08X\n\n\n", PC);		
	}

	void check_image(){
		/*
		printf("PC = %d %X\n", PC, iimage[0]);	
		for(int i = 0; i < iimage_words; ++i){
			printf("opcode = %X ", ins[i].get_opcode());	
			std::cout << std::hex << std::setfill('0') << std::setw(8) << iimage[i+2] << std::endl; 
		}*/
		printf("iimage_words = %d\n", iimage_words);
		printf("PC = %d, SP = %d\n", PC, reg[29]);
		std::cout  << "opcode" << '\t' 
					<< "rs" << '\t'
					<< "rt" << '\t' 
					<< "rd" << '\t' 
					<< "C_shamt" << '\t' 
					<< "funct" << std::endl;

		for(int i = 0; i < iimage_words; ++i){
			std::cout << i+1 << ' '; 	
			ins[i].print();
		}
		for(int i = 0; i < dimage_words + 10; ++i)
			printf("%d -> 0x%08X\n",i, dimage[i]);
	}
	 
	void decode_instruction(){
		int current = PC / 4;
		for(int i = 0; i < iimage_words; ++i)
			ins[current++].decode(iimage[i+2]);
	}

	void destruct(){
		fclose(IOfunction::snapshot);	
	}
}
