#include "simulator.h"

namespace Simulator{
	char get_char(s64 address){
		if( address % 4 == 0 )
			return (char)((dimage[address/4] & 0xFF000000) >> 24);
		
		else if(address % 4 == 1)
			return (char)((dimage[address/4] & 0x00FF0000) >> 16);
		
		else if(address % 4 == 2)
			return (char)((dimage[address/4] & 0x0000FF00) >> 8);
		
		return (char)((dimage[address/4] & 0x000000FF));
	}

	short get_short(s64 address){
		if( address % 4 == 0)	
			return (short)((dimage[address/4] & 0xFFFF0000) >> 16);	
		return (short)(dimage[address/4] & 0x0000FFFF);
	}
	
	void save_short(s64 sum, u32 rt){
		int ans = reg[rt] & 0x0000FFFF;
		int tar = sum / 4;
		if( sum % 4 == 0 ){
			dimage[tar] &= 0x0000FFFF;
			ans = ans << 16;
			dimage[tar] |= ans;
		}
		else{
			dimage[tar] &= 0xFFFF0000;
			dimage[tar] |= ans;	
		}
	}

	void save_char(s64 sum, u32 rt){
		int ans = reg[rt] & 0x000000FF;
		int tar = sum / 4;
		if( sum % 4 == 0){
			dimage[tar] &= 0x00FFFFFF;
			ans = ans << 24;
			dimage[tar] |= ans;
		}
		else if( sum % 4 == 1){
			dimage[tar] &= 0xFF00FFFF;
			ans = ans << 16;
			dimage[tar] |= ans;
		}
		else if( sum % 4 == 2 ){
			dimage[tar] &= 0xFFFF00FF;
			ans = ans << 8;
			dimage[tar] |= ans;
		}
		else{
			dimage[tar] &= 0xFFFFFF00;
			dimage[tar] |= ans;
		}
	}

}
