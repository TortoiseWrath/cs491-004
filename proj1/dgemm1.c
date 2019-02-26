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