/*
Modifique el programa resultante del numeral anterior de manera que
no el número de factoriales a calcular no este limitado a 2. 
Para este caso, el programa puede crear tantos hilos como sean necesarios
para el cálculo del factorial dependiendo del número de argumentos pasados.
El hilo principal deberá esperar a que terminen el resto de los hilos y a 
medida que vayan terminando muestran un mensaje que indique el identificador del hilo finalizado.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<time.h>
#include <pthread.h>

void *factorial (void* args);

int main (int argc, char *argv[]) {
  pthread_t threads_ids[argc];
  
  for(int i=1;i<argc;i++){
    pthread_create (&threads_ids[i], NULL, factorial, argv[i]);
  } 
  srand(time(0)); 
  for(int i=1;i<argc;i++){
    pthread_join(threads_ids[i],NULL);
  } 

  return 0;
}

void*  factorial (void* args) {
  long long int resultado= 1;
  int num;
  int n = atoi(args);;
  for (num= 2; num<= n; num++) {
    resultado= resultado*num;
    printf ("Factorial de %d, resultado parcial %lld\n", n, resultado);
    sleep (random()%3);
  }
  
  printf ("El factorial de %d es %lld\n", n, resultado);
  printf("Termino de ejecutar el ThreadId: %lu \n",(unsigned long)pthread_self());


  return NULL;
}

