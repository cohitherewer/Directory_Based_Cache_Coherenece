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
	vector<processor *> core;
	for(int i=0;i<process_count;i++){
		processor *p=new processor();
		core.push_back(p);
	}
	
	test_case_generation *test=new test_case_generation(process_count);
// 
	test->generate_test_case(test_case_number);
// 
	test->execute_test(core);
}