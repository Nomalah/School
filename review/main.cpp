#include <iostream>

using namespace std;

// Forward Declarations
bool is_prime(int to_test);

int main(){
    cout << "Hello World!\n";

    int last_prime = 0;
    int gap_record = 0;

    // for(init, condition, repeat)
    for(int i = 2; gap_record <= 1000; i++){
        if(is_prime(i)){
            int temp = i - last_prime;
            if(temp > gap_record){
                gap_record = temp;
                cout << temp << " prime:" << i << endl;
            }else{
                cout << temp << "  \r";
            }
            last_prime = i;
        }
    }
    return 0;
}


// Actual Declaration
bool is_prime(int to_test){
    // All numbers between 2 and one less then to_test
    for(int i = 2; i*i < to_test; i++){
        if(to_test % i == 0){
            return false;
        }
    }
    return true;
}


// ervin's
/*int main()
{
    int gap_size = 0;
    int last_prime = 0;
    for (int i = 2; gap_size < 20; i++)
    {
        bool is_prime = true;
        for(int a = 2; a < i; a++){
            if(i % a == 0){
                is_prime = false;
                gap_size++;
                break;
            }
        }
        if(is_prime){
            gap_size = 0;
            last_prime = i;
        }
    }

    for (int i = 0; i < 20; i++)
    {
        cout << last_prime + i + 1 << endl;
    }
    return 0;
}*/