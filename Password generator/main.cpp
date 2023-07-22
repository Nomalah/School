#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    srand (time(NULL));
    for (size_t j = 0; j < 10; j++) {
        for(int i = 0; i < 16; i++){
            char temp = rand() % 126 + 32;
            cout << temp;
        }
        cout << endl;
    }
    return 0;
}
