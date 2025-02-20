/// assign_3_13_mersenne.cpp
/// Dallas Hart
/// 11/25/2019
/// This program prints the mersenne primes up to a user inputed number

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
    for (int i=1; pow(2,i)-1<=maxNum; i++)
    {
        if (isPrime(pow(2,i)-1))/// use function
        {
            cout << pow(2,i)-1 << " is a mersenne prime" << endl; /// output
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
1000000
1 is a mersenne prime
3 is a mersenne prime
7 is a mersenne prime
31 is a mersenne prime
127 is a mersenne prime
8191 is a mersenne prime
131071 is a mersenne prime
524287 is a mersenne prime

Process returned 0 (0x0)   execution time : 3.997 s
Press any key to continue.

*/
