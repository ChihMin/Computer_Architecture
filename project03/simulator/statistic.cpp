#include "simulator.h"
#include <cstring>
namespace Simulator{

	int I_MEM_SIZE;
	int D_MEM_SIZE;
	int I_PAGE_SIZE;
	int D_PAGE_SIZE;
	int I_CACHE_SIZE;
	int I_BLOCK_SIZE;
	int I_SET;
	int D_CACHE_SIZE;
	int D_BLOCK_SIZE;
	int D_SET;
	int hits, misses, hitNum, missNum;
	

	void statistic(int argc, int *argv){
		initialize(true);
		
		I_MEM_SIZE = argv[0];
		D_MEM_SIZE = argv[1];
		I_PAGE_SIZE = argv[2];
		D_PAGE_SIZE = argv[3];
		I_CACHE_SIZE = argv[4];
		I_BLOCK_SIZE = argv[5];
		I_SET = argv[6];
		D_CACHE_SIZE = argv[7];
		D_BLOCK_SIZE = argv[8];
		D_SET = argv[9];


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
		write_report();
		//execute(test_mode);

		//destruct();	
	}

	void write_report(){
		fprintf( fptr_report, "ICache :\n");
		fprintf( fptr_report, "# hits: %u\n", hits );
		fprintf( fptr_report, "# misses: %u\n\n", misses );
		fprintf( fptr_report, "DCache :\n");
		fprintf( fptr_report, "# hits: %u\n", hits );
		fprintf( fptr_report, "# misses: %u\n\n", misses );
		fprintf( fptr_report, "ITLB :\n");
		fprintf( fptr_report, "# hits: %u\n", hits );
		fprintf( fptr_report, "# misses: %u\n\n", misses );
		fprintf( fptr_report, "DTLB :\n");
		fprintf( fptr_report, "# hits: %u\n", hits );
		fprintf( fptr_report, "# misses: %u\n\n", misses );
		fprintf( fptr_report, "IPageTable :\n");
		fprintf( fptr_report, "# hits: %u\n", hitNum ); 
		fprintf( fptr_report, "# misses: %u\n\n", missNum );
		fprintf( fptr_report, "DPageTable :\n");
		fprintf( fptr_report, "# hits: %u\n", hitNum ); 
		fprintf( fptr_report, "# misses: %u\n\n", missNum );
	}
}
