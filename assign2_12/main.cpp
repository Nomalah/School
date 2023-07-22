/// assign_2_12_diamond.cpp
/// Dallas Hart
/// Copyright 10/31/2019
/// makes a diamond

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    int input;
    cout << "please input the total number of rows you want in a diamond" << endl;
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
    /// I HAVE NO IDEA HOW I MADE MY OWN THING WORK
    for (int x = 1; x<=floor(input/2); x++)
        {
            cout << " ";
        }
        cout << "*" << endl;
    for (int y = 1; y<floor(input/2); y++)
    {
        for (int x = 1; x<=floor(input/2)-y; x++)
        {
            cout << " ";
        }
        cout << "*";
        for (int i=1; i<=2*y-1; i++){
            cout << " ";
        }
        cout<< "*" << endl;
    }
    if (input % 2 == 1){
        cout << "*";
         for (int x = 1; x<=input-2; x++)
        {
            cout << " ";
        }
        cout<< "*" << endl;
    }
    for (int y = floor(input/2)-1; y>=1; y--)
    {
        for (int x = 1; x<=floor(input/2)-y; x++)
        {
            cout << " ";
        }
        cout << "*";
        for (int i=1; i<=2*y-1; i++){
            cout << " ";
        }
        cout<< "*" << endl;
    }
     for (int x = 1; x<=floor(input/2); x++)
        {
            cout << " ";
        }
        cout << "*" << endl;
    return 0;
}

/*
test cases
please input the total number of rows you want in a diamond
7
   *
  * *
 *   *
*     *
 *   *
  * *
   *

Process returned 0 (0x0)   execution time : 1.741 s
Press any key to continue.
*/
