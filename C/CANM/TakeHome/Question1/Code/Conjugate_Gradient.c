// Note: In the screenshots of my code, comments have been intentionally omitted to ensure clear and unobstructed visibility of the code structure and logic.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Function to read matrix A and vector b from a file
void readInputsFromFile(const char *filename, double **A, double *b, int n) {
    FILE *file = fopen(filename, "r"); // Open the file for reading
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(1);
    }

    // Read matrix A from the file
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(file, "%lf", &A[i][j]) != 1) {
                fprintf(stderr, "Error: Invalid input format in file\n");
                fclose(file);
                exit(1);
            }
        }
    }

    // Read vector b from the file
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%lf", &b[i]) != 1) {
            fprintf(stderr, "Error: Invalid input format in file\n");
            fclose(file);
            exit(1);
        }
    }

    fclose(file); // Close the file
}

// Function to multiply a matrix with a vector
double* multiplyMatrixVector(double **A, double *b, int n) {
    double *result = (double *)malloc(n * sizeof(double)); // Allocate memory for the result vector
    if (result == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    // Perform matrix-vector multiplication
    for (int i = 0; i < n; i++) {
        result[i] = 0;
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * b[j];
        }
    }

    return result; // Return the result vector
}

// Function to subtract two vectors
double* subtractVectors(double *v1, double *v2, int n) {
    double *result = (double *)malloc(n * sizeof(double)); // Allocate memory for the result vector
    if (!result) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    // Perform element-wise subtraction
    for (int i = 0; i < n; i++) {
        result[i] = v1[i] - v2[i];
    }

    return result; // Return the result vector
}

// Function to compute the dot product of two vectors
double multiplyVectors(int n, double *v1, double *v2) {
    double result = 0.0;
    // Compute the sum of element-wise products
    for (int i = 0; i < n; i++) {
        result += v1[i] * v2[i];
    }
    return result; // Return the dot product
}

// Function to solve a system of linear equations using the Conjugate Gradient method
double* Conjugate_Gradient(double **A, double *b, int n, double epsilon, int *iterations) {
    *iterations = 0; // Initialize the iteration counter

    // Allocate memory for the solution vector and initialize it with initial guesses (e.g., 1.0)
    double *x = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) x[i] = 1.0;

    // Compute the initial residual r = b - A*x
    double *Ax = multiplyMatrixVector(A, x, n);
    double *r = subtractVectors(b, Ax, n);
    free(Ax); // Free the temporary vector Ax

    // Allocate memory for the direction vector d and the new residual r_new
    double *d = (double *)malloc(n * sizeof(double));
    double *r_new = (double *)malloc(n * sizeof(double));

    // Initialize the direction vector d with the residual r
    for (int i = 0; i < n; i++) d[i] = r[i];

    // Compute the initial tolerance as the norm of the residual
    double tol = sqrt(multiplyVectors(n, r, r));

    // Iterate until the tolerance is less than the specified epsilon
    while (tol > epsilon) {
        // Compute A*d
        double *Ad = multiplyMatrixVector(A, d, n);

        // Compute the step size alpha
        double alpha = multiplyVectors(n, r, r) / multiplyVectors(n, d, Ad);

        // Update the solution vector x
        for (int i = 0; i < n; i++) x[i] += alpha * d[i];

        // Update the residual r_new
        for (int i = 0; i < n; i++) r_new[i] = r[i] - alpha * Ad[i];

        // Compute the scaling factor beta
        double beta = multiplyVectors(n, r_new, r_new) / multiplyVectors(n, r, r);

        // Update the direction vector d
        for (int i = 0; i < n; i++) d[i] = r_new[i] + beta * d[i];

        // Update the residual r
        for (int i = 0; i < n; i++) r[i] = r_new[i];

        // Recompute the tolerance
        tol = sqrt(multiplyVectors(n, r, r));

        free(Ad); // Free the temporary vector Ad
        (*iterations)++; // Increment the iteration counter
    }

    // Free allocated memory for residuals and direction vector
    free(r);
    free(r_new);
    free(d);

    return x; // Return the solution vector
}

// Main function to execute the Conjugate Gradient method
int main() {
    int n;
    printf("Enter the number of variables: ");
    scanf("%d", &n); // Read the size of the system

    double epsilon;
    printf("Enter the value of epsilon: ");
    scanf("%lf", &epsilon); // Read the convergence tolerance

    // Allocate memory for matrix A
    double **A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }

    // Allocate memory for vector b
    double *b = (double *)malloc(n * sizeof(double));

    // Read inputs from the file
    readInputsFromFile("inputs.txt", A, b, n);

    clock_t start = clock(); // Start the timer
    int iterations;
    double *x = Conjugate_Gradient(A, b, n, epsilon, &iterations); // Solve the system
    clock_t end = clock(); // End the timer

    // Compute the time taken in nanoseconds
    double time_ns = ((double)(end - start)) * 1e9 / CLOCKS_PER_SEC;

    // Print the results
    printf("\n==============================\n");
    printf("Converged in %d iterations.\n", iterations);
    printf("Time taken to solve: %.0f ns\n", time_ns);
    printf("==============================\n");

    printf("\nSolution Vector:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %.3lf\n", i + 1, x[i]);
    }
    printf("==============================\n");

    // Free allocated memory
    for (int i = 0; i < n; i++) free(A[i]);
    free(A);
    free(b);
    free(x);

    return 0;
}