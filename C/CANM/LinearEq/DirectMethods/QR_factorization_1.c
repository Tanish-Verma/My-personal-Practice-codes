#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int Gram_schmidt(int n, double **A, double **Q)
{
    for (int i = 0; i < n; i++)
    {
        Q[i][0] = A[i][0];
    }
    
    
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Q[j][i] = A[j][i];
            for (size_t k = 0; k < i; k++)
            {
                double norm = 0;
                double vector_product=0;
                for (size_t l = 0; l < n; l++)
                {
                    vector_product+=Q[l][k]*A[l][i];
                    norm += Q[l][k] * Q[l][k];
                }
                Q[j][i] -= (vector_product*Q[j][k]) / norm;
            }
        }
    }
    for (size_t i = 0; i < n; i++)
    {
        double norm = 0;
        for (size_t j = 0; j < n; j++)
        {
            norm += Q[j][i] * Q[j][i];
        }
        norm = sqrt(norm);
        for (size_t k = 0; k < n; k++)
        {
            Q[k][i] /= norm;
        }
    }

    printf("Matrix Q after Gram-Schmidt process:\n");
    for (int i = 0; i < n; i++) {
        printf("[");
        for (int j = 0; j < n; j++) {
            printf("%.5lf ", Q[i][j]);
        }
        printf("]\n");
    }
} 
double *backward_substitution(int n, double **A, double *b){
    double *x = (double *)malloc(n * sizeof(double));
    if (x == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    x[n-1] = b[n-1] / A[n-1][n-1];
    for(int i=n-2; i>=0; i--){
        double sum = 0;
        for(int j=i+1; j<n; j++){
            sum = sum + A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }
    return x;
}

void transpose(int n, double **A) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

void matrix_multiply_nn(int n, double **A, double **B, double **C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_multiply_n1(int n, double **A, double *B, double *C) {
    for (int i = 0; i < n; i++) {
        C[i] = 0;
        for (int j = 0; j < n; j++) {
            C[i] += A[i][j] * B[j];
        }
    }
}

double * QR_factorization(int n, double**A,double*b){
    double **Q = (double **)malloc(n * sizeof(double *));
    if (Q == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<n; i++){
        Q[i] = (double *)malloc(n * sizeof(double));
        if (Q[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    double **R = (double **)malloc(n * sizeof(double *));
    if (R == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<n; i++){
        R[i] = (double *)malloc(n * sizeof(double));
        if (R[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    Gram_schmidt(n,A,Q);
    transpose(n,Q);
    matrix_multiply_nn(n,Q,A,R);
    double *b1 = (double *)malloc(n * sizeof(double));
    if (b1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    matrix_multiply_n1(n,Q,b,b1);
    for(int i=0; i<n; i++){
        free(Q[i]);
    }
    free(Q);

    double * x=backward_substitution(n,R,b1);
    for(int i=0; i<n; i++){
        free(R[i]);
    }
    free(R);
    free(b1);
    return x;
}

void read_file_input(int n, double **A, double *b){
    FILE *file = fopen("inputs.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if (fscanf(file, "%lf", &A[i][j]) != 1) {
                fprintf(stderr, "Invalid input\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    for(int i=0; i<n; i++){
        if (fscanf(file, "%lf", &b[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            exit(EXIT_FAILURE);
        }
    }
    
    fclose(file);
}

void print_matrix(int n , double ** A){
    for (size_t i = 0; i < n; i++)
    {
        /* code */
        printf("[");
        for (size_t j = 0; j < n; j++)
        {
            printf("%.5lf ",A[i][j]);
        }
        printf("]\n");
    }
    
}

void delete_text_files() {
    remove("input.txt");
    remove("solutions.txt");
    remove("computed_values.txt");
}
int main()
{
    int n;
    printf("Enter the size of matrix: ");
    scanf("%d",&n);
    double **A = (double **)malloc(n * sizeof(double *));
    if (A == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<n; i++){
        A[i] = (double *)malloc(n * sizeof(double));
        if (A[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
   

    double *b = (double *)malloc(n * sizeof(double));
    if (b == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    read_file_input(n,A,b);
    double * x=QR_factorization(n,A,b);
    for(int i=0; i<n; i++){
        printf("The value of x[%d] is: %lf\n", i+1, x[i]);
    }


    // Free allocated memory
    for(int i=0; i<n; i++){
        free(A[i]);
    }
    free(A);
    free(b);
    free(x);

    // Delete the text files
    delete_text_files();
    return 0;
}