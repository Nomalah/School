/// assign_4_8_badDivide.cpp
/// Dallas Hart
/// Copyright 1/3/2020
/// prints a bad simplification of a fraction

#include <iostream>

using namespace std;

int main()
{
    string numerator;
    string denominator;
    /// get input
    while (true)
    {
        cout << "Please input the numerator of the fraction" << endl;
        cin >> numerator;
        bool validInput = true;
        /// make sure input is all numbers (must still be a string)
        for (int i = 0; i<numerator.size(); i++)
        {
            if (numerator[i] < 48 || numerator[i] > 57)
                validInput = false;
            break;
        }
        if (validInput)
            break;
    }
    /// get input
    while (true)
    {
        cout << "Please input the denominator of the fraction" << endl;
        cin >> denominator;
        bool validInput = true;
        /// make sure input is all numbers (must still be a string)
        for (int i = 0; i<denominator.size(); i++)
        {
            if (denominator[i] < 48 || denominator[i] > 57)
                validInput = false;
            break;
        }
        if (validInput)
            break;
    }
    /// replace cancel outs with spaces
    for (int x = 0; x < numerator.size(); x++)
    {
        for (int y = 0; y < denominator.size(); y++)
        {
            if (numerator[x] == denominator[y])
            {
                numerator[x] = ' ';
                denominator[y] = ' ';
                break;
            }
        }
    }
    /// print (without spaces)
    for (int x = 0; x < numerator.size(); x++)
    {
        if (numerator[x] != ' ')
        {
            cout << numerator[x];
        }
    }
    cout << " / ";
    for (int y = 0; y < denominator.size(); y++)
    {
        if (denominator[y] != ' ')
        {
            cout << denominator[y];
        }
    }
    return 0;
}

/*
TEST CASES

Please input the numerator of the fraction
323
Please input the denominator of the fraction
635
23 / 65
Process returned 0 (0x0)   execution time : 11.228 s
Press any key to continue.

*/
