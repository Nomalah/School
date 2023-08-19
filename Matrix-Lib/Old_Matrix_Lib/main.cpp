#include <iostream>
#include <math.h>
#include <time.h>
#include <cstdlib>
#include <string>
#include "neuralNetwork.h"
#include "matrix.h"

using namespace std;


int main()
{
    int numOfLayers = 3;
    int layerSizes[3] = {2,4,1};
    neuralNetwork evaluation(numOfLayers, layerSizes);
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
        trainingData[i][0] = listData[i][0]; 
        trainingData[i][1] = listData[i][1];
        trainingTarget[i] = new float[1];
        listTarget[i][0] = listTarget[i][0];
    }
    srand(time(0));
    for(int i = 0; i < 100000; i++){
        int r = rand() % 4;
        evaluation.train(trainingData[r], listTarget[r]);
    }
    for(int i = 0; i < 4; i++){
        out.fromArray(evaluation.think(listData[i]), 1);
        out.print();
    }
	out.destroyMatrix();
    return 0;
}
