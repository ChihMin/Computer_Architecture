#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <iomanip>

#include "interpreter.h"
#include "definition.h"
#include "IOfunction.h"


namespace Simulator{
	void initialize();
	void run();
	void check_image();
}

#endif
