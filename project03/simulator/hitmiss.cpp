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

		for(int i = 0; i < 300; ++i)
			cache[i] = !type ? I_cache[i] : D_cache[i];

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
		Memory entry = TLB_PASS(V_address);
		CACHE_PASS(entry, V_address);
	/*	
		if(type){
			printf("--------------------------\n");
			printf("SET  VALID VA VP PA PP TIME\n"); 
			for(int i = 0; i < BLOCK_NUM; ++i)
				for(int j = 0; j < SET; ++j){
					printf("%d : ", j);
					cache[i][j].print();
				}
			printf("---------------------------\n");
		}
	*/
	}

	void CACHE_PASS(Memory entry, u32 V_address){
		V_address = (V_address / 4) * 4;
		u32 V_page = entry.get_VP();
		u32 P_page = entry.get_PP();
		u32 P_address = P_page * PAGE_SIZE + V_address % PAGE_SIZE ;
		/* ^^^^^^^^^^ This guy is physical address in memory */
		
		entry.set_PA(P_address);
		entry.set_time(cycle);
		entry.set_VP(V_address / PAGE_SIZE);
		entry.set_VA(V_address);
		
		//printf("v address : %d, set : %d\n", V_page, SET);
		
		u32 block_index = (P_address / BLOCK_SIZE / SET) % BLOCK_NUM;
		

		/* BELOW is cahce hit if find entry */
		for(int set = 0; set < SET; ++set){
			if(cache[block_index][set].is_valid()){
				if(cache[block_index][set].get_PA()/BLOCK_SIZE == P_address/BLOCK_SIZE){
					(*CACHE_hits)++;
					cache[block_index][set].set_time(cycle);
					// ^^^^^^^^  update hit time
					
					//printf("%d -> %d in %d : %d : %d, %d\n", cycle, set, SET, block_index, P_address, V_address);
					return;
				}
			}
		}
		
		/* BELOW is cache miss situation */
		
		//printf("SET : %d --> circle %d miss\n", SET, cycle);
		(*CACHE_miss)++;

		/* Find invalid block */
		for(int set = 0; set < SET; ++set){
			if(!cache[block_index][set].is_valid()){
				cache[block_index][set] = entry;
				return;
			}
		}

		/* Find LRU entry to swap out */
		int time = (int)1e9;
		int target_set = 0;
		for(int set = 0; set < SET; ++set){
			if(cache[block_index][set].get_time() < time){
				time = cache[block_index][set].get_time();
				target_set = set;
			}
		}
		cache[block_index][target_set] = entry;

		/***** REMEMBER TO DEAL WITH PAGE SWAP OUT PROBLEM ****/
	}


	Memory TLB_PASS(u32 V_address){
		u32 V_page = V_address / PAGE_SIZE; // Get Virtual Page
		u32 P_address;
		u32 P_page;
		Memory entry;

		bool is_hit = false;
		for(int i = 0; i < TLB_NUM; ++i){
			/* If TLB is valid and has entry */
			if(tlb[i].is_valid()){
				if(tlb[i].get_VP() == V_page){
					is_hit = true;
					(*TLB_hits)++;		// TLB hits add	
					tlb[i].set_time(cycle);
					return tlb[i];
				}
			}
		}
		
		// If TLB miss, then query page table
		(*TLB_miss)++;	// TLB miss add
		entry =  PTE_PASS(V_address);
		
		// is used to find invalid index 
		int swap_in = -1; 
		int time = (int)1e9;
		for(int i = 0; i < TLB_NUM; ++i){
			if (!tlb[i].is_valid()){
				swap_in = i;
				break;
			}
			else if(time > tlb[i].get_time()){
				time = tlb[i].get_time();
				swap_in = i;
			}
		}
		
		tlb[swap_in] = entry;
		return entry;
		
	}

	Memory PTE_PASS(u32 V_address){
		u32 V_page = V_address / PAGE_SIZE; // GET virtual page
		if(pte[V_page].is_valid()){
			/*
			 * PTE valid bit is used to record 
			 * 
			 * IF data is valid in pte
			 *		then add page hits
			 * 
			 * and transfer pte[V_page] data to TLB 
			 */
			(*PAGE_hits)++;
			pte[V_page].set_time(cycle);
			return pte[V_page];
		}

		/********* BELOW ARE PAGE MISS BLOCKS *************\
		 * This block is used to find invalid block       *
		 * Or the LRU Page to replace                     *
		 **************************************************
		 ** IF SWAP ACTION HAPPENDS, UPDATE TLB AND CACHE *
		 ** This  way  is to prevent that data is not in  *
		 ** Physical page, but in cache or TLB.           * 
		\**************************************************/
		
		(*PAGE_miss)++;

		int first_invalid_page = -1;
		for(int i = 0; i < PAGE_NUM; ++i){
			/* i is physical page number */

			/* 
			 * Need to find invalid page 
			 * Just search each entry in PTE
			 */

			bool find_page = false;
			for(int j = 0; j < V_PAGE_NUM; ++j){
				if(pte[j].is_valid()){
					if(pte[j].get_PP() == i){
						find_page = true;
						break;
					}
				}
			}

			if(!find_page){
				/* If cannot find page */
				first_invalid_page = i;
				break;
			}
		}

		if(first_invalid_page != -1){
			/*
			 * Here can find invalid entry
			 * Just set page information to PTE
			 */

			pte[V_page].set_VA(V_address);
			pte[V_page].set_VP(V_page);
			pte[V_page].set_PP(first_invalid_page);
			pte[V_page].set_time(cycle);
			pte[V_page].set_valid(true);
		}
		else{
			/*
			 * 1. This block is used to find LRU entry
			 * 2. And swap out LRU and swap in 
			 * 3. Update cache and TLB block
			 *	  (valid ----> invalid)
			 */
			
			int swap_out_page = -1;
			int swap_in_page = -1;
			int time = (int)1e9;
			for(int i = 0; i < V_PAGE_NUM; ++i){
				if(pte[i].is_valid()){
					if(time > pte[i].get_time()){
						swap_in_page = pte[i].get_PP(); 
						time = pte[i].get_time();
						swap_out_page = i;
					}
				}
			}
			
			// Let pte be invalid
			pte[swap_out_page].set_valid(false);
			

			pte[V_page].set_VA(V_address);
			pte[V_page].set_VP(V_page);
			pte[V_page].set_PP(swap_in_page);
			pte[V_page].set_time(cycle);
			pte[V_page].set_valid(true);

			
			/* update TLB entry */

			for(int i = 0; i < TLB_NUM; ++i)
				if(tlb[i].get_VP() == swap_out_page)
					tlb[i].set_valid(false);
		
			/* update cache */
			
			for(int i = 0; i < BLOCK_NUM; ++i)
				for(int j = 0; j < SET; ++j){
					u32 page = swap_out_page;
					if(cache[i][j].get_VP() == page){
						cache[i][j].set_valid(false);
						//printf("here !!!!!\n");
					}
				}
			
		}
		return pte[V_page];
	}
}
