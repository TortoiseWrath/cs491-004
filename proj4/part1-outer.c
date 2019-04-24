#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 2000

int main(int argc, char *argv[]) {
	int t = 8;
	if(argc == 2) {
		t = atoi(argv[1]);
	}
	omp_set_num_threads(t);
	
	double *A = malloc(sizeof *A * N * N);
	double *B = malloc(sizeof *B * N * N);
	double *C = malloc(sizeof *C * N * N);
	double *C0 = malloc(sizeof *C * N * N);

	if(t == 8) {
		// When testing with 8 threads, check against sequential

		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				A[i*N+j] = j*1;
				B[i*N+j] = i*j+2;
				C0[i*N+j] = j-i*2;
			}
		}
		double start_seq = omp_get_wtime(); // start time measurement
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				double sum = 0;
				for(int k = 0; k < N; k++) {
					sum += A[i*N+k]*B[k*N+j];
				}
				C0[i*N+j] = sum;
			}
		}
		double end_seq = omp_get_wtime(); // end time measurement
		printf("Sequential time of computation: %f seconds\n", end_seq - start_seq);
	}

	double total_time = 0;

	for(int n = 0; n < 5; n++) {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				A[i*N+j] = j*1;
				B[i*N+j] = i*j+2;
				C[i*N+j] = j-i*2;
			}
		}
	
		double start = omp_get_wtime(); // start time measurement
		#pragma omp parallel for
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				double sum = 0;
				for(int k = 0; k < N; k++) {
					sum += A[i*N+k]*B[k*N+j];
				}
				C[i*N+j] = sum;
			}
		}
		double end = omp_get_wtime(); // end time measurement
		printf("Time of computation: %f seconds\n", end - start);

		if(t == 8) {
			double maxdiff = 0;
			for(int i = 0; i < N*N; i++) {
				double diff = abs(C[i] - C0[i]);
				if(diff > maxdiff) maxdiff = diff;
			}
			printf("Maximum difference is %f\n", maxdiff);
		}

		total_time += end - start;
	}

	free(A); free(B); free(C);

	printf("Average time of computation: %f seconds\n", total_time / 5);
	return(0);
}