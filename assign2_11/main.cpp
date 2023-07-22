/// assign_2_11_factor.cpp
/// Dallas Hart
/// Copyright 10/31/2019
/// finds the factors of a number

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int input;
    cout << "Please input the number you would like the factors of:" << endl;
    //Idiot Proofing
    while (true)
    {
        cin >> input; // input for number of second
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
    cout << "The Factors of " << input << " are... ";
    for (int i=1; i<=floor(sqrt(input)); i++)/// on nessisary to go to the sqrt of the number
    {
        if (input % i == 0)/// checks if the number is a factor
        {
            cout << i << ", " << input/i << ", ";/// prints the number and its counterpart.
        }
    }
    return 0;
}

/*
test cases
Please input the number you would like the factors of:
10
The Factors of 10 are... 1, 10, 2, 5,
Process returned 0 (0x0)   execution time : 4.533 s
Press any key to continue.
*/
