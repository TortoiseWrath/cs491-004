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