#include "interpreter.h"

uchar Interpreter::get_opcode(u32 ins){
	return ( ins & OPCODE_MASK ) >> 26;
}
