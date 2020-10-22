//============================================================================
// Introducción a los Modelos Computacionales
// Name        : practica1.cpp
// Author      : Pedro A. Gutiérrez
// Version     :
// Copyright   : Universidad de Córdoba
//============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>    // To obtain current time time()
#include <cstdlib>  // To establish the seed srand() and generate pseudorandom numbers rand()
#include <string.h>
#include <math.h>
#include <float.h> // For DBL_MAX

#include "imc/MultilayerPerceptron.h"


using namespace imc;
using namespace std;

int main(int argc, char **argv) {
	// Process the command line
  bool tflag = 0, Tflag = 0, wflag = 0, pflag = 0, oflag = 0;
  char *Tvalue = NULL, *wvalue = NULL;
  int c;
  int fvalue = 0, svalue = 0;

  opterr = 0;

  char *trainFileName = NULL;

  int niter = 1000;
  int nOfLayers = 1, nOfNeurons = 5;
  double eta = 0.1, mu = 0.9, valRatio = 0.0, decrementFactor = 1;

    // a: Option that requires an argument
    // a:: The argument required is optional
    while ((c = getopt(argc, argv, "t:i:l:n:e:m:v:h:d:T:w:pof:s")) != -1)
    {
        // The parameters needed for using the optional prediction mode of Kaggle have been included.
        // You should add the rest of parameters needed for the lab assignment.
        switch(c){
            case 't':
                tflag = true;
                trainFileName = optarg;
                break;
            case 'i':
                niter = atoi(optarg);
                break;
            case 'l':
                nOfLayers = atoi(optarg);
                break;
            case 'h':
                nOfNeurons = atoi(optarg);
                break;
            case 'e':
                eta = atof(optarg);
                break;
            case 'm':
                mu = atof(optarg);
                break;
            case 'v':
                valRatio = atof(optarg);
                break;
            case 'd':
                decrementFactor = atof(optarg);
                break;
            case 'T':
                Tflag = true;
                Tvalue = optarg;
                break;
            case 'w':
                wflag = true;
                wvalue = optarg;
                break;
            case 'p':
                pflag = true;
                break;
            case 'o':
                oflag = true;
                break;
            case 'f':
                fvalue = atoi(optarg);
                break;
            case 's':
                svalue = 1;
                break;
            case '?':
                if (optopt == 't' || optopt == 'i' || optopt == 'l' || optopt == 'h' || optopt == 'e' ||
                    optopt == 'm' || optopt == 'v' || optopt == 'd' ||
                    optopt == 'T' || optopt == 'w' || optopt == 'p' || optopt == 'f')
                    fprintf (stderr, "The option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                             "Unknown character `\\x%x'.\n",
                             optopt);
                return EXIT_FAILURE;
            default:
                return EXIT_FAILURE;
        }
    }

    std::cerr << "Train file: "<< trainFileName <<", test file: "<< Tvalue <<", iteraciones: "<< niter <<", layers: "<< nOfLayers <<
    ", neurons: "<< nOfNeurons <<", eta: "<< eta <<", mu: "<< mu << ", f: " << decrementFactor << ", v: " << valRatio <<
    ", o: "<< oflag << ", f: " << fvalue << ", s: " << svalue << '\n';

    if (tflag == false) {
      std::cerr << "You must provide a train file" << '\n';
      return EXIT_FAILURE;
    }

    if (Tflag == false) {
      std::cerr << "You must provide a test file" << '\n';
      return EXIT_FAILURE;
    }



    if (!pflag) {
        //////////////////////////////////
        // TRAINING AND EVALUATION MODE //
        //////////////////////////////////

        // Multilayer perceptron object
    	MultilayerPerceptron mlp;

      // Parameters of the mlp. For example, mlp.eta = value
      mlp.eta = eta;
      mlp.mu = mu;
      mlp.decrementFactor = decrementFactor;
      mlp.validationRatio = valRatio;
      mlp.online = oflag;
      mlp.outputFunction = svalue;

    	// Type of error considered
    	int error = fvalue; // This should be completed

    	// Maximum number of iterations
    	int maxIter = niter; // This should be completed

        // Read training and test data: call to mlp.readData(...)
        Dataset * trainDataset = mlp.readData(trainFileName);

      	Dataset * testDataset = mlp.readData(Tvalue);

        // Initialize topology vector
        int layers = nOfLayers+2;
      	int * topology = new int[layers]; // This should be corrected

        topology[0] = trainDataset->nOfInputs;
        for (int i = 1; i < layers-1; i++) {
          topology[i] = nOfNeurons;
        }
        topology[layers-1] = trainDataset->nOfOutputs;
          // Initialize the network using the topology vector
          mlp.initialize(layers,topology);

		// Seed for random numbers
		int seeds[] = {1,2,3,4,5};
		double *trainErrors = new double[5];
		double *testErrors = new double[5];
		double *trainCCRs = new double[5];
		double *testCCRs = new double[5];
		double bestTestError = DBL_MAX;
		for(int i=0; i<5; i++){
			cout << "**********" << endl;
			cout << "SEED " << seeds[i] << endl;
			cout << "**********" << endl;
			srand(seeds[i]);
			mlp.runBackPropagation(trainDataset,testDataset,maxIter,&(trainErrors[i]),&(testErrors[i]),&(trainCCRs[i]),&(testCCRs[i]),error);
			cout << "We end!! => Final test CCR: " << testCCRs[i] << endl;

			// We save the weights every time we find a better model
			if(wflag && testErrors[i] <= bestTestError)
			{
				mlp.saveWeights(wvalue);
				bestTestError = testErrors[i];
			}
		}


		double trainAverageError = 0, trainStdError = 0;
		double testAverageError = 0, testStdError = 0;
		double trainAverageCCR = 0, trainStdCCR = 0;
		double testAverageCCR = 0, testStdCCR = 0;

        // Obtain training and test averages and standard deviations

		cout << "WE HAVE FINISHED WITH ALL THE SEEDS" << endl;

		cout << "FINAL REPORT" << endl;
		cout << "*************" << endl;
	    cout << "Train error (Mean +- SD): " << trainAverageError << " +- " << trainStdError << endl;
	    cout << "Test error (Mean +- SD): " << testAverageError << " +- " << testStdError << endl;
	    cout << "Train CCR (Mean +- SD): " << trainAverageCCR << " +- " << trainStdCCR << endl;
	    cout << "Test CCR (Mean +- SD): " << testAverageCCR << " +- " << testStdCCR << endl;
		return EXIT_SUCCESS;
    } else {

        //////////////////////////////
        // PREDICTION MODE (KAGGLE) //
        //////////////////////////////

        // You do not have to modify anything from here.

        // Multilayer perceptron object
        MultilayerPerceptron mlp;

        // Initializing the network with the topology vector
        if(!wflag || !mlp.readWeights(wvalue))
        {
            cerr << "Error while reading weights, we can not continue" << endl;
            exit(-1);
        }

        // Reading training and test data: call to mlp.readData(...)
        Dataset *testDataset;
        testDataset = mlp.readData(Tvalue);
        if(testDataset == NULL)
        {
            cerr << "The test file is not valid, we can not continue" << endl;
            exit(-1);
        }

        mlp.predict(testDataset);

        return EXIT_SUCCESS;

	}
}
