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
	for (int i = 1; i < nl; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			layers[i].neurons[j].w = new double[layers[i-1].nOfNeurons +1];
			layers[i].neurons[j].wCopy = new double[layers[i-1].nOfNeurons +1];
			layers[i].neurons[j].deltaW = new double[layers[i-1].nOfNeurons +1];
			layers[i].neurons[j].lastDeltaW = new double[layers[i-1].nOfNeurons +1];
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
			delete[] layers[i].neurons[j].w;
			delete[] layers[i].neurons[j].wCopy;
			delete[] layers[i].neurons[j].deltaW;
			delete[] layers[i].neurons[j].lastDeltaW;
		}
		delete[] layers[i].neurons;
	}
	delete[] layers;
}

// ------------------------------
// Feel all the weights (w) with random numbers between -1 and +1
void MultilayerPerceptron::randomWeights() {
	for (int i = 1; i < nOfLayers ; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				layers[i].neurons[j].w[k] = ((double) (rand()%20001)/10000) -1;
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
// Get the outputs predicted by the network (out vector the output layer) and save them in the vector passed as an argument
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
				layers[i].neurons[j].wCopy[k] = layers[i].neurons[j].w[k];
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
				layers[i].neurons[j].w[k] = layers[i].neurons[j].wCopy[k];
			}
		}
	}
}

// ------------------------------
// Calculate and propagate the outputs of the neurons, from the first layer until the last one -->-->
void MultilayerPerceptron::forwardPropagate() {
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
}

// ------------------------------
// Obtain the output error (MSE) of the out vector of the output layer wrt a target vector and return it
double MultilayerPerceptron::obtainError(double* target) {
	double MSE = 0;

	for (int i = 0; i < layers[nOfLayers-1].nOfNeurons; i++) {
		MSE += (layers[nOfLayers-1].neurons[i].out - target[i]) * (layers[nOfLayers-1].neurons[i].out - target[i]);
	}
	MSE /= layers[nOfLayers-1].nOfNeurons;

	return MSE;
}


// ------------------------------
// Backpropagate the output error wrt a vector passed as an argument, from the last layer to the first one <--<--
void MultilayerPerceptron::backpropagateError(double* target) {
	double sum = 0;
	for (int j = 0; j < layers[nOfLayers-1].nOfNeurons; j++) {
		layers[nOfLayers-1].neurons[j].delta = -1*(target[j] - layers[nOfLayers-1].neurons[j].out) * (layers[nOfLayers-1].neurons[j].out * (1 - layers[nOfLayers-1].neurons[j].out));
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
			for (int k = 1; k < layers[i-1].nOfNeurons+1; k++) {
				layers[i].neurons[j].deltaW[k] = layers[i].neurons[j].deltaW[k] + layers[i].neurons[j].delta * layers[i-1].neurons[k-1].out;
			}
			layers[i].neurons[j].deltaW[0] = layers[i].neurons[j].deltaW[0] + layers[i].neurons[j].delta;
		}
	}
}

// ------------------------------
// Update the network weights, from the first layer to the last one
void MultilayerPerceptron::weightAdjustment() {
	for (int i = 1; i < nOfLayers; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 1; k < layers[i-1].nOfNeurons+1; k++) {
				layers[i].neurons[j].w[k] = layers[i].neurons[j].w[k] - eta * layers[i].neurons[j].deltaW[k] - mu * (eta * layers[i].neurons[j].lastDeltaW[k]);
			}
			layers[i].neurons[j].w[0] = layers[i].neurons[j].w[0] - eta * layers[i].neurons[j].deltaW[0] - mu * (eta * layers[i].neurons[j].lastDeltaW[0]);
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
void MultilayerPerceptron::performEpochOnline(double* input, double* target) {
	for (int i = 1; i < nOfLayers; i++) {
		for (int j = 0; j < layers[i].nOfNeurons; j++) {
			for (int k = 0; k < layers[i-1].nOfNeurons+1; k++) {
				layers[i].neurons[j].deltaW[k] = 0;
			}
		}
	}
	feedInputs(input);
	forwardPropagate();
	backpropagateError(target);
	accumulateChange();
	weightAdjustment();
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
// Perform an online training for a specific trainDataset
void MultilayerPerceptron::trainOnline(Dataset* trainDataset) {
	int i;
	for(i=0; i<trainDataset->nOfPatterns; i++){
		performEpochOnline(trainDataset->inputs[i], trainDataset->outputs[i]);
	}
}

// ------------------------------
// Test the network with a dataset and return the MSE
double MultilayerPerceptron::test(Dataset* testDataset) {
	double sumError = 0;
	for (int i = 0; i < testDataset->nOfPatterns; i++) {
		feedInputs(testDataset->inputs[i]);
		forwardPropagate();
		sumError += obtainError(testDataset->outputs[i]);
	}
	sumError /= testDataset->nOfPatterns;

	return sumError;
}


// Optional - KAGGLE
// Test the network with a dataset and return the MSE
// Your have to use the format from Kaggle: two columns (Id y predictied)
void MultilayerPerceptron::predict(Dataset* pDatosTest)
{
	int i;
	int j;
	int numSalidas = layers[nOfLayers-1].nOfNeurons;
	double * obtained = new double[numSalidas];

	cout << "Id,Predicted" << endl;

	for (i=0; i<pDatosTest->nOfPatterns; i++){

		feedInputs(pDatosTest->inputs[i]);
		forwardPropagate();
		getOutputs(obtained);

		cout << i;

		for (j = 0; j < numSalidas; j++)
			cout << "," << obtained[j];
		cout << endl;

	}
}

// ------------------------------
// Run the traning algorithm for a given number of epochs, using trainDataset
// Once finished, check the performance of the network in testDataset
// Both training and test MSEs should be obtained and stored in errorTrain and errorTest
void MultilayerPerceptron::runOnlineBackPropagation(Dataset * trainDataset, Dataset * pDatosTest, int maxiter, double *errorTrain, double *errorTest)
{
	int countTrain = 0;

	// Random assignment of weights (starting point)
	randomWeights();

	double minTrainError = 0, lastValidationError = 0;
	int iterWithoutImproving, iterWithoutImprovingV = 0;
	double testError = 0;

	double validationError = 0;

	Dataset *newTrainData, *validationTrainData;

	newTrainData = new Dataset;
	validationTrainData = new Dataset;
	// Generate validation data
	if(validationRatio > 0 && validationRatio < 1){
		validationTrainData->nOfInputs = trainDataset->nOfInputs;
		validationTrainData->nOfOutputs = trainDataset->nOfOutputs;
		validationTrainData->nOfPatterns = trainDataset->nOfPatterns*validationRatio;
		validationTrainData->inputs = new double*[validationTrainData->nOfPatterns];
		validationTrainData->outputs = new double*[validationTrainData->nOfPatterns];

		for (int i = 0; i < validationTrainData->nOfPatterns; i++) {
			validationTrainData->inputs[i] = new double[validationTrainData->nOfInputs];
			validationTrainData->outputs[i] = new double[validationTrainData->nOfOutputs];
		}

		newTrainData->nOfInputs = trainDataset->nOfInputs;
		newTrainData->nOfOutputs = trainDataset->nOfOutputs;
		newTrainData->nOfPatterns = trainDataset->nOfPatterns - validationTrainData->nOfPatterns;
		newTrainData->inputs = new double*[newTrainData->nOfPatterns];
		newTrainData->outputs = new double*[newTrainData->nOfPatterns];

		for (int i = 0; i < newTrainData->nOfPatterns; i++) {
			newTrainData->inputs[i] = new double[newTrainData->nOfInputs];
			newTrainData->outputs[i] = new double[newTrainData->nOfOutputs];
		}

		int *randomVector = integerRandomVectoWithoutRepeating(0,trainDataset->nOfPatterns-1,trainDataset->nOfPatterns);
		int i;


		for(i = 0; i < validationTrainData->nOfPatterns; i++) {
			validationTrainData->inputs[i] = trainDataset->inputs[randomVector[i]];
			validationTrainData->outputs[i] = trainDataset->outputs[randomVector[i]];
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

		trainOnline(newTrainData);
		double trainError = test(newTrainData);
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


		// Check validation stopping condition and force it
		// BE CAREFUL: in this case, we have to save the last validation error, not the minimum one
		// Apart from this, the way the stopping condition is checked is the same than that
		// applied for the training set
		if (validationRatio > 0 && validationRatio < 1) {
			validationError = test(validationTrainData);
			if(countTrain==0 || validationError < lastValidationError){
				copyWeights();
				iterWithoutImprovingV = 0;
			}
			else if( (validationError-lastValidationError) < 0.00001)
				iterWithoutImprovingV = 0;
			else
				iterWithoutImprovingV++;

			if(iterWithoutImprovingV==50){
				cout << "We exit because the validation is not improving!!"<< endl;
				restoreWeights();
				countTrain = maxiter;
			}
			lastValidationError = validationError;
		}

		countTrain++;

		cout << "Iteration " << countTrain << "\t Training error: " << trainError << "\t Validation error: " << validationError << endl;
	} while ( countTrain<maxiter );
	if (validationTrainData != NULL) {
		delete [] validationTrainData;
	}

	cout << "NETWORK WEIGHTS" << endl;
	cout << "===============" << endl;

	printNetwork();

	cout << "Desired output Vs Obtained output (test)" << endl;
	cout << "=========================================" << endl;
	for(int i=0; i<pDatosTest->nOfPatterns; i++){
		double* prediction = new double[pDatosTest->nOfOutputs];

		// Feed the inputs and propagate the values
		feedInputs(pDatosTest->inputs[i]);

		forwardPropagate();

		getOutputs(prediction);

		for(int j=0; j<pDatosTest->nOfOutputs; j++)
			cout << pDatosTest->outputs[i][j] << " -- " << prediction[j] << " ";
		cout << endl;
		delete [] prediction;

		testError = test(pDatosTest);

	}

	*errorTest=testError;
	*errorTrain=minTrainError;

}

// Optional Kaggle: Save the model weights in a textfile
bool MultilayerPerceptron::saveWeights(const char * archivo)
{
	// Object for writing the file
	ofstream f(archivo);

	if(!f.is_open())
		return false;

	// Write the number of layers and the number of layers in every layer
	f << nOfLayers;

	for(int i = 0; i < nOfLayers; i++)
		f << " " << layers[i].nOfNeurons;
	f << endl;

	// Write the weight matrix of every layer
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				f << layers[i].neurons[j].w[k] << " ";

	f.close();

	return true;

}


// Optional Kaggle: Load the model weights from a textfile
bool MultilayerPerceptron::readWeights(const char * archivo)
{
	// Object for reading a file
	ifstream f(archivo);

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
		f >> npl[i];

	// Initialize vectors and data structures
	initialize(nl, npl);

	// Read weights
	for(int i = 1; i < nOfLayers; i++)
		for(int j = 0; j < layers[i].nOfNeurons; j++)
			for(int k = 0; k < layers[i-1].nOfNeurons + 1; k++)
				f >> layers[i].neurons[j].w[k];

	f.close();
	delete[] npl;

	return true;
}
