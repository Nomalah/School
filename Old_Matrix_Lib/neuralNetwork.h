#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <mutex>
#include "matrix.h"

class neuralNetwork
{
	public:
		neuralNetwork(int numOfLayers, int* sizeOfLayers);
    	~neuralNetwork();
    	float* think(float* inputArr);
    	void train(float* trainIn, float* trainTarget);
    	void trainMultiple(float** trainIn, float** trainTarget, int trainSize, int iterations);
	private:
    	int numOfLayers;
    	int* sizeOfLayers;
    	matrix** weights;
    	matrix** bias;
    	std::mutex lock;
};
#endif // MATRIX_H
