#include "IOfunction.h"

void load_binary(u32 *iimage, const char *iimage_file, u32 *dimage, const char *dimage_file){
	u32 in;
	FILE *iimageR = fopen(iimage_file, "rb" );
	FILE *dimageR = fopen(dimage_file, "rb" );
	
	int i = 0;
	while( i < 300 && fread(&in, sizeof(u32), 1, iimageR) ){
		trans_small_to_big_endian( in );
		iimage[i++] = in;
	}

	i = 0;
	while( i < 300 && fread(&in, sizeof(u32), 1, dimageR) ){
		trans_small_to_big_endian( in );
		dimage[i++] = in;
	}
	
	fclose( iimageR );	
	fclose( dimageR );
}

void trans_small_to_big_endian(u32 &in){
	uchar tar[4];
	for(int i = 1; i <= 4; ++i){
		u32  mask = ((long long int)1 << ( i * 8 ) ) - 1; 	
		tar[4 - i] = (in & mask) >> ( (i - 1) * 8 ); 
		//printf("%X ", tar[4-i] );
	}
	
	in = 0;
	for(int i = 0; i < 4; ++i){
		in |= ( tar[i] << (i * 8 ) );
	}
	//printf("\n");
}
