#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAXLON 1000

void cuenta (char *);

int main (int argc, char *argv[]) { 
  if (argc!= 2) {
    printf ("Indica el nombre de un fichero.\n");
    exit(0);
  }
  cuenta(argv[1]);
  return 0;
}

void cuenta (char *nombre) {
  int pos, cont= 0, leidos;
  char cadena[MAXLON];
  int fd;
  fd= open(nombre,O_RDONLY);
  char valores [7];
  int suma=0;
  while ((leidos =read(fd,cadena,MAXLON))!= 0) {
    for (pos= 0; pos< leidos; pos++) { 
      if (cadena[pos]== ','){
        //valores[cont]=NULL;
        suma=suma+atoi(valores);
        memset(valores,'\0',7);
        cont=0;
      }
      else{
        valores[cont]=cadena[pos];
        cont++;
      }
    }
  }
  suma=suma+atoi(valores);
  printf("Fichero %s:la suma de los valores encontraods es: %d \n", nombre, suma);
  close(fd);
}
