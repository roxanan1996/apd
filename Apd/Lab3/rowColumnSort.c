/******************************************************************************
* FILE: rowColumnSort.c
* AUTHOR: Cristian Chilipirea
* Skeleton for shear sort
******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <stdbool.h>

#define N 25
#define SQRTN 5 // has to be sqrt(N)

void bubbleSortC(int *v) {
	int sorted = 0;
	while(!sorted) {
		sorted = 1;
		// count++;
		 #pragma omp parallel for
		for(int i = 0; i < SQRTN - 1; i++) {
			if(v[i] > v[i + 1]) {
				int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sorted = 0;
			}
		}

		 #pragma omp barrier
	}
}

void bubbleSortD(int *v) {
	int sorted = 0;
	while(!sorted) {
		sorted = 1;
		// count++;
		// #pragma omp parallel for 
		for(int i = 0; i < SQRTN - 1; i++) {
			if(v[i] < v[i + 1]) {
				 int aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sorted = 0;
			}
		}

		// #pragma omp barrier
	}
}
void displayMatrix(int m[][SQRTN]) {
	// DO NOT MODIFY
	int i,j;
	for(i = 0; i < SQRTN; i++) {
		for(j = 0; j < SQRTN; j++) {
			printf("%i ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void copyMatrixInVectorSnake(int *v, int m[][SQRTN]) {
	// DO NOT MODIFY
	int i, j;
	for(i=0;i<SQRTN;i++) {
		if(i%2 == 0) {
			for(j=0;j<SQRTN;j++) {
				v[i*SQRTN+j] = m[i][j];
			}
		} else {
			for(j=SQRTN;j>0;j--) {
				v[i*SQRTN+(SQRTN-j)] = m[i][j-1];
			}
		}
	}
}

void compareVectors(int * a, int * b) {
	// DO NOT MODIFY
	int i;
	for(i = 0; i < N; i++) {
		if(a[i]!=b[i]) {
			printf("Sorted incorrectly\n");
			return;
		}
	}
	printf("Sorted correctly\n");
}

void displayVector(int * v) {
	// DO NOT MODIFY
	int i;
	for(i = 0; i < N; i++) {
		printf("%i ", v[i]);
	}
	printf("\n");
}

int cmp(const void *a, const void *b) {
	// DO NOT MODIFY
	int A = *(int*)a;
	int B = *(int*)b;
	return A-B;
}

int main(int argc, char *argv[]) {
	srand(42);
	int m[SQRTN][SQRTN];
	int v[N];
	int vQSort[N];
	int i,j;

	// generate the vector v with random values
	// DO NOT MODIFY
	for(i = 0; i < SQRTN; i++)
		for(j = 0; j < SQRTN; j++)
			m[i][j] = rand()%10;

	// make copy to check it against qsort
	// DO NOT MODIFY
	copyMatrixInVectorSnake(vQSort, m);
	qsort(vQSort, N, sizeof(int), cmp);

	displayMatrix(m);
	// sort the matrix m using ShearSort

	// int *line = (int*)malloc(sizeof(int)*SQRTN);
	int *column = (int*)malloc(sizeof(int)*SQRTN);
	for (int i = 1; i < N; i *= 2) {
		// sort the lines in :
		#pragma omp parallel for private(j)
		for (int j = 0; j < SQRTN; j += 2) {
			bubbleSortC(m[j]);
			printf("bubble linia %d\n", j);
		}
		#pragma omp parallel for private(j)
		for (int j = 1; j < SQRTN; j += 2) {
			bubbleSortD(m[j]);
			printf("bubble linia %d\n", j);
		}

		// sort the columns in ascending order

		#pragma omp barrier
		// displayMatrix(m);
		for (int j = 0; j < SQRTN; ++j) {
			// int *column = (int*)malloc(sizeof(int)*SQRTN);
			for (int k = 0; k < SQRTN; ++k) {
				column[k] = m[k][j];
			}

			bubbleSortC(column);
			
			for (int k = 0; k < SQRTN; ++k) {
				m[k][j] = column[k];
			}	
		}

		displayMatrix(m);
	}

	// free(column);		
	displayMatrix(m);
	copyMatrixInVectorSnake(v, m);
	displayVector(v);
	displayVector(vQSort);
	compareVectors(v,vQSort);

	return 0;
}

// 