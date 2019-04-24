#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000
#define T 5000	

int main(void) {
	omp_set_num_threads(4);

	double *A = malloc(sizeof *A * N * N * 2);
	double *B = malloc(sizeof *B * N * N * 2);

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
			A[N*N + i*N + j] = A[i*N + j] = 0;
		}
	}

	for(int i = 0; i < N * N * 2; i++) { // copy A to B
		B[i] = A[i];
	}

	// Sequential version
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
	printf("Time of sequential computation: %f seconds\n", end - start);

	// Parallel version
	double start2 = omp_get_wtime(); // start time measurement
	for(int iteration = 0; iteration < T; iteration++) {
		int working_array = (iteration % 2) * N * N;
		int source_array = (1 - iteration % 2) * N * N;
		#pragma omp parallel for
		for(int i = 1; i < N - 1; i++) {
			for(int j = 1; j < N - 1; j++) {
				B[working_array + i*N + j] = 0.25 * (
					B[source_array + (i-1) * N + j] + 
					B[source_array + (i+1) * N + j] +
					B[source_array + i * N + j - 1] +
					B[source_array + i * N + j + 1]);
			}
		}
	}
	double end2 = omp_get_wtime(); // end time measurement
	printf("Time of parallel computation: %f seconds\n", end2 - start2);
	
	int final_array = (1-T%2)*N*N;
	double maxdiff = 0;
	for(int i = 0; i < N*N; i++) {
		double diff = A[final_array + i] - B[final_array + i];
		if(diff > maxdiff) maxdiff = diff;
	}
	printf("Maximum difference: %f\n", maxdiff);

	printf("Speedup factor: %.2f\n", (end - start) / (end2 - start2));

	free(A); free(B);

	return(0);
}