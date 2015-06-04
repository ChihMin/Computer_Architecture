#include "simulator.h"

namespace Simulator{
	int PAGE_SIZE;
	int MEM_SIZE;
	int CACHE_SIZE;
	int BLOCK_SIZE;
	int SET;
	
	int V_PAGE_NUM;
	int BLOCK_NUM;
	int PAGE_NUM;
	int TLB_NUM;


	Memory *cache[300];
	Memory *tlb;
	Memory *pte;
	
	int *TLB_hits;
	int *TLB_miss;
	int *PAGE_hits;
	int *PAGE_miss;
	int *CACHE_hits;
	int *CACHE_miss;

	void init_memory(int type){
		/*	
			extern int I_MEM_SIZE;
			extern int D_MEM_SIZE;
			extern int I_PAGE_SIZE;
			extern int D_PAGE_SIZE;
			extern int I_CACHE_SIZE;
			extern int I_BLOCK_SIZE;
			extern int I_SET;
			extern int D_CACHE_SIZE;
			extern int D_BLOCK_SIZE;
			extern int D_SET;

			extern int I_V_PAGE_NUM;
			extern int D_V_PAGE_NUM;
			extern int I_BLOCK_NUM;
			extern int I_PAGE_NUM;
			extern int D_BLOCK_NUM;
			extern int D_PAGE_NUM;
			extern int I_TLB_NUM;
			extern int D_TLB_NUM;

			extern Memory D_cache[][300];
			extern Memory I_cache[][300];
			
			extern Memory I_tlb[];
			extern Memory D_tlb[];
			
			extern Memory I_pte[];
			extern Memory D_pte[];
		*/
		PAGE_SIZE  = !type ? I_PAGE_SIZE : D_PAGE_SIZE;
		MEM_SIZE   = !type ? I_MEM_SIZE : D_MEM_SIZE;
		CACHE_SIZE = !type ? I_CACHE_SIZE : D_CACHE_SIZE;
		BLOCK_SIZE = !type ? I_BLOCK_SIZE : D_BLOCK_SIZE;
		SET = !type ? I_SET : D_SET;
		
		V_PAGE_NUM = !type ? I_V_PAGE_NUM : D_V_PAGE_NUM;
		BLOCK_NUM = !type ? I_BLOCK_NUM : D_BLOCK_NUM;
		PAGE_NUM = !type ? I_PAGE_NUM : D_PAGE_NUM;
		TLB_NUM = !type ? I_TLB_NUM : D_TLB_NUM;
	
		tlb = !type ? I_tlb : D_tlb;
		pte = !type ? I_pte : D_pte;
		
		/*
			int *TLB_hits;
			int *TLB_miss;
			int *PAGE_hits;
			int *PAGE_miss;
			int *CACHE_hits;
			int *CACHE_miss;
		 */ 

		TLB_hits = !type ? &I_TLB_hits : &D_TLB_hits;
		TLB_miss = !type ? &I_TLB_miss : &D_TLB_miss;
		PAGE_hits = !type ? &I_PAGE_hits : &D_PAGE_hits;
		PAGE_miss = !type ? &I_PAGE_miss : &D_PAGE_miss;
		CACHE_hits = !type ? &I_CACHE_hits : &D_CACHE_hits;
		CACHE_miss = !type ? &I_CACHE_miss : &D_CACHE_miss;
	}
	
	void hit_miss_calculator(u32 V_address, int type){
		init_memory(type);
		TLB_PASS(V_address);
	}

	void TLB_PASS(u32 V_address){
		u32 V_page = V_address / PAGE_SIZE; // Get Virtual Page
		
		for(int i = 0; i < TLB_NUM; ++i){
			/* If TLB is valid and has entry */
			if(tlb[i].is_valid()){
					
			}
		}
	}
}
