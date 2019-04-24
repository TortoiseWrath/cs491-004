#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef long long int lli;

int main(int argc, char *argv[]) {
	lli n = 10000000000;
	lli low_value = 2;
	lli high_value = n;
	lli size = high_value - low_value + 1;

	char *marked = calloc(1, size);
	if(marked == NULL) {
		printf("Cannot allocate enough memory\n");
		exit(1);
	}

	lli index = 0; // index of current prime
	lli prime = 2; // current prime
	lli first;     // index of first multiple
	do {
		for(lli i = prime * prime - low_value; i < size; i += prime) {
			marked[i] = 1;
		}
		while(marked[++index]);
		prime = index + 2;
	} while(prime * prime <= n);

	lli count = 0;
	for(lli i = 0; i < size; i++) {
		if(!marked[i]) {
			count++;
		}
	}
	printf("%lli primes are less than or equal to %lli\n", count, n);
	return 0;
}