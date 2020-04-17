#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "reinasLasVegas.hpp"
#include "place.hpp"


bool LasVegasQueens(const int &n,std::vector<int> &solution){
  srand(time(NULL));
  solution.resize(n+1);
  std::vector<int> ok;
  int counter;
  for (unsigned int i = 1; i <= n; i++) {
    solution[i]=0;
  }
  for (int k = 1; k <= n; k++) {
    counter = 0;
    ok.clear();
    for (int j = 1; j <= n; j++) {
      solution[k]=j;
      if (place(k,solution)==true) {
        counter++;
        ok.push_back(j);
      }
    }
    if (counter==0){
      k=n;
    }else{
      int pos=ok[rand()%counter];
      solution[k]=pos;
    }
  }
  if (counter==0) {
    return false;
  }else{
    return true;
  }
}
