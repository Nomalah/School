/// assign_4_9_farePrime.cpp
/// Dallas Hart
/// Copyright 1/3/2020
/// prints the all fare primes up to a disired number

#include <iostream>
#include <math.h>
#include <string>
#include <fstream>

using namespace std;

bool isPrime(int num);
int in(string inMessage, string failMessage);

int main()
{
    /// make/open output file
    ofstream out;
    out.open("output.txt");

    /// max search area
    int maxNum = in("input the max prime to search for","input the max prime to search for");

    ///iterate through all the nums
    for (int i=2; i<=maxNum; i++)
    {
        bool primeFlag = true;
        string usedNum = to_string(i);

        /// rotate
        for (int x=0; x<usedNum.size(); x++)
        {
            char temp = usedNum[usedNum.size()-1];
            for (int y=usedNum.size()-2; y>=0; y--)
            {
                usedNum[y+1]=usedNum[y];
            }
            usedNum[0] = temp;
            /// check rotation
            primeFlag = primeFlag && isPrime(stoi(usedNum,nullptr,10));/// use function
        }
        if (primeFlag)/// after checking all rotations
        {
            out << i << ", "; /// output
        }
    }
    /// close file
    out.close();
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
TEST CASES

input the max prime to search for
100000

Process returned 0 (0x0)   execution time : 6.537 s
Press any key to continue.

output.txt
2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, 97, 113, 131, 197, 199, 311, 337, 373, 719, 733, 919, 971, 991, 1193, 1931, 3119, 3779, 7793, 7937, 9311, 9377, 11939, 19391, 19937, 37199, 39119, 71993, 91193, 93719, 93911, 99371,
*/
