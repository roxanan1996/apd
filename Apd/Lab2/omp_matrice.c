/******************************************************************************
* FILE: omp_matrice.c
* AUTHOR: Cristian Chilipirea
* Matrix multiplication C = A * B
* A = B (eg for N=3)
* A = 1 1 1
      0 1 1
      0 0 1
* C = 1 2 3
      0 1 2
      0 0 1
******************************************************************************/
#include<stdio.h>

#define N 3

int main(int argc, char argv[]) {
	int A[N][N];
	int B[N][N];
	int C[N][N];
	int D[N][N];
	int i, j, k;

	// generate data
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			C[i][j] = 0;
			D[i][j] = 0;
			if(i <= j) {
				A[i][j] = 1;
				B[i][j] = 1;
			}
			else {
				A[i][j] = 0;
				B[i][j] = 0;
			}
		}
	}


	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = 0; k < N; k++) {
				D[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	// multiply matrices
	#pragma omp for
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = 0; k < N; k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	//display
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%i\t",C[i][j]);
		}
		printf("\n");
	}

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%i\t",D[i][j]);
		}
		printf("\n");
	}
}