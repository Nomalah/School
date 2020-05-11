#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>
#include "matrix.h"

class neural_network{
	public:
		neural_network(std::vector<unsigned> layer_sizes);
    	~neural_network();
    	std::vector<double> think(std::vector<double> input_arr);
    	void train(std::vector<double> training_data, std::vector<double> training_target);
	private:
    	std::vector<unsigned> layer_sizes;
    	std::vector<matrix> weights;
    	std::vector<matrix> bias;
};

#endif // NEURALNETWORK_H
