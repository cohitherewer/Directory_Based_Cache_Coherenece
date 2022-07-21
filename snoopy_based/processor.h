#include "local_cache.h"

#define CACHE_CAPACITY 1001

class processor{
private:
	local_cache *l1_cache;
public:
	processor(){
		l1_cache=new local_cache(CACHE_CAPACITY);
	}
	void change_address_state(address *addr,char state){
		this->l1_cache->change_addr_state(addr,state);
	}
	void get_current_state(){
		l1_cache->get_cache_content();
		cout<<endl;
	}
	void get_request(string request_type,address *addr,vector<processor *> processes,int index){
		if(request_type[0]=='R'){
			if(l1_cache->if_contains(addr)){
				printf("READ HIT");
			}else{
				l1_cache->modify_cache(addr);
				printf("READ MISS");
			}
			for(int i=0;i<processes.size();++i){
				if(processes[i]->l1_cache->if_contains(addr)){
					processes[i]->change_address_state(addr,'S');
				}
			}
		}else if(request_type[0]=='W'){
			printf("READEX");
			for(int i=0;i<processes.size();++i){
				processes[i]->change_address_state(addr,'I');
			}

			processes[index]->change_address_state(addr,'M');
			for(int i=0;i<processes.size();i++){

			}
		}else{
			printf("Invalid Request");
		}
	}
};