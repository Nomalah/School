/// assign_3_3_power.cpp
/// Dallas Hart
/// 11/25/2019
/// This program calculates powers

#include <iostream>

using namespace std;

float in(string inMessage, string failMessage);
float power(float base, int exponent);

int main()
{
    /// input base and exponent using only one function
    float basenum=in("enter the exponent base:","enter the exponent base:");
    int expnum=(int)in("enter the exponent exponent:","enter the exponent exponent:");

    /// output
    cout << basenum << " to the power of " << expnum << " is " << power(basenum,expnum);
    return 0;
}

float in(string inMessage, string failMessage)
{
    float input;
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

float power(float base, int exponent)
{
    /// multiply itself exponent number of times
    int endNum=1;
    for (int i=0; i<exponent; i++)/// iterate
    {
        endNum*=base;
    }
    return endNum;
}

/*

test cases
enter the exponent base:
5
enter the exponent exponent:
5
5 to the power of 5 is 3125
Process returned 0 (0x0)   execution time : 3.061 s
Press any key to continue.

*/
