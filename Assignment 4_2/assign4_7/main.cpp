/// assign_4_7_fCharSen.cpp
/// Dallas Hart
/// Copyright 1/3/2020
/// prints the first character of each word in a sentance

#include <iostream>

using namespace std;

int main()
{
    /// input sentance
    cout << "Please input a sentance" << endl;
    string input;
    getline(cin,input);
    bool spaceFlag = true;
    /// output
    for (int i=0; i<input.size(); i++)
    {
        /// if space ready for next char
        if (input[i] == ' ')
        {
            spaceFlag=true;
        }
        else if (spaceFlag)/// if last character was a space that means this one is the first char
        {
            cout << input[i];
            spaceFlag=false;
        }
    }
    return 0;
}

/*
TEST CASES

Please input a sentance
hello ther hoe are you doing
hthayd
Process returned 0 (0x0)   execution time : 13.579 s
Press any key to continue.

*/
