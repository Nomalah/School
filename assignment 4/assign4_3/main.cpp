/// assign_4_3_factors.cpp
/// Dallas Hart
/// Copyright 1/3/2020
/// prints the factors of a int

#include <iostream>
#include <math.h>

using namespace std;

int in(string inMessage, string failMessage);
int* factorsOf(int num);

int main()
{
    cout << "Please input a positive integer and I will return all its factors" << endl;
    /// take input
    int inNum = in ("Please input a positive integer", "Input a positive integer");

    ///array of factors
    int* factors = factorsOf(inNum);

    ///list them
    for (int i=1; i<=factors[0]; i++)
    {
        cout << factors[i] << endl;
    }

    /// delete factors
    delete[] factors;
    return 0;
}

int in(string inMessage, string failMessage)
{
    int input;
    cout << inMessage << endl;
    while(true)
    {
        cin >> input; // input for number of second
        if (cin.fail())// dummy-proofing
        {
            cout << failMessage << endl;
            cin.clear(); //clear stream
            cin.ignore(80, '\n'); //clear 80 characters until a \n is reached.
        }
        else
        {
            return input; //exit the loop if everything is ok
        }
    }
}

int* factorsOf(int num)
{
    /// start array with number of factors
    int* factors = new int [1];
    int numOfFactors = 0;
    for (int i=1; i<=sqrt(num); i++)
    {
        if (num%i==0)
        {
            if (numOfFactors%10==0)
            {
                ///extend the arrray
                int* temp = new int [numOfFactors+11];
                for (int x=1; x<=numOfFactors; x++)
                {
                    temp[x] = factors[x];
                }
                factors = new int [numOfFactors+11];
                for (int x=1; x<=numOfFactors; x++)
                {
                    factors[x] = temp[x];
                }
                ///delete the temporary array
                delete[] temp;
            }
            /// add the factors to the array
            factors[numOfFactors+1]=i;
            factors[numOfFactors+2]=num/i;
            numOfFactors+=2;
        }
    }
    /// sort the factors from smallest to largest
    for (int x=0; x<numOfFactors; x++)
    {
        for (int y=1; y<numOfFactors; y++)
        {
            if (factors[y]>factors[y+1])
            {
                int temp = factors[y+1];
                factors[y+1] = factors[y];
                factors[y] = temp;
            }
        }
    }

    /// set first position to its size
    factors[0] = numOfFactors;
    return factors;
}

/*
TEST CASES

Please input a positive integer and I will return all its factors
Please input a positive integer
5040
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
12
14
15
16
18
20
21
24
28
30
35
36
40
42
45
48
56
60
63
70
72
80
84
90
105
112
120
126
140
144
168
180
210
240
252
280
315
336
360
420
504
560
630
720
840
1008
1260
1680
2520
5040

Process returned 0 (0x0)   execution time : 9.706 s
Press any key to continue.


*/
