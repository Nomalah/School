/// assign_3_11_intrest.cpp
/// Dallas Hart
/// 11/25/2019
/// This program finds the present value of an investment

#include <iostream>

using namespace std;

float in(string inMessage, string failMessage);
float intrest(float start, float rate, int time);

int main()
{
    ///input
    float startValue=(float)in("enter the start value:","enter a number:");
    float rate=(float)in("enter the rate:","enter a number:");
    int timePeriod=in("enter the number of time periods:","enter a number:");
    cout << "new value = " << intrest(startValue,rate,timePeriod); /// add the interest
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

float intrest(float start, float rate, int time)
{
    float temp = 1;
    for (int i = 0; i<time; i++){
        temp*=1+rate;
    }
    return temp*start;
}

/*
test cases

enter the start value:
10
enter the rate:
0.5
enter the number of time periods:
3
new value = 33.75
Process returned 0 (0x0)   execution time : 18.142 s
Press any key to continue.

*/
