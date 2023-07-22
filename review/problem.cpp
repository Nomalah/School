#include <iostream>
#include <vector>

#define abs(x) ((x) > 0 ? (x) : (-x))

/*
list of n long
it's max value can be the list

list of 5 long - max value 5

1, 2, 3, 4, 5 // return -1
1, 2, 3, 2, 4 // dupe return 2
1, 2, 3, 5, 6, 3, 1, 2 // dupe return 3
*/

using namespace std;

int brute_force(vector<int>);
int space_force(vector<int>);
int space_time(vector<int>&);

int main(){
    vector<int> test1 = {1, 2, 3, 4, 5};
    vector<int> test2 = {1, 2, 3, 2, 4};
    vector<int> test3 = {1, 2, 3, 5, 6, 3, 1, 2};
    

    cout << space_time(test1) << endl;
    cout << space_time(test2) << endl;
    cout << space_time(test3) << endl;
}

// O(n^2)
int brute_force(vector<int> test_arr){
    int first_duplicate = test_arr.size();
    for(int i = 0; i < test_arr.size()-1; i++){
        for(int j = i + 1; j < test_arr.size(); j++){
            if(test_arr[i] == test_arr[j]){
                if(j < first_duplicate){
                    first_duplicate = j;
                    break;
                }
            }
        }
    }
    // if it did find a duplicate
    if(first_duplicate != test_arr.size()){
        return test_arr[first_duplicate];
    }

    return -1;
}

// O(n)
// O(1)
int space_force(vector<int> test_arr){
    int* map = new int[test_arr.size()]{};
    for(int i = 0; i < test_arr.size(); i++){
        map[test_arr[i] - 1]++;
        if(map[test_arr[i] - 1] == 2)
            return test_arr[i];
    }
    return -1;
}

/*
vector<int> test1 = {1, 2, 3, 4, 5};


    vector<int> test2 = {1, 2, 3, 2, 4};
*/


//{-1, 2, -3, 2, 4};
int space_time(vector<int>& test_arr){
    for(int i = 0; i < test_arr.size(); i++){
        if(test_arr[abs(test_arr[i]) - 1] < 0)
            return abs(test_arr[i]);
        test_arr[abs(test_arr[i]) - 1] = -test_arr[abs(test_arr[i]) - 1];
    }
    
    for(int& i : test_arr){
        i = abs(i);
    }
    return -1;
}