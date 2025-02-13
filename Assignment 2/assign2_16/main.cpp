/// assign_2_16_cubes.cpp
/// Dallas Hart
/// Copyright 10/31/2019
/// finds perfect cubes that are the sum of 3 other perfect cubes

#include <iostream>
#include <math.h>

using namespace std;

bool check(int num, int left, int goal, int current)///recursive?
{
    if (left == 0)///check if the final combo is correct
    {
        if(current+num*num*num==goal)/// it is
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    for (int i=left; i<num; i++) /// go to next number if not final number
    {
        if(check(i,left-1,goal,current+num*num*num))///recursive part?
        {
            return true;
        }
    }
    return false;

}

int main()
{
    int input;
    cout << "please in put a number and I will find all the perfect cubes that are also the sum of 3 other perfect cubes under it" << endl;
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
    for (int cube = 1; cube<=floor(cbrt(input)); cube++) /// checks every perfect cube for its perfect cube sum
    {
        for (int i=3; i<cube; i++)
        {
            if(check(i,2,cube*cube*cube,0))/// start the recusion
            {
                cout << cube*cube*cube << " can be made up of the sum of 3 other perfect cubes" << endl;
            }
        }
    }
    return 0;
}
/*
test cases

please in put a number and I will find all the perfect cubes that are also the sum of 3 other perfect cubes under it
15625
216 can be made up of the sum of 3 other perfect cubes
729 can be made up of the sum of 3 other perfect cubes
1728 can be made up of the sum of 3 other perfect cubes
5832 can be made up of the sum of 3 other perfect cubes
5832 can be made up of the sum of 3 other perfect cubes
6859 can be made up of the sum of 3 other perfect cubes
8000 can be made up of the sum of 3 other perfect cubes
13824 can be made up of the sum of 3 other perfect cubes
15625 can be made up of the sum of 3 other perfect cubes

Process returned 0 (0x0)   execution time : 7.800 s
Press any key to continue.
*/
