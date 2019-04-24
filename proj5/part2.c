#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000
#define T 5000

int main(void) {
	double *A = malloc(sizeof *A * N * N * 2);

	for(int i = 0; i < N; i++) {
		// Initialize left wall
		A[i*N] = 20;
		A[N*N + i*N] = 20;
		// Initialize right wall
		A[i*N + N-1] = 20;
		A[N*N + i*N + N-1] = 20;
		// Initialize bottom wall
		A[N*N - i - 1] = 20;
		A[N*N*2 - i - 1] = 20;
		// Initialize top wall
		if(i >= 0.3 * N && i < 0.7 * N) {
			// is on fire
			A[i] = 100;
			A[N*N + i] = 100;
		}
		else {
			A[i] = 20;
			A[N*N + i] = 20;
		}
	}

	for(int i = 1; i < N-1; i++) { // Initialize interior points
		for(int j = 1; j < N-1; j++) {
			A[N*N + i*N + j] = A[i*N + j] = 20;
		}
	}

	double start = omp_get_wtime(); // start time measurement
	for(int iteration = 0; iteration < T; iteration++) {
		int working_array = (iteration % 2) * N * N;
		int source_array = (1 - iteration % 2) * N * N;
		for(int i = 1; i < N - 1; i++) {
			for(int j = 1; j < N - 1; j++) {
				A[working_array + i*N + j] = 0.25 * (
					A[source_array + (i-1) * N + j] + 
					A[source_array + (i+1) * N + j] +
					A[source_array + i * N + j - 1] +
					A[source_array + i * N + j + 1]);
			}
		}
	}
	double end = omp_get_wtime(); // end time measurement
	printf("Time of computation: %f seconds\n", end - start);

	int final_array = (1-T%2)*N*N;
	for(int y = 0; y < N; y += N/8) {
		for(int x = 0; x < N; x += N/8) {
			printf("%f ", A[final_array + y*N + x]);
		}
		printf("\n");
	}
	printf("\n");
	for(int y = N/16; y < N; y += N/8) {
		for(int x = N/16; x < N; x += N/8) {
			printf("%f ", A[final_array + y*N + x]);
		}
		printf("\n");
	}

	free(A);

	return(0);
}