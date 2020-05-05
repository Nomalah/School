#include <iostream>
#include <math.h>
#include <mutex>
#include "matrix.h"
#include "neuralNetwork.h"


using namespace std;

neuralNetwork::neuralNetwork(int numOfLayers, int* sizeOfLayers)
{
    this -> numOfLayers = numOfLayers;
    this -> sizeOfLayers = sizeOfLayers;
    weights = new matrix*[numOfLayers-1];
    bias = new matrix*[numOfLayers-1];
    for (int i = 0; i < numOfLayers - 1; i++)
    {
        weights[i] = new matrix(sizeOfLayers[i+1],sizeOfLayers[i], "Weights");
        (*weights[i]).randomize();
        bias[i] = new matrix(sizeOfLayers[i+1], 1, "Bias");
        (*bias[i]).randomize();
    }
}

neuralNetwork::~neuralNetwork()
{
    cout << "Neural network destuctor" << endl;
    for (int i = 0; i < numOfLayers - 1; i++)
    {
        (*weights[i]).destroyMatrix();
        delete weights[i];
        (*bias[i]).destroyMatrix();
        delete bias[i];
    }
    delete [] weights;
    delete [] bias;
    delete [] sizeOfLayers;
}

float* neuralNetwork::think(float* inputArr)
{
    matrix input(inputArr, sizeOfLayers[0], "input");
    matrix output(0,0, "output");
    for (int i = 0; i < numOfLayers-1; i++)
    {
        lock.lock();
        output.setTo((*weights[i]).dot(input));
        lock.unlock();
        output.setTo(output + (*bias[i]));
        output.mapFunc([](float v, int x, int y)
        {
            return 1/(1+exp(-v));
        });
        input = output;
    }
    input.destroyMatrix();
    output.mapFunc([](float v, int, int) -> float
    {
        return log(v/(1-v));
    });
    return output.toArray(true);
}

void neuralNetwork::train(float* trainIn, float* trainTarget)
{
    matrix input (trainIn, sizeOfLayers[0], "input");
    matrix output(0,0, "output");
    matrix** layerOutputs = new matrix*[numOfLayers];
    for (int i = 0; i < numOfLayers; i++)
    {
        layerOutputs[i] = new matrix(0, 0, "layerOutputs");
    }
    *layerOutputs[0] = input;
    lock.lock();
    for (int i = 0; i < numOfLayers-1; i++)
    {
        output.setTo((*weights[i]).dot(input));
        output.setTo(output + (*bias[i]));
        output.mapFunc([](float v, int, int) -> float
        {
            return 1/(1+exp(-v));
        });
        input = output;
        *layerOutputs[i+1] = output;
    }
    input.destroyMatrix();
    output.destroyMatrix();

    matrix targets(trainTarget, sizeOfLayers[numOfLayers-1], "targets");
    matrix** layerErrors = new matrix*[numOfLayers-1];

    for (int i = 0; i < numOfLayers - 1; i++)
    {
        layerErrors[i] = new matrix(0,0, "layerErrors");
    }

    matrix deSigmoidOut((*layerOutputs[numOfLayers-1]).rows,(*layerOutputs[numOfLayers-1]).cols, "desigmoid");
    deSigmoidOut.mapFunc([=](float v, int x, int y) -> float
    {
        return log((*layerOutputs[numOfLayers-1]).data[y][x]/(1-(*layerOutputs[numOfLayers-1]).data[y][x]));
    });

    (*layerErrors[numOfLayers-2]).setTo(targets - deSigmoidOut);
    targets.destroyMatrix();
    deSigmoidOut.destroyMatrix();

    //cout << "adjust Weights" << endl;
    for (int i = numOfLayers-1; i > 0; i--)
    {
        matrix gradient(0,0, "Gradient");
        gradient = (*layerOutputs[i]);

        gradient.mapFunc([](float v, int x, int y) -> float{return v * (1 - v);});

        gradient.setTo(gradient * (*layerErrors[i-1]));

        gradient.mapFunc([](float v, int x, int y) -> float{return v * 0.1;});

        matrix layerOutputT = (*layerOutputs[i-1]).transpose();
        matrix weightsDeltas = gradient.dot(layerOutputT);
        layerOutputT.destroyMatrix();

        (*weights[i-1]).setTo(*weights[i-1] + weightsDeltas);
        (*bias[i-1]).setTo(*bias[i-1] + gradient);
        weightsDeltas.destroyMatrix();
        gradient.destroyMatrix();
        if(i==1)
        {
            break;
        }
        matrix weightT(0,0,"weightT");
        weightT.setTo((*weights[i-1]).transpose());
        (*layerErrors[i-2]).setTo(weightT.dot(*layerErrors[i-1]));
        weightT.destroyMatrix();
    }
    lock.unlock();
    for (int i = 0; i < numOfLayers; i++)
    {
        (*layerOutputs[i]).destroyMatrix();
        delete layerOutputs[i];
    }
    delete[] layerOutputs;
    for (int i = 0; i < numOfLayers - 1; i++)
    {
        (*layerErrors[i]).destroyMatrix();
        delete layerErrors[i];
    }
    delete[] layerErrors;
    return;
}

void neuralNetwork::trainMultiple(float** trainIn, float** trainTarget, int trainSize, int iterations){
    for (int iterationNumber = 0; iterationNumber < iterations; iterationNumber++){
        int temp = rand()%trainSize;
        train(trainIn[temp],trainTarget[temp]);
    }
    return;
}

