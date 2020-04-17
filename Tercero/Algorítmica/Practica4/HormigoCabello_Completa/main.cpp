#include "algorithm.hpp"
#include "suppressioncollinearpointsmethod.hpp"
#include "greedymethod.hpp"
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
   //It creates a pointer to algorithm class to use overload in execution
   Algorithm *a;

   char fileNameDC[100], fileNamePA[100];
   int n;

   int op;

   do {
     std::cout << "1.- Collinear Suppression Method" << '\n';
     std::cout << "2.- Greedy Method" << '\n';
     std::cout << "0.- Exit" << '\n';
     std::cin >> op;

     if (op==0) {
        std::cout << "Exiting.." << '\n';
     }  else if (op<0 or op>2) {
       std::cout << "Wrong option" << '\n';
     }else if (op!=0) {
       cout << "Digital curve to obtain polygonal approximation: ";
       cin >> fileNameDC;
       if (op==1) {
         //Creates a new class for method and the pointer points to the new class
         a = new CollinearSuppressionMethod(fileNameDC);
       }else if (op==2) {
         std::cout << "Number of points: ";
         std::cin >> n;
         a = new GreedyMethod(fileNameDC,20);
       }
       a->apply();
       cout << "Number of points of the polygonal approxmation: " << a->getNumberPointsPolygonalApproximation() << endl;
       cout << "The value of ISE is " << a->getISE() << endl;

       DigitalCurve aP = a->getPolygonalApproximation();

       cout << "Name of file to save the polygonal approximation: ";
       cin >> fileNamePA;

       aP.saveDigitalCurve(fileNamePA);
     }
  } while(op!=0);

   return 0;
}
