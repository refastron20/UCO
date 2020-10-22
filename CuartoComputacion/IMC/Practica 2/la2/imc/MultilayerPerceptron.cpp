/*********************************************************************
* File  : MultilayerPerceptron.cpp
* Date  : 2020
*********************************************************************/

#include "MultilayerPerceptron.h"

#include "util.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()
#include <limits>
#include <math.h>


using namespace imc;
using namespace std;
using namespace util;

// ------------------------------
// Obtain an integer random number in the range [Low,High]
int randomInt(int Low, int High)
{
	int random;
	random = (rand()%(High+Low+1))-Low;
	return random;
}

// ------------------------------
// Obtain a real random number in the range [Low,High]
double randomDouble(double Low, double High)
{
	double random;
	random = Low + ((double) (rand())) /( (double) (RAND_MAX/(High-Low)));
	return random;
}

// ------------------------------
// Constructor: Default values for all the parameters
MultilayerPerceptron::MultilayerPerceptron()
{
	nOfLayers = 0;
	layers = NULL;
	eta = 0;
	mu = 0;
	validationRatio = 0;
	decrementFactor = 0;
}

// ------------------------------
// Allocate memory for the data structures
// nl is the number of layers and npl is a vetor containing the number of neurons in every layer
// Give values to Layer* layers
int MultilayerPerceptron::initialize(int nl, int npl[]) {
	nOfLayers = nl;
	layers = new Layer[nl];
	for (int i = 0; i < nl; i++) {
		layers[i].nOfNeurons = npl[i];
		layers[i].neurons = new Neuron[npl[i]];
	}
	for (int i = 1; i < nl - 1; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			layers[i].neurons[j].w = new double[layers[i-1].nOfNeurons +1];
			layers[i].neurons[j].wCopy = new double[layers[i-1].nOfNeurons +1];
			layers[i].neurons[j].deltaW = new double[layers[i-1].nOfNeurons +1];
			layers[i].neurons[j].lastDeltaW = new double[layers[i-1].nOfNeurons +1];
		}
	}

	if (outputFunction == 1) {
		for (int j = 0; j < layers[nOfLayers-1].nOfNeurons-1; j++) {
			layers[nOfLayers-1].neurons[j].w = new double[layers[nOfLayers-2].nOfNeurons +1];
			layers[nOfLayers-1].neurons[j].wCopy = new double[layers[nOfLayers-2].nOfNeurons +1];
			layers[nOfLayers-1].neurons[j].deltaW = new double[layers[nOfLayers-2].nOfNeurons +1];
			layers[nOfLayers-1].neurons[j].lastDeltaW = new double[layers[nOfLayers-2].nOfNeurons +1];
		}
		layers[nOfLayers-1].neurons[layers[nOfLayers-1].nOfNeurons-1].w = NULL;
		layers[nOfLayers-1].neurons[layers[nOfLayers-1].nOfNeurons-1].wCopy = NULL;
		layers[nOfLayers-1].neurons[layers[nOfLayers-1].nOfNeurons-1].deltaW = NULL;
		layers[nOfLayers-1].neurons[layers[nOfLayers-1].nOfNeurons-1].lastDeltaW = NULL;
	}else{
		for (int j = 0; j < layers[nOfLayers-1].nOfNeurons; j++) {
			layers[nOfLayers-1].neurons[j].w = new double[layers[nOfLayers-2].nOfNeurons +1];
			layers[nOfLayers-1].neurons[j].wCopy = new double[layers[nOfLayers-2].nOfNeurons +1];
			layers[nOfLayers-1].neurons[j].deltaW = new double[layers[nOfLayers-2].nOfNeurons +1];
			layers[nOfLayers-1].neurons[j].lastDeltaW = new double[layers[nOfLayers-2].nOfNeurons +1];
		}
	}

	return 1;
}


// ------------------------------
// DESTRUCTOR: free memory
MultilayerPerceptron::~MultilayerPerceptron() {
	if (layers!=NULL) {
		freeMemory();
	}
}


// ------------------------------
// Free memory for the data structures
void MultilayerPerceptron::freeMemory() {
	delete[] layers[0].neurons;
	for (int i = 1; i < nOfLayers; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			if (layers[i].neurons[j].w != NULL) {
				delete[] layers[i].neurons[j].w;
				delete[] layers[i].neurons[j].wCopy;
				delete[] layers[i].neurons[j].deltaW;
				delete[] layers[i].neurons[j].lastDeltaW;
			}
		}
		delete[] layers[i].neurons;
	}
	delete[] layers;
}

// ------------------------------
// Fill all the weights (w) with random numbers between -1 and +1
void MultilayerPerceptron::randomWeights() {
	for (int i = 1; i < nOfLayers ; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				if (layers[i].neurons[j].w != NULL) {
					layers[i].neurons[j].w[k] = randomDouble(-1, 1);
				}
			}
		}
	}
}

// ------------------------------
// Feed the input neurons of the network with a vector passed as an argument
void MultilayerPerceptron::feedInputs(double* input) {
	for (int i = 0; i < layers[0].nOfNeurons; i++) {
		layers[0].neurons[i].out = input[i];
	}
}

// ------------------------------
// Get the outputs predicted by the network (out vector of the output layer) and save them in the vector passed as an argument
void MultilayerPerceptron::getOutputs(double* output)
{
	for (int i = 0; i < layers[nOfLayers-1].nOfNeurons; i++) {
		output[i] = layers[nOfLayers-1].neurons[i].out;
	}
}

// ------------------------------
// Make a copy of all the weights (copy w in wCopy)
void MultilayerPerceptron::copyWeights() {
	for (int i = 1; i < nOfLayers ; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				if (layers[i].neurons[j].w != NULL) {
					layers[i].neurons[j].wCopy[k] = layers[i].neurons[j].w[k];
				}
			}
		}
	}
}

// ------------------------------
// Restore a copy of all the weights (copy wCopy in w)
void MultilayerPerceptron::restoreWeights() {
	for (int i = 1; i < nOfLayers ; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				if (layers[i].neurons[j].w != NULL) {
					layers[i].neurons[j].w[k] = layers[i].neurons[j].wCopy[k];
				}
			}
		}
	}
}

// ------------------------------
// Calculate and propagate the outputs of the neurons, from the first layer until the last one -->-->
void MultilayerPerceptron::forwardPropagate() {
	if (outputFunction == 0) {
		for (int i = 1; i < nOfLayers; i++) {
			for (int j = 0; j < layers[i].nOfNeurons; j++) {
				layers[i].neurons[j].net = 0;
				layers[i].neurons[j].net += layers[i].neurons[j].w[0];
				for (int k = 1; k < layers[i-1].nOfNeurons+1; k++) {
					layers[i].neurons[j].net += layers[i].neurons[j].w[k] * layers[i-1].neurons[k-1].out;
				}
				layers[i].neurons[j].net *= -1;
				layers[i].neurons[j].out = 1/(1+exp(layers[i].neurons[j].net));
			}
		}
	}else{
		double sumNet = 0;
		for (int i = 1; i < nOfLayers-1; i++) {
			for (int j = 0; j < layers[i].nOfNeurons; j++) {
				layers[i].neurons[j].net = 0;
				layers[i].neurons[j].net += layers[i].neurons[j].w[0];
				for (int k = 1; k < layers[i-1].nOfNeurons+1; k++) {
					layers[i].neurons[j].net += layers[i].neurons[j].w[k] * layers[i-1].neurons[k-1].out;
				}
				layers[i].neurons[j].net *= -1;
				layers[i].neurons[j].out = 1/(1+exp(layers[i].neurons[j].net));
			}
		}
		for (int j = 0; j < layers[nOfLayers-1].nOfNeurons-1; j++) {
			layers[nOfLayers-1].neurons[j].net = 0;
			layers[nOfLayers-1].neurons[j].net += layers[nOfLayers-1].neurons[j].w[0];
			for (int k = 1; k < layers[nOfLayers-2].nOfNeurons+1; k++) {
				layers[nOfLayers-1].neurons[j].net += layers[nOfLayers-1].neurons[j].w[k] * layers[nOfLayers-2].neurons[k-1].out;
			}
			sumNet += layers[nOfLayers-1].neurons[j].net;
		}
		layers[nOfLayers-1].neurons[layers[nOfLayers-1].nOfNeurons-1].net = 0;
		for (int j = 0; j < layers[nOfLayers-1].nOfNeurons; j++) {
			layers[nOfLayers-1].neurons[j].out = exp(layers[nOfLayers-1].neurons[j].net)/(1+exp(sumNet));
		}
	}
}

// ------------------------------
// Obtain the output error (MSE) of the out vector of the output layer wrt a target vector and return it
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
double MultilayerPerceptron::obtainError(double* target, int errorFunction) {
	double error = 0;

	if (errorFunction == 0) {
		for (int i = 0; i < layers[nOfLayers-1].nOfNeurons; i++) {
			error += (layers[nOfLayers-1].neurons[i].out - target[i]) * (layers[nOfLayers-1].neurons[i].out - target[i]);
		}
	}else{
		for (int i = 0; i < layers[nOfLayers-1].nOfNeurons; i++) {
			error += layers[nOfLayers-1].neurons[i].out * log(target[i]);
		}
	}

	error /= layers[nOfLayers-1].nOfNeurons;

	return error;
}


// ------------------------------
// Backpropagate the output error wrt a vector passed as an argument, from the last layer to the first one <--<--
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::backpropagateError(double* target, int errorFunction) {
	double sum = 0;

	if (outputFunction == 0) {
		if (errorFunction == 0) {
			for (int j = 0; j < layers[nOfLayers-1].nOfNeurons; j++) {
				layers[nOfLayers-1].neurons[j].delta = -1*(target[j] - layers[nOfLayers-1].neurons[j].out) * (layers[nOfLayers-1].neurons[j].out * (1 - layers[nOfLayers-1].neurons[j].out));
			}
		}else{
			for (int j = 0; j < layers[nOfLayers-1].nOfNeurons; j++) {
				layers[nOfLayers-1].neurons[j].delta = -1*(target[j] / layers[nOfLayers-1].neurons[j].out) * (layers[nOfLayers-1].neurons[j].out * (1 - layers[nOfLayers-1].neurons[j].out));
			}
		}
	}else{
		double sum = 0;
		int I;
		if (errorFunction == 0) {
			for (int j = 0; j < layers[nOfLayers-1].nOfNeurons; j++) {
				for (int i = 0; i < layers[nOfLayers-1].nOfNeurons; i++) {
					if (i == j) {
						I = 1;
					}else{
						I = 0;
					}
					sum += ((target[i] - layers[nOfLayers-1].neurons[i].out) * layers[nOfLayers-1].neurons[j].out * (I - layers[nOfLayers-1].neurons[i].out));
				}
				layers[nOfLayers-1].neurons[j].delta = -sum;
				sum = 0;
			}
		}else{
			for (int j = 0; j < layers[nOfLayers-1].nOfNeurons; j++) {
				for (int i = 0; i < layers[nOfLayers-1].nOfNeurons; i++) {
					if (i == j) {
						I = 1;
					}else{
						I = 0;
					}
					sum += ((target[i] / layers[nOfLayers-1].neurons[i].out) * layers[nOfLayers-1].neurons[j].out * (I - layers[nOfLayers-1].neurons[i].out));
				}
				layers[nOfLayers-1].neurons[j].delta = -sum;
				sum = 0;
			}
		}
	}

	for (int i = nOfLayers-2; i > 0 ; i--) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i+1].nOfNeurons; k++) {
				sum += layers[i+1].neurons[k].w[j+1] * layers[i+1].neurons[k].delta;
			}
			layers[i].neurons[j].delta = sum * (layers[i].neurons[j].out * (1 - layers[i].neurons[j].out));
			sum = 0;
		}
	}
}

// ------------------------------
// Accumulate the changes produced by one pattern and save them in deltaW
void MultilayerPerceptron::accumulateChange() {
	for (int i = 1; i < nOfLayers; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			if (layers[i].neurons[j].deltaW != NULL) {
				for (int k = 1; k < layers[i-1].nOfNeurons+1; k++) {
					layers[i].neurons[j].deltaW[k] = layers[i].neurons[j].deltaW[k] + layers[i].neurons[j].delta * layers[i-1].neurons[k-1].out;
				}
				layers[i].neurons[j].deltaW[0] = layers[i].neurons[j].deltaW[0] + layers[i].neurons[j].delta;
			}
		}
	}
}

// ------------------------------
// Update the network weights, from the first layer to the last one
void MultilayerPerceptron::weightAdjustment() {
	double muPerLayer = 0;
	int N = 0;
	if (online) {
		N = 1;
	}else{
		N = nOfTrainingPatterns;
	}
	for (int i = 1; i < nOfLayers; i++) {
		muPerLayer = pow(decrementFactor, -((nOfLayers-1)-i)) * mu;
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 1; k < layers[i-1].nOfNeurons+1; k++) {
				layers[i].neurons[j].w[k] = layers[i].neurons[j].w[k] - (eta * layers[i].neurons[j].deltaW[k])/N - (muPerLayer * (eta * layers[i].neurons[j].lastDeltaW[k]))/N;
			}
			layers[i].neurons[j].w[0] = layers[i].neurons[j].w[0] - (eta * layers[i].neurons[j].deltaW[0])/N - (muPerLayer * (eta * layers[i].neurons[j].lastDeltaW[0]))/N;
		}
	}
}

// ------------------------------
// Print the network, i.e. all the weight matrices
void MultilayerPerceptron::printNetwork() {
	std::cout << "NETWORK WEIGHTS" << '\n';
	std::cout << "===============" << '\n';
	for (int i = 1; i < nOfLayers; i++) {
		std::cout << "Layer " << i << '\n';
		std::cout << "------" << '\n';
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				std::cout << layers[i].neurons[j].w[k]<< " ";
			}
			std::cout  << '\n';
		}
		std::cout  << '\n';
	}
}

// ------------------------------
// Perform an epoch: forward propagate the inputs, backpropagate the error and adjust the weights
// input is the input vector of the pattern and target is the desired output vector of the pattern
// The step of adjusting the weights must be performed only in the online case
// If the algorithm is offline, the weightAdjustment must be performed in the "train" function
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::performEpoch(double* input, double* target, int errorFunction) {
	for (int i = 1; i < nOfLayers; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				if (layers[i].neurons[j].deltaW != NULL) {
					layers[i].neurons[j].deltaW[k] = 0;
				}
			}
		}
	}
	feedInputs(input);
	forwardPropagate();
	backpropagateError(target, errorFunction);
	accumulateChange();
	if (online) {
		weightAdjustment();
	}
}

// ------------------------------
// Read a dataset from a file name and return it
Dataset* MultilayerPerceptron::readData(const char *fileName) {
	Dataset *data;
	data = new Dataset;
	string aux;
	ifstream file(fileName);
	if(!file.is_open()){
		std::cerr << "Couldn't open the file" << '\n';
		exit(1);
	}
	getline(file, aux, ' ');
	data->nOfInputs = atoi(aux.c_str());
	getline(file, aux, ' ');
	data->nOfOutputs = atoi(aux.c_str());
	getline(file, aux);
	data->nOfPatterns = atoi(aux.c_str());

	nOfTrainingPatterns = data->nOfPatterns;

	data->inputs = new double*[data->nOfPatterns];
	data->outputs = new double*[data->nOfPatterns];

	for (int i = 0; i < data->nOfPatterns; i++) {
		data->inputs[i] = new double[data->nOfInputs];
		data->outputs[i] = new double[data->nOfOutputs];
	}

	int n, i = 0;
	for(int k = 0; k < data->nOfPatterns; k++){
		for (i = 0; i < data->nOfInputs ; i++) {
			getline(file, aux, ' ');
			n = atoi(aux.c_str());
			data->inputs[k][i] = n;
		}
		for (i=0; i < data->nOfOutputs-1 ; i++) {
			getline(file, aux, ' ');
			n = atoi(aux.c_str());
			data->outputs[k][i] = n;
		}
		getline(file, aux);
		n = atoi(aux.c_str());
		data->outputs[k][i] = n;

	}

	file.close();
	return data;
}


// ------------------------------
// Train the network for a dataset (one iteration of the external loop)
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::train(Dataset* trainDataset, int errorFunction) {
	int i;
	for(i=0; i<trainDataset->nOfPatterns; i++){
		performEpoch(trainDataset->inputs[i], trainDataset->outputs[i], errorFunction);
	}
	if (!online) {
		weightAdjustment();
	}
}

// ------------------------------
// Test the network with a dataset and return the error
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
double MultilayerPerceptron::test(Dataset* dataset, int errorFunction) {
	double sumError = 0;
	for (int i = 0; i < dataset->nOfPatterns; i++) {
		feedInputs(dataset->inputs[i]);
		forwardPropagate();
		sumError += obtainError(dataset->outputs[i], errorFunction);
	}
	sumError /= dataset->nOfPatterns;

	return sumError;
}


// ------------------------------
// Test the network with a dataset and return the CCR
double MultilayerPerceptron::testClassification(Dataset* dataset) {
	double CCR = 0;
	int sum = 0;
	double *obtainedOutputs;
	obtainedOutputs = new double[dataset->nOfOutputs];

	for (int i = 0; i < dataset->nOfPatterns; i++) {
		feedInputs(dataset->inputs[i]);
		forwardPropagate();
		getOutputs(obtainedOutputs);
		if (maxIndexVector(dataset->outputs[i], dataset->nOfOutputs) == maxIndexVector(obtainedOutputs, dataset->nOfOutputs)) {
			sum++;
		}
	}
	delete [] obtainedOutputs;

	CCR = 100*(sum/dataset->nOfPatterns);

	return CCR;
}


// ------------------------------
// Optional Kaggle: Obtain the predicted outputs for a dataset
void MultilayerPerceptron::predict(Dataset* dataset)
{
	int i;
	int j;
	int numSalidas = layers[nOfLayers-1].nOfNeurons;
	double * salidas = new double[numSalidas];

	cout << "Id,Category" << endl;

	for (i=0; i<dataset->nOfPatterns; i++){

		feedInputs(dataset->inputs[i]);
		forwardPropagate();
		getOutputs(salidas);

		int maxIndex = 0;
		for (j = 0; j < numSalidas; j++)
			if (salidas[j] >= salidas[maxIndex])
				maxIndex = j;

		cout << i << "," << maxIndex << endl;

	}
}



// ------------------------------
// Run the traning algorithm for a given number of epochs, using trainDataset
// Once finished, check the performance of the network in testDataset
// Both training and test MSEs should be obtained and stored in errorTrain and errorTest
// Both training and test CCRs should be obtained and stored in ccrTrain and ccrTest
// errorFunction=1 => Cross Entropy // errorFunction=0 => MSE
void MultilayerPerceptron::runBackPropagation(Dataset * trainDataset, Dataset * testDataset, int maxiter, double *errorTrain, double *errorTest, double *ccrTrain, double *ccrTest, int errorFunction)
{
	int countTrain = 0;

	// Random assignment of weights (starting point)
	randomWeights();

	double minTrainError = 0;
	int iterWithoutImproving = 0;
	nOfTrainingPatterns = trainDataset->nOfPatterns;

	Dataset * validationDataset = NULL;
	double validationError = 0, previousValidationError = 0;
	int iterWithoutImprovingValidation = 0;

	Dataset *newTrainData;

	newTrainData = new Dataset;
	validationDataset = new Dataset;

	// Generate validation data
	if(validationRatio > 0 && validationRatio < 1){
		validationDataset->nOfInputs = trainDataset->nOfInputs;
		validationDataset->nOfOutputs = trainDataset->nOfOutputs;
		validationDataset->nOfPatterns = trainDataset->nOfPatterns*validationRatio;
		validationDataset->inputs = new double*[validationDataset->nOfPatterns];
		validationDataset->outputs = new double*[validationDataset->nOfPatterns];

		for (int i = 0; i < validationDataset->nOfPatterns; i++) {
			validationDataset->inputs[i] = new double[validationDataset->nOfInputs];
			validationDataset->outputs[i] = new double[validationDataset->nOfOutputs];
		}

		newTrainData->nOfInputs = trainDataset->nOfInputs;
		newTrainData->nOfOutputs = trainDataset->nOfOutputs;
		newTrainData->nOfPatterns = trainDataset->nOfPatterns - validationDataset->nOfPatterns;
		newTrainData->inputs = new double*[newTrainData->nOfPatterns];
		newTrainData->outputs = new double*[newTrainData->nOfPatterns];

		for (int i = 0; i < newTrainData->nOfPatterns; i++) {
			newTrainData->inputs[i] = new double[newTrainData->nOfInputs];
			newTrainData->outputs[i] = new double[newTrainData->nOfOutputs];
		}

		int *randomVector = integerRandomVectorWithoutRepeating(0,trainDataset->nOfPatterns-1,trainDataset->nOfPatterns);
		int i;


		for(i = 0; i < validationDataset->nOfPatterns; i++) {
			validationDataset->inputs[i] = trainDataset->inputs[randomVector[i]];
			validationDataset->outputs[i] = trainDataset->outputs[randomVector[i]];
		}
		for (int j = 0; j < newTrainData->nOfPatterns; j++) {
			newTrainData->inputs[j] = trainDataset->inputs[randomVector[i]];
			newTrainData->outputs[j] = trainDataset->outputs[randomVector[i]];
			i++;
		}
	}else{
		newTrainData = trainDataset;
	}

	// Learning
	do {

		train(newTrainData,errorFunction);

		double trainError = test(newTrainData,errorFunction);
		if(countTrain==0 || trainError < minTrainError){
			minTrainError = trainError;
			copyWeights();
			iterWithoutImproving = 0;
		}
		else if( (trainError-minTrainError) < 0.00001)
			iterWithoutImproving = 0;
		else
			iterWithoutImproving++;

		if(iterWithoutImproving==50){
			cout << "We exit because the training is not improving!!"<< endl;
			restoreWeights();
			countTrain = maxiter;
		}

		countTrain++;

		if(validationDataset!=NULL){
			if(previousValidationError==0)
				previousValidationError = 999999999.9999999999;
			else
				previousValidationError = validationError;
			validationError = test(validationDataset,errorFunction);
			if(validationError < previousValidationError)
				iterWithoutImprovingValidation = 0;
			else if((validationError-previousValidationError) < 0.00001)
				iterWithoutImprovingValidation = 0;
			else
				iterWithoutImprovingValidation++;
			if(iterWithoutImprovingValidation==50){
				cout << "We exit because validation is not improving!!"<< endl;
				restoreWeights();
				countTrain = maxiter;
			}
		}

		cout << "Iteration " << countTrain << "\t Training error: " << trainError << "\t Validation error: " << validationError << endl;

	} while ( countTrain<maxiter );

	if (validationDataset != NULL) {
		delete [] validationDataset;
	}

	if ( (iterWithoutImprovingValidation!=50) && (iterWithoutImproving!=50))
		restoreWeights();

	cout << "NETWORK WEIGHTS" << endl;
	cout << "===============" << endl;
	printNetwork();

	cout << "Desired output Vs Obtained output (test)" << endl;
	cout << "=========================================" << endl;
	for(int i=0; i<testDataset->nOfPatterns; i++){
		double* prediction = new double[testDataset->nOfOutputs];

		// Feed the inputs and propagate the values
		feedInputs(testDataset->inputs[i]);
		forwardPropagate();
		getOutputs(prediction);
		for(int j=0; j<testDataset->nOfOutputs; j++)
			cout << testDataset->outputs[i][j] << " -- " << prediction[j] << " ";
		cout << endl;
		delete[] prediction;

	}

	*errorTest=test(testDataset,errorFunction);;
	*errorTrain=minTrainError;
	*ccrTest = testClassification(testDataset);
	*ccrTrain = testClassification(trainDataset);

}

// -------------------------
// Optional Kaggle: Save the model weights in a textfile
bool MultilayerPerceptron::saveWeights(const char * fileName)
{
	// Object for writing the file
	ofstream f(fileName);

	if(!f.is_open())
		return false;

	// Write the number of layers and the number of layers in every layer
	f << nOfLayers;

	for(int i = 0; i < nOfLayers; i++)
	{
		f << " " << layers[i].nOfNeurons;
	}
	f << " " << outputFunction;
	f << endl;

	// Write the weight matrix of every layer
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				if(layers[i].neurons[j].w!=NULL)
				    f << layers[i].neurons[j].w[k] << " ";

	f.close();

	return true;

}


// -----------------------
// Optional Kaggle: Load the model weights from a textfile
bool MultilayerPerceptron::readWeights(const char * fileName)
{
	// Object for reading a file
	ifstream f(fileName);

	if(!f.is_open())
		return false;

	// Number of layers and number of neurons in every layer
	int nl;
	int *npl;

	// Read number of layers
	f >> nl;

	npl = new int[nl];

	// Read number of neurons in every layer
	for(int i = 0; i < nl; i++)
	{
		f >> npl[i];
	}
	f >> outputFunction;

	// Initialize vectors and data structures
	initialize(nl, npl);

	// Read weights
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				if(!(outputFunction==1 && (i==(nOfLayers-1)) && (k==(layers[i].nOfNeurons-1))))
					f >> layers[i].neurons[j].w[k];

	f.close();
	delete[] npl;

	return true;
}
