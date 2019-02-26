#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// implementations of dgemm0 through dgemm3 omitted on this page

void timeMultiplication(char *name, void (*mmm)(double*, double*,
    double*, int), double *a, double *b, double *c, int n) {
    clock_t start = clock();
    (*mmm)(a, b, c, n);
    double seconds = (double) (clock() - start) / CLOCKS_PER_SEC;
    double gflops = ((double) 3 * n*n*n) / 1000000000.0 / seconds;
    printf("%s completed in %.6f seconds (%.4f GFLOPS)\n", name,
        seconds, gflops);
}

int main(int argc, char *argv[]) {
    srand(time(0));

    int n = 1000;
    if(argc > 1) {
        n = atoi(argv[1]);
    }
    double *a = malloc(sizeof(double) * n*n);
    double *b = malloc(sizeof(double) * n*n);
    double *c0 = malloc(sizeof(double) * n*n);
    double *c1 = malloc(sizeof(double) * n*n);
    double *c2 = malloc(sizeof(double) * n*n);
    double *c3 = malloc(sizeof(double) * n*n);

    for(int i = 0; i < n*n; i++) { 
        // Initialize A and B to random values and C to zero
        a[i] = (double) rand() / RAND_MAX * 1024;
        b[i] = (double) rand() / RAND_MAX * 1024;
        c0[i] = c1[i] = c2[i] = c3[i] = 0;
    }

    timeMultiplication("dgemm0", dgemm0, a, b, c0, n);
    timeMultiplication("dgemm1", dgemm1, a, b, c1, n);
    timeMultiplication("dgemm2", dgemm2, a, b, c2, n);
    timeMultiplication("dgemm3", dgemm3, a, b, c3, n);

    double maxdiff1 = 0;
    double maxdiff2 = 0;
    double maxdiff3 = 0;
    for(int i = 0; i < n*n; i++) {
        double diff1 = fabs(c1[i] - c0[i]);
        if(diff1 > maxdiff1) {
            maxdiff1 = diff1;
        }
        double diff2 = fabs(c2[i] - c0[i]);
        if(diff2 > maxdiff2) {
            maxdiff2 = diff2;
        }
        double diff3 = fabs(c3[i] - c0[i]);
        if(diff3 > maxdiff3) {
            maxdiff3 = diff3;
        }
    }
    printf("Maximum difference for dgemm1 is %.6f\n, maxdiff1);
    printf("Maximum difference for dgemm2 is %.6f\n, maxdiff2);
    printf("Maximum difference for dgemm3 is %.6f\n, maxdiff3);

    free(a);
    free(b);
    free(c0);
    free(c1);
    free(c2);
    free(c3);
    return 0;
}