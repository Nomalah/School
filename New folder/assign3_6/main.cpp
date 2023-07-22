/// assign_3_6_reverseOther.cpp
/// Dallas Hart
/// 11/25/2019
/// This program reverse back every other character to the screen.

#include <iostream>
#include <string>

using namespace std;

string in(string inMessage, string failMessage);
void reverseOther(string word);

int main()
{
    /// enter full string
    string inWord=in("enter a string","enter a string");
    reverseOther(inWord); /// call function
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

void reverseOther(string word)
{
    /// odd length strings vs even length
    if (word.length()%2==1)
    {
        for(int i=0; i<word.length()-1; i+=2)
        {
            cout << word.at(i+1) << word.at(i);
        }
        cout << word.at(word.length()-1); /// avoid crashing
    }
    else
    {
        for(int i=0; i<word.length(); i+=2)
        {
            cout << word.at(i+1) << word.at(i);
        }
    }
}

/*
test cases

enter a string
hello there
ehll ohtree
Process returned 0 (0x0)   execution time : 3.440 s
Press any key to continue.

*/
