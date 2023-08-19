#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "matrix.h"
#include "neuralNetwork.h"

using namespace std;

double randMToN(double M, double N)
{
    return M + (rand() / ( RAND_MAX / (N-M) ) ) ;  
}

int main(){
    // seed the random number gen
    srand(time(NULL));
    
    // 2 inputs, 4 hidden nodes, 1 output
    neural_network my_net({2, 4, 1});

    vector<vector<double>> test_inputs = {{8, 2}, {2, 0}, {5, 7}, {2, 2}};
    vector<vector<double>> test_outputs = {{16}, {0}, {35}, {4}};

    for(int i = 0; i < 4; i++){
        cout << "Input: " << test_inputs[i][0] << ", " << test_inputs[i][1] << ": ";
        cout << my_net.think(test_inputs[i])[0] << endl;
    }

    cout << "\ntraining...\n\n";

    // Train 1 million times
    for(int i = 0; i < 10; i++){
        vector<double> training_inputs = {randMToN(0.0f, 1000.0f), randMToN(0.0f, 1000.0f)};
        vector<double> training_outputs = {training_inputs[0] * training_inputs[1]};
        my_net.train(training_inputs, training_outputs);
        cout << "Input: " << test_inputs[0][0] << ", " << test_inputs[0][1] << ": ";
        cout << my_net.think(test_inputs[0])[0] << '\r';
    }

    for(int i = 0; i < 4; i++){
        cout << "Input: " << test_inputs[i][0] << ", " << test_inputs[i][1] << ": ";
        cout << my_net.think(test_inputs[i])[0] << endl;
    }
    return 0;
}