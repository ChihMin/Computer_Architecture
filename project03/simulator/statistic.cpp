#include "simulator.h"

namespace Simulator{
	void statistic(int argc, int *argv){
		

		initialize();
		
		int I_MEM_SIZE = argv[0];
		int D_MEM_SIZE = argv[1];
		int I_PAGE_SIZE = argv[2];
		int D_PAGE_SIZE = argv[3];
		int I_CACHE_SIZE = argv[4];
		int I_BLOCK_SIZE = argv[5];
		int I_SET = argv[6];
		int D_CACHE_SIZE = argv[7];
		int D_BLOCK_SIZE = argv[8];
		int D_SET = argv[9];


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
		write_snapshot();
		execute(test_mode);

		destruct();	
	}
}
