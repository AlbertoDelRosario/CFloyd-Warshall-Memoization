#include "FileIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;
char *delim = "\t";
int numOfVertices;

int getNumOfVertices(){
  return numOfVertices;
}

int initializeGraph(int** graph){

  int i;
  int j;
  int k;

	char* ch;

  ch = malloc(100*numOfVertices);
  i = 0;
  while(fgets(ch, 100*numOfVertices, fp) != NULL && i < numOfVertices){
    char* aux = strtok(ch, delim);
    for(j = 0; j < numOfVertices; j = j + 1){
      if(strcmp(aux, "INF") != 0){
        graph[i][j] = atoi(aux);
      }else{
        graph[i][j] = 99999;
      }
			if(j != numOfVertices - 1){
      	aux = strtok(NULL, delim);
			}
    }
    i = i + 1;
  }
}

int initReader(char *filename){

	char *ch;
	fp = fopen(filename, "r");

	if(fp == NULL){
		printf("Error: No se ha podido abrir el fichero\n");
		exit(EXIT_FAILURE);
	}

	ch = malloc(10*sizeof(int*));

	if(fgets(ch, 10, fp) != NULL){
		numOfVertices = atoi(ch);
	}else{
		printf("Error: No se puede leer el fichero\n");
		exit(EXIT_FAILURE);
	}

	return numOfVertices;
}
