#include<bits/stdc++.h>
#define dbg(x) cout<<#x<<" = "<<x<<endl
using namespace std;
/*
	Basic address structure 
	Processors will request this addresses
*/
class address{
public:
	int location;
	address(){
		location=0;
	}
};