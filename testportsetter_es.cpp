#include "iostream"
#include "string"
#include <cstring>

#ifndef PROGRAMTEST_H
#define PROGRAMTEST_H

using namespace std;

//FUNCTION DECLARATIONS
int main(int argc, char* args[]);
int test(const string& commandLine, const string& expectedCompareFile);

//main
int main(int argc, char* args[]) {
	string testString = "";

	//PASSED HELP TESTS
	testString = "setport";
	test(testString.c_str(), "testhelp_es.txt");

	testString = "setport -h";
	test(testString.c_str(), "testhelp_es.txt");

	testString = "setport --help";
	test(testString.c_str(),"testhelp_es.txt");

	testString = "setport -?";
	test(testString.c_str(),"testhelp_es.txt");


//TESTS
	//Successes	-e		//Take time to test this
	
	//VERSION TESTS
	testString = "setport -v";
	test(testString.c_str(),"testversion_es.txt");

	testString = "setport --version";
	test(testString.c_str(),"testversion_es.txt");	
	
	
	//ABOUT TESTS
	testString = "setport -!";
	test(testString.c_str(),"testabout_es.txt");

	testString = "setport --about";
	test(testString.c_str(),"testabout_es.txt");


	//PASSED TESTS
	testString = "setport -p 4040";
	test(testString.c_str(), "success_es.txt");

	testString = "setport --port 4040";
	test(testString.c_str(), "success_es.txt");

	//NEGATIVE TESTS
	testString = "setport help";
	test(testString.c_str(), "fail2_es.txt");

	testString = "setport -help";
	test(testString.c_str(), "fail2_es.txt");

	testString = "setport --h";
	test(testString.c_str(), "fail2_es.txt");

	testString = "setport -h --help";
	test(testString.c_str(), "fail2_es.txt");

	testString = "setport -hs";
	test(testString.c_str(), "fail2_es.txt");

	testString = "setport -p --port 9";
	test(testString.c_str(), "fail1_es.txt");

	testString = "setport -p 77 33";
	test(testString.c_str(), "fail1_es.txt");

	testString = "setport -p -21";
	test(testString.c_str(), "fail3_es.txt");

	testString = "setport -p 0";
	test(testString.c_str(), "fail3_es.txt");

	testString = "setport --port";
	test(testString.c_str(), "fail2_es.txt");

	testString = "setport -p 90642";
	test(testString.c_str(), "fail3_es.txt");

	testString = "setport -x 45321";
	test(testString.c_str(), "fail2_es.txt");

	testString = "setport -P 714";
	test(testString.c_str(), "fail2_es.txt");
	
}


//test
int test(const string& commandLine, const string& expectedCompareFile) {
	bool bPass = true;
	printf("TESTING: %s \n", commandLine.c_str());

	string cmd = commandLine + " > temp.txt";

	//Running the command
	system(cmd.c_str());

	FILE *fp = fopen("./temp.txt", "r");
	if (fp != nullptr) {

		FILE *fpExpected = fopen(expectedCompareFile.c_str(), "r");
		if (fpExpected != nullptr) {

			char tmpLine[1024];
			char expectedLine[1024];
	
			while (fgets ( tmpLine, 1024, fp ) != nullptr){
				fgets(expectedLine, 1024, fpExpected);
				#ifdef debug
				printf("expectedLine is: %s \n", expectedLine);
				printf("tmpLine line is: %s \n", tmpLine);
				#endif
				// compare the two
				if (strcmp(expectedLine, tmpLine) != 0){
					printf("The files are different \n");
					bPass = false;
					break;
				}
			}
			fclose(fpExpected);
		} 
		else {
			printf("failed opening %s", expectedCompareFile.c_str());
		}
	//Close the file
	fclose(fp);	
	} 
	else {
		printf("failed opening ./temp.txt");
	}

	//Check if the error returned is the error received 
	if (bPass) {
		printf("Test Passed \n \n");
		return 0;
	}
	else {
		printf("Test Failed \n \n");
		return 1;
	}
}
#endif