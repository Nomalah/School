/// assign_3_9_binary.cpp
/// Dallas Hart
/// 11/25/2019
/// This program converts decimal to binary

#include <iostream>

using namespace std;

int in(string inMessage, string failMessage);
void convertBinary(int num);

int main()
{
    ///input
    int inNum=in("enter a number:","enter a number:");
    convertBinary(inNum); /// convet
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

void convertBinary(int num)
{
    int tempNum=num;
    int maxBaseTwo=1;
    while (maxBaseTwo<=num) /// find out the max place counter
    {
        maxBaseTwo*=2;
    }

    /// count down from the max only changing to a one if space left in num.
    for (int i=maxBaseTwo/2; i>=1; i/=2)
    {
        if (tempNum-i>=0)
        {
            tempNum-=i;
            cout << "1";
        }
        else
        {
            cout <<"0";
        }
    }
}

/*
test cases

enter a number:
1783
11011110111
Process returned 0 (0x0)   execution time : 10.566 s
Press any key to continue.

*/
