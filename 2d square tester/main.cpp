#include <iostream>
#include <cstdlib>

using namespace std;

struct point{
    double x, y, z;
};

struct slope{
    double m;
    bool v_line;
};

int main()
{
    int check [3][4][2] = {
        {
            {0,1},
            {2,3},
            {0,2},
            {1,3}
        },
        {
            {0,1},
            {3,2},
            {0,3},
            {1,2}
        },
        {
            {0,2},
            {3,1},
            {0,3},
            {2,1}
        }
    }

    point vertexes [4];
    for (size_t i = 0; i < 4; i++) {
        cin >> vertexes[i].x >> vertexes[i].y;
    }

    for (size_t if (if (/* condition */) {
        /* code */
    }) {
        /* code */
    } = 0; if (if (/* condition */) {
        /* code */
    }) {
        /* code */
    } < count; if (if (/* condition */) {
        /* code */
    }) {
        /* code */
    }++) {
        /* code */
    }
    return 0;
}
