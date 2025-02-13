/// assign_4_2_charRev.cpp
/// Dallas Hart
/// Copyright 1/3/2020
/// prints the reverse of 10 char


#include <iostream>
#include <iomanip>

using namespace std;

char in(string inMessage, string failMessage);

int main()
{
    cout << "Please input 10 characters, and I will print them in reverse in a table" << endl;
    char* arr = new char [10]; /// declare array

    for (int i=0; i<10; i++)  /// take in input
    {
        arr[i] = in ("Please input a character", "Input a character");
    }

    cout << "In#|Reverse\n---+-------" << endl;/// make table
    for (int i=0; i<10; i++)
    {
        cout << setw(2) << i+1 << setw(3) << "| ";
        cout << arr[9-i] << endl;
    }
    delete[] arr;/// clean up array
    return 0;
}

char in(string inMessage, string failMessage)
{
    char input;
    cout << inMessage << endl;
    while(true)
    {
        cin >> input; // input for number of second
        if (cin.fail())// dummy-proofing
        {
            cout << failMessage << endl;
            cin.clear(); //clear stream
            cin.ignore(80, '\n'); //clear 80 characters until a \n is reached.
        }
        else
        {
            return input; //exit the loop if everything is ok
        }
    }
}

/*
TEST CASES

Please input 10 characters, and I will print them in reverse in a table
Please input a character

ds
Please input a character
Please input a character
df
Please input a character
Please input a character
t
Please input a character
jh
Please input a character
Please input a character

f
Please input a character
d
Please input a character
e
In#|Reverse
---+-------
 1 | e
 2 | d
 3 | f
 4 | h
 5 | j
 6 | t
 7 | f
 8 | d
 9 | s
10 | d

Process returned 0 (0x0)   execution time : 6.471 s
Press any key to continue.


*/
