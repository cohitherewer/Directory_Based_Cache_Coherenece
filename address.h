#include<bits/stdc++.h>

// define for basic debug
#define dbg(x) cout<<#x<<" = "<<x<<endl
using namespace std;
/*
	Basic address class 
	Processors will request this addresses
*/
class address{
public:
	// public: location
	// parameters: None
	// can be set later
	int location;
	address(){
		location=0;
	}
};