
#include <vector>    // necesario para el contenedor vector
#include "algorithm.hpp"
#include "dynamicprogrammingmethod.hpp"
#include "digitalcurve.hpp"
//#include "heapvectorMasood.hpp"
//#include "nodoMasood.hpp"

using namespace std;

/* Functions for Collinear suppression method */

//Constructor.

DynamicProgrammingMethod::DynamicProgrammingMethod(char *fileName, int numberPointsPolygonalApproximation){
	//A digital curve is created to load the digital curve in file
	DigitalCurve dc(fileName);

	//Digital curve as saved as original curve
	setOriginalCurve(dc);

	//Set the number of points of the polygonal approximation
	setNumberPointsPolygonalApproximation(numberPointsPolygonalApproximation);
}

//Destructor
DynamicProgrammingMethod::~DynamicProgrammingMethod()
{
}

void DynamicProgrammingMethod::apply(){
	calculateSummations();

	int nPointsDC = getOriginalCurve().getNumberPointsDigitalCurve();
	int nPointsA = getNumberPointsPolygonalApproximation() + 1;
	vector<vector<double> > E;
	vector<vector<int> > father;

	//relleno las matrices

	E = vector<vector<double> >(nPointsDC, vector<double>(nPointsA));
	father = vector<vector<int> >(nPointsDC, vector<int>(nPointsA));/*+1*/

	//E y father
	for(int i=0; i< nPointsDC; i++){
		for(int j=0; j<nPointsA; j++){
			E[i][j] = 499999999;
			father[i][j] = -1;
		}
	}
	E[1][1] = 0;

	for(int m=2; m<nPointsA; m++){
		for(int n=m; n<nPointsDC; n++){
			//En principio el minimo es el primero
			double min;

			if(m-1 < n){
				min = E[m-1][m-1] + abs(calculateISEValue(m-2, n-1));
				father[n][m] = m-1;
				E[n][m] = min;
			}
			for(int j=m; j<n; j++){
				double aux = E[j][m-1] + abs(calculateISEValue(j-1, n-1));
				if(aux < min){
					father[n][m] = j;
					E[n][m] = aux;
					min = aux;
				}
			}
		}
	}

	vector<int> aux;
	aux.push_back(nPointsDC-1);
	int anterior = nPointsDC-1; //-1 porque es 0 index
	for(int i=nPointsA-1; i>1; i--){
		aux.insert(aux.begin(), father[anterior][i]-1);
		anterior = father[anterior][i];
	}

	setDominantPointsPosition(aux);
	calculatePolygonalApproximation();
}