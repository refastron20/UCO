#include "reinasBacktracking.hpp"
#include <vector>
#include <cmath>
#include "place.hpp"

void BacktrackingQueens(const int &n, std::vector<std::vector<int>> &solutions){
  std::vector<int> solution(n+1);
  solution[1]=0;
  int k=1;
  while (k>0) {
    solution[k]++;
    while (solution[k]<=n and place(k,solution)==false) {
      solution[k]++;
    }
    if (solution[k]<=n) {
      if (k==n) {
        solutions.push_back(solution);
      }else{
        k++;
        solution[k]=0;
      }
    }else{
      k--;
    }
  }
}
