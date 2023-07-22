/// assign_2_9_isPrime.cpp
/// Dallas Hart
/// Copyright 10/31/2019
/// Prints all prime numbers up to the inputed one


#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    int input;
    bool isPrime;
    cout << "Please input the maximum possible prime" << endl;
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
    /// one is not a prime so no need to check it
    for (int i=2; i<=input; i++)
    {
        isPrime = true; /// reset the prime flag
        for (int num=2; num<=floor(sqrt(i)); num++) /// only nessisary to check up to the sqrt
        {
            if (i % num == 0)
            {
                isPrime = false;
                break; /// stop the loop scince we already know its not prime
            }
        }

        ///if the number survives gettng divided it must be prime
        if (isPrime)
        {
            cout << i << " is prime" << endl;
        }

    }
    return 0;
}

/*
test cases
Please input the maximum possible prime
89
2 is prime
3 is prime
5 is prime
7 is prime
11 is prime
13 is prime
17 is prime
19 is prime
23 is prime
29 is prime
31 is prime
37 is prime
41 is prime
43 is prime
47 is prime
53 is prime
59 is prime
61 is prime
67 is prime
71 is prime
73 is prime
79 is prime
83 is prime
89 is prime

Process returned 0 (0x0)   execution time : 3.402 s
Press any key to continue.
*/
