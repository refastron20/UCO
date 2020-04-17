#ifndef DYNAMICPROGRAMMINGMETHOD_HPP
#define DYNAMICPROGRAMMINGMETHOD_HPP

#include "algorithm.hpp"

class DynamicProgrammingMethod:public Algorithm{

private:

public:
  //Constructor
  DynamicProgrammingMethod(char *fileName,int &points);

  //Destructor
  ~DynamicProgrammingMethod();

  void apply();
};
#endif
