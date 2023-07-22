/// assign_2_3_1-x.cpp
/// Dallas Hart
/// Copyright 10/31/2019
/// prints 1 to x

#include <iostream>

using namespace std;

int main()
{

    long long int input;
    cout << "Please input a positive integer" << endl;
    //Idiot Proofing
    while (true)
    {
        cin >> input; // input
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
    if (input<=0){
        cout << "You cannont enter 0 or a negative number!";
        return 0;
    }
    for (long long int i=1;i<=input;i++){
        cout << i << endl;///simple for loop
    }
    return 0;
}

/*
test cases
Please input a positive integer
15
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15

Process returned 0 (0x0)   execution time : 1.605 s
Press any key to continue.
*/
