// Note: In the screenshots of my code, comments have been intentionally omitted to ensure clear and unobstructed visibility of the code structure and logic.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
double* subtractVectors(double *vector1, double *vector2, int n) {
    double *result = (double *)malloc(n * sizeof(double)); // Allocate memory for the result vector
    if (result == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    // Perform element-wise subtraction
    for (int i = 0; i < n; i++) {
        result[i] = vector1[i] - vector2[i];
    }

    return result; // Return the result vector
}

// Function to calculate the Euclidean norm of a vector
double calculateNorm(double *vector, int n) {
    double norm = 0.0;
    // Compute the sum of squares of the vector elements
    for (int i = 0; i < n; i++) {
        norm += vector[i] * vector[i];
    }
    return norm; // Return the norm
}

// Function to solve a system of linear equations using the Gauss-Seidel method
double* Gauss_seidel(double **A, double *b, int n, double weight, double epsilon) {
    double *x = (double *)malloc(n * sizeof(double)); // Allocate memory for the solution vector
    if (x == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    double *xg = (double *)malloc(n * sizeof(double)); // Allocate memory for the previous iteration vector
    if (xg == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    // Initialize xg with initial guesses (e.g., 1.0 for all elements)
    for (int i = 0; i < n; i++) {
        xg[i] = 1.0;
    }

    // Copy initial guesses into x
    for (int i = 0; i < n; i++) {
        x[i] = xg[i];
    }

    // Compute the initial residual and tolerance
    double *residual = subtractVectors(b, multiplyMatrixVector(A, xg, n), n);
    if (residual == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for residual\n");
        exit(1);
    }
    double tolerance = calculateNorm(residual, n);
    int iteration = 0;

    // Iterate until the tolerance is less than the specified epsilon
    while (tolerance > epsilon) {
        for (int i = 0; i < n; i++) {
            double sigma = 0.0;
            // Compute the sum of A[i][j] * x[j] for j != i
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sigma += A[i][j] * x[j];
                }
            }
            // Update the value of x[i] using the weighted Gauss-Seidel formula
            x[i] = (1 - weight) * xg[i] + weight * (b[i] - sigma) / A[i][i];
        }

        // Update xg with the new values of x
        for (int i = 0; i < n; i++) {
            xg[i] = x[i];
        }

        // Recalculate the residual and tolerance
        free(residual);
        residual = subtractVectors(b, multiplyMatrixVector(A, xg, n), n);
        tolerance = calculateNorm(residual, n);

        iteration++; // Increment the iteration counter
    }

    printf("\n==============================\n");
    printf("Converged in %d iterations.\n", iteration);
    printf("==============================\n");

    free(residual); // Free the residual vector
    return x; // Return the solution vector
}

// Main function to execute the Gauss-Seidel method
int main() {
    int n;
    printf("Enter the number of variables: ");
    scanf("%d", &n); // Read the size of the system

    double epsilon;
    printf("Enter the value of epsilon: ");
    scanf("%lf", &epsilon); // Read the convergence tolerance

    double w;
    printf("Enter the value of weight w: ");
    scanf("%lf", &w); // Read the relaxation factor

    // Allocate memory for matrix A
    double **A = (double **)malloc(n * sizeof(double *));
    if (A == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }
    for (size_t i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        if (A[i] == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            return 1;
        }
    }

    // Allocate memory for vector b
    double *b = (double *)malloc(n * sizeof(double));
    if (b == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }

    // Read inputs from the file
    readInputsFromFile("inputs.txt", A, b, n);

    clock_t start, end;
    double cpu_time_used;

    // Solve the system using the Gauss-Seidel method and measure runtime
    start = clock();
    double *solution = Gauss_seidel(A, b, n, w, epsilon);
    end = clock();

    cpu_time_used = ((double)(end - start)) * 1000000000 / CLOCKS_PER_SEC;
    printf("\n==============================\n");
    printf("Time taken to solve: %.0f ns\n", cpu_time_used);
    printf("==============================\n");

    // Print the solution vector
    printf("\n==============================\n");
    printf("Solution Vector:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %.3lf\n", i + 1, solution[i]);
    }
    printf("==============================\n");

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(solution);

    return 0;
}