#include "address.h"
#include <cstdlib>


/*
This class defines the local cache of a processor
*/
class hash_function{
public:
	size_t operator()(const address *addr) const{
		return (hash<string>()(to_string(addr->location)));
	}
};
class local_cache{

private:
	int max_capacity;
	unordered_map<address *,bool,hash_function> blocks;
public:
	void get_cache_content(){
		for(auto it:blocks){
			cout<<it.first->location<<' '<<it.first->current_state;
		}
	}
	local_cache(int max_capacity){
		this->max_capacity=max_capacity;
	}

	bool if_contains(address *block){
		return this->blocks.find(block)!=this->blocks.end();
	}

	void modify_cache(address *addr){
		if(blocks.size()>=this->max_capacity){
			auto it=blocks.begin();
			blocks.erase(it);
		}
		blocks[addr]=true;
	}

	void change_addr_state(address *addr,char state){
		if(if_contains(addr)){
			blocks.erase(addr);
			address *r2=new address();
			r2->location=addr->location;
			r2->current_state=state;
			blocks[r2]=true;
		}
	}
};