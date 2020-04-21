/*
El profesor de un curso desea un programa en lenguaje C 
que calcule la desviación estándar (símbolo σ o s) de las 
notas obtenidas por sus estudiantes en el curso 

**Requisitos**:
* El número de notas es variable (se debe usar memoria dinámica).
* El programa debe crear tantos hilos como se especifique en el
 parámetro de entrada cantidad_hilos, se debe ejecutar así: 
    ./nombre_ejecutable fichero_notas.csv cantidad_hilos
    Para calcular la desviación estándar, implemente la función: calculate_standard_deviation()

Necesito

*/
#include <stdio.h>
#include <math.h> 
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pthread.h>

char *fileToArray(char *filePath);
float *fileArrayToList(int *n,char *scores);
float mean(int n, float *score);
void calculate_standard_deviation(int n, float *score, float mean);
void *desviationStd(void *filePath);

int main(int argc, char *argv[]) {

    if (argc == 1) {
      printf ("Ingrese path de las notas y el número de hilos\n");
      exit(0);
    }else
    if(argc ==2){
        printf("Ingrese el número de hilos");
        exit(0);
    }else if(argc > 3){
        printf("Ingreso mas parametros de los necesarios");
        exit(0);
    }

    int n_threads = atoi((char *)argv[2]);
    pthread_t threads_ids[n_threads]; 

    for(int i=0;i<n_threads;i++){    
        pthread_create (&threads_ids[i], NULL,desviationStd ,argv[1]);
    } 

    for (int i = 0; i < n_threads; i++){
        pthread_join(threads_ids[i], NULL);
    }

   
   return 0;
}


void *desviationStd(void *filePath){

    int n=0;
    char *textarray =fileToArray(filePath);
    float *scoresList = fileArrayToList(&n,textarray);
    float meanS = mean(n,scoresList);
    calculate_standard_deviation(n,scoresList,meanS);
    pthread_exit(NULL);

}

char *fileToArray(char *filePath){
    FILE *fp;
    char pc;
    fp = fopen(filePath, "rt");
    char *scoresArray = (char *)malloc(1*sizeof(char));
    
    if (fp == NULL){
        printf("No se puedo abrir el file\n");
        exit(0);
    }
    pc = fgetc(fp);
    while (pc != EOF){
        char sp[2] = "\0";
        sp[0] = pc;
        scoresArray = (char *)realloc(scoresArray, (strlen(scoresArray) + strlen(sp) + 1) * sizeof(char));
        strcat(scoresArray, sp);
        pc = fgetc(fp);
    }

    fclose(fp);
    return scoresArray;

}

float *fileArrayToList(int *n,char *scores){
    char deli[] = " ";
    char *ptr = strtok(scores, deli);
    int n_elements = 1, index = 0;
    float *nbrs = (float *)malloc(0 * sizeof(float));
    while (ptr != NULL){
        nbrs = (float *)realloc(nbrs, (n_elements) * sizeof(float));
        float number = atof(ptr);
        *(nbrs + index) = number;

        ptr = strtok(NULL, deli);
        n_elements = n_elements + 1;
        index = index + 1;
        *n = *n + 1;
    }
    return nbrs;

}

float mean(int n, float *score){
    float meanR = 0.0;
    float sumT = 0;
    for (int k = 0; k < n; k++){
        sumT = sumT + score[k];
    }
    meanR = sumT / n;
    return meanR;


}


void calculate_standard_deviation(int n, float *score, float mean){
    float sumR = 0;
    for (int i = 0; i < n; i++){
        sumR = sumR + pow((score[i] - mean), 2);
    }
    float norma = 1 / ((float)n - 1);
    float std = sqrt(norma * sumR);
    printf("Std = %f\n",std);
}














