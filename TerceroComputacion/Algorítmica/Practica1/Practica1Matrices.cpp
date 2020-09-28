#include <vector>
#include <cstdlib>
#include <fstream>
#include "ClaseTiempo.cpp"
#include "Practica1Matrices.hpp"
#include "Practica1Vectores.hpp"
/*
  Se he de introducir la función de multiplicar matrices en sistemaEcuaciones.hpp para que el programa funcione
*/
#include "sistemaEcuaciones.hpp"


void funcionMatrices(){
  vector <vector <double> > m1, m2;
  vector <double> tiemposReales, n, tiemposEstimados, a;
  int min, max, inc;
  Clock time;

  cout << "Orden mínimo: ";
  cin >> min;
  cout << "\n" <<"Orden máximo: ";
  cin >> max;
  cout << "\n" <<"Incremento:";
  cin >> inc;


  for (int i = min; i <= max; i+=inc) {
    //reservamos espacio para los elementos de las matrices
    m1.resize(i);
    m2.resize(i);
    for (int j = 0; j < i; j++) {
      m1[j].resize(i);
      m2[j].resize(i);
    }


    //Para cada repetición rellenamos las matrices con valores nuevos
    rellenarMatriz(m1);
    rellenarMatriz(m2);
    //iniciamos el reloj
    time.start();
    multiplicarMatrices(m1,m2,m1);
    //paramos el reloj
    if (time.isStarted())
  	{
  		time.stop();
  	}
    //introducimos el tiempo en el vector de tiempos reales
    tiemposReales.push_back(time.elapsed());
    //introducimos el número de elementos en el vector de ns
    n.push_back(i);

    //liberamos el espacio reservado en las matrices
    m1.clear();
    m2.clear();
    for (int j = 0; j < i; j++) {
      m1[j].clear();
      m2[j].clear();
    }
  }

  //Hacemos el ajuste polinomico
  ajustePolinomico(n,tiemposReales,a);
  //Calculamos los timepos estimados
  calcularTiemposEstimadosPolinomico(n,a,tiemposEstimados);


  //Guardamos en un fichero los n, tiempos reales y los estimados
  std::ofstream fich("tiemposMatrices.txt");
  if (!fich.is_open()) {
    std::cerr << "No se pudo abrir el fichero, saliendo..." << '\n';
  }
  for (unsigned int i = 0; i < n.size(); i++) {
    fich<<n[i]<<" "<<tiemposReales[i]<<" "<<tiemposEstimados[i]<<std::endl;
  }
  fich.close();

  //Mostramos la ecuación de la curva ajustada y el coeficiente de determinación
  std::cout << "Ecuación de la curva ajustada= " <<a[0]<<"+"<<a[1]<<"n+"<<a[2]<<"n^2+"<<a[3]<<"n^3"<< '\n';
  double coef;
  //usamos la función de los vectores ya que no hace falta cambiar nada
  coef=calcularCoeficienteDeterminacion(tiemposReales,tiemposEstimados);
  std::cout << "coeficiente de determinación= " <<coef<< '\n';

  double NumeroN=1;
  coef=0;
  //calculamos el tiempo para multiplicar dos matrices de orden n
  //Si introduce 0 salimos
  do{
    std::cout << "Para que N quiere calcular el tiempo?" << '\n';
    std::cin >> NumeroN;
    if (NumeroN!=0) {
      coef=calcularTiempoEstimadoPolinomico(NumeroN,a);
      std::cout << "Tardaría " <<coef<<" días para multiplicar dos matrices de orden "<<NumeroN<< '\n';
    }
  }while(NumeroN!=0);

}

//función para rellenar una matriz
void rellenarMatriz(vector<vector <double> > &v){
  for (int i = 0; i < (int) v.size(); i++) {
    for (int j = 0; j < (int) v[0].size(); j++) {
      v[i][j]=(double)(rand()%11)/100+0.95;
    }
  }
}

//función que realiza el ajuste polinómico a una curva n³
void ajustePolinomico(const vector <double> &n, const vector <double> &tiemposReales, vector <double> &a){
  double x=0,x2=0,x3=0,x4=0,x5=0,x6=0,t=0,xt=0,xt2=0,xt3=0;
  //calculamos los sumatorios necesarios
  for (int i = 0; i <(int) n.size(); i++) {
    x+=n[i];
    x2+=pow(n[i],2);
    x3+=pow(n[i],3);
    x4+=pow(n[i],4);
    x5+=pow(n[i],5);
    x6+=pow(n[i],6);
    t+=tiemposReales[i];
    xt+=n[i]*tiemposReales[i];
    xt2+=pow(n[i],2)*tiemposReales[i];
    xt3+=pow(n[i],3)*tiemposReales[i];
  }
  vector < vector < double > > A;
  A = vector< vector< double > >(4, vector< double > (4));

  //rellenamos la matriz A
  A[0][0]=n.size();
  A[0][1]=x;
  A[0][2]=x2;
  A[0][3]=x3;
  A[1][0]=x;
  A[1][1]=x2;
  A[1][2]=x3;
  A[1][3]=x4;
  A[2][0]=x2;
  A[2][1]=x3;
  A[2][2]=x4;
  A[2][3]=x5;
  A[3][0]=x3;
  A[3][1]=x4;
  A[3][2]=x5;
  A[3][3]=x6;

  vector < vector < double > > B;
  B = vector< vector< double > >(4, vector< double > (1));

  //Rellenamos la matriz B
  B[0][0]=t;
  B[1][0]=xt;
  B[2][0]=xt2;
  B[3][0]=xt3;

  vector < vector < double > > X;
  X = vector< vector< double > >(4, vector< double > (4));

  resolverSistemaEcuaciones(A,B,4,X);

  a.push_back(X[0][0]);
  a.push_back(X[1][0]);
  a.push_back(X[2][0]);
  a.push_back(X[3][0]);
}

//calculamos los tiempos estimados para el polinomio de grado 3
void calcularTiemposEstimadosPolinomico(const vector <double> &n, const vector <double> &a, vector <double> &tiemposEstimados){
  int m=n.size();
  tiemposEstimados.resize(m);
  for (int i = 0; i < m; i++) {
    tiemposEstimados[i]=a[0]+a[1]*n[i]+a[2]*pow(n[i],2)+a[3]*pow(n[i],3);
  }
}

//calculamos el tiempo para un polinomio de grado 3 y una n específica
double calcularTiempoEstimadoPolinomico(const double &n, const vector <double> &a){
    return ((a[0]+a[1]*n+a[2]*pow(n,2)+a[3]*pow(n,3))/(double)(86400000000));
}
