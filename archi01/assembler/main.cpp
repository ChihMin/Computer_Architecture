#include <ctime>
#include <cstdlib>
#include "definition.h"
#include "simulator.h"
#include <bitset>
#include <iostream>


FILE *iimage;
FILE *dimage; 

using namespace std;

void write_ins(u32 ins){
	
	//cout << bitset<32>(ins) << endl;

	uchar A = (ins & 0xFF000000) >> 24;
	uchar B = (ins & 0x00FF0000) >> 16;
	uchar C = (ins & 0x0000FF00) >> 8;
	uchar D = (ins & 0x000000FF);
	
	fwrite(&A , sizeof(uchar), 1, iimage);
	fwrite(&B , sizeof(uchar), 1, iimage);
	fwrite(&C , sizeof(uchar), 1, iimage);
	fwrite(&D , sizeof(uchar), 1, iimage);
}

void write_data(u32 ins){
	uchar A = (ins & 0xFF000000) >> 24;
	uchar B = (ins & 0x00FF0000) >> 16;
	uchar C = (ins & 0x0000FF00) >> 8;
	uchar D = (ins & 0x000000FF);
	
	fwrite(&A , sizeof(uchar), 1, dimage);
	fwrite(&B , sizeof(uchar), 1, dimage);
	fwrite(&C , sizeof(uchar), 1, dimage);
	fwrite(&D , sizeof(uchar), 1, dimage);
}
void rtype(u32 opcode, u32 rd, u32 rs, u32 rt, u32 funct){
	u32 ins = 0;
	uchar C = 0xF;;
	ins |= (opcode << 26);
	ins |= (rs << 21);
	ins |= (rt << 16);
	ins |= (rd << 11);
	ins |= (C << 6);
	ins |= (funct); 
	write_ins(ins);
}
	
void rtype(u32 opcode, u32 rd, u32 rt, short C, u32 funct){
	u32 ins = 0;
	u32 rs = 0xF;
	ins |= (opcode << 26);
	ins |= (rs << 21);
	ins |= (rt << 16);
	ins |= (rd << 11);
	ins |= (C << 6);
	ins |= (funct); 
	write_ins(ins);
	
	//printf("funct = %d\n", funct);	
}

void rtype(u32 opcode, u32 rs, u32 funct){
	u32 ins = 0;
	u32 rt = 0xF;
	u32 rd = 0xF;
	u32 C = 0xF;

	ins |= (opcode << 26);
	ins |= (rs << 21);
	ins |= (rt << 16);
	ins |= (rd << 11);
	ins |= (C << 6);
	ins |= (funct);
	
	 
	write_ins(ins);
}

void IType(u32 opcode, u32 rt, u32 rs, u16 C){
	u32 ins = 0;
	ins |= (opcode << 26);
	ins |= (rs << 21);
	ins |= (rt << 16);
	ins |= C;
	write_ins(ins);	
}

void halt(){
	write_ins(0xFFABCDEF);
}

int main(){

	iimage = fopen("iimage.bin", "wb");
	dimage = fopen("dimage.bin", "wb");
	u32 PC = 0, SP = 400;
	u32 iimage_words = 57;
	u32 dimage_words = 5;

	write_data(SP);
	write_data(dimage_words);
	
	write_data(0x80000000);
	write_data(0x7FFFFFFF);
	write_data(0xABCDEF12);
	write_data(0x12348678);
	write_data(0x1234ABCD);	
	for(int i = 0; i < 100000; ++i){
		u32 tmp = rand() + rand(); 
		write_data(tmp);
	}
	

	write_ins(PC);
	write_ins(iimage_words);
	
	IType(LW, 10, 9, 0);
	IType(LW, 11, 9, 4);
	IType(LW, 8 , 9, 8);
	rtype(R_TYPE, 0, 11, (u32)11, ADD);
	rtype(R_TYPE, 0, 11, (u32)10, SUB);
	rtype(R_TYPE, 0, 10, (u32)11, SUB);
	rtype(R_TYPE, 0, 10, (u32)10, AND);
	rtype(R_TYPE, 0, 10, (u32)10, OR);
	rtype(R_TYPE, 0, 10, (u32)10, XOR);
	rtype(R_TYPE, 0, 10, (u32)10, NOR);
	rtype(R_TYPE, 0, 10, (u32)10, NAND);
	rtype(R_TYPE, 0, 10, (u32)10, SLT);
	rtype(R_TYPE, 0, 10, (short)31, SRL);
	rtype(R_TYPE, 0, 10, (short)31, SRA);
	rtype(R_TYPE, 12, 11, (u32)11, ADD);
	rtype(R_TYPE, 12, 11, (u32)10, SUB);
	rtype(R_TYPE, 12, 10, (u32)11, SUB);
	rtype(R_TYPE, 12, 10, (u32)11, AND);
	rtype(R_TYPE, 12, 10, (u32)11, OR);
	rtype(R_TYPE, 12, 10, (u32)11, XOR);
	rtype(R_TYPE, 12, 10, (u32)11, NOR);
	rtype(R_TYPE, 12, 10, (u32)11, NAND);
	rtype(R_TYPE, 12, 10, (u32)11, SLT);	
	rtype(R_TYPE, 12, 11, (u32)10, SLT);
	rtype(R_TYPE, 12, 10, (short)31, SRL);
	rtype(R_TYPE, 12, 10, (short)31, SRA);
	IType(LW, 0, 9, 16);
	IType(LH, 0, 9, 18);
	IType(LHU, 0, 9, 14);
	IType(LB, 0, 9, 13);
	IType(LBU, 0, 9, 15);
	IType(LUI, 0, 9, 0xABCD);
	IType(ANDI, 0, 12, 0xFFFF);
	IType(ORI, 0, 12, 0xFFFF);
	IType(NORI, 0, 12, 0xFFFF);
	IType(SLTI, 13, 9, -1);
	IType(SLTI, 13, 9, 0);
	IType(SLTI, 13, 9, 1);
	IType(SLTI, 13, 9, 0x8000);
	IType(SLTI, 13, 9, 0x7999);
	IType(SLTI, 0, 9, 0x7999);
	IType(LW, 15, 9, 16);
	IType(LH, 13, 9, 18);
	IType(LHU, 13, 9, 18);
	IType(LH, 13, 9, 14);
	IType(LHU, 13, 9, 14);
	IType(LB, 13, 9, 12);
	IType(LBU, 13, 9, 12);
	IType(LB, 13, 9, 13);
	IType(LBU, 13, 9, 13);
	IType(LB, 13, 9, 14);
	IType(LBU, 13, 9, 14);
	IType(LB, 13, 9, 15);
	IType(LBU, 13, 9, 15);
	IType(LUI, 13, 9, 0xABCD);
	IType(ANDI, 13, 12, 0xFFFF);
	halt();


	for(int i = 0; i < 100000; ++i){
		u32 tmp = rand();
		write_ins(tmp);
	}

	
	fclose(dimage);	
	fclose(iimage);
	return 0;
}
