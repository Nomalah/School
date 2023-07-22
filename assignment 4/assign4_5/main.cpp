/// assign_4_5_revPoem.cpp
/// Dallas Hart
/// Copyright 1/3/2020
/// prints the reverse of a poem

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    /// open file
    ifstream poem;
    poem.open("poem.txt");
    if (poem.is_open())
    {
        /// load file into array
        string* line = new string[1];
        int length = 0;
        while (getline(poem,line[length]))
        {
            length++;
            ///extend array by 1
            string* temp = new string[length];
            for (int i=0; i<length; i++)
            {
                temp[i] = line[i];
            }
            line = new string [length+1];
            for (int i=0; i<length; i++)
            {
                line[i] = temp[i];
            }
            /// delete temp array
            delete[] temp;
        }

        /// output file backwards
        for (int i=length-1; i>=0; i--)
        {
            cout << line[i] << endl;
        }
        /// close file
        poem.close();
    }
    else
    {
        cout << "Unable to open file!";
    }
    return 0;
}

/*
TEST CASES

Today was a very good day
And you'll never in a million years hear me say
It's all beyond my control
My attitude
Creates
The reality
I'm sure you can agree that
It's not true that good exists
Only if one's surroundings are good
True happiness can be attained
Because
It's all in the mind and heart
And it's not true that
Satisfaction and happiness don't last.
Some goodness does shine through once in a while
Even if
This world is a pretty evil place.
Because, when you take a closer look,
There's something good in every day
And don't try to convince me that
Today was the absolute worst day ever

Process returned 0 (0x0)   execution time : 0.045 s
Press any key to continue.

*/
