#include "FileIO/FileIO.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
  int** grafo;

	int i;
	int j;

	int max = initReader("text2.txt");

	grafo = malloc(max*sizeof(int*));
	for(i  = 0; i < max; i = i + 1){
		grafo[i] = malloc(max*sizeof(int));
	}

  initializeGraph(grafo);

	int size = sizeof(grafo);

  for(i = 0; i < max; i = i + 1){
    for(j = 0; j < max; j = j + 1){
			if(grafo[i][j] != 99999){
      	printf("%d\t", grafo[i][j]);
			}else{
				printf("INF\t");
			}
    }
    printf("\n");
  }

}
