// include necssary libraries
#include "processor.h"
#include<iterator>
#include<fstream>

using namespace std;
// specify blocks numbers
#define BLOCK_NUMBERS 100

class test_case_generation{
private:
	// priate members
	vector<string> operation;
	int block_number;
	int processor_count;

	string generate_single_test(){
		/*
		Generate single test cases
		format READ/WRITE BLOCK_NO PROCESSOR_NUMBER
		*/
		int op=rand() %2;
		int bn=rand() % block_number;

		int pc=rand() % processor_count;

		// tuple<string,int,int> test_case(operation[op],bn,pc);
		return operation[op]+ " "+to_string(bn)+" "+to_string(pc);
	}


	vector<string> string_split(string s){
		// split string
		// utility function to split the string in tree parts while reading from files
		vector<string> words;string T="";
		for(int i=0;i<(int)s.size();i++){
			if(s[i]!=' '){
				T+=s[i];
			}else{
				words.push_back(T);T="";
			}
		}
		if(T!="")words.push_back(T);
		return words;
	}
public:
	test_case_generation()=delete;
	test_case_generation(int processor_count){
		/*
			Parameterized constructor
		*/
		this->processor_count=processor_count;
		this->block_number=BLOCK_NUMBERS;
		operation.push_back("READ");operation.push_back("WRITE");
	}

	void generate_test_case(int test_case_count){
		// Parameter : test_case_count
		vector<string> test_cases;
		for(int cnt=1;cnt<=test_case_count;cnt+=1){
			srand(cnt);
			string cases=generate_single_test();
			test_cases.push_back(cases);
		}
		// store them in test_cases.txt in file.
		ofstream output_file("test_cases.txt");
		ostream_iterator<string> output_iterator(output_file,"\n");
		copy(test_cases.begin(),test_cases.end(),output_iterator);
	}

	void execute_test(vector<processor *> process){
		// execute the tests
		fstream file;
		file.open("test_cases.txt",ios::in);
		if(file.is_open()){
			string cases="";
			while(getline(file,cases)){
				vector<string> instruction=string_split(cases);

				int core=stoi(instruction[2]);
				int bn=stoi(instruction[1]);
				bn=10;

				address *r1=new address();
				r1->location=bn;
				
				string op=instruction[0]+'\0';


				process[core]->get_request(op,r1,process,core);

				for(int i=0;i<process.size();i++){
					dbg(i);
					process[i]->get_current_state();
				}
				cout<<endl;

			}
		}
		file.close();
	}
};