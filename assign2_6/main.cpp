/// assign_2_6_poscount.cpp
/// Dallas Hart
/// Copyright 10/31/2019
/// counts positive numbers

#include <iostream>

using namespace std;

int main()
{
    long long int counter=0,input=0;
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
        if (input > 0){
            counter++; /// add to counter
        }
    }
    while (input!=0);
    cout << counter << " positive number(s) have been entered" << endl;
    return 0;
}
/*
test cases
Please input a integer
6
Please input a integer
89
Please input a integer
-2
Please input a integer
-5
Please input a integer
0
average: 22
smallest: -5
largest: 89

Process returned 0 (0x0)   execution time : 13.326 s
Press any key to continue.
*/
