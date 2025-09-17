#include <x86intrin.h>
#include <stdio.h>

void dgemm(int n, double *a, double *b, double *c) {
    for (int i = 0; i < n; i+=4) {
        for (int j = 0; j < n; j++) {
            __m256d c0 = _mm256_load_pd(c + i + j * n);
            for (int k = 0; k < n; k++) {
                c0 = _mm256_add_pd(c0, 
                        _mm256_mul_pd(_mm256_load_pd(a + i + k * n),
                            _mm256_broadcast_sd(b + k + j * n)));
            }
            _mm256_store_pd(c + i + j * n, c0);
        }
    }
}


int main(void) {
    double a[] = {1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};
    double b[16] = {0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0};

    dgemm(4, a, a, b);

    for (int i = 0; i < 16; i++) { 
        printf("%f ", b[i]);
    }

    printf("\n");
}
