// Note: In the screenshots of my code, comments have been intentionally omitted to ensure clear and unobstructed visibility of the code structure and logic.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

// Function to perform the Gram-Schmidt process to compute the orthogonal matrix Q
void Gram_schmidt(int n, double **A, double **Q)
{
    // Initialize the first column of Q as the first column of A
    for (int i = 0; i < n; i++)
    {
        Q[i][0] = A[i][0];
    }

    // Iterate over each column of A starting from the second column
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Q[j][i] = A[j][i]; // Copy the current column of A into Q
            for (size_t k = 0; k < i; k++) // Iterate over previous columns of Q
            {
                double norm = 0;
                double vector_product = 0;
                for (size_t l = 0; l < n; l++) // Compute the projection of A[:,i] onto Q[:,k]
                {
                    vector_product += Q[l][k] * A[l][i]; //Calculates the dot product between column k of Q and column i of A
                    norm += Q[l][k] * Q[l][k];// Calculates the squared norm of column k of Q
                }
                // Subtract the projection from Q[:,i]
                Q[j][i] -= (vector_product * Q[j][k]) / norm;
            }
        }
    }

    // Normalize each column of Q to make it orthonormal
    for (size_t i = 0; i < n; i++)
    {
        double norm = 0;
        for (size_t j = 0; j < n; j++) // Compute the norm of the column
        {
            norm += Q[j][i] * Q[j][i];
        }
        norm = sqrt(norm); // Take the square root of the sum of squares
        for (size_t k = 0; k < n; k++) // Divide each element by the norm
        {
            Q[k][i] /= norm;
        }
    }

    // Print the orthogonal matrix Q
    printf("Matrix Q after Gram-Schmidt process:\n");
    for (int i = 0; i < n; i++) {
        printf("[");
        for (int j = 0; j < n; j++) {
            printf("%.5lf ", Q[i][j]);
        }
        printf("]\n");
    }
}

// Function to perform backward substitution to solve Rx = b
double *backward_substitution(int n, double **A, double *b){
    double *x = (double *)malloc(n * sizeof(double));
    if (x == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    // Solve for the last variable
    x[n-1] = b[n-1] / A[n-1][n-1];
    // Iterate from the second-to-last variable to the first
    for(int i=n-2; i>=0; i--){
        double sum = 0;
        for(int j=i+1; j<n; j++){ // Compute the sum of known terms
            sum = sum + A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i]; // Solve for the current variable
    }
    return x;
}

// Function to transpose a square matrix in-place
void transpose(int n, double **A) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

// Function to multiply two square matrices A and B, storing the result in C
void matrix_multiply_nn(int n, double **A, double **B, double **C) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0; // Initialize the result element to 0
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j]; // Perform the dot product
            }
        }
    }
}

// Function to multiply a square matrix A with a vector B, storing the result in C
void matrix_multiply_n1(int n, double **A, double *B, double *C) {
    for (int i = 0; i < n; i++) {
        C[i] = 0; // Initialize the result element to 0
        for (int j = 0; j < n; j++) {
            C[i] += A[i][j] * B[j]; // Perform the dot product
        }
    }
}

// Function to perform QR factorization and solve Ax = b
double * QR_factorization(int n, double**A,double*b){
    // Allocate memory for Q and R matrices
    double **Q = malloc(n * sizeof(double*));
    double **R = malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        Q[i] = malloc(n * sizeof(double));
        R[i] = malloc(n * sizeof(double));
    }

    // Perform the Gram-Schmidt process to compute Q
    Gram_schmidt(n,A,Q);

    // Transpose Q to compute Q^T
    transpose(n,Q);

    // Compute R = Q^T * A
    matrix_multiply_nn(n,Q,A,R);

    // Compute Q^T * b
    double *b1 = (double *)malloc(n * sizeof(double));
    if (b1 == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    matrix_multiply_n1(n,Q,b,b1);

    // Free memory allocated for Q
    for(int i=0; i<n; i++){
        free(Q[i]);
    }
    free(Q);

    // Solve Rx = Q^T * b using backward substitution
    double * x = backward_substitution(n,R,b1);

    // Free memory allocated for R and b1
    for(int i=0; i<n; i++){
        free(R[i]);
    }
    free(R);
    free(b1);

    return x; // Return the solution vector x
}

// Function to read matrix A and vector b from a file
void read_file_input(int n, double **A, double *b){
    FILE *file = fopen("inputs.txt", "r"); // Open the input file
    if (file == NULL) {
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }
    // Read the matrix A from the file
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if (fscanf(file, "%lf", &A[i][j]) != 1) {
                fprintf(stderr, "Invalid input\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    // Read the vector b from the file
    for(int i=0; i<n; i++){
        if (fscanf(file, "%lf", &b[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            exit(EXIT_FAILURE);
        }
    }
    fclose(file); // Close the file
}

// Main function to execute the QR factorization and solve the system
int main()
{
    int n;
    printf("Enter the number of variables: ");
    scanf("%d", &n); // Read the size of the system

    // Allocate memory for matrix A and vector b
    double **A = malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        A[i] = malloc(n * sizeof(double));
    }
    double *b = (double *)malloc(n * sizeof(double));
    if (b == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Read input from file
    read_file_input(n,A,b);

    // Measure runtime of QR factorization
    clock_t start = clock();
    double *x = QR_factorization(n, A, b);
    clock_t end = clock();

    // Print the solution vector
    printf("\n==============================\n");
    printf("Solution Vector (x):\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %10.6f\n", i + 1, x[i]);
    }
    printf("==============================\n");

    // Print runtime
    printf("\n==============================\n");
    printf("Time taken: %ld ns\n", (end - start) * 1000000000L / CLOCKS_PER_SEC);
    printf("==============================\n");

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(x);

    return 0;
}