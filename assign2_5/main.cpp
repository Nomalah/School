/// assign_2_5_d-q.cpp
/// Dallas Hart
/// Copyright 10/31/2019
/// cooses smalled largest and average of numbers
#include <iostream>

using namespace std;

int main()
{
    long long int input = 0, total = 0, small=0, big=0, counter = 0;
    do
    {
        cout << "Please input a integer" << endl;
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
        if (input == 0)
        {
            break;
        }
        counter++;
        total += input;
        if (input<small)/// update smallest number
        {
            small = input;
        }
        if (input>big) /// update largest number
        {
            big = input;
        }
    }
    while (input!=0);

    cout << "average: " << total/counter << endl;
    cout << "smallest: " << small << endl;
    cout << "largest: " << big << endl;
    return 0;
}
/*
test cases
Please input a integer
7
Please input a integer
-5
Please input a integer
0
average: 1
smallest: -5
largest: 7

Process returned 0 (0x0)   execution time : 7.259 s
Press any key to continue.

*/
