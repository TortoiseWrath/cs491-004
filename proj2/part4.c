#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void ijk(double *a, double *b, double *c, int n, int B) {
	for(int i = 0; i < n; i += B) {
		for(int j = 0; j < n; j += B) {
			for(int k = 0; k < n; k += B) {
				for(int i1 = i; i1 < i + B && i1 < n; i1 += 2) {
					for(int j1 = j; j1 < j + B && j1 < n; j1 += 2) {
						register double c00, c01, c10, c11;
						c00 = c01 = c10 = c11 = 0;
						for(int k1 = k; k1 < k + B && k1 < n; k1 += 2) {
							register double a00 = a[i1*n+k1];
							register double a10 = a[(i1+1)*n+k1];
							register double a01 = a[i1*n+k1+1];
							register double a11 = a[(i1+1)*n+k1+1];
							register double b00 = b[k1*n+j1];
							register double b10 = b[(k1+1)*n+j1];
							register double b01 = b[k1*n+j1+1];
							register double b11 = b[(k1+1)*n+j1+1];
							
							c00 += a00 * b00 + a01 * b10;
							c10 += a10 * b00 + a11 * b10;
							c01 += a00 * b01 + a01 * b11;
							c11 += a10 * a01 + a11 * b11;
						}
						c[i1*n+j1] += c00;
						c[(i1+1)*n+j1] += c10;
						c[i1*n+j1+1] += c01;
						c[(i1+1)*n+j1+1] += c11;
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
				for(int j1 = j; j1 < j + B && j1 < n; j1 += 2) {
					for(int i1 = i; i1 < i + B && i1 < n; i1 += 2) {
						register double c00, c01, c10, c11;
						c00 = c01 = c10 = c11 = 0;
						for(int k1 = k; k1 < k + B && k1 < n; k1 += 2) {
							register double a00 = a[i1*n+k1];
							register double a10 = a[(i1+1)*n+k1];
							register double a01 = a[i1*n+k1+1];
							register double a11 = a[(i1+1)*n+k1+1];
							register double b00 = b[k1*n+j1];
							register double b10 = b[(k1+1)*n+j1];
							register double b01 = b[k1*n+j1+1];
							register double b11 = b[(k1+1)*n+j1+1];
							
							c00 += a00 * b00 + a01 * b10;
							c10 += a10 * b00 + a11 * b10;
							c01 += a00 * b01 + a01 * b11;
							c11 += a10 * a01 + a11 * b11;
						}
						c[i1*n+j1] += c00;
						c[(i1+1)*n+j1] += c10;
						c[i1*n+j1+1] += c01;
						c[(i1+1)*n+j1+1] += c11;
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
				for(int k1 = k; k1 < k + B && k1 < n; k1 += 2) {
					for(int i1 = i; i1 < i + B && i1 < n; i1 += 2) {
						register double a00 = a[i1*n+k1];
						register double a10 = a[(i1+1)*n+k1];
						register double a01 = a[i1*n+k1+1];
						register double a11 = a[(i1+1)*n+k1+1];
						for(int j1 = j; j1 < j + B && j1 < n; j1 += 2) {
							register double b00 = b[k1*n+j1];
							register double b10 = b[(k1+1)*n+j1];
							register double b01 = b[k1*n+j1+1];
							register double b11 = b[(k1+1)*n+j1+1];
							c[i1*n+j1] += a00 * b00 + a01 * b10;
							c[(i1+1)*n+j1] += a10 * b00 + a11 * b10;
							c[i1*n+j1+1] += a00 * b01 + a01 * b11;
							c[(i1+1)*n+j1+1] += a10 * a01 + a11 * b11;
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
				for(int i1 = i; i1 < i + B && i1 < n; i1 += 2) {
					for(int k1 = k; k1 < k + B && k1 < n; k1 += 2) {
						register double a00 = a[i1*n+k1];
						register double a10 = a[(i1+1)*n+k1];
						register double a01 = a[i1*n+k1+1];
						register double a11 = a[(i1+1)*n+k1+1];
						for(int j1 = j; j1 < j + B && j1 < n; j1 += 2) {
							register double b00 = b[k1*n+j1];
							register double b10 = b[(k1+1)*n+j1];
							register double b01 = b[k1*n+j1+1];
							register double b11 = b[(k1+1)*n+j1+1];
							c[i1*n+j1] += a00 * b00 + a01 * b10;
							c[(i1+1)*n+j1] += a10 * b00 + a11 * b10;
							c[i1*n+j1+1] += a00 * b01 + a01 * b11;
							c[(i1+1)*n+j1+1] += a10 * a01 + a11 * b11;
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
				for(int j1 = j; j1 < j + B && j1 < n; j1 += 2) {
					for(int k1 = k; k1 < k + B && k1 < n; k1 += 2) {
						register double b00 = b[k1*n+j1];
						register double b10 = b[(k1+1)*n+j1];
						register double b01 = b[k1*n+j1+1];
						register double b11 = b[(k1+1)*n+j1+1];
						for(int i1 = i; i1 < i + B && i1 < n; i1 += 2) {
							register double a00 = a[i1*n+k1];
							register double a10 = a[(i1+1)*n+k1];
							register double a01 = a[i1*n+k1+1];
							register double a11 = a[(i1+1)*n+k1+1];
							c[i1*n+j1] += a00 * b00 + a01 * b10;
							c[(i1+1)*n+j1] += a10 * b00 + a11 * b10;
							c[i1*n+j1+1] += a00 * b01 + a01 * b11;
							c[(i1+1)*n+j1+1] += a10 * a01 + a11 * b11;
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
				for(int k1 = k; k1 < k + B && k1 < n; k1 += 2) {
					for(int j1 = j; j1 < j + B && j1 < n; j1 += 2) {
						register double b00 = b[k1*n+j1];
						register double b10 = b[(k1+1)*n+j1];
						register double b01 = b[k1*n+j1+1];
						register double b11 = b[(k1+1)*n+j1+1];
						for(int i1 = i; i1 < i + B && i1 < n; i1 += 2) {
							register double a00 = a[i1*n+k1];
							register double a10 = a[(i1+1)*n+k1];
							register double a01 = a[i1*n+k1+1];
							register double a11 = a[(i1+1)*n+k1+1];
							c[i1*n+j1] += a00 * b00 + a01 * b10;
							c[(i1+1)*n+j1] += a10 * b00 + a11 * b10;
							c[i1*n+j1+1] += a00 * b01 + a01 * b11;
							c[(i1+1)*n+j1+1] += a10 * a01 + a11 * b11;
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
	int B = 2;
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