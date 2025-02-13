/// assign_2_13_fare.cpp
/// Dallas Hart
/// Copyright 10/31/2019
/// Does the fare sequence

#include <iostream>

using namespace std;

int main()
{
    int input;
    cout << "Please input the number of terms you would like in the fare sequence: ";
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
    long double fn, f3=0, f2=1, f1=1;
    for (int i=1;i<=input;i++){
        fn=f1+f2-f3/2;///fare calculation for nect term
        cout << "term #" << i << " = " << fn << endl;
        f3=f2;/// shifts the number
        f2=f1;
        f1=fn;
    }
    return 0;
}
/*
test cases

Please input the number of terms you would like in the fare sequence: 8
term #1 = 2
term #2 = 2.5
term #3 = 4
term #4 = 5.5
term #5 = 8.25
term #6 = 11.75
term #7 = 17.25
term #8 = 24.875

Process returned 0 (0x0)   execution time : 13.656 s
Press any key to continue.
*/
