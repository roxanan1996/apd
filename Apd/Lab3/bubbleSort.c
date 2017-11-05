/******************************************************************************
* FILE: bubbleSort.c
* AUTHOR: Cristian Chilipirea
* Generates, sorts using Bubble sort and displays a vector
******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define N 5

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
	int displayWidth = 2 + log10(v[N-1]);
	for(i = 0; i < N; i++) {
		printf("%*i", displayWidth, v[i]);
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
	int sorted = 0;
	int aux;
	int *v = (int*)malloc(sizeof(int)*N);
	int *copy = (int*)malloc(sizeof(int)*N);
	int *vQSort = (int*)malloc(sizeof(int)*N);
	int i;

	// generate the vector v with random values
	// DO NOT MODIFY
	srand(42);
	for(i = 0; i < N; i++) {
		v[i] = rand()%N;
		copy[i] = v[i];
	}

	// make copy to check it against qsort
	// DO NOT MODIFY
	for(i = 0; i < N; i++)
		vQSort[i] = v[i];
	qsort(vQSort, N, sizeof(int), cmp);

	displayVector(v);
	// sort the vector v
	// PARALLELIZE ME
	
	int count = 0;
	while(!sorted) {
		sorted = 1;
		count++;
		#pragma omp parallel for private(aux)
		for(i = 0; i < N-1; i++) {
			if(v[i] > v[i + 1]) {
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
				sorted = 0;
			}
		}

		#pragma omp barrier
	}

	printf("primul count %d\n", count);
	sorted = 0;
	count = 0;
	while(!sorted) {
		count++;
		sorted = 1;
		// #pragma omp parallel for shared(sorted)
		for(i = 0; i < N-1; i++) {
			if(copy[i] > copy[i + 1]) {
				aux = copy[i];
				copy[i] = copy[i + 1];
				copy[i + 1] = aux;
				sorted = 0;
			}
		}

		// #pragma omp barrier
	}

	printf("al doilea count%d\n", count);
	displayVector(v);
	displayVector(vQSort);
	compareVectors(v, vQSort);

	return 0;
}