/// assign_2_7_smallbig.cpp
/// Dallas Hart
/// Copyright 10/31/2019
/// prints from the smaller number to the bigger number

#include <iostream>

using namespace std;

int main()
{
    long long int inputs [2];
    for (int i=0; i<2; i++)
    {
        cout << "Please input a integer" << endl;
        //Idiot Proofing
        while (true)
        {
            cin >> inputs[i]; // input for number of second
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
    }
    cout << "\n\nLowest to Highest\n";
    for (int i=inputs[0];i<=inputs[1];i++){
        cout << i << endl; /// forwards
    }
    for (int i=inputs[1];i<=inputs[0];i++){
        cout << i << endl; /// backwards
    }
    return 0;
}
/*
test cases
Please input a integer
5
Please input a integer
9


Lowest to Highest
5
6
7
8
9

Process returned 0 (0x0)   execution time : 4.112 s
Press any key to continue.

Please input a integer
9
Please input a integer
5


Lowest to Highest
5
6
7
8
9

Process returned 0 (0x0)   execution time : 5.634 s
Press any key to continue.
*/
