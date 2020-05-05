#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <mutex>
#include "matrix.h"

using namespace std;

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
    	mutex lock;
};
#endif // MATRIX_H
