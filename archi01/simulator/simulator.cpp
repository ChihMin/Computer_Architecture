#include "simulator.h"

namespace Simulator{
	u32 iimage_word;
	u32 dimage_word;
	u32 iimage[300];
	u32 dimage[300];
	char iimagePath[] = "../testcase/branch/iimage.bin";
	char dimagePath[] = "../testcase/branch/dimage.bin";

	void initialize(){
		memset(iimage, 0, sizeof( iimage ) );
		memset(dimage, 0, sizeof( dimage ) );
	}

	void run(){
		initialize();

		load_binary(iimage, iimagePath, dimage, dimagePath);		
		check_image();	
	}

	void check_image(){
		
		for(int i = 0; i < 300; ++i){
			printf("opcode = %X ", Interpreter::get_opcode(iimage[i]));
		
			std::cout << std::hex << std::setfill('0') << std::setw(8) << iimage[i] << std::endl; 
		}
	} 


}
