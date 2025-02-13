/// assign_4_1_floatAvg.cpp
/// Dallas Hart
/// Copyright 1/3/2020
/// prints the average of 10 floats

#include <iostream>

using namespace std;

float in(string inMessage, string failMessage);

int main()
{
    cout << "Please input 10 floating point numbers and I will return the average" << endl;
    float* arr = new float [10];/// declare array
    float total = 0;

    for (int i=0; i<10; i++) /// just input the numbers
    {
        arr[i] = in ("Please input a floating point number", "INPUT A FLOAT");
    }

    cout << "You entered these floating point numbers:" << endl;
    for (int i= 0; i<10; i++) /// list the numbers and total them
    {
        total += arr[i];
        cout << arr[i] << ", ";
    }
    cout << endl << "The average of these floating point numbers is:" << endl;
    cout << total/10.0; /// average
    delete[] arr; /// delete array
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

/*
TEST CASES
Please input 10 floating point numbers and I will return the average
Please input a floating point number
6.9
Please input a floating point number
5.8
Please input a floating point number
2.7
Please input a floating point number
0.1
Please input a floating point number
11.4
Please input a floating point number
.6
Please input a floating point number
9.9
Please input a floating point number
7.2
Please input a floating point number
3.3
Please input a floating point number
26
You entered these floating point numbers:
6.9, 5.8, 2.7, 0.1, 11.4, 0.6, 9.9, 7.2, 3.3, 26,
The average of these floating point numbers is:
7.39
Process returned 0 (0x0)   execution time : 46.668 s
Press any key to continue.

*/
