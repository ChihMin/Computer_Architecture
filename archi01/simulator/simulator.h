#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <iomanip>

#include "IOfunction.h"

namespace Simulator{
	
	/* R Type Instruction */
	const u32 R_TYPE = 0x00;
	const u32 ADD = 0x20;
	const u32 SUB = 0x22;
	const u32 AND = 0x24;
	const u32 OR =  0x25;
	const u32 XOR = 0x26;
	const u32 NOR = 0x27;
	const u32 NAND = 0x28;
	const u32 SLT = 0x2A;
	const u32 SLL = 0x00;
	const u32 SRL = 0x02;
	const u32 SRA = 0x03;
	const u32 JR = 0x08; 

	extern u32 PC, cycle;
	extern u32 iimage_words;
	extern u32 dimage_words;
	
	extern u32 iimage[];
	extern u32 dimage[]; 
	
	extern u32 reg[];
	extern Instruction ins[]; 

	void initialize();
	void run();
	void execute();
	void decode_instruction();
	void check_image();
	void write_snapshot();
	void destruct();
}

#endif
