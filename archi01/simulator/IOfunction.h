#ifndef IOFUNCTION_H
#define IOFUNCTION_H

#include "definition.h"
#include "interpreter.h"

namespace IOfunction{

	void load_binary(u32 *iimage, const char *iimage_file, 
				 u32 *dimage, const char *dimage_file);
	
	void dump_instruction(u32 &PC, u32 &iimage_words, const u32 *iimage, Instruction *ins);

	void trans_small_to_big_endian(u32 &in);
}
#endif

