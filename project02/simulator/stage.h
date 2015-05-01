#include "simulator.h"

class Entry{

public :
	
	Entry(Instruction _ins, u32 _fake_ins, bool _errorp[]);
	Instruction get_ins();
	u32 get_fake_ins();
	bool get_error(int i);

private :
	
	Instruction ins;
	u32 fake_ins;
	bool error[5];
}

class Stage{

public :
	
	Stage();

private :
	
	Entry stage[6];

};
