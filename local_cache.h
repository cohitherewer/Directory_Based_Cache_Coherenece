// include necessary libraries
#include "directory.h"

/*
	Very Basic Cache.
	We can implement LRU or LFU Cache later 
*/

class local_cache{
private:
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
	local_cache()=delete;
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
		int position=find_block(addr);
		if(position!=-1){
			blocks.erase(blocks.begin()+position+1);
		}
	}

	void cache_update(address *addr){
		// cout<<"FUCK\n";
		if(blocks.size()>=this->capacity){
			blocks.erase(blocks.begin());
		}
		blocks.push_back(addr);
	}
	void show_cache(){
		for(auto it:blocks){
			printf("%d ",it->location);
		}
		printf("\n");
	}
};