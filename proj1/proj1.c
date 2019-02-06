#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void dgemm0(double *a, double *b, double *c, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                c[i*n+j] += a[i*n+k] * b[k*n+j];
            }
        }
    }
}

void dgemm1(double *a, double *b, double *c, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            register double r = c[i*n+j];
            for(int k = 0; k < n; k++) {
                r += a[i*n+k] * b[k*n+j];
            }
            c[i*n+j] = r;
        }
    }
}

void dgemm2(double *a, double *b, double *c, int n) {
    int i, j, k;
    for(i = 0; i < n; i += 2) {
        for(j = 0; j < n; j += 2) {
            register double c0 = c[i*n + j];
            register double c1 = c[i*n + j+1];
            register double c2 = c[(i+1)*n + j];
            register double c3 = c[(i+1)*n + j+1];
            for(k = 0; k < n; k += 2) {
                register double a0 = a[i*n + k];
                register double a1 = a[i*n + k+1];
                register double a2 = a[(i+1)*n + k];
                register double a3 = a[(i+1)*n + k+1];
                register double b0 = b[k*n + j];
                register double b1 = b[k*n + j+1];
                register double b2 = b[(k+1)*n + j];
                register double b3 = b[(k+1)*n + j+1];
                c0 += a0*b0 + a1*b2;
                c2 += a2*b0 + a3*b2;
                c1 += a0*b1 + a1*b3;
                c3 += a2*b1 + a3*b3;
            }
            c[i*n + j] = c0;
            c[i*n + j+1] = c1;
            c[(i+1)*n + j] = c2;
            c[(i+1)*n + j+1] = c3;
        }
    }
}

void dgemm3(double *a, double *b, double *c, int n) {
    register int i, j, k;
    register int rn = n;
    for(i = 0; i < rn; i += 2) {
        register int in = i*rn;
        for(k = 0; k < rn; k += 2) {
            register int kn = k*rn;
            register double a0 = a[in + k];
            register double a1 = a[in + k+1];
            register double a2 = a[in+rn + k];
            register double a3 = a[in+rn + k+1];
            for(j = 0; j < rn; j += 2) {
                register double b0 = b[kn + j];
                register double b1 = b[kn + j+1];
                register double b2 = b[kn+rn + j];
                register double b3 = b[kn+rn + j+1];
                c[in + j] += a0*b0 + a1*b2;
                c[in+rn + j] += a2*b0 + a3*b2;
                c[in + j+1] += a0*b1 + a1*b3;
                c[in+rn + j+1] += a2*b1 + a3*b3;
            }
        }
    }
}

void timeMultiplication(char *name, void (*mmm)(double*, double*, double*, int), double *a, double *b, double *c, int n) {
    clock_t start = clock();
    (*mmm)(a, b, c, n);
    double seconds = (double) (clock() - start) / CLOCKS_PER_SEC;
    double gflops = ((double) 3 * n*n*n) / 1000000000.0 / seconds;
    printf("%s completed in %.6f seconds (%.4f GFLOPS)\n", name, seconds, gflops);
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

    for(int i = 0; i < n*n; i++) { // Initialize A and B to random values and C to zero
        a[i] = (double) rand() / RAND_MAX * 1024; // 1024 is arbitrary
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
    printf("Maximum difference for dgemm1 is %.6f\nMaximum difference for dgemm2 is %.6f\nMaximum difference for dgemm3 is %.6f\n", maxdiff1, maxdiff2, maxdiff3);

    free(a);
    free(b);
    free(c0);
    free(c1);
    free(c2);
    free(c3);
    return 0;
}