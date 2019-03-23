#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

typedef long long int lli;

int main(int argc, char *argv[]) {
	int id, p;
	lli global_count = 0;

	MPI_Init(&argc, &argv);
	MPI_Barrier(MPI_COMM_WORLD);
	double elapsed_time = -MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	if(argc != 2) {
		if(!id) {
			printf("Command line: %s <m>\n", argv[0]);
			MPI_Finalize();
			exit(1);
		}
	}

	lli n = atoll(argv[1]);
	lli low_value = 2 + id*(n-1)/p;
	lli high_value = 1 + (id+1)*(n-1)/p;
	lli size = high_value - low_value + 1;
	lli proc0_size = (n-1)/p;
	if((2 + proc0_size) < (lli) sqrt((long double) n)) {
		if(!id) printf("Too many processes\n");
		MPI_Finalize();
		exit(1);
	}

	char *marked = calloc(1, size);
	if(marked == NULL) {
		printf("Cannot allocate enough memory\n");
		MPI_Finalize();
		exit(1);
	}

	lli index = 0; // index of current prime
	lli prime = 2; // current prime
	lli first;     // index of first multiple
	do {
		if(prime * prime > low_value) {
			first = prime * prime - low_value;
		}
		else {
			if(!(low_value % prime)) {
				first = 0;
			}
			else {
				first = prime - (low_value % prime);
			}
		}
		for(lli i = first; i < size; i += prime) {
			marked[i] = 1;
		}
		if (!id) {
			while(marked[++index]);
			prime = index + 2;
		}
		MPI_Bcast(&prime, 1, MPI_LONG_LONG_INT, 0, MPI_COMM_WORLD);
	} while(prime * prime <= n);

	lli count = 0;
	for(lli i = 0; i < size; i++) {
		if(!marked[i]) {
			count++;
		}
	}
	MPI_Reduce(&count, &global_count, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	elapsed_time += MPI_Wtime();
	if(!id) {
		printf("%lli primes are less than or equal to %lli\n", global_count, n);
		printf("Total elapsed time: %10.6f\n", elapsed_time);
	}
	MPI_Finalize();
	return 0;
}