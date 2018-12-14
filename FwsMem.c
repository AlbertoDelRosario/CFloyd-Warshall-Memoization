#include "FileIO/FileIO.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int INF = 99999;
int v;
int*** M;
int debugInput;
int debugOutput;
int debugTime;
char* filen;
struct timespec start={0,0}, tend={0,0};

int min(int e1, int e2){
	if(e1 <= e2){
		return e1;
	}else{
		return e2;
	}
}

void printSolution(int** dist, char* msg){
	printf("%s\n", msg);
	int i;
	int j;

	for(i = 0; i < v; i = i + 1){
		for(j = 0; j < v; j = j + 1){
			if(dist[i][j] == INF){
				printf("INF\t");
			}else{
				printf("%d\t", dist[i][j]);
			}
		}
		printf("\n");
	}
}

void initM(){
  int i;
  int j;
  int k;
  M = malloc(v*sizeof(int**));
  for(i = 0; i < v; i = i + 1){
    M[i] = malloc(v*sizeof(int*));
  }

  for(i = 0; i < v; i = i + 1){
    for(j = 0; j < v; j = j + 1){
      M[i][j] = malloc(v*sizeof(int));
    }
  }

  for(i = 0; i < v; i = i + 1){
    for(j = 0; j < v; j = j + 1){
      for(k = 0; k < v; k = k + 1){
        M[i][j][k] = INF;
      }
    }
  }

}

int fwsRec(int** graph, int k, int i, int j){
	if(M[k][i][j] == INF){
		if(k == 0){
			M[k][i][j] = graph[i][j];
		}else{
			int path1 = fwsRec(graph, k - 1, i, j);
			int path2 = fwsRec(graph, k - 1, i, k) + fwsRec(graph, k - 1, k, j);
			M[k][i][j] = min(path1, path2);
		}
	}

	return M[k][i][j];
}

void floydWarshall(int** graph){
	int i;
	int j;

	if(debugInput == 1){
		printSolution(graph, "Input vertexs weight matrix");
	}

	int** dist;

	dist = malloc(v*sizeof(int*));
	for(i = 0; i < v; i = i + 1){
		dist[i] = malloc(v*sizeof(int));
	}

	for(i = 0; i < v; i = i + 1){
		for(j = 0; j < v; j = j + 1){
			dist[i][j] = fwsRec(graph, v-1, i, j);
		}
	}

	if(debugOutput == 1){
		printSolution(dist, "\nThe following matrix shos the shortest distances between every pair of vertices");
	}

	if(debugTime == 1){
		clock_gettime(CLOCK_MONOTONIC, &tend);
		double diff = ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)start.tv_sec + 1.0e-9*start.tv_nsec);
		printf("--------------------------------------\nTime: %.10f seconds\n", diff);
	}
}

int captureArgs(int argc, char* argv[]){
	int i;

	debugTime = 0;
  debugInput = 0;
  debugOutput = 0;
  int hasFile = 0;

	for(i = 0; i < argc; i = i + 1){
		if(strcmp(argv[i], "-di") == 0){
			debugInput = 1;
		}
		if(strcmp(argv[i], "-do") == 0){
			debugOutput = 1;
		}
		if(strcmp(argv[i], "-dt") == 0){
			debugTime = 1;
		}
		if(strcmp(argv[i], "-f") == 0 && i < argc -1){
			hasFile = 1;
			filen = malloc(sizeof(argv[i+1])*sizeof(char));
			strcpy(filen, argv[i+1]);
		}
	}

	if(!hasFile){
		return -1;
	}

	return 0;
}

int main(int argc, char* argv[]){
	int i;

	clock_gettime(CLOCK_MONOTONIC, &start);

	if(captureArgs(argc, argv) == -1){
		printf("\nError: Wrong Arguments\n");
		return -1;
	}

	initReader(filen);

	v = getNumOfVertices();

	int** graph;

	graph = malloc(v*sizeof(int*));
	for(i = 0; i < v; i = i + 1){
		graph[i] = malloc(v*sizeof(int));
	}

	initializeGraph(graph);

	initM();

	floydWarshall(graph);
}
