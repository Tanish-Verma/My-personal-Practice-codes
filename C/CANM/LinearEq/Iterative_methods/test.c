#include <stdio.h>
#include <math.h>
#define MAX_ITER 100
#define TOL 1e-6
#define N 3  // Change this for different system sizes

void gauss_jacobi(double a[N][N], double b[N], double x[N]) {
    double x_old[N];
    int iter = 0;
    while (iter < MAX_ITER) {
        for (int i = 0; i < N; i++) {
            x_old[i] = x[i];
        }
        
        for (int i = 0; i < N; i++) {
            double sum = 0.0;
            for (int j = 0; j < N; j++) {
                if (j != i) {
                    sum += a[i][j] * x_old[j];
                }
            }
            x[i] = (b[i] - sum) / a[i][i];
        }
        
        double error = 0.0;
        for (int i = 0; i < N; i++) {
            error += fabs(x[i] - x_old[i]);
        }
        if (error < TOL) break;
        iter++;
    }
}

void gauss_seidel(double a[N][N], double b[N], double x[N]) {
    int iter = 0;
    while (iter < MAX_ITER) {
        double x_old[N];
        for (int i = 0; i < N; i++) {
            x_old[i] = x[i];
        }
        
        for (int i = 0; i < N; i++) {
            double sum = 0.0;
            for (int j = 0; j < N; j++) {
                if (j != i) {
                    sum += a[i][j] * x[j];
                }
            }
            x[i] = (b[i] - sum) / a[i][i];
        }
        
        double error = 0.0;
        for (int i = 0; i < N; i++) {
            error += fabs(x[i] - x_old[i]);
        }
        if (error < TOL) break;
        iter++;
    }
}

int main() {
    double a[N][N] = {{4, -1, 0}, {-1, 4, -1}, {0, -1, 4}};
    double b[N] = {2, 6, 2};
    double x[N] = {0, 0, 0};  // Initial guess

    printf("Gauss-Jacobi Method:\n");
    gauss_jacobi(a, b, x);
    for (int i = 0; i < N; i++) {
        printf("x[%d] = %lf\n", i, x[i]);
    }
    
    // Reset initial guess for Gauss-Seidel
    for (int i = 0; i < N; i++) x[i] = 0;
    
    printf("\nGauss-Seidel Method:\n");
    gauss_seidel(a, b, x);
    for (int i = 0; i < N; i++) {
        printf("x[%d] = %lf\n", i, x[i]);
    }
    
    return 0;
}
