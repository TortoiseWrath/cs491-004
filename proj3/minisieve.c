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
	}
	while(sieving_primes[++index]);
	prime = index * 2 + 3;
} while(prime * prime <= max_sieving_prime);