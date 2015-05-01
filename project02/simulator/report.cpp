#include "simulator.h"

namespace Simulator{
	void print_stage_state(){
		stage.update_error(error);
		stage.update_reg(reg);
	}
}
