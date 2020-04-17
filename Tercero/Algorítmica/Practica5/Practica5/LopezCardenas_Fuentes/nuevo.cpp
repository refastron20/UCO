







void DynamicProgrammingMethod::apply(){
  calculateSummations();

  int nPointsDC = getOriginalCurve().getNumberPointsDigitalCurve();
  int nPointsA = getNumberPointsPolygonalApproximation() + 1;

  std::vector<std::vector<double> > E;
  std::vector<std::vector<int> > father;

  E = std::vector<std::vector<double> > (nPointsDC, std::vector<double> nPointsA);
  father = std::vector<std::vector<int> > (nPointsDC, std::vector<int> nPointsA);

  for (int i = 0; i < nPointsDC; i++) {
    for (int j = 0; j < nPointsA; j++) {
      M[i][j] = 499999999;
      father[i][j] = -1;
    }
  }
  E[1][1] = 0;

  for (int m = 2; m < nPointsA; m++) {
    for (int n = m; n < nPointsDC; n++) {
        double min;

        if (m - 1 < n) {
          min = E[m-1][m-1]+ abs(calculateISEValue(m-2, n-1));
          father[n][m] = m - 1;
          E[n][m] = min;
        }
        for (int j = n; j < m; j++) {
          double aux = E[j][m-1]+abs(calculateISEValue(j-1, n-1));
          if (aux < min) {
            father[n][m]= j;
            E[n][m]= aux;
            min = aux;
          }
        }
    }
  }

  std::vector<int> v;
  v.push_back(nPointsDC-1);
  for (size_t i = nPointsA; i >1; i--) {
    v.insert(v.begin(), father[anterior][i]-1);
    anterior = father[anterior][i];
  }

  setDominantPointsPosition(v);
  calculatePolygonalApproximation();
}









void dynamicprogrammingmethod::apply(){
  calculateSummations();

  int nPointsDC = getOriginalCurve().getNumberPointsDigitalCurve();
  int nPointsA = getNumberPointsPolygonalApproximation() + 1;

  std::vector<std::vector<double> > E;
  std::vector<std::vector<int> > father;

  E = std::vector<std::vector<double>> (nPointsDC, std::vector<double> nPointsA);
  father = std::vector<std::vector<int>> (nPointsDC, std::vector<int> nPointsA);

  for (size_t i = 0; i < nPointsDC; i++) {
    for (size_t j = 0; j < nPointsA; j++) {
      E[i][j] = 499999999;
      father[i][j] = -1;
    }
  }

  E[1][1] = 0;

  for (size_t m = 2; m < nPointsA; m++) {
    for (size_t n = m; n < nPointsDC; n++) {
      double min;

      if (m -1 < n) {
        min = E[m-1][m-1]+ abs(calculateISEValue(m-2, n-1));
        E[n][m]= min;
        father = m-1;
      }
      for (size_t j = n; j < m; j++) {
        double aux = E[j][m-1]+ abs(calculateISEValue(j-1,n-1));
        if (aux < min) {
          E[n][m] = aux;
          father[n][m] = j;
          min = aux;
        }
      }
    }
  }

  std::vector<int> v;
  v.push_back(nPointsDC -1);
  int anterior = nPointsDC -1;
  for (size_t i = nPointsA -1; i > 1; i--) {
    v.insert(v.begin(), father[anterior][i]-1);
    anterior = father[anterior][i];
  }

  setDominantPointsPosition(v);
  calculatePolygonalApproximation();

}
