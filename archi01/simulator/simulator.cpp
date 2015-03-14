#include "simulator.h"

namespace Simulator{
	u32 iimage_word;
	u32 dimage_word;
	u32 iimage[300];
	u32 dimage[300];
	char iimagePath[] = "../testcase/";
	char dimagePath[] = "../testcase/";

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

	} 

}
