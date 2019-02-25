#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void ijk(double *a, double *b, double *c, int n, int B) {
	for(int i = 0; i < n; i += B) {
		for(int j = 0; j < n; j += B) {
			for(int k = 0; k < n; k += B) {
				for(int i1 = i; i1 < i + B && i1 < n; i1++) {
					for(int j1 = j; j1 < j + B && j1 < n; j1++) {
						register double r = 0;
						for(int k1 = k; k1 < k + B && k1 < n; k1++) {
							r += a[i1*n+k1]*b[k1*n+j1];
						}
						c[i1*n+j1] += r;
					}
				}
			}
		}
	}
}

void jik(double *a, double *b, double *c, int n, int B) {
	for(int j = 0; j < n; j += B) {
		for(int i = 0; i < n; i += B) {
			for(int k = 0; k < n; k += B) {
				for(int j1 = j; j1 < j + B && j1 < n; j1++) {
					for(int i1 = i; i1 < i + B && i1 < n; i1++) {
						register double r = 0;
						for(int k1 = k; k1 < k + B && k1 < n; k1++) {
							r += a[i1*n+k1]*b[k1*n+j1];
						}
						c[i1*n+j1] += r;
					}
				}
			}
		}
	}
}

void kij(double *a, double *b, double *c, int n, int B) {
	for(int k = 0; k < n; k += B) {
		for(int i = 0; i < n; i += B) {
			for(int j = 0; j < n; j += B) {
				for(int k1 = k; k1 < k + B && k1 < n; k1++) {
					for(int i1 = i; i1 < i + B && i1 < n; i1++) {
						register double aval = a[i1*n+k1];
						for(int j1 = j; j1 < j + B && j1 < n; j1++) {
							c[i1*n+j1] += aval*b[k1*n+j1];
						}
					}
				}
			}
		}
	}
}

void ikj(double *a, double *b, double *c, int n, int B) {
	for(int i = 0; i < n; i += B) {
		for(int k = 0; k < n; k += B) {
			for(int j = 0; j < n; j += B) {
				for(int i1 = i; i1 < i + B && i1 < n; i1++) {
					for(int k1 = k; k1 < k + B && k1 < n; k1++) {
						register double aval = a[i1*n+k1];
						for(int j1 = j; j1 < j + B && j1 < n; j1++) {
							c[i1*n+j1] += aval*b[k1*n+j1];
						}
					}
				}
			}
		}
	}
}

void jki(double *a, double *b, double *c, int n, int B) {
	for(int j = 0; j < n; j += B) {
		for(int k = 0; k < n; k += B) {
			for(int i = 0; i < n; i += B) {
				for(int j1 = j; j1 < j + B && j1 < n; j1++) {
					for(int k1 = k; k1 < k + B && k1 < n; k1++) {
						register double bval = b[k1*n+j1];
						for(int i1 = i; i1 < i + B && i1 < n; i1++) {
							c[i1*n+j1] += a[i1*n+k1]*bval;
						}
					}
				}
			}
		}
	}
}

void kji(double *a, double *b, double *c, int n, int B) {
	for(int k = 0; k < n; k += B) {
		for(int j = 0; j < n; j += B) {
			for(int i = 0; i < n; i += B) {
				for(int k1 = k; k1 < k + B && k1 < n; k1++) {
					for(int j1 = j; j1 < j + B && j1 < n; j1++) {
						register double bval = b[k1*n+j1];
						for(int i1 = i; i1 < i + B && i1 < n; i1++) {
							c[i1*n+j1] += a[i1*n+k1]*bval;
						}
					}
				}
			}
		}
	}
}

void timeMultiplication(char *name, void (*mmm)(double*, double*, double*, int, int), double *a, double *b, double *c, int n, int B) {
    clock_t start = clock();
    (*mmm)(a, b, c, n, B);
    double seconds = (double) (clock() - start) / CLOCKS_PER_SEC;
    double gflops = ((double) 3 * n*n*n) / 1000000000.0 / seconds;
    printf("%s with block size %i completed in %.6f seconds (%.4f GFLOPS)\n", name, B, seconds, gflops);
}

void timeAndCompare(char *name, void (*mmm)(double*, double*, double*, int, int), double *a, double *b, double *c0, double *c, int n, int B) {
	for(int i = 0; i < n*n; i++) { // clear out matrix c
		c[i] = 0;
	}
	timeMultiplication(name, mmm, a, b, c, n, B);
	double maxdiff = 0;
	for(int j = 0; j < n*n; j++) {
		double diff = fabs(c[j] - c0[j]);
		if(diff > maxdiff) {
			maxdiff = diff;
		}
	}
	printf("Maximum difference is %.6f\n", maxdiff);
}

int main(int argc, char *argv[]) {
    srand(time(0));

    int n = 400;
    if(argc > 1) {
        n = atoi(argv[1]);
    }
	int B = 1;
    if(argc > 2) {
        B = atoi(argv[2]);
    }
    double *a = malloc(sizeof(double) * n*n);
    double *b = malloc(sizeof(double) * n*n);
	double *c0 = malloc(sizeof(double) * n*n);
	double *c = malloc(sizeof(double) * n*n);

    for(int i = 0; i < n*n; i++) { // Initialize A and B to random values
        a[i] = (double) rand() / RAND_MAX * 1024; // 1024 is arbitrary
        b[i] = (double) rand() / RAND_MAX * 1024;
		c0[i] = 0;
    }

    timeMultiplication("ijk", ijk, a, b, c0, n, B);
    timeAndCompare("ikj", ikj, a, b, c0, c, n, B);
    timeAndCompare("jik", jik, a, b, c0, c, n, B);
    timeAndCompare("jki", jki, a, b, c0, c, n, B);
    timeAndCompare("kij", kij, a, b, c0, c, n, B);
    timeAndCompare("kji", kji, a, b, c0, c, n, B);

    free(a);
    free(b);
    free(c);
	free(c0);
    return 0;
}