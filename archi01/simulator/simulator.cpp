#include "simulator.h"

namespace Simulator{
	u32 iimage[256];
	u32 dimage[256];
	char iimagePath[] = "../testcase/";
	char dimagePath[] = "../testcase/";

	void run(){
		load_binary(iimage, iimagePath, dimage, dimagePath);		
	}
}
