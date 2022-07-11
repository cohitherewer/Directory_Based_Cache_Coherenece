#include "local_cache.h"

#define CACHE_CAPACITY 100

/*
	CLASS for PROCESSOR PROGRAM
*/
class Processor{
private:
	local_cache *L1_cache;

	int search_directory(directory *dir,address *addr){
		// This function searches the address in the directory and returns its corresponding index
		// returns -1 if not found
		int index=0;
		for(auto it:dir->D){
			if(addr->location==it.first->location){
				dbg(index);
				return index;
			}else{
				index+=1;
			}
		}
		return -1;
	}

	void directory_modification(directory *dir,address *addr,int pro_index,int processor_count,string request_type){
		// cout<<request_type<<endl;
		// dbg(request_type);
		if(request_type[0]=='R'){
			if(dir->is_full()){
				// delete the first position
				dir->D.erase(dir->D.begin());
			}
			vector<int> bit_array(processor_count+1,0);
			dir->D.push_back(make_pair(addr,bit_array));
			// mark that directory
			dir->D[dir->D.size()-1].second[pro_index]=1;
			// mark exclusive bit as 1
			dir->D[dir->D.size()-1].second[processor_count]=1;
		}else if(request_type[0]=='W'){
			int position=search_directory(dir,addr);
			if(position!=-1){
				for(int itr=0;itr<dir->D[position].second.size();itr+=1){
					dir->D[position].second[itr]=0;
				}
			// make the exclusive bit 1
				dir->D[position].second[processor_count]=1;
				dir->D[position].second[pro_index]=1;
			}else{
				if(dir->is_full()){
				// delete the first position
					dir->D.erase(dir->D.begin());
				}
				vector<int> bit_array(processor_count+1,0);
				dir->D.push_back(make_pair(addr,bit_array));
			// mark that directory
				dir->D[dir->D.size()-1].second[pro_index]=1;
			// mark exclusive bit as 1
				dir->D[dir->D.size()-1].second[processor_count]=1;
			}
		}else{
			printf("INVALID REQUEST\n");
		}
	}
public:
	Processor(){
		// instanciate the processor program 
		// every processor has its own L1 Cache
		L1_cache=new local_cache(CACHE_CAPACITY);
	}


	vector<int> L1_request(string request_type,address *addr,directory *dir,int pro_index,int processor_count){
		// this function process the request coming to the particular processor
		// return empty list for read request
		// return list of caches for write request
		// need to invalidate those caches
		// cout<<request_type<<endl;
		dbg(request_type[0]);

		if(request_type[0]=='R'){
			// if found in local cache do nothing
			if(L1_cache->read_request(addr)){
				printf("L1 READ HIT");
			}else{
				// search in directory
				int position=search_directory(dir,addr);
				if(position!=-1){
					printf("WE got it in directory\n");
					printf("position: %d\n",position);
					// now find out in which cache the block is there
					if(dir->D[position].second[processor_count]==1){
						dir->D[position].second[processor_count]=0;
					}
					dir->D[position].second[pro_index]=1;
				}else{
					// directory miss Got it from main memory
					// lets assume that main memory always contains the block
					directory_modification(dir,addr,pro_index,processor_count,request_type);
				}
				L1_cache->cache_update(addr);
			}
			return {};
		}else if(request_type[0]=='W'){
			// if write request
			// find if the block is in directory
			int position=search_directory(dir,addr);
			// dbg(position);
			vector<int> caches;
			if(position!=-1){
				// int pro_index=0;
				for(int itr=0;itr<dir->D[position].second.size()-1;itr+=1){
					if(dir->D[position].second[itr]==1){
						caches.push_back(itr);
					}
				}
			}
			// dbg(position);
			L1_cache->cache_update(addr);
			// directory miss
			// dbg(position);
			directory_modification(dir,addr,pro_index,processor_count,request_type);
			return caches;
		}else{
			// some valid test case checking
			printf("INVALID REQUEST-1");return {};
		}
		return {};
	}

	void cache_modification(directory *dir,Processor *another_processor,address *addr,int pro_index,int processor_count){
		// modifies the caches
		int position=this->search_directory(dir,addr);
		dir->D[position].second[pro_index]=0;
		// if(this->dir->D[position].second[processor_count])

		another_processor->L1_cache->delete_block(addr);
	}

	void show_processor(directory *dir){

		cout<<"CACHE: ";
		L1_cache->show_cache();cout<<endl;
		cout<<"DIRECTORY: ";
		dir->show_directory();
	}
};