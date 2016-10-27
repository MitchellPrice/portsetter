#include "iostream"
#include "string"
#include <cstring>

#ifndef PROGRAMTEST_H
#define PROGRAMTEST_H

using namespace std;

//FUNCTION DECLARATIONS
int main(int argc, char* args[]);
int test(const string& commandLine, const string& expectedCompareFile);
void checkLanguage();
void checkFormatting(string envString, string whichEnv);

//MEMBER VARIABLES
//The language defaults to English
string firstTwo = "en";
char* langEnv;

//main
int main(int argc, char* args[]) {
	string testString = "";
	checkLanguage();


	//PASSED HELP TESTS
	testString = "setport";
	test(testString.c_str(), "testhelp_" + firstTwo + ".txt");
	
	testString = "setport -h";
	test(testString.c_str(), "testhelp_" + firstTwo + ".txt");

	testString = "setport --help";
	test(testString.c_str(),"testhelp_" + firstTwo + ".txt");

	testString = "setport -?";
	test(testString.c_str(),"testhelp_" + firstTwo + ".txt");


	//VERSION TESTS
	testString = "setport -v";
	test(testString.c_str(),"testversion_" + firstTwo + ".txt");

	testString = "setport --version";
	test(testString.c_str(),"testversion_" + firstTwo + ".txt");	
	
	
	//ABOUT TESTS
	testString = "setport -!";
	test(testString.c_str(),"testabout_" + firstTwo + ".txt");

	testString = "setport --about";
	test(testString.c_str(),"testabout_" + firstTwo + ".txt");


	//PASSED TESTS
	testString = "setport -p 4040";
	test(testString.c_str(), "success_" + firstTwo + ".txt");

	testString = "setport --port 4040";
	test(testString.c_str(), "success_" + firstTwo + ".txt");


	//NEGATIVE TESTS
	testString = "setport help";
	test(testString.c_str(), "fail2_" + firstTwo + ".txt");

	testString = "setport -help";
	test(testString.c_str(), "fail2_" + firstTwo + ".txt");

	testString = "setport --h";
	test(testString.c_str(), "fail2_" + firstTwo + ".txt");

	testString = "setport -h --help";
	test(testString.c_str(), "fail2_" + firstTwo + ".txt");

	testString = "setport -hs";
	test(testString.c_str(), "fail2_" + firstTwo + ".txt");

	testString = "setport -p --port 9";
	test(testString.c_str(), "fail1_" + firstTwo + ".txt");

	testString = "setport -p 77 33";
	test(testString.c_str(), "fail1_" + firstTwo + ".txt");

	testString = "setport -p -21";
	test(testString.c_str(), "fail3_" + firstTwo + ".txt");

	testString = "setport -p 0";
	test(testString.c_str(), "fail3_" + firstTwo + ".txt");

	testString = "setport --port";
	test(testString.c_str(), "fail2_" + firstTwo + ".txt");

	testString = "setport -p 90642";
	test(testString.c_str(), "fail3_" + firstTwo + ".txt");

	testString = "setport -x 45321";
	test(testString.c_str(), "fail2_" + firstTwo + ".txt");

	testString = "setport -P 714";
	test(testString.c_str(), "fail2_" + firstTwo + ".txt");
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

//----------------------------checkLanguage and checkFormatting-------------------------------------------
//checkLanguage
void checkLanguage(){
	//LANGUAGE
	langEnv = getenv("LANGUAGE");
	if (langEnv == nullptr || strcmp(langEnv, "") == 0 || strcmp(langEnv, "C") == 0 || strcmp(langEnv, "C.UTF-8") == 0){
		//LC_ALL
		langEnv = getenv("LC_ALL");
		if (langEnv == nullptr || strcmp(langEnv, "") == 0 || strcmp(langEnv, "C") == 0 || strcmp(langEnv, "C.UTF-8") == 0){
			//LC_MESSAGES
			langEnv = getenv("LC_MESSAGES");
			if (langEnv == nullptr || strcmp(langEnv, "") == 0 || strcmp(langEnv, "C") == 0 || strcmp(langEnv, "C.UTF-8") == 0){
				//LANG
				langEnv = getenv("LANG");
					if (langEnv == nullptr || strcmp(langEnv, "") == 0 || strcmp(langEnv, "C") == 0 || strcmp(langEnv, "C.UTF-8") == 0){
					//none of the environment variables are set, default to english	
					firstTwo = "en";
				} else {
					checkFormatting(langEnv, "LANG");	//LANG		
				}	
			} else {
				checkFormatting(langEnv, "LC_MESSAGES");	//LC_MESSAGES
			}
		} else {
			checkFormatting(langEnv, "LC_ALL");		//LC_ALL
		}
	} else {
		checkFormatting(langEnv, "LANGUAGE");	//LANGUAGE
	}	
}

//checkFormatting
void checkFormatting(string envString, string whichEnv){
	bool formatIsCorrect = false;
	string tempString;
	//ex: es
	if(envString.size() == 2){
		if (islower(envString[0]) && islower(envString[1])){
			formatIsCorrect = true;
			firstTwo = envString;
		}
	}
	//ex: es_MX
	if(envString.size() == 5){
		if (islower(envString[0]) && islower(envString[1])){
			if(envString[2] =='_'){
				if(isupper(envString[3]) && isupper(envString[4])){
					formatIsCorrect = true;
					firstTwo = envString.substr(0, 2);
				}
			}
		}
	}
	//ex: es.UTF-8
	if(envString.size() == 8){
		if (islower(envString[0]) && islower(envString[1])){
			tempString = envString.substr(2, 6);
			if(tempString.compare(".UTF-8") ==0){
				formatIsCorrect = true;
				firstTwo = envString.substr(0, 2);
			}
		}
	}
	//ex: es_MX.UTF-8
	if(envString.size() == 11){
		if (islower(envString[0]) && islower(envString[1])){
			if(envString[2] == '_'){
				if(isupper(envString[3]) && isupper(envString[4])){
					tempString = envString.substr(5, 6);
					if(tempString.compare(".UTF-8") ==0){
						formatIsCorrect = true;
						firstTwo = envString.substr(0, 2);
					}
				}
			}
		}
	}
	//If the formatting is incorrect
	if (formatIsCorrect == false){
		printf("Bad language specification in environment variable %s=%s. Using English. \n", whichEnv.c_str(), envString.c_str());
		firstTwo = "en";
	}
}
#endif