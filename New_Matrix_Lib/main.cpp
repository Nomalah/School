#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "matrix.h"
#include "neuralNetwork.h"

using namespace std;



int main(){
    
    srand(time(NULL));
    
    neural_network my_net({2, 4, 1});

    cout << "Input: 0, 0: " << my_net.think({0, 0})[0] << endl;
    cout << "Input: 0, 1: " << my_net.think({0, 1})[0] << endl;
    cout << "Input: 1, 0: " << my_net.think({1, 0})[0] << endl;
    cout << "Input: 1, 1: " << my_net.think({1, 1})[0] << endl;

    cout << endl << "training..." << endl << endl;
    vector<vector<double>> training_inputs = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    vector<vector<double>> training_outputs = {{0}, {1}, {1}, {0}};
    //mem fault in training
    for(int i = 0; i < 10000000; i++){
        int x = rand() % 4;
        my_net.train(training_inputs[x], training_outputs[x]);
    }
    cout << "Input: 0, 0: " << my_net.think({0, 0})[0] << endl;
    cout << "Input: 0, 1: " << my_net.think({0, 1})[0] << endl;
    cout << "Input: 1, 0: " << my_net.think({1, 0})[0] << endl;
    cout << "Input: 1, 1: " << my_net.think({1, 1})[0] << endl;
    return 0;
}