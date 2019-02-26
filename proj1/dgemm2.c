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