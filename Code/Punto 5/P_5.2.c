#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>

#define MAXLON 1000

int result=0;

struct cuenta_parms
{
  /* The character to print.  */
  char * nombre;
  int punteroa;
  int punterod;
};
int cuentaCaracter (char *nombre) {
  int pos, cont= 0, leidos;
  char cadena[MAXLON];
  int fd;
  fd= open(nombre,O_RDONLY);
  while ((leidos =read(fd,cadena,MAXLON))!= 0) {
    for (pos= 0; pos< leidos; pos++) {
      if (cadena[pos]== ','){
        cont++;
      }
    }
  }
  cont=cont+1;
  int  div=((cont%2) ? cont/2+1:cont/2);
  printf("El valor de la división es %d ",div);
  cont= 0;
  close(fd);
  fd= open(nombre,O_RDONLY);
  while ((leidos =read(fd,cadena,MAXLON))!= 0) {
    for (pos= 0; pos< leidos; pos++) {
      if (cadena[pos]== ','){
        cont++;
        if(cont==div){
          return pos+1;
        }
      }
    }
  }
  close(fd);
  return 0;
}
void *cuenta (void* parameters) {
  struct cuenta_parms* p = (struct cuenta_parms*) parameters;
  int pos, cont= 0, leidos;
  char cadena[MAXLON];
  int fd;
  fd= open(p->nombre,O_RDONLY);
  char valores [7];
  int suma=0;
  int hasta=p->punteroa;
  while ((leidos =read(fd,cadena,MAXLON))!= 0) {
    if(p->punteroa==-1){
     hasta=leidos;
    }
    for (pos=p->punterod; pos< hasta; pos++) { 
      if (cadena[pos]== ','){
        
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
  result=result+suma;
  printf("Fichero %s: la suma de los valores parciales es: %d \n", p->nombre, suma);
  close(fd);
  return NULL;
}
int main (int argc, char *argv[]) { 

  if (argc!= 2) {
    printf ("Indica el nombre de un fichero.\n");
    exit(0);
  }
  int cvalores=cuentaCaracter (argv[1]);

  pthread_t thread1_id;
  pthread_t thread2_id;

  struct cuenta_parms thread1_args;
  struct cuenta_parms thread2_args;

  thread1_args.nombre = argv[1];
  thread2_args.nombre = argv[1];

  thread1_args.punteroa = cvalores;
  thread2_args.punteroa = -1;

  thread1_args.punterod = 0;
  thread2_args.punterod = cvalores;

  pthread_create (&thread1_id, NULL, &cuenta, &thread1_args);
  pthread_create (&thread2_id, NULL, &cuenta, &thread2_args);

  /*-------INSERTAR AQUÍ-------*/
  pthread_join (thread1_id, NULL);
  pthread_join (thread2_id, NULL);

  printf("La suma total es %d \n",result);
  return 0;
}

