/**********************************************************************
 * MPI-based vector sorting (quicksort)
 *********************************************************************/


#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <time.h>

#define N               400        /* number of elements in matrix */

MPI_Status status;

int v[N];

void quicksort(const int izq,const int der, int *v){
  int i = izq;
  int j = der;
  int mitad = v[(i+j)/2];
  do {

    while (v[i]<mitad)
      i++;

    while (v[j]>mitad)
      j--;

    if (i<=j) {
      int aux = v[i];
      v[i] = v[j];
      v[j] = aux;
      i++;
      j--;
    }
  } while(i<=j);
  if (izq<j)
    quicksort(izq,j,v);
  if (i<der)
    quicksort(i,der,v);
}

int main(int argc, char **argv)
{
  int numtasks,taskid,numworkers,source,dest,rows,offset,i,j,k;
  srand(time(NULL));
  float t_init, t_final, t_total

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

  numworkers = numtasks-1;

  /*---------------------------- master ----------------------------*/
  if (taskid == 0) {

    for (i=0; i<N; i++) {
      v[i] = rand()%100;
    }

    t_ini = clock();

    //dividimos los elementos entre los trabajadores
    nElements = N/numworkers;
    //offset es el elemento por el que empezarán a ordenar los trabajadores
    offset = 0;

    for (dest=1; dest<=numworkers; dest++)
    {
      //Enviamos offset
      MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
      //Enviamos el número de elementos sobre los que operará el trabajador dest
      MPI_Send(&nElements, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
      //Eniamos las filas de la matriz a que vamos a multiplicar
      MPI_Send(&v[offset], nElements, MPI_INT,dest,1, MPI_COMM_WORLD);
      //aumentamos el offset para el siguiente trabajador
      offset += nElements;
    }

    /* wait for results from all worker tasks */
    for (i=1; i<=numworkers; i++)
    {
      source = i;
      //recibimos el offset
      MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
      //recibimos el número de filas que ha multiplicado el trabajador source
      MPI_Recv(&nElements, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
      //recibimos las filas multiplicadas por source
      MPI_Recv(&v[offset], nElements, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
    }

    numworkers /= 2;
    nElements = N/numworkers;
    offset = 0;

    for (dest=1; dest<=numworkers; dest++)
    {
      //Enviamos offset
      MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
      //Enviamos el número de elementos sobre los que operará el trabajador dest
      MPI_Send(&nElements, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
      //Eniamos las filas de la matriz a que vamos a multiplicar
      MPI_Send(&v[offset], nElements, MPI_INT,dest,1, MPI_COMM_WORLD);
      //aumentamos el offset para el siguiente trabajador
      offset += nElements;
    }

    for (i=1; i<=numworkers; i++)
    {
      source = i;
      //recibimos el offset
      MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
      //recibimos el número de filas que ha multiplicado el trabajador source
      MPI_Recv(&nElements, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
      //recibimos las filas multiplicadas por source
      MPI_Recv(&v[offset], nElements, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
    }

    quicksort(0,N-1, v);

    t_final = clock();
    t_total = (t_ini-t_final)/CLOCKS_PER_SEC;

    printf("Here is the result vector:\n");
    printf("{");
    for (i=0; i<N; i++) {
        printf("%d ", v[i]);
    }
    printf("}\n");
    fprintf(stdout,"Time = %f\n", t_total);

  }

  /*---------------------------- worker----------------------------*/
  if (taskid > 0) {
    //la fuente es el programa padre
    source = 0;
    //recibimos el offset
    MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
    //recibimos el número de fiulas a multiplicar
    MPI_Recv(&nElements, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
    //recibimos las filas a multiplicar y las guardamos en a
    MPI_Recv(&v, nElements, MPI_INT, source, 1, MPI_COMM_WORLD, &status);

    quicksort(offset, nElements-1, v);

    //enviamos la información
    MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(&nElements, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(&v, nElements, MPI_INT, 0, 2, MPI_COMM_WORLD);
  }

  MPI_Finalize();
}
