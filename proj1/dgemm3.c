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