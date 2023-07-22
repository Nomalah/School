#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

class neuralNetwork{
    public:
    	neuralNetwork(int initLayers, float initLayerSizes[]){
    	    learningRate = 0.1;

    		numOfLayers = initLayers;

    		layerSizes = new int [numOfLayers];
    		for (int i = 0; i < numOfLayers; i++){
    			layerSizes[i] = initLayerSizes[i];
			}

    		srand((unsigned int) time(0));
    		weights = new float** [numOfLayers-1];
			for (int i = 0; i < numOfLayers-1; i++){
    			weights[i] = new float* [layerSizes[i]];
				for (int j = 0; j < layerSizes[i]; j++){
     				weights [i][j] = new float [layerSizes[i+1]];
					for (int r = 0; r < layerSizes[i+1]; r++){
    					weights [i][j][r] = (float)rand()/(float)RAND_MAX;
					}
				}
			}
		}

		void setlr (float lr){
            learningRate = lr;
		}

		float* think (float inputs[]){
		    float* lastLayerOutput = new float [layerSizes[0]];
			for (int i = 0; i < layerSizes[0]; i++){
    			lastLayerOutput[i] = inputs[i];
			}
			for (int i = 1; i < numOfLayers; i++){
    			float* thisLayerOutput = new float [layerSizes[i]];
				for (int x = 0; x < layerSizes[i]; x++){
					float total = 0;
    				for (int y = 0; y < layerSizes[i-1]; y++){
    					total += lastLayerOutput[y] * weights[i-1][y][x];
					}
					thisLayerOutput[x] = 1 / (1 + exp(total));
				}
				lastLayerOutput = thisLayerOutput;
			}
			return lastLayerOutput;
		}

		void train(float inputs[], float answers[]){
		    float** layerOutputs = new float* [numOfLayers];
		    for (int i = 0; i < numOfLayers; i++){
    			layerOutputs[i] = new float[layerSizes[i]];
			}
			for (int i = 0; i < layerSizes[0]; i++){
    			layerOutputs[0][i] = inputs[i];
			}
			for (int i = 1; i < numOfLayers; i++){
				for (int x = 0; x < layerSizes[i]; x++){
					float total = 0;
    				for (int y = 0; y < layerSizes[i-1]; y++){
    					total += layerOutputs[i-1][y] * weights[i-1][y][x];
					}
					layerOutputs[i][x] = 1 / (1 + exp(total));
				}
			}

		    float* guess = layerOutputs[numOfLayers-1];
		    float** layerErrors = new float* [numOfLayers];
		    for (int i = 0; i < numOfLayers; i++){
    			layerErrors[i] = new float[layerSizes[i]];
		    }

			for (int i = 0; i < layerSizes[numOfLayers-1]; i++){
    			layerErrors [numOfLayers-1][i] = answers[i]-guess[i];
			}
			for (int i = numOfLayers-1; i > 0; i--){
                for (int y = 0; y < layerSizes[i-1]; y++){
                    float total = 0;
    				for (int x = 0; x < layerSizes[i]; x++){
    				    total += layerErrors[i][x] * weights[i-1][y][x];
					}
                    layerErrors[i-1][y] = total;
				}
				for (int x = 0; x < layerSizes[i]; x++){
    				for (int y = 0; y < layerSizes[i-1]; y++){
    				    weights[i-1][y][x] += layerErrors[i][x] * learningRate * layerOutputs[i-1][y]*(layerOutputs[i][x]*(1-layerOutputs[i][x]));
					}
				}
			}
		}
	private:
		int numOfLayers;
		int* layerSizes;
		float*** weights;
		float learningRate;
};


int main() {
	float evalLayerSizes [3] = {2,2,1};
	neuralNetwork evaluation(3,evalLayerSizes);

	float testData[2] = {1,1};
	float* guessedOutput = evaluation.think(testData);
    cout << "Before Training:" << guessedOutput[0] << endl;
	float trainData[4][2] = {{0,0},{1,0},{0,1},{1,1}};
	float trainAnswers[4][1] = {{0},{1},{1},{0}};
	for (int i = 0; i<1000000; i++){
        int random = rand()%4;
        evaluation.train(trainData[random],trainAnswers[random]);
	}
    guessedOutput = evaluation.think(testData);
    cout << "After Training:" << guessedOutput[0] << endl;
	return 0;
}
