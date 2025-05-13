// Note: In the screenshots of my code, comments have been intentionally omitted to ensure clear and unobstructed visibility of the code structure and logic.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to perform LU Decomposition of matrix A into L and U
void LU_Decomposition(int n, double **A, double **L, double **U){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i<=j){ // Compute elements of U (upper triangular matrix)
                U[i][j] = A[i][j];
                for(int k=0; k<i; k++){
                    U[i][j] -= L[i][k] * U[k][j]; // Subtract the sum of L[i][k] * U[k][j]
                }
                if(i==j){ // Diagonal elements of L are set to 1
                    L[i][j] = 1;
                } else {
                    L[i][j] = 0; // Off-diagonal elements of L are 0
                }
            } else { // Compute elements of L (lower triangular matrix)
                L[i][j] = A[i][j];
                for(int k=0; k<j; k++){
                    L[i][j] -= L[i][k] * U[k][j]; // Subtract the sum of L[i][k] * U[k][j]
                }
                L[i][j] /= U[j][j]; // Divide by the diagonal element of U
                U[i][j] = 0; // Off-diagonal elements of U are 0
            }
        }
    }
}

// Function to perform forward substitution to solve L*y = b
double* Forward_Substitution(int n, double **L, double *b){
    double *x = (double*)malloc(n * sizeof(double));
    if (x == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<n; i++){
        x[i] = b[i]; // Initialize x[i] with b[i]
        for(int j=0; j<i; j++){
            x[i] -= L[i][j] * x[j]; // Subtract the known terms
        }
    }
    return x;   
}

// Function to perform backward substitution to solve U*x = y
double* Backward_Substitution(int n, double **U, double *b){
    double *x = (double *)malloc(n * sizeof(double));
    if (x == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for(int i=n-1; i>=0; i--){ // Start from the last row
        x[i] = b[i]; // Initialize x[i] with b[i]
        for(int j=i+1; j<n; j++){
            x[i] -= U[i][j] * x[j]; // Subtract the known terms
        }
        x[i] /= U[i][i]; // Divide by the diagonal element of U
    }
    return x;
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
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }
    // Read the vector b from the file
    for(int i=0; i<n; i++){
        if (fscanf(file, "%lf", &b[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }
    fclose(file); // Close the file
}

// Main function to perform LU decomposition and solve the system of equations
int main(){
    int n;
    printf("Enter the number of equations: ");
    scanf("%d", &n); // Read the size of the system

    // Allocate memory for matrices A, L, U
    double **A = (double **)malloc(n * sizeof(double *));
    double **L = (double **)malloc(n * sizeof(double *));
    double **U = (double **)malloc(n * sizeof(double *));
    if (A == NULL || L == NULL || U == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<n; i++){
        A[i] = (double *)malloc(n * sizeof(double));
        L[i] = (double *)calloc(n, sizeof(double)); // Initialize L with zeros
        U[i] = (double *)calloc(n, sizeof(double)); // Initialize U with zeros
        if (A[i] == NULL || L[i] == NULL || U[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    // Allocate memory for vector b
    double *b = (double *)malloc(n * sizeof(double));
    if (b == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Read input from file
    read_file_input(n, A, b);

    clock_t start, end;
    double cpu_time_used;

    // Perform LU decomposition and measure time
    start = clock();
    LU_Decomposition(n, A, L, U);
    end = clock();
    cpu_time_used = ((double)(end - start)) * 1000000000 / CLOCKS_PER_SEC;
    printf("\n==============================\n");
    printf("Time taken for LU Decomposition: %.0f ns\n", cpu_time_used);
    double total_time = cpu_time_used;
    printf("==============================\n");

    // Solve the system of equations using forward and backward substitution
    start = clock();
    double *y = Forward_Substitution(n, L, b); // Solve L*y = b
    double *x = Backward_Substitution(n, U, y); // Solve U*x = y
    end = clock();
    cpu_time_used = ((double)(end - start)) * 1000000000 / CLOCKS_PER_SEC;
    total_time += cpu_time_used;

    printf("\n==============================\n");
    printf("Time taken for solving equations: %.0f ns\n", cpu_time_used);
    printf("Total time taken: %.0f ns\n", total_time);
    printf("==============================\n");

    // Print the solution vector
    printf("\n==============================\n");
    for(int i=0; i<n; i++){
        printf("The value of x[%d] is: %.3lf\n", i+1, x[i]);
    }
    printf("==============================\n");

    // Free allocated memory
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