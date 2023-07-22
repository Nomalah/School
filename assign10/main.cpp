/// assign_1_10_farmSilos.cpp
/// Dallas Hart
/// Copyright 10/7/2019
/// Calculates the required amount of silos for a farmer with a given field.

#include <iostream>
#include <math.h>
#include <string>

#define b inputs[0]
#define l inputs[1]
#define c inputs[2]
#define r inputs[3]
#define h inputs[4]

using namespace std;

int main()
{
    double inputs [5]; // b = 0,l = 1,c = 2,r = 3,h = 4 Each array section represents a variable
    string questionNames [5] = {"Field Width:", "Field Length:", "Cubic meters of grain per hectare:", "Silo Radius:", "Silo Height:"};
    for (int i=0; i<5; i++)//input time!
    {
        while (true)// dummy-proofing
        {
            cout << questionNames[i];
            cin >> inputs [i]; // input for number of second
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

    }
    //TWO GIANT CALCULATIONS
    int temp = (c/10000*(b*l))/(M_PI*r*r*h); // number of silos
    cout << "Number of Silos: ";
    cout << ceil(temp) << endl; // max amount of silo's (volume of grain / volume of silo)
    cout << "Grain Height in last Silo: ";
    cout << (temp - floor(temp))*h << endl; //% of silo * silo height = height of grain
    return 0;
}

/*
Test Cases

Field Width:100
Field Length:100
Cubic meters of grain per hectare:
f
Enter a Number!
Cubic meters of grain per hectare:10000
Silo Radius:1
Silo Height:10
Number of Silos: 318
Grain Height in last Silo: 0

Process returned 0 (0x0)   execution time : 16.301 s
Press any key to continue.

*/
