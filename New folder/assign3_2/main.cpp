/// assign_3_2_printAsterisk.cpp
/// Dallas Hart
/// 11/25/2019
/// This program prints the number of asterisks from the user

#include <iostream>

using namespace std;

int in(string inMessage, string failMessage);
int printAsterisk(int printNum);

int main()
{
    /// input
    int numOfAsterisk=in("enter a number:","enter a number:");

    /// run function
    printAsterisk(numOfAsterisk);
    return 0;
}

int in(string inMessage, string failMessage)
{
    int input;
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

int printAsterisk(int printNum)
{
    /// print the number of askterisks
    for(int i=0;i<printNum;i++){
        cout << "*";
    }
}

/*
test cases

enter a number:
5
*****
Process returned 0 (0x0)   execution time : 7.216 s
Press any key to continue.

*/
