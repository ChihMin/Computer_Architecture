#include "IOfunction.h"
#include "cstdio"

void load_binary(u32 *iimage, const char *iimage_file, u32 *dimage, const char *dimage_file){
	u32 in;
	FILE *iimageR = fopen(iimage_file, "rb" );
	FILE *dimageR = fopen(dimage_file, "rb" );
	
	
	fclose( iimageR );	
	fclose( dimageR );
}
