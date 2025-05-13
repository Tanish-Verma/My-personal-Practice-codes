#include <stdio.h>
#include <stdlib.h>


void Gauss_elimination(int n, double **A, double *b) {
    for(int k=0;k<n;k++){
        for(int i=k+1;i<n;i++){
            double m = A[i][k]/A[k][k];
            for(int j=k+1;j<n;j++){
                A[i][j] = A[i][j] - m*A[k][j];
            }
            b[i] = b[i] - m*b[k];
        }
    }
}

double * backward_substitution(int n, double **A, double *b){
    double *x = (double *)malloc(n*sizeof(double));
    x[n-1] = b[n-1]/A[n-1][n-1];
    for(int i=n-2;i>=0;i--){
        double sum = 0;
        for(int j=i+1;j<n;j++){
            sum = sum + A[i][j]*x[j];
        }
        x[i] = (b[i] - sum)/A[i][i];
    }
    return x;
}
int main(){
    int n;
    printf("Enter the number of equations: ");
    scanf("%d", &n);
    double **A = (double **)malloc(n*sizeof(double *));
    for(int i=0;i<n;i++){
        A[i] = (double *)malloc(n*sizeof(double));
    }
    double *b = (double *)malloc(n*sizeof(double));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("Enter the value of A[%d][%d]: ", i+1, j+1);
            scanf("%lf", &A[i][j]);
        }
    }
    for(int i=0;i<n;i++){
        printf("Enter the value of b[%d]: ", i+1);
        scanf("%lf", &b[i]);
    }
    Gauss_elimination(n, A, b);
    double *x = backward_substitution(n, A, b);
    for(int i=0;i<n;i++){
        printf("The value of x[%d] is: %lf\n", i+1, x[i]);
    }
    return 0;
}