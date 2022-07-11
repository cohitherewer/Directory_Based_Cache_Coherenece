// include the address.h
#include "address.h"
using namespace std;

// define directory capacity
#define DIRECTORY_CAPACITY 1000

/*
DIRECTORY CLASS
*/
class directory{
	// no private member for direct accessing
public:
	int capacity;
	// the data strcture is address-> corresponding block(can be boolean blocks)
	// blocks will be of size: # of processor +1
	// 1 for exclusize bit

	vector<pair<address *,vector<int>>> D;
	
	// Default constructor
	// setting the constructor 
	directory(){
		this->capacity=DIRECTORY_CAPACITY;
	}

	int is_full(){
		// check if the directory is full
		// true if full
		return this->capacity<=this->D.size();
	}

	void show_directory(){
		// show the directory when necessary
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