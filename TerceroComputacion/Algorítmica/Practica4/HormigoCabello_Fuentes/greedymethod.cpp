
#include <vector>    // necesario para el contenedor vector
#include "algorithm.hpp"
#include "greedymethod.hpp"
#include "digitalcurve.hpp"
//#include "heapvectorMasood.hpp"
//#include "nodoMasood.hpp"



using namespace std;

/* Functions for Collinear suppression method */

//Constructor.

GreedyMethod::GreedyMethod(char *fileName, int numberPointsPolygonalApproximation)
{
  //A digital curve is created to load the digital curve in file
	DigitalCurve dc(fileName);

  //Digital curve as saved as original curve
  setOriginalCurve(dc);

  //Set the number of points of the polygonal approximation
  setNumberPointsPolygonalApproximation(numberPointsPolygonalApproximation);
}

//Destructor
GreedyMethod::~GreedyMethod()
{
}

void GreedyMethod::apply()
{
	this->calculateSummations();
	//eliminamos los puntos alineados
  this->collinearPointsElimination();

	//calculamos de cuanto en cuanto se tienen que coger los puntos
	int salto=(this->getDominantPointsPosition().size()/(this->getNumberPointsPolygonalApproximation()-1));

	//vector con las posiciones de los puntos finales
	std::vector<int> posiciones;

	//Cogemos todas las posiciones del vector completo
	for (unsigned int i = 0; i < this->getDominantPointsPosition().size(); i+=salto) {
		posiciones.push_back(this->getDominantPointsPosition()[i]);
	}
	posiciones.push_back(this->getDominantPointsPosition()[0]);

	for (size_t i = 0; i < posiciones.size(); i++) {
	}

	long double errorActual,errorOpcional;
	int posicionAux;
	for (unsigned int i = 1; i < posiciones.size()-1; i++) {
		posicionAux=posiciones[i];
		errorActual=this->calculateISEValue(posiciones[i-1],posiciones[i])+this->calculateISEValue(posiciones[i],posiciones[i+1]);
		for (unsigned int j = posiciones[i-1]+1; j < posiciones[i+1]; j++) {
			errorOpcional=this->calculateISEValue(posiciones[i-1],j)+this->calculateISEValue(j,posiciones[i+1]);
			if (errorOpcional<errorActual){
				posicionAux=j;
			}
		}
		posiciones[i]=posicionAux;
	}
	errorActual=this->calculateISEValue(posiciones[posiciones.size()-2],posiciones[0])+this->calculateISEValue(posiciones[0],posiciones[1]);
	int j=posiciones[posiciones.size()-2]+1;
	while (j==-1) {
		errorOpcional=this->calculateISEValue(posiciones.size()-2,j)+this->calculateISEValue(j,posiciones[1]);
		if (errorOpcional<errorActual){
			posicionAux=j;
		}
		if (j==this->getDominantPointsPosition()[this->getDominantPointsPosition().size()-1]) {
			j=0;
		}
		if (j==posiciones[1]-1) {
			j=-1;
		}
		j++;
	}
	posiciones[0]=posiciones[posiciones.size()-1]=posicionAux;

	this->setDominantPointsPosition(posiciones);
	this->calculatePolygonalApproximation();
}
