/// assign_3_5_printOther.cpp
/// Dallas Hart
/// 11/25/2019
/// This program prints back every other character to the screen.

#include <iostream>
#include <string>
using namespace std;

string in(string inMessage, string failMessage);
void printOther(string word);

int main()
{
    /// input full string
    string inWord=in("enter a string","enter a string");
    printOther(inWord);
    return 0;
}

string in(string inMessage, string failMessage)
{
    string input;
    cout << inMessage << endl;
    while(true)
    {
        getline(cin,input); // input for number of
        if (cin.fail())// dummy-proofing
        {
            cout << failMessage << endl;
            cin.clear(); //clear stream
            cin.ignore(256, '\n'); //clear 80 characters until a \n is reached.
        }
        else
        {
            return input; //exit the loop if everything is ok
        }
    }
}

void printOther(string word)
{
    /// just print every other letter
    for(int i=0;i<word.length();i+=2){
        cout << word.at(i) <<" ";
    }
}

/*
test cases

enter a string
hello there
h l o t e e
Process returned 0 (0x0)   execution time : 3.422 s
Press any key to continue.

*/
