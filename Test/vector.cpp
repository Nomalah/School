#include <iostream>
#include <vector>

using namespace std;

void print(const vector<int> to_print)
{
    for (int i : to_print)
        cout << i << " ";
    cout << endl;
}

/*
Acessing arrays and vectors are a O(1) operation


*/

int main(){
    {
    vector<int> my_vec = {15, 20, 7, 3};
    print(my_vec);
    // current size of your vector
    cout << my_vec.size() << endl;

    // max length your vector can have
    cout << my_vec.max_size() << endl;

    // capacity, (largest the vector can be before reallocation)
    cout << my_vec.capacity() << endl;

    // boolean checks if vector is empty
    cout << my_vec.empty() << endl;

    // accessing the vector
    cout << my_vec[3] << endl;
    cout << my_vec.at(3) << endl; // Throw std::out_of_range

    cout << my_vec.front() << endl; // First element
    cout << my_vec.back() << endl;  // Last element of the vector

    // Resizes your vector
    my_vec.resize(10, 6);
    print(my_vec);
    my_vec.resize(3);
    cout << my_vec.capacity() << endl;
    my_vec.shrink_to_fit();
    cout << my_vec.capacity() << endl;

    print(my_vec);
    my_vec.clear();
    print(my_vec);
    cout << my_vec.size() << endl;

    for (int i = 0; i < 20; i++)
    {
        my_vec.push_back(i);
        int *x = my_vec.data();
        cout << x << " ";
    }
    cout << endl;
    print(my_vec);
    // returns a pointer to the start of the vectors memory

    int x[] = {1, 3, 5, 6, 2};

    my_vec.pop_back();
    print(my_vec);
    my_vec.insert(my_vec.begin(), x, x + 5);
    my_vec.erase(my_vec.begin() + 7, my_vec.end()); // not inclusive of the last element
    print(my_vec);

    vector<int> other = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    my_vec.swap(other);
    print(my_vec);
    print(other);

    my_vec.emplace(my_vec.begin(), 5);
    my_vec.emplace_back(20);
    print(my_vec);
    /*
    assume length 5
    my_vec.begin() point to index 0 (my_vec[0])
    my_vec.end() point to index 5 (my_vec[5])
    my_vec.rbegin() point to index 4 (my_vec[4])
    my_vec.rend() point to index -1 (my_vec[-1])
)
    my_vec.cbegin() point to index 0 (my_vec[0])
    my_vec.cend() point to index 5 (my_vec[5])
    my_vec.crbegin() point to index 4 (my_vec[4])
    my_vec.crend() point to index -1 (my_vec[-1])
    */
    }
    cin.get();

    const int x = 5;
    void* ptr = &x;
    *ptr = 20;

    /*long long u = 0;
    long long* x = nullptr;
    for(int p = 0; p < 20; p++){
        for(int j = 0; j < 1024; j++){ // allocate 1 gb
            //for(int i = 0; i < 1024; i++){ // allocate 1 mb
                x = new long long[131072]; // alocate 1 kb
                for(int z = 0; z < 131072; z++){
                    x[z] = ((p*1024 + j) * 131072 + z) * 8;
                    //for(int _ = 0; _ < 10 ; _++) u++;
                }  
            //}
        }
    }*/

    cin.get();
    return 0;
}