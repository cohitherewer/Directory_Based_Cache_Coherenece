// include necessary libraries
#include "directory.h"

/*
	Very Basic Cache.
	We can implement LRU or LFU Cache later 
*/

class local_cache{
private:
	// private members:
	// capacity and blocks containing the addresses
	int capacity;
	vector<address *> blocks;


	bool block_exist(address *request){
		// This functions returns if the blocks existance
		// true if founc
		for(auto it:blocks){
			if(it->location == request->location){
				return true;
			}
		}
		return false;
	}
	
	int find_block(address *addr){
		// this blocks finds the block in local cache
		// return true if found
		int index=0;
		for(auto it:blocks){
			if(it->location==addr->location){
				return index;
			}else{
				index+=1;
			}
		}
		return -1;
	}
public:
	// default constructor is deleted
	local_cache()=delete;

	// additional constructore is there 
	local_cache(int capacity){
		// instantiate a local bus with caching ability with 10 blocks with some capacity;
		this->capacity=capacity;
	}

	bool read_request(address *request){
		// This function check for read hit or miss, issues read miss 
		// True if hit

		printf("Read miss");
		return block_exist(request);
	}

	bool write_request(address *request){
		// This function check for write hit or miss, issues write miss
		// true if hit
		printf("Write miss");
		return block_exist(request);
	}

	void delete_block(address *addr){
		// delete the block while full or necessary
		int position=find_block(addr);
		if(position!=-1){
			blocks.erase(blocks.begin()+position+1);
		}
	}

	void cache_update(address *addr){
		// update the L1 cache block when necessay
		if(blocks.size()>=this->capacity){
			blocks.erase(blocks.begin());
		}
		blocks.push_back(addr);
	}

	void show_cache(){
		// show the content of cache block
		for(auto it:blocks){
			printf("%d ",it->location);
		}
		printf("\n");
	}
};