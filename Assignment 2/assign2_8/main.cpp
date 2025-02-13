/// assign_2_8_cfdegrees.cpp
/// Dallas Hart
/// Copyright 10/31/2019
/// prints celcius from -40 to 250 with feinheight

#include <iostream>

using namespace std;

int main()
{
    for (int i=-40; i<=250; i+=5)///simple for loop coumting by 5's
    {
        cout << "Celsius: " << i << " Fahrenheit: " << i*1.8+32 << endl;///i*1.8+32 is the equation for fahrenheit
    }
    return 0;
}

/*
test cases

Celsius: -40 Fahrenheit: -40
Celsius: -35 Fahrenheit: -31
Celsius: -30 Fahrenheit: -22
Celsius: -25 Fahrenheit: -13
Celsius: -20 Fahrenheit: -4
Celsius: -15 Fahrenheit: 5
Celsius: -10 Fahrenheit: 14
Celsius: -5 Fahrenheit: 23
Celsius: 0 Fahrenheit: 32
Celsius: 5 Fahrenheit: 41
Celsius: 10 Fahrenheit: 50
Celsius: 15 Fahrenheit: 59
Celsius: 20 Fahrenheit: 68
Celsius: 25 Fahrenheit: 77
Celsius: 30 Fahrenheit: 86
Celsius: 35 Fahrenheit: 95
Celsius: 40 Fahrenheit: 104
Celsius: 45 Fahrenheit: 113
Celsius: 50 Fahrenheit: 122
Celsius: 55 Fahrenheit: 131
Celsius: 60 Fahrenheit: 140
Celsius: 65 Fahrenheit: 149
Celsius: 70 Fahrenheit: 158
Celsius: 75 Fahrenheit: 167
Celsius: 80 Fahrenheit: 176
Celsius: 85 Fahrenheit: 185
Celsius: 90 Fahrenheit: 194
Celsius: 95 Fahrenheit: 203
Celsius: 100 Fahrenheit: 212
Celsius: 105 Fahrenheit: 221
Celsius: 110 Fahrenheit: 230
Celsius: 115 Fahrenheit: 239
Celsius: 120 Fahrenheit: 248
Celsius: 125 Fahrenheit: 257
Celsius: 130 Fahrenheit: 266
Celsius: 135 Fahrenheit: 275
Celsius: 140 Fahrenheit: 284
Celsius: 145 Fahrenheit: 293
Celsius: 150 Fahrenheit: 302
Celsius: 155 Fahrenheit: 311
Celsius: 160 Fahrenheit: 320
Celsius: 165 Fahrenheit: 329
Celsius: 170 Fahrenheit: 338
Celsius: 175 Fahrenheit: 347
Celsius: 180 Fahrenheit: 356
Celsius: 185 Fahrenheit: 365
Celsius: 190 Fahrenheit: 374
Celsius: 195 Fahrenheit: 383
Celsius: 200 Fahrenheit: 392
Celsius: 205 Fahrenheit: 401
Celsius: 210 Fahrenheit: 410
Celsius: 215 Fahrenheit: 419
Celsius: 220 Fahrenheit: 428
Celsius: 225 Fahrenheit: 437
Celsius: 230 Fahrenheit: 446
Celsius: 235 Fahrenheit: 455
Celsius: 240 Fahrenheit: 464
Celsius: 245 Fahrenheit: 473
Celsius: 250 Fahrenheit: 482

Process returned 0 (0x0)   execution time : 0.106 s
Press any key to continue.
*/
