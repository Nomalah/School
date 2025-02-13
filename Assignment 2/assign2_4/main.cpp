/// assign_2_4_average5.cpp
/// Dallas Hart
/// Copyright 10/31/2019
/// totals 5 numbers

#include <iostream>

using namespace std;

int input()
{
    int num;
    cout << "Please a float you would like to add to 4 others" << endl;
    //Idiot Proofing
    while (true)
    {
        cin >> num; // input for number of second
        if (cin.fail())// dummy-proofing
        {
            cout << "Enter a Number!" << endl;
            cin.clear(); //clear stream
            cin.ignore(80, '\n'); //clear 80 characters until a \n is reached.
        }
        else
        {
            return num; //exit the loop if everything is ok
        }
    }
}
int main()
{
    int total=0;
    int counter = 0;

    cout << "For Loop" << endl;
    for (int i=0; i<5; i++)
    {
        total+=input();/// for loop
    }
    cout << "Total = " << total << endl;

    total=0;

    cout << "While Loop" << endl;
    while (counter < 5)
    {
        total+=input();
        counter++;/// while loop
    }
    cout << "Total = " << total << endl;

    counter=0;
    total=0;

    cout << "Do / While Loop" << endl;
    do
    {
        total+=input();
        counter++;/// do while loop
    }
    while(counter < 5);
    cout << "Total = " << total << endl;

    return 0;
}
/*
test cases

For Loop
Please a float you would like to add to 4 others
-5
Please a float you would like to add to 4 others
6
Please a float you would like to add to 4 others
7
Please a float you would like to add to 4 others
8
Please a float you would like to add to 4 others
3
Total = 19
While Loop
Please a float you would like to add to 4 others
7
Please a float you would like to add to 4 others
4
Please a float you would like to add to 4 others
3
Please a float you would like to add to 4 others
-5
Please a float you would like to add to 4 others
7
Total = 16
Do / While Loop
Please a float you would like to add to 4 others
6
Please a float you would like to add to 4 others
7
Please a float you would like to add to 4 others
9
Please a float you would like to add to 4 others
3
Please a float you would like to add to 4 others
-
Enter a Number!
-9
Total = 16

Process returned 0 (0x0)   execution time : 38.116 s
Press any key to continue.
*/
