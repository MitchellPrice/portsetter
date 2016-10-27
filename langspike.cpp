#include <string>
#include <iostream>
using namespace std;

//TODO:  Put enum in main

enum {
   HELLO, 
   DO_SOMETHING,
   INCORRECT_FLAG,
   GOODBYE 
};

// en
string en[] = {
   "Hello",
   "Please do something",
   "incorrect flag",
   "Goodbye"
};

// es
string es[] = {
   "Hola",
   "Favor de hacer algo",
   "indicador incorrecto",
   "Chao"
};

string* msg = en; //defaults to English

//TODO:  Right here I need to determine which language is used
    //Member variable that holds which language - msg needs to be a memeber
        //Does it have to be a pointer? - to change the value in a method?

//demo of a function that can print out messages in any language WITHOUT BEING AWARE OF THE LANGUAGE BEING USED
void someProcess() {
   cout << msg[HELLO] << endl;
   cout << msg[TOO_MANY_PARAMETERS] << endl;
   cout << msg[GOODBYE] << endl;
   cout << "-----------" << endl;
}

int main(int argc, char *args[]) {
string locale;

//TODO: get the env var 
    //Check if they are empty - if empty or not found move to the next one
        //get the locale value from env vars in this order
        //1. LANGUAGE
        //2. LC_ALL
        //3. LC_MESSAGES, (LC_TIME, ...)
        //4. LANG
            //If it is one of these values move to the next one
            //ignore these values 
            //null
            //""
            //"C"
            //"C.UTF-8"

string language;
//if no locale value, default the language to English

//RegEx is not needed - we can use any string manipulation 
    // error out on invalid SYNTAX, don't worry about a valid VALUE e.g. 
    // es is good because country and format are optional
    // en_FR is good because format is optional
    // en.UTF-8 is good because country is optional
    // en_NZ.UTF-8 is good
    // zz_ZZ.UTF-8 is good syntax, the fact that there's no language zz or country ZZ is not important. They could appear after your program is released.
        //Examples of Errors
        // e1 is bad syntax, no number
        // english is bad syntax, only 2 letter language
        // en_USA is bad syntax, only 2 letter country
        // EN is bad syntax, only lowercase language
        // en_us is bad syntax, only uppercase country
        //parse out the language without the country or format - just grab "en" or "es"

//vector msg;
//read the appropriate messages from the right language file into Vector msg
// The following is untried. Consider it psuedo code.
// ifstream in("portsetter_" + lang + ".txt");
// string line;
// while (!in.eof()) {
// in >> line;
// msg.push_back(line);
// }

//Proof Of Concept (POC) working code
 someProcess();

 msg = es;
 someProcess();
 
 msg = en;
 someProcess();
}

//some differences between POC and the actual requirements
//1. msg is a vector instead of an array
//2. no someProcess(). Everywhere you have cout << "some literal string", you'll change to cout << msg[LITERAL_STRING]
//3. everywhere except version(), e.g. "1.0.1a" is not translated
//4. msg vector will come from a messages file, not hardcoded like in POC
//5. usage() and about() don't need to be put into msg vector. They will just print out the appropriate file.
//6. POC has both Spanish and English loaded. You will only load 1 language.
//7. if a language, say German, is requested, and you don't have German files, print error message about missing the user's language, and then continue as normal in English.
//  You can use this format or one of your own choosing. "Missing de translation files. Using English." (de is German)
//  Continue as normal in English means setport -p 837 would print "Listening on port 837" and return 0;

//sudo locale-gen "es_MX.UTF-8"