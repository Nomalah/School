#include <iostream>
#include <math.h>
#include <vector>
#include <initializer_list>
#include <stdlib.h>

#include "matrix.h"
#include "neuralNetwork.h"

#define LOG(x) std::cout << x << std::endl

void print(std::vector<double> to_print){
    for(double i : to_print)
        std::cout << i << ' ';
    std::cout << std::endl;
}


void randomize(matrix& rhs){
    rhs.map_function([](double val) -> double{
        return (double)rand() / RAND_MAX * 2 - 1;
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
    matrix input(1, layer_sizes[0]);
    
    {
        unsigned i = 0;
        input.map_function([&](double val) -> double{
            return input_arr[i++];
        });
    }

    matrix output;
    for(int i = 0; i < layer_sizes.size()-1; i++){
        output = dot(weights[i], input);
        output = output + bias[i];
        output.map_function([](double val){
            return 1/(1+exp(-val));
        });
        input = output;
    }

    output.map_function([](double val) -> double{
        return log(val/(1-val));
    });
    return output;
}

void neural_network::train(std::vector<double> training_data, std::vector<double> training_target){
    matrix input (1, layer_sizes[0]);

    {
        unsigned i = 0;
        input.map_function([&i, &training_data](double val) -> double{
            return training_data[i++];
        });
    }

    matrix output;
    
    std::vector<matrix> layerOutputs;
    layerOutputs.reserve(layer_sizes.size());
    for (int i = 0; i < layer_sizes.size(); i++){
        layerOutputs.push_back(matrix());
    }
    layerOutputs[0] = input;
    
    for (int i = 0; i < layer_sizes.size()-1; i++){
        output = dot(weights[i], input);
        output = output + bias[i];
        output.map_function([](double val) -> double{
            return 1/(1+exp(-val));
        });
        input = output;
        layerOutputs[i+1] = output;
    }
    
    matrix targets(1, layer_sizes[layer_sizes.size()-1]);

    {
        unsigned i = 0;
        targets.map_function([&i, &training_target](double val) -> double{
            return training_target[i++];
        });
    }

    std::vector<matrix> layerErrors;
    layerErrors.reserve(layer_sizes.size()-1);

    for (int i = 0; i < layer_sizes.size()-1; i++){
        layerErrors.push_back(matrix());
    }

    matrix deSigmoidOut(layerOutputs[layer_sizes.size()-1]);
    deSigmoidOut.map_function([](double val) -> double{
        return log(val/(1-val));
    });

    layerErrors[layer_sizes.size()-2] = targets - deSigmoidOut;

    //cout << "adjust Weights" << endl;
    for (int i = layer_sizes.size()-1; i > 0; i--){
        matrix gradient (layerOutputs[i]);
        //gradient = (*layerOutputs[i]);

        gradient.map_function([](double val) -> double{
            return val * (1 - val);
        });

        gradient = gradient * layerErrors[i-1];

        gradient.map_function([](double val) -> double{
            return val * 0.1;
        });

        matrix layerOutputT = transpose(layerOutputs[i-1]);
        matrix weightsDeltas = dot(gradient, layerOutputT);

        weights[i-1] = weights[i-1] + weightsDeltas;
        bias[i-1] = bias[i-1] + gradient;
    
        if(i==1)
            break;

        matrix weightT(transpose(weights[i-1]));
        layerErrors[i-2] = dot(weightT, layerErrors[i-1]);
    }
    return;
}

