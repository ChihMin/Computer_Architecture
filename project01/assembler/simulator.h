#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>


	const s64 MAX = 2147483647;
	const s64 MIN = -2147483648;
	
/*********** R Type Instruction ***********/
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
/*****************************************/

/*********** I Type Instruction **********/
	const u32 ADDI = 0x08;
	const u32 LW = 0x23;
	const u32 LH = 0x21;
	const u32 LHU = 0x25;
	const u32 LB = 0x20;
	const u32 LBU = 0x24;
	const u32 SW = 0x2B;
	const u32 SH = 0x29;
	const u32 SB = 0x28;
	const u32 LUI = 0x0F;
	const u32 ANDI = 0x0C;
	const u32 ORI = 0x0D;
	const u32 NORI = 0x0E;
	const u32 SLTI = 0x0A;
	const u32 BEQ = 0x04;
	const u32 BNE = 0x05;
/*****************************************/

/************* J TYPE & HALT ************/
	const u32 J = 0x02;
	const u32 JAL = 0x03;
	const u32 HALT = 0x3F;
/****************************************/

#endif
