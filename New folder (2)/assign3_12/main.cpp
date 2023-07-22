/// assign_3_12_series.cpp
/// Dallas Hart
/// 11/25/2019
/// This program calcuates an infinite series

#include <iostream>

using namespace std;

float in(string inMessage, string failMessage);
double exp(double c, int termNum);

int main()
{
    ///input
    double multiplyVal=in("enter the start value:","enter a number:");
    int numOfTerms=(int)in("enter the number of time periods:","enter a number:");
    cout << "infinite series ~ " << exp(multiplyVal,numOfTerms); /// add the interest
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

double exp(double c, int termNum)
{
    double total=0;
    for (int i = 0; i<termNum; i++)
    {
        double temp=1;/// exponent is important
        for (int x = 0; x<i; x++)
        {
            temp*=c;
        }
        double factorial=1;/// factorial is important
        for (int x = 1; x<=i; x++)
        {
            factorial*=x;
        }
        total+=temp/factorial;
    }
    return total;
}

/*
test cases

enter the start value:
5
enter the number of time periods:
50
new value = 148.413
Process returned 0 (0x0)   execution time : 8.489 s
Press any key to continue.


*/
