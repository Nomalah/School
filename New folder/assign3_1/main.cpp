/// assign_3_1_daysmonth.cpp
/// Dallas Hart
/// 11/25/2019
/// This program prints the number of days in a certain month

#include <iostream>

using namespace std;

int in(string inMessage, string failMessage);
int daysMonth(int monthNum);

int main()
{
    ///get input
    int month=in("enter a month number:","enter a number from 1 to 12:");

    /// run the function
    daysMonth(month);
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
int daysMonth(int monthNum)
{
    /// look up table
    int days [12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    /// output
    cout << "month " << monthNum << " has " << days[monthNum-1] << " days";
}

/*
test cases

enter a month number:
5
month 5 has 31 days
Process returned 0 (0x0)   execution time : 2.610 s
Press any key to continue.

*/
