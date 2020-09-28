#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <fstream>
#include "ClaseTiempo.cpp"
#include "Practica1Vectores.hpp"
#include "sistemaEcuaciones.hpp"

//TODO Arreglar

using namespace std;

void funcionVector(){
  Clock time;
  vector <int> v;
  vector <double> tiemposReales, n, tiemposEstimados;
  int min, max, inc, rep, m,sum=0;
  double media=0.0,a0,a1;

  //Se piden por teclado las variables necesarias
  cout << "Numero mínimo de n: ";
  cin >> min;
  cout << "\n" <<"Numero máximo de n: ";
  cin >> max;
  cout << "\n" <<"Incremento:";
  cin >> inc;
  cout << "\n" <<"Numero de repeticiones por cada valor de n:";
  cin >> rep;

  //se dimensiona el vector
  v.resize(max);
  m=max;

  //Comprobamos que la función quicksort ordena bien el vector
  rellenaVector(v);
  quicksort(0,m-1,v);
  assert(estaOrdenado(v));


  //iniciamos el bucle de repeticiones
  for (int i = min; i <= max; i+=inc) {
    //reservamos espacio para los elementos
    v.resize(i);
    m=v.size();
    sum=0;
    media=0.0;
    for (int j = 0; j < rep; j++) {
      //Para cada repetición rellenamos el vector con valores nuevos
      rellenaVector(v);
      //iniciamos el reloj
      time.start();
      quicksort(0,m-1,v);
      //paramos el reloj
      if (time.isStarted())
    	{
    		time.stop();
    	}
      //vamos sumando el tiempo de las repeticiones
      sum+=time.elapsed();
    }
    //hacemos la media de los tiempos y los introducimos al vector tiempos
    media=(double)sum/(double)rep;
    tiemposReales.push_back(media);
    //introducimos el número de elementos en el vector de ns
    n.push_back(i);
    v.clear();
  }

  //Hacemos el ajuste de la función para sacar a0 y a1
  ajusteNlogN(n,tiemposReales,a0,a1);
  //calculamos los tiempos estimados para cada n
  calcularTiemposEstimadosNlogN(n,a0,a1,tiemposEstimados);


  //Guardamos en un fichero los n, tiempos reales y los estimados
  std::ofstream fich("tiempos.txt");
  if (!fich.is_open()) {
    std::cerr << "No se pudo abrir el fichero, saliendo..." << '\n';
  }
  for (unsigned int i = 0; i < n.size(); i++) {
    fich<<n[i]<<" "<<tiemposReales[i]<<" "<<tiemposEstimados[i]<<std::endl;
  }
  fich.close();

  //Mostramos la ecuación de la curva ajustada y el coeficiente de determinación
  std::cout << "Ecuación de la curva ajustada= " <<a0<<"+"<<a1<<"nlogn"<< '\n';
  double coef;
  coef=calcularCoeficienteDeterminacion(tiemposReales,tiemposEstimados);
  std::cout << "coeficiente de determinación= " <<coef<< '\n';

  double NumeroN=1;
  coef=0;
  //calculamos el tiempo para ordenar un vector de N elementos que introduce el usuario por teclado
  //Si introduce 0 salimos
  do{
    std::cout << "Para que N quiere calcular el tiempo?" << '\n';
    std::cin >> NumeroN;
    if (NumeroN!=0) {
      coef=calcularTiempoEstimadoNlogN(NumeroN,a0,a1);
      std::cout << "Tardaría " <<coef<<" días para ordenar un vector de "<<NumeroN<<" elementos"<< '\n';
    }
  }while(NumeroN!=0);
}

void rellenaVector(vector <int> &v){
  int n=v.size();
  v.clear();
  //rellenamos el vector con números aleatorios
  for (int i = 0; i < n; i++) {
    v[i]=rand()%10000;
  }
}

//Algoritmo de ordenación quicksort
void quicksort(int izq, int der, vector <int> &v )
{
int i, j, x , aux;
i = izq;
j = der;
x = v[ (izq + der) /2 ];
    while(i<=j){
        while( (v[i] < x) )
        {
            i++;
        }

        while( (x < v[j]))
        {
            j--;
        }

        if( i <= j )
        {
            aux = v[i];
            v[i]=v[j];
            v[j] = aux;
            i++;
            j--;
        }

    }

    if( izq < j )
        quicksort(izq, j,v );
    if( i < der )
        quicksort(i, der,v );
}

//función que comprueba si está ordenado
bool estaOrdenado(const vector <int> &v){
  //recorremos el vector y comprobamos si el elemento anterior al actual es menor
  //si no lo es retornamos falso
  for(unsigned int i=1; i< v.capacity();i++){
    if (v[i-1]>v[i]) {
      return false;
    }
  }
  //si esta ordenado se retorna verdad
  return true;
}

//Función de ajuste de la curva con cambio z=nlogn
void ajusteNlogN(vector <double> &n, vector <double> &tiemposReales, double &a0, double &a1){
  int m=n.size();
  double x=0, t=0, xt=0, aux=0, x2=0.0;

  //recorremos el vector n haciendo el cambio de variable en aux
  //En cada variable acumulamos las distintas variables que necesitaremos para la matriz
  //del sistema de ecuaciones
  for (int i = 0; i < m; i++) {
    aux=n[i]*log10(n[i]);
    x+=aux;
    x2+=pow(aux,2);
    t+=tiemposReales[i];
    xt+=aux*tiemposReales[i];
  }

  vector < vector < double > > A;
  A = vector< vector< double > >(2, vector< double > (2));

  //rellenamos la matriz A
  A[0][0]=m;
  A[0][1]=x;
  A[1][0]=x;
  A[1][1]=x2;

  vector < vector < double > > B;
  B = vector< vector< double > >(2, vector< double > (1));

  //Rellenamos la matriz B
  B[0][0]=t;
  B[1][0]=xt;

  vector < vector < double > > X;
  X = vector< vector< double > >(2, vector< double > (2));

  //Resolvemos el sistema y le asignamos el valor a a0 y a1
  resolverSistemaEcuaciones(A,B,2,X);
  a0=X[0][0];
  a1=X[1][0];
}

//Función que calcula los tiempos estimados para cada n
void calcularTiemposEstimadosNlogN(const vector <double> &n, const double &a0, const double &a1, vector <double> &tiemposEstimados){
  //Para calcular los tiempos estimados simplemente sustituimos en nuestra función
  //de ajuste de curva los n y nuestros a0 y a1 anteriormente calculados
  int m=n.size();
  tiemposEstimados.resize(m);
  for (int i = 0; i < m; i++) {
    tiemposEstimados[i]=a0+(a1*n[i]*log10(n[i]));
  }
}

//Función que calcula el coeficiente de determinación
double calcularCoeficienteDeterminacion(const vector <double> &tiemposReales, const vector <double> &tiemposEstimados){
  double suma1=0.0, suma2=0.0, media1=0.0, media2=0.0;
  //calculamos el sumatorio de los tiempos reales y estimados
  for (size_t i = 0; i < tiemposReales.size(); i++) {
    suma1+=tiemposReales[i];
    suma2+=tiemposEstimados[i];
  }

  //con los sumatorios podemos obtener la media
  media1=suma1/tiemposReales.size();
  media2=suma2/tiemposEstimados.size();
  suma1=0;suma2=0;

  //Seguimos la fórmula de la varianza sumatorio(x-media)/n-1
  for (size_t i = 0; i < tiemposReales.size(); i++) {
    suma1+=pow(tiemposReales[i]-media1,2);
    suma2+=pow(tiemposEstimados[i]-media2,2);
  }
  suma1/=(tiemposReales.size()-1);
  suma2/=(tiemposEstimados.size()-1);

  //devolvemos la división de las varianzas, es decir, el coeficiente de determinación
  return suma2/suma1;
}

//Función que calcula el tiempo estimado para una n concreta
double calcularTiempoEstimadoNlogN(const double &n, const double &a0, const double &a1){
  return ((a0+a1*n*log10(n))/(double)(86400000000));
}
