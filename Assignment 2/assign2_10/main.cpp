/// assign_2_10_collatz.cpp
/// Dallas Hart
/// Copyright 10/31/2019
/// collatz conjecture

#include <iostream>

using namespace std;

int main()
{
    int input;
    int steps = 0;
    cout << "Please input the number you would like to test for the collatz conjecture" << endl;
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
    cout << input << " has ";
    while (input != 1)/// contune if the number is not one
    {
        if (input % 2 == 0)
        {
            input /=2;/// divide by two if able to
        }
        else
        {
            input = input * 3 + 1;/// or muliply and add one
        }
        steps++;
    }
    cout << steps << " steps" << endl
;

    for (int i=10000; i<=10060; i++)
    {
        steps = 0;
        int temp = i;
        cout << temp << " has ";
        while (temp != 1)/// contune if the number is not one
        {
            if (temp % 2 == 0)
            {
                temp /=2;/// divide by two if able to
            }
            else
            {
                temp = temp * 3 + 1;/// or muliply and add one
            }
            steps++;
        }
        cout << steps << " steps" << endl;
    }
    return 0;
}
/*
test cases
Please input the number you would like to test for the collatz conjecture
80
80 has 9 steps
10000 has 29 steps
10001 has 179 steps
10002 has 65 steps
10003 has 65 steps
10004 has 29 steps
10005 has 29 steps
10006 has 179 steps
10007 has 179 steps
10008 has 29 steps
10009 has 166 steps
10010 has 29 steps
10011 has 210 steps
10012 has 65 steps
10013 has 65 steps
10014 has 65 steps
10015 has 65 steps
10016 has 135 steps
10017 has 91 steps
10018 has 91 steps
10019 has 91 steps
10020 has 91 steps
10021 has 91 steps
10022 has 91 steps
10023 has 65 steps
10024 has 135 steps
10025 has 91 steps
10026 has 135 steps
10027 has 91 steps
10028 has 42 steps
10029 has 42 steps
10030 has 42 steps
10031 has 47 steps
10032 has 135 steps
10033 has 42 steps
10034 has 42 steps
10035 has 42 steps
10036 has 135 steps
10037 has 135 steps
10038 has 65 steps
10039 has 65 steps
10040 has 91 steps
10041 has 65 steps
10042 has 91 steps
10043 has 42 steps
10044 has 91 steps
10045 has 91 steps
10046 has 91 steps
10047 has 91 steps
10048 has 42 steps
10049 has 135 steps
10050 has 117 steps
10051 has 117 steps
10052 has 135 steps
10053 has 135 steps
10054 has 135 steps
10055 has 91 steps
10056 has 42 steps
10057 has 117 steps
10058 has 42 steps
10059 has 135 steps
10060 has 42 steps

Process returned 0 (0x0)   execution time : 3.883 s
Press any key to continue.
*/
