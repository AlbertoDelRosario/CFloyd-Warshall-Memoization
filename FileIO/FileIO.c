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

//Method that fills a graph with the values passed through a textfile
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
        graph[i][j] = 99999; //An INF means that there is no connection.
      }
			if(j != numOfVertices - 1){
      	aux = strtok(NULL, delim);
			}
    }
    i = i + 1;
  }
}

//It is necesary to separate the initialization of the graph so that it is possible
//to the user to assign memory to the matrix of the graph
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
