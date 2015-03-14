#include "IOfunction.h"

void load_binary(u32 *iimage, const char *iimage_file, u32 *dimage, const char *dimage_file){
	u32 in;
	FILE *iimageR = fopen(iimage_file, "rb" );
	FILE *dimageR = fopen(dimage_file, "rb" );
	
	int i = 0;
	while( i < 300 && fread(&in, sizeof(u32), 1, iimageR) ){
		iimage[i] = in;
	}

	while( i < 300 && fread(&in, sizeof(u32), 1, dimageR) ){
		dimage[i] = in;
	}
	
	fclose( iimageR );	
	fclose( dimageR );
}
