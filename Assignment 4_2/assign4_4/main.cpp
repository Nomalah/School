/// assign_4_4_fChar.cpp
/// Dallas Hart
/// Copyright 1/3/2020
/// prints the first character of each line of a file called essay

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    /// open file
    ifstream essay;
    essay.open("essay.txt");
    if (essay.is_open())
    {
        string line;
        while (getline(essay,line))
        {
            cout << line[0] << endl;///output first letter
        }
        /// close file
        essay.close();
    }
    else
    {
        cout << "Unable to open file!";
    }
    return 0;
}

/*
TEST CASES

N
G
t
g
y
u
n
g
t
l
y
d
n
g
t
r
a
a
d
y
n
g
t
m
y
c
n
g
t
s
g
n
g
t
t
a
l
a
h
y

-
T

Process returned 0 (0x0)   execution time : 0.037 s
Press any key to continue.

*/
