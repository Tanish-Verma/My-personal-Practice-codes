#include <stdio.h>
#include <stdlib.h>

void LU_Decomposition(int n, double **A, double **L, double **U){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i<=j){
                U[i][j] = A[i][j];
                for(int k=0; k<i; k++){
                    U[i][j] -= L[i][k] * U[k][j];
                }
                if(i==j){
                    L[i][j] = 1;
                } else {
                    L[i][j] = 0;
                }
            } else {
                L[i][j] = A[i][j];
                for(int k=0; k<j; k++){
                    L[i][j] -= L[i][k] * U[k][j];
                }
                L[i][j] /= U[j][j];
                U[i][j] = 0;
            }
        }
    }
}

double* Forward_Substitution(int n, double **L, double *b){
    double *x = (double*)malloc(n * sizeof(double));
    if (x == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<n; i++){
        x[i] = b[i];
        for(int j=0; j<i; j++){
            x[i] -= L[i][j] * x[j];
        }
    }
    return x;   
}

double* Backward_Substitution(int n, double **U, double *b){
    double *x = (double *)malloc(n * sizeof(double));
    if (x == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for(int i=n-1; i>=0; i--){
        x[i] = b[i];
        for(int j=i+1; j<n; j++){
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
    return x;
}

void read_file_input(int n, double **A, double *b){
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if (fscanf(file, "%lf", &A[i][j]) != 1) {
                fprintf(stderr, "Invalid input\n");
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }
    for(int i=0; i<n; i++){
        if (fscanf(file, "%lf", &b[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }
    fclose(file);
}

int main(){
    int n;
    printf("Enter the number of equations: ");
    scanf("%d", &n);

    double **A = (double **)malloc(n * sizeof(double *));
    double **L = (double **)malloc(n * sizeof(double *));
    double **U = (double **)malloc(n * sizeof(double *));
    if (A == NULL || L == NULL || U == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<n; i++){
        A[i] = (double *)malloc(n * sizeof(double));
        L[i] = (double *)calloc(n, sizeof(double)); 
        U[i] = (double *)calloc(n, sizeof(double));
        if (A[i] == NULL || L[i] == NULL || U[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    double *b = (double *)malloc(n * sizeof(double));
    if (b == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    read_file_input(n, A, b);
    
    LU_Decomposition(n, A, L, U);

    printf("The Lower Triangular Matrix is: \n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%lf ", L[i][j]);
        }
        printf("\n");
    }

    printf("The Upper Triangular Matrix is: \n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%lf ", U[i][j]);
        }
        printf("\n");
    }

    double *y = Forward_Substitution(n, L, b);
    double *x = Backward_Substitution(n, U, y);

    for(int i=0; i<n; i++){
        printf("The value of x[%d] is: %lf\n", i+1, x[i]);
    }

    for(int i=0; i<n; i++){
        free(A[i]);
        free(L[i]);
        free(U[i]);
    }
    free(A);
    free(L);
    free(U);
    free(b);
    free(y);
    free(x);

    return 0;
}