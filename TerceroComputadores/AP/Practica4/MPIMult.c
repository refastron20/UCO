/**********************************************************************
 * MPI-based matrix multiplication AxB=C
 *********************************************************************/


#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <time.h>

#define N               4000        /* number of rows and columns in matrix */

MPI_Status status;

double a[N][N],b[N][N],c[N][N];

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
      for (j=0; j<N; j++) {
        a[i][j]= rand()%100;
        b[i][j]= rand()%100;
      }
    }

    t_ini = clock();

    //dividimos las filas de la matriz a entre los trabajadores
    rows = N/numworkers;
    //offset es la fila por la que empezarán a multiplicar
    offset = 0;

    for (dest=1; dest<=numworkers; dest++)
    {
      //Enviamos offset
      MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
      //Enviamos el número de filas sobre las que operará el trabajador dest
      MPI_Send(&rows, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
      //Eniamos las filas de la matriz a que vamos a multiplicar
      MPI_Send(&a[offset][0], rows*N, MPI_DOUBLE,dest,1, MPI_COMM_WORLD);
      //enviamos b entera ya que no la estamos paralelizando
      MPI_Send(&b, N*N, MPI_DOUBLE, dest, 1, MPI_COMM_WORLD);
      //aumentamos el offset para el siguiente trabajador
      offset += rows;
    }

    /* wait for results from all worker tasks */
    for (i=1; i<=numworkers; i++)
    {
      source = i;
      //recibimos el offset
      MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
      //recibimos el número de filas que ha multiplicado el trabajador source
      MPI_Recv(&rows, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
      //recibimos las filas multiplicadas por source
      MPI_Recv(&c[offset][0], rows*N, MPI_DOUBLE, source, 2, MPI_COMM_WORLD, &status);
    }

    t_final = clock();
    t_total = (t_ini-t_final)/CLOCKS_PER_SEC;

    /*printf("Here is the result matrix:\n");
    for (i=0; i<N; i++) {
      for (j=0; j<N; j++)
        printf("%6.2f   ", c[i][j]);
      printf ("\n");
    }*/

    fprintf(stdout,"Time = %f\n", t_total);

  }

  /*---------------------------- worker----------------------------*/
  if (taskid > 0) {
    //la fuente es el programa padre
    source = 0;
    //recibimos el offset
    MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
    //recibimos el número de fiulas a multiplicar
    MPI_Recv(&rows, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
    //recibimos las filas a multiplicar y las guardamos en a
    MPI_Recv(&a, rows*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);
    //recibimos b
    MPI_Recv(&b, N*N, MPI_DOUBLE, source, 1, MPI_COMM_WORLD, &status);

    /* Matrix multiplication */
    for (i=0; i<N; i++)
      for (j=0; j<rows; j++) {
        c[i][j] = 0.0;
        for (k=0; k<N; k++)
          c[i][j] += a[i][k] * b[k][j];
      }

    //enviamos la información
    MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(&c, rows*N, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
  }

  MPI_Finalize();
}
