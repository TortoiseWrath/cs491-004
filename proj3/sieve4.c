#include <mpi.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef long long int lli;

int main(int argc, char *argv[]) {
	int id, p;
	lli global_count; 

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
	lli low_value = 3 + id*(n-1)/p;
	lli high_value = 2 + (id+1)*(n-1)/p;
	if(!(low_value % 2)) {
		low_value++;
	}
	if(!(high_value % 2)) {
		high_value--;
	}
	lli size = (high_value - low_value) / 2 + 1;
	lli proc0_high = 2 + (n-1)/p;
	if(proc0_high < (lli) sqrt((long double) n)) {
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

	lli max_sieving_prime = (lli) sqrt((long double) n);
	if(max_sieving_prime%2 == 0) max_sieving_prime--;
	char *sieving_primes = calloc(1, max_sieving_prime/2);
	lli index = 0;
	lli prime = 3;
	do {
		for(lli i = prime * prime; i <= max_sieving_prime; i += prime) {
			if(i % 2 == 0) {
				continue; // skip even numbers
			}
			sieving_primes[(i - 3) / 2] = 1;
			//printf("minisieve marked %lli\n", i);
		}
		while(sieving_primes[++index]);
		prime = index * 2 + 3;
	} while(prime * prime <= max_sieving_prime);

	lli block_size_index = max_sieving_prime / 2 - 1;
	while(marked[--block_size_index]); // find index of largest prime < sqrt(n)
	lli block_size = (block_size_index * 2 + 3) * 2;
	for(lli block_low = low_value; block_low < high_value; block_low += block_size + 2) {
		lli block_high = block_low + block_size;
		if(block_high > high_value) {
			block_high = high_value;
		}
		// printf("process %i (%lli-%lli) has block from %lli to %lli\n", id, low_value, high_value, block_low, block_high);
		lli first;
		for(lli index = 0; index*2+3 <= max_sieving_prime; index++) {
			if(sieving_primes[index]) continue;
			lli prime = 2 * index + 3;
			if(prime * prime > block_high) {
				break; // done with this block
			}
			if(prime * prime > block_low) {
				first = prime * prime;
			}
			else {
				if(!(block_low % prime)) {
					first = block_low;
				}
				else {
					first = prime - (block_low % prime) + block_low;
				}
			}
			for(lli i = first; i <= block_high; i += prime) {
				if(i % 2 == 0) {
					continue; // skip even numbers
				}
				marked[(i - low_value) / 2] = 1;
				// printf("%lli is not prime so marked %lli in process %i\n", i, (i - low_value) / 2, id);
			}
		}
	}

	lli count = 0; 
	if(!id) count = 1; // count 2 which was skipped
	for(lli i = 0; i < size; i++) {
		if(!marked[i]) {
			count++;
			// printf("process %i says %lli is prime\n", id, low_value + i*2);
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