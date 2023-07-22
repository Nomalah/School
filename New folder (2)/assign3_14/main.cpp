/// assign_3_14_sophieGermain.cpp
/// Dallas Hart
/// 11/25/2019
/// This program prints the sophie germain primes up to a user inputed number

#include <iostream>
#include <math.h>

using namespace std;

bool isPrime(int num);
int in(string inMessage, string failMessage);

int main()
{
    /// max search area
    int maxNum = in("input the max prime to search for","input the max prime to search for");

    ///iterate through all the nums
    for (int i=1; i<=maxNum; i++)
    {
        if (isPrime(i)&&isPrime(2*i+1))/// use function
        {
            cout << i << " is a sophie Germain prime" << endl; /// output
        }
    }
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


bool isPrime(int inNum)
{
    bool isPrime = true; /// reset the prime flag
    for (int num=2; num<=floor(sqrt(inNum)); num++) /// only nessisary to check up to the sqrt
    {
        if (inNum % num == 0)
        {
            isPrime = false;
            break; /// stop the loop scince we already know its not prime
        }
    }
    ///if the number survives gettng divided it must be prime
    if (isPrime)
    {
        return true;
    }
}


/*
test cases

input the max prime to search for
150
1 is a sophie Germain prime
2 is a sophie Germain prime
3 is a sophie Germain prime
5 is a sophie Germain prime
11 is a sophie Germain prime
23 is a sophie Germain prime
29 is a sophie Germain prime
41 is a sophie Germain prime
53 is a sophie Germain prime
83 is a sophie Germain prime
89 is a sophie Germain prime
113 is a sophie Germain prime
131 is a sophie Germain prime

Process returned 0 (0x0)   execution time : 2.675 s
Press any key to continue.

*/
