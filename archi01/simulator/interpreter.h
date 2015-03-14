#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "definition.h"
#define OPCODE_MASK 0xFC000000

namespace Interpreter{

	uchar get_opcode(u32 ins);
}

#endif
