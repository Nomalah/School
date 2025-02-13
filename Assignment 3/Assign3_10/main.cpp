/// assign_3_10_adp.cpp
/// Dallas Hart
/// Copyright 11/25/2019
/// ffinds bert & ernie numbers

#include <iostream>
#include <math.h>

using namespace std;

int bertErnie(int inputNum);
int in(string inMessage, string failMessage);

int main()
{
    int maxNum = in("input a maximum number", "Enter a Number!");
    int total;
    int current, previous = 0;
    for (int num =1; num<=maxNum; num++) /// run for all numbers under maximum
    {
        current = bertErnie(num);
        if ((current==1||current==2)&&(previous==1||previous==2)&&(current!=previous))
        {
            cout << num << " and " << num-1 << " are bert and ernie numbers"<<endl;
        }

        previous=current;
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

int bertErnie(int inputNum)
{
    int total = 0;
    for (int i=1; i<=floor(sqrt(inputNum)); i++) /// only need the sqrt of the number
    {
        if (inputNum % i == 0)
        {
            total+=i+inputNum/i; /// add the  factors to the total
        }
    }
    total-=inputNum; ///subtract original number

    if (total>inputNum*2) /// if number is bert
    {
        return 2;
    }
    else if (total==1) /// total will be 1 if it is a prime
    {
        return 1;
    }
    return 0;
}
/*

test cases

input a maximum number
1000
180 and 179 are bert and ernie numbers
181 and 180 are bert and ernie numbers
240 and 239 are bert and ernie numbers
241 and 240 are bert and ernie numbers
360 and 359 are bert and ernie numbers
420 and 419 are bert and ernie numbers
421 and 420 are bert and ernie numbers
480 and 479 are bert and ernie numbers
504 and 503 are bert and ernie numbers
541 and 540 are bert and ernie numbers
600 and 599 are bert and ernie numbers
601 and 600 are bert and ernie numbers
660 and 659 are bert and ernie numbers
661 and 660 are bert and ernie numbers
720 and 719 are bert and ernie numbers
840 and 839 are bert and ernie numbers

Process returned 0 (0x0)   execution time : 2.559 s
Press any key to continue.

*/
