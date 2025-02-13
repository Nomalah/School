/// assign_2_15_adp.cpp
/// Dallas Hart
/// Copyright 10/31/2019
/// figures if a number is perfect abundant or deficient

#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int input;
    int total=0;
    cout << "input a maximum number" << endl;
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
    for (int num =1; num<=input; num++) /// run for all numbers under maximum
    {
        total = 0;
        for (int i=1; i<=floor(sqrt(num)); i++) /// only need the sqrt of the number
        {
            if (num % i == 0)
            {
                total+=i+num/i; /// add the  factors to the total
            }
        }
        total-=num; ///subtract original number
        if (total>num) /// dicide which one it is
        {
            cout << num << " is Abundant"<< endl;
        }
        else if (total<num)
        {
            cout << num << " is deficient"<< endl;
        }
        else
        {
            cout << num << " is Perfect"<< endl;
        }
    }
    return 0;
}
/*

test cases

input a maximum number
50
1 is Perfect
2 is deficient
3 is deficient
4 is Abundant
5 is deficient
6 is Perfect
7 is deficient
8 is deficient
9 is deficient
10 is deficient
11 is deficient
12 is Abundant
13 is deficient
14 is deficient
15 is deficient
16 is Abundant
17 is deficient
18 is Abundant
19 is deficient
20 is Abundant
21 is deficient
22 is deficient
23 is deficient
24 is Abundant
25 is deficient
26 is deficient
27 is deficient
28 is Perfect
29 is deficient
30 is Abundant
31 is deficient
32 is deficient
33 is deficient
34 is deficient
35 is deficient
36 is Abundant
37 is deficient
38 is deficient
39 is deficient
40 is Abundant
41 is deficient
42 is Abundant
43 is deficient
44 is deficient
45 is deficient
46 is deficient
47 is deficient
48 is Abundant
49 is deficient
50 is deficient

Process returned 0 (0x0)   execution time : 13.423 s
Press any key to continue.
*/
