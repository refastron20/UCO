#include "place.hpp"
#include <cmath>

bool place(const int &k, const std::vector<int> &x){
  for (int i = 1; i < k; i++) {
    if (x[i]==x[k] or abs(x[i]-x[k])==abs(i-k)) {
      return false;
    }
  }
  return true;
}
