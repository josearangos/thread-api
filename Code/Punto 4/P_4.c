#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#define MAXLON 1000

struct cuenta_parms
{
  /* The character to print.  */
  char * nombre;

};

void * cuenta (void* parameters) {
  struct cuenta_parms* p = (struct cuenta_parms*) parameters;

  int pos, cont= 0, leidos;
  char cadena[MAXLON];
  int fd;
  fd= open(p->nombre,O_RDONLY);
  while ((leidos =read(fd,cadena,MAXLON))!= 0) {
    for (pos= 0; pos< leidos; pos++) {
      if ((cadena[pos]== 'a') || (cadena[pos]== 'A')) {
        cont++;
      }
    }
  }
  printf("Fichero %s: %d caracteres 'a' o 'A' encontrados\n", p->nombre, cont);
  close(fd);
  return NULL;
}

int main (int argc, char *argv[]) {
  if (argc < 2) {
    printf ("Indica el nombre de un fichero.\n");
    exit(0);
  }
  int count=1;
  while(count<argc){

    pthread_t thread1_id;
    struct cuenta_parms thread1_args;

    thread1_args.nombre = argv[count];

    pthread_create (&thread1_id, NULL, &cuenta, &thread1_args);

    /*-------INSERTAR AQUÍ-------*/
    pthread_join (thread1_id, NULL);

    count+=1;
  }
  return 0;
}

