// Faresquare question
// d = (a+b)^2
// Using my timing code and PC: 100 Runs: Avg Time: 1.15468 seconds
#include <iostream>
#include "timer.h"

using namespace std;

int main()
{
    // put outside of timing for loop
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    timer clock;
    // put outside of timing for loop
    unsigned long long i, i2, a, b, d;

    /// y=1 (2 digits)
    clock.reset();
    d = 10;
    for (i = 4; i < d; i++)
    {
        i2 = i*i;

        b = i2%d;

        if (b <= 2)
        {
            a = i2/d;

            if (a%2 == 0)
            {
                a += b;

                if (i2 == a*a)
                {
                    cout <<i2<<'\n';
                }
            }
        }
    }

    /// y=2 (4 digits)
    d = 100;
    for (i = 32; i < d; i++)
    {
        i2 = i*i;

        b = i2%d;

        if (b <= 25)
        {
            a = i2/d;

            if (a%2 == 0)
            {
                a += b;

                if (i2 == a*a)
                {
                    cout <<i2<<'\n';
                }
            }
        }
    }

    /// y=3 (6 digits)
    d = 1000;
    for (i = 317; i < d; i++)
    {
        i2 = i*i;

        b = i2%d;

        if (b <= 250)
        {
            a = i2/d;

            if (a%2 == 0)
            {
                a += b;

                if (i2 == a*a)
                {
                    cout <<i2<<'\n';
                }
            }
        }
    }

    /// y=4 (8 digits)
    d = 10000;
    for (i = 3163; i < d; i++)
    {
        i2 = i*i;

        b = i2%d;

        if (b <= 2500)
        {
            a = i2/d;

            if (a%2 == 0)
            {
                a += b;

                if (i2 == a*a)
                {
                    cout <<i2<<'\n';
                }
            }
        }
    }

    /// y=5 (10 digits)
    d = 100000;
    for (i = 31623; i < d; i++)
    {
        i2 = i*i;

        b = i2%d;

        if (b <= 25000)
        {
            a = i2/d;

            if (a%2 == 0)
            {
                a += b;

                if (i2 == a*a)
                {
                    cout <<i2<<'\n';
                }
            }
        }
    }

    /// y=6 (12 digits)
    d = 1000000;
    for (i = 316228; i < d; i++)
    {
        i2 = i*i;

        b = i2%d;

        if (b <= 250000)
        {
            a = i2/d;

            if (a%2 == 0)
            {
                a += b;

                if (i2 == a*a)
                {
                    cout <<i2<<'\n';
                }
            }
        }
    }

    /// y=7 (14 digits)
    d = 10000000;
    for (i = 3162278; i < d; i++)
    {
        i2 = i*i;

        b = i2%d;

        if (b <= 2500000)
        {
            a = i2/d;

            if (a%2 == 0)
            {
                a += b;

                if (i2 == a*a)
                {
                    cout <<i2<<'\n';
                }
            }
        }
    }

    /// y=8 (16 digits)
    d =     100000000;
    for (i = 31622777; i < d; i++)
    {
        i2 = i*i;

        b = i2%d;

        if (b <= 25000000)
        {
            a = i2/d;

            if (a%2 == 0)
            {
                a += b;

                if (i2 == a*a)
                {
                    cout <<i2<<'\n';
                }
            }
        }
    }
    clock.stop();
    cout << clock.get();
    return 0;
}
