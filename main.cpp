// TESTING MY CODE
#include "test_case.h"
using namespace std;

int main()
{
	// Processor p1,p2,p3;


	int process_count;
	cout<<"Enter the process count:";
	cin>>process_count;

	int test_case_number;
	cout<<"Enter the test case number:";
	cin>>test_case_number;
	vector<Processor *> core;
	for(int i=0;i<process_count;i++){
		Processor *p=new Processor();
		core.push_back(p);
	}
	// address *r1=new address();
	// r1->location=10;

	directory *d1=new directory();
	// vector<int> x=p1.L1_request("READ",r1,d1,0,3);
	// p1.show_processor(d1);
	// vector<int> y=p2.L1_request("WRITE",r1,d1,1,3);
	// // p2.cache_modification(d1,p1,r1,0,3);
	// // cout<<x<<y<<endl;

	// // printf("%d",x.size());
	// // printf("%d",y.size());
	// p2.show_processor(d1);
	// address *r2=new address();r2->location=100;
	// vector<int> z=p3.L1_request("READ",r2,d1,2,3);
	// p3.show_processor(d1);

	// y=p2.L1_request("READ",r2,d1,1,3);
	// p2.show_processor(d1);

	test_case_generation *test=new test_case_generation(process_count);
// 
	test->generate_test_case(test_case_number);
// 
	test->execute_test(core,d1);
	// for(int i=0;i<10;i++){
	// 	address *r1=new address();
	// 	r1->location=10+i;

	// 	printf("%d ",r1->location);
	// }
}