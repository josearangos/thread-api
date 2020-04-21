/*
Modifique el programa anterior de manera que reciba dos números
enteros como parámetros de entrada y calcule sus factoriales de manera 
concurrente utilizando dos hilos que se ejecutan en paralelo con el hilo principal.
 El hilo principal deberá esperar a que terminen los otros dos hilos. 
 Recuerda  añadir el parámetro ```-lpthread``` al comienzo del ```gcc``` para compilar 
 la aplicación multihilo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<time.h>
#include <pthread.h>

void*  factorial (void* arg);

int main (int argc, char *argv[]) {
  pthread_t thread_id_1;
  pthread_t thread_id_2;
  int fact_1=0;
  int fact_2=0;
  int* fact_r_1;
  int* fact_r_2;

  srand(time(0)); 

  if (argc== 3) {
    fact_1 =  atoi(argv[1]);
    fact_2 =  atoi(argv[2]);
    
    pthread_create (&thread_id_1, NULL, &factorial, &fact_1);
    pthread_create (&thread_id_2, NULL, &factorial, &fact_2);

    pthread_join(thread_id_1, (void *) &fact_r_1);
    pthread_join(thread_id_2, (void *) &fact_r_2);

    printf ("El factorial de %d es %d\n", fact_1, *fact_r_1);
    printf ("El factorial de %d es %d\n", fact_2, *fact_r_2);


  }
  return 0;
}

void*  factorial (void* arg) {
  long long int resultado= 1;
  int num;
  int n = *((int*)arg);
  for (num= 2; num<= n; num++) {
    resultado= resultado*num;
    printf ("Factorial de %d, resultado parcial %lld\n", n, resultado);
    sleep (random()%3);
  }
  int* p_c = malloc(sizeof(int));
  *p_c = resultado;
  return p_c;

}