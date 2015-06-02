#include "simulator.h"

int main(int argc, char **argv){
	
	int arg[20];
	if(argc == 1){
		arg[0] = 64;
		arg[1] = 32;
		arg[2] = 8 ;
		arg[3] = 16;
		arg[4] = 16;
		arg[5] = 4 ;
		arg[6] = 4 ;
		arg[7] = 16;
		arg[8] = 4 ;
		arg[9] = 1 ;
	}
	for(int i = 1; i < argc; ++i)
		arg[i-1] = atoi(argv[i]);
	
	Simulator::run();		
	Simulator::statistic(argc - 1, arg);		
	return 0;
}
