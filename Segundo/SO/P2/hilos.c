#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

double counter = 0;
int Eligiendo[]={0,0,0};
int Numero[]={0,0,0};
#define ITER	1000
#define NHILOS	4

int main()
{
    pthread_t hilos[NHILOS];
    int status, i, v[NHILOS];
    extern double counter;
    void *adder(void *);
    double *r_value;
    // Create NHILOS threads
    for (i = 0; i < NHILOS; i++) {
	      v[i] = i;
        printf("%d\n",v[i] );
	      if ((status = pthread_create(&hilos[i], NULL, adder, (void *) &v[i])))
        exit(status);
    }
    // Wait threads
    for (i = 0; i < NHILOS; i++) {
	pthread_join(hilos[i], (void **) &r_value);
	printf("Value returned by %lu thread: %lf\n", hilos[i], *r_value);
    }

    // Final result
    fprintf(stdout, "%f\n", counter);

    return 0;
}

void *adder(void *p)
{
    double l, *to_return;
    extern double counter;
    int *id, i;
    int max(int,int,int);
    int j;
    id = (int *) p;

    while(1){
    Eligiendo[*id]=1;
    Numero[*id]=1+max(Numero[0],Numero[1],Numero[2])+1;
    Eligiendo[*id]=0;
    for (j = 0; j < NHILOS; j++) {
      while(Eligiendo[j]);
      while((Numero[j]!=0)&&((Numero[j],j)<(Numero[*id],*id)));
    }
    for (i = 0; i < ITER; i++) {
	    l = counter;
	    fprintf(stdout, "Hilo %d: %f\n", *id, counter);
	    l++;
	    counter = l;
    }

    Numero[*id]=0;
    to_return = malloc(sizeof(double));

    *to_return = counter;

    pthread_exit((void *) to_return);
  }
}

int max(int a, int b, int c){
  if((a>b)&&(a>c)) return a;
  if((b>a)&&(b>c)) return b;
  return c;
}
