#include "address.h"
using namespace std;

#define DIRECTORY_CAPACITY 1000

class directory{
public:
	int capacity;
	vector<pair<address *,vector<int>>> D;
	directory(){
		this->capacity=DIRECTORY_CAPACITY;
	}
	int is_full(){
		return this->capacity<=this->D.size();
	}

	void show_directory(){
		printf("Address: [CACHES]\n");
		for(auto it:D){
			printf("%d ",it.first->location);
			printf("[");
			for(auto i:it.second){
				printf(" %d ",i);
			}
			printf("]\n");
		}
	}
};