#include "IOfunction.h"

namespace IOfunction{

	FILE *snapshot;
	FILE *error_dump;

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
		int j = 0;
		int dimage_words = 300;
		while( j < dimage_words && fread(&in, sizeof(u32), 1, dimageR) ){
			trans_small_to_big_endian( in );
			if( i == 1 )
				dimage_words = in;
			
			if( i > 1 )	j++; 
			dimage[i++] = in;
		}
		printf("dimage_words = %d\n", dimage_words);
		fclose( iimageR );	
		fclose( dimageR );
	}

	void dump_instruction(u32 &PC, u32 &iimage_words, const u32 *iimage, Instruction *ins){
		PC =  iimage[0];
		iimage_words = iimage[1];
	}

	void dump_data(int &SP, u32 &dimage_words, u32 *dimage){
		SP = dimage[0];
		dimage_words = dimage[1];
		for(int i = 0; i < dimage_words; ++i)
			dimage[i] = dimage[i+2];
		
	}

	void trans_small_to_big_endian(u32 &in){
		uchar tar[4];
		for(int i = 1; i <= 4; ++i){
			u32 mask = ((long long int)1 << ( i * 8 ) ) - 1; 	
			tar[4 - i] = (in & mask) >> ( (i - 1) * 8 ); 
			//printf("%X ", tar[4-i] );
		}
	
		in = 0;
		for(int i = 0; i < 4; ++i){
			in |= ( tar[i] << (i * 8 ) );
		}
		//printf("\n");
	}

}
