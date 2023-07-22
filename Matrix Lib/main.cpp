#include <iostream>
#include <math.h>
#include <string>
#include <thread>
#include "neuralNet.h"
#include "matrix.h"

using namespace std;


int main()
{
    int numOfLayers = 3;
    int layerSizes[3] = {2,4,1};
    neuralNetwork evaluation(numOfLayers,layerSizes);
    float test[2] = {1,0};
    //cout << "here";
    matrix out (evaluation.think(test), 1, "out");
    //cout << "here";
    out.print();
    float listData [4][2] = {{0,0},{1,0},{0,1},{1,1}};
    float listTarget [4][1] = {{0},{1},{1},{0}};

    float** trainingData = new float* [4];
    float** trainingTarget = new float* [4];
    for (int i = 0; i < 4; i++){
        trainingData[i] = new float [2];
        listData[i][0] = listData[i][0]; listData[i][1] = listData[i][1];
        trainingTarget[i] = new float [1];
        listTarget[i][0] = listTarget[i][0];
    }
    //= {{0,0},{1,0},{0,1},{1,1}};
//= {{0},{1},{1},{0}};
    int numOfThreads = 1;
    thread trainingThreads[numOfThreads];

    for (int i = 0; i < numOfThreads; i++)
    {
        trainingThreads[i] = thread(&neuralNetwork::trainMultiple, &evaluation, trainingData, trainingTarget, 4, 100000);
        cout << i << "\r";
    }
    for (int i = 0; i < numOfThreads; i++)
    {
        (trainingThreads[i]).join();
    }
    out.fromArray(evaluation.think(test), 1);
    out.print();
	out.destroyMatrix();
    return 0;
}
