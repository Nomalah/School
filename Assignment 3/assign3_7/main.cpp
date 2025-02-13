/// assign_3_7_square.cpp
/// Dallas Hart
/// 11/25/2019
/// This program will make a square from a string

#include <iostream>
#include <string>

using namespace std;

string in(string inMessage, string failMessage);
void square(string word);

int main()
{
    /// input full string
    string inWord=in("enter a string","enter a string");
    square(inWord); /// call function
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

void square(string word)
{
    ///Print Word normally
    for(int i=0; i<word.length(); i++)
    {
        cout << word.at(i);
    }
    cout << endl;

    /// print middle words
    for(int i=1; i<word.length()-1; i++)
    {
        cout << word.at(i);
        for(int c=0; c<word.length()-2; c++)/// number of spaces = length - front and back (2)
        {
            cout << " ";
        }
        cout << word.at(word.length()-i-1)<<endl;
    }

   ///Print word backwards
    for(int i=word.length()-1; i>=0; i--)
    {
        cout << word.at(i);
    }

}

/*
test cases

enter a string
hello there
hello there
e         r
l         e
l         h
o         t

t         o
h         l
e         l
r         e
ereht olleh
Process returned 0 (0x0)   execution time : 3.605 s
Press any key to continue.


*/
