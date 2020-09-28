#include "funcionesMatematicas.hpp"

#include <vector>
#include <cmath>

double factorial(const int n){
  if (n==0) {
    return 1;
  }else{
    return n*factorial(n-1);
  }
}

double media(const std::vector<int> &v){
  double sum=0;
  for (unsigned int i = 0; i < v.size(); i++) {
    sum+=v[i];
  }
  return sum/v.size();
}

double varianza(const std::vector<int> &v){
  double med=media(v),sum=0;
  for (unsigned int i = 0; i < v.size(); i++) {
    sum+=pow(v[i]-med,2);
  }
  sum/=(v.size()-1);

  return sum;
}
