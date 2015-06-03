#include "memory.h"

Memory::Memory(){
	valid = false;
}

void Memory::set_time(u32 time){
	this->Time = time;
}

void Memory::set_VA(u32 VA){
	this->VirtualAddress = VA;
}

void Memory::set_VP(u32 VP){
	this->VirtualPage = VP;
}

void Memory::set_PA(u32 PA){
	this->PhysicalAddress = PA;
}

void Memory::set_PP(u32 PP){
	this->PhysicalPage = PP;
}

void Memory::set_valid(bool valid){
	this->valid = valid;
}

void Memory::set_ins(Instruction ins){
	this->ins = ins;
}

u32 Memory::get_time(){
	return this->Time;
}

u32 Memory::get_VA(){
	return this->VirtualAddress;
}

u32 Memory::get_VP(){
	return this->VirtualPage;
}

u32 Memory::get_PA(){
	return this->PhysicalAddress;
}

u32 Memory::get_PP(){
	return this->PhysicalPage;
}

bool Memory::is_valid(){
	return this->valid;
}

Instruction Memory::get_ins(){
	return this->ins;
}
