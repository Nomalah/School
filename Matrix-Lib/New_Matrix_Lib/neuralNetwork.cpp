#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>

#include "matrix.h"
#include "neuralNetwork.h"

#define LOG(x) std::cout << x << std::endl

void print(std::vector<double> to_print){
    for(double i : to_print)
        std::cout << i << ' ';
    std::cout << std::endl;
}


inline void randomize(matrix& rhs){
    rhs.map_function([](double val) -> double{
        return rand() / (RAND_MAX + 1.);
    });
}

neural_network::neural_network(std::vector<unsigned> layer_sizes)
    : layer_sizes(layer_sizes){
    weights.reserve(layer_sizes.size()-1);
    bias.reserve(layer_sizes.size()-1);
    for (int i = 0; i < layer_sizes.size()-1; i++){
        weights.push_back(matrix(layer_sizes[i], layer_sizes[i+1]));
        bias.push_back(matrix(1, layer_sizes[i+1]));
        randomize(weights[i]);
        randomize(bias[i]);
    }
}

neural_network::~neural_network(){
    weights.clear();
    bias.clear();
    layer_sizes.clear();
}

std::vector<double> neural_network::think(std::vector<double> input_arr){
    matrix input{input_arr};

    matrix output;
    for(int i = 0; i < layer_sizes.size()-1; i++){
        output = dot(weights[i], input); 
        output = output + bias[i]; 
        output.map_function(neural_network::sigmoid);
        input = output; 
    }

    output.map_function(neural_network::desigmoid);
    return output;
}

void neural_network::train(std::vector<double>& training_data, std::vector<double>& training_target){
    matrix input{training_data};

    std::vector<matrix> layerOutputs(layer_sizes.size());

    layerOutputs[0] = input; // copy assignment
    
    for (int i = 0; i < layer_sizes.size()-1; i++){
        matrix output{dot(weights[i], input) + bias[i]};
        output.map_function(neural_network::sigmoid);
        input = output;
        layerOutputs[i+1] = output;
    }
    
    matrix targets{training_target};

    std::vector<matrix> layerErrors(layer_sizes.size()-1);

    matrix deSigmoidOut(layerOutputs[layer_sizes.size()-1]);
    deSigmoidOut.map_function(neural_network::desigmoid);

    layerErrors[layer_sizes.size()-2] = targets - deSigmoidOut; // one move

    for (int i = layer_sizes.size()-1; i > 0; i--){
        matrix gradient{layerOutputs[i]};
        
        gradient.map_function([](double val) -> double{
            return val * (1 - val) * 0.1;
        });

        gradient = gradient * layerErrors[i-1]; // one move

        weights[i-1] = weights[i-1] + dot(gradient, transpose(layerOutputs[i-1]));
        bias[i-1] = bias[i-1] + gradient;

        if(i==1)
            break;

        layerErrors[i-2] = dot(transpose(weights[i-1]), layerErrors[i-1]); // 2 moves
    }
}

