#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <iomanip>

#include "IOfunction.h"


namespace Simulator{
	extern u32 PC;
	extern u32 iimage_words;
	extern u32 dimage_words;
	
	extern u32 iimage[];
	extern u32 dimage[]; 

	void initialize();
	void run();
	void decode_instruction();
	void check_image();
}

#endif
