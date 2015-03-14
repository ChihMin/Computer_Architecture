#ifndef IOFUNCTION_H
#define IOFUNCTION_H

#include "definition.h"

void load_binary(u32 *iimage, const char *iimage_file, 
				 u32 *dimage, const char *dimage_file);

void trans_small_to_big_endian(u32 &in);

#endif

