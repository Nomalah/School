// a1_3_trianglePaths.cpp
// Dallas Hart
// 
// Calculate max path sum through a triangle construction and output path and path sum

#include <iostream>

// Number of lines in triangle construction
#define SIZE 1000ULL

// Calculates the qth triangle number
#define TRIANGLE(q) (((q) * (q) + (q)) / 2)

int main() {
    // Store construction in 2D array
    uint64_t grouping[SIZE][SIZE];
    
    // Create triangle construction
    /* Example construction for SIZE = 10
     1  2  6  7 15 16 28 29 45 46       
     3  5  8 14 17 27 30 44 47  0     
     4  9 13 18 26 31 43 48  0  0      
    10 12 19 25 32 42 49  0  0  0  
    11 20 24 33 41 50  0  0  0  0    
    21 23 34 40 51  0  0  0  0  0   
    22 35 39 52  0  0  0  0  0  0        
    36 38 53  0  0  0  0  0  0  0      
    37 54  0  0  0  0  0  0  0  0       
    55  0  0  0  0  0  0  0  0  0   
    */
    int x = 0;
    int y = 0;
    uint64_t num = 1;
    bool down = false;
    while (x < SIZE && y < SIZE) {
        grouping[x][y] = num;
        if (!down) {
            if (y == 0) {
                x++;
                down = !down;
            } else {
                x++;
                y--;
            }
        } else {
            if (x == 0) {
                y++;
                down = !down;
            } else {
                x--;
                y++;
            }
        }
        num++;
    }

    // For values of SIZE where (SIZE/2)%2 == 1, this is the calcuation for the max path sum
    unsigned long long removeTotal = 0;
    for (y = 1; y < SIZE; y += 4) {
        removeTotal += grouping[0][y];
    }
    for (x = 3; x < SIZE; x += 4) {
        removeTotal += grouping[x][0];
    }

    // Reset position
    x = 0;
    y = 0;
    uint64_t total = 0;

    // Hardcoded to print first 2 positions
    std::cout << grouping[x][y] << "->";
    total += grouping[x][y];
    x++;
    std::cout << grouping[x][y] << "->";
    total += grouping[x][y];

    while (x < SIZE - 1 && y < SIZE - 1) {
        if (y == 0) {
            if (x % 4 == 1) {
                // Turn around and start going down
                x++;
                std::cout << grouping[x][y] << "->";
                total += grouping[x][y];
            } else {
                // Staircase down & left
                bool downOrLeft = true;
                while (true) {
                    if (downOrLeft) {
                        y++;
                    } else {
                        x--;
                    }
                    if (!(x < SIZE && y < SIZE)) break;
                    std::cout << grouping[x][y] << "->";
                    total += grouping[x][y];

                    downOrLeft = !downOrLeft;
                }
                x++;
            }
        } else if (x == 0) {
            if (y % 4 == 3) {
                // Turn around and start going up
                y++;
                std::cout << grouping[x][y] << "->";
                total += grouping[x][y];
            } else {
                // Staircase up & right
                bool upOrRight = true;
                while (true){
                    if (upOrRight) {
                        x++;
                    } else {
                        y--;
                    }
                    if (!(x < SIZE && y < SIZE)) break;
                    std::cout << grouping[x][y] << "->";
                    total += grouping[x][y];

                    upOrRight = !upOrRight;
                }
                y++;
            }
        }
    }
    // Display calcluation and manual addition to ensure integrity
    std::cout << "Calculation:" << TRIANGLE(TRIANGLE(SIZE)) - removeTotal << " vs Addition:" << total << std::endl;
}

/*
...->498505->500497->498504->500498->498503->500499->498502->500500->Calculation:125166791750 vs Addition:125166791750
*/