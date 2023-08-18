// a1_3_trianglePaths
// Dallas Hart
//
// Calculate max path sum through a triangle construction and output path and path sum

#include <iostream>

int main()
{
    // Number of rows for the triangle
    std::size_t size = 1000;
    uint64_t total = 0;
    // Traverse through all
    for (size_t i = 1; i <= size; i++)
    {
        // Odd rows take the diagonal value
        if (i % 2 == 1)
        {
            int pathStep = (i - 1) * (i / 2 + 1) + 1;
            std::cout << pathStep << "->";
            total += pathStep;
        }
        else // Even rows take the larger of the 2 diagonal values
        {
            int pathStep = i * i / 2 + 1;
            std::cout << pathStep << "->";
            total += pathStep;
        }
    }
    // Display calcluation and manual addition to ensure integrity
    std::cout << "Total:" << total << std::endl;
}

/*
...->486099->487085->488073->489061->490051->491041->492033->493025->494019->495013->496009->497005->498003->499001->500001->Total:166917500
*/