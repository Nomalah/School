/// assign_1_12_timeConversion.cpp
/// Dallas Hart
/// Copyright 10/7/2019
/// Allows the conversion of integer number of seconds to years, weeks, days, hours, minutes and seconds

#include <iostream>
#include <math.h>
#include <string>

using namespace std;

int main()
{
    int units [6]; //Storage of each kind of Variable
    int divisors [5] = {60,60,24,7,52}; // the required divisor to convert to the next unit.
    string names [6] = {"second(s)", "minute(s)", "hour(s)", "day(s)", "week(s)", "year(s)"}; // unit names


    cout << "Please input a integer number of seconds and I will convert it to years, weeks, days, hours, minutes and seconds: ";

    //Idiot Proofing
    while (true)
    {
        cin >> units [0]; // input for number of second
        if (cin.fail())// dummy-proofing
        {
            cout << "Enter a Number!" << endl;
            cin.clear(); //clear stream
            cin.ignore(80, '\n'); //clear 80 characters until a \n is reached.
        }
        else
        {
            break; //exit the loop if everything is ok
        }
    }

    cout << units [0] << " seconds is..." << endl; // beginning of the output

    // Calculates each of the units
    for (int i=0; i<6; i++)
    {
        units[i+1]=floor(units[i]/divisors[i]); // calculates the next unit
        units[i]= units[i]%divisors[i]; // calculates the remaining units
    }
    // print the units largest to smallest
    for (int i=5; i>=0; i--)
    {
        if (units[i] !=0) // only print the unit if they are over 0
        {
            cout << units[i] << " " << names[i] << endl;
        }
    }
    return 0;
}

/*
Test Cases

Please input a integer number of seconds and I will convert it to years, weeks, days, hours, minutes and seconds: f
Enter a Number!
f
Enter a Number!
35012
35012 seconds is...
9 hour(s)
43 minute(s)
32 second(s)

Process returned 0 (0x0)   execution time : 14.785 s
Press any key to continue.


*/
