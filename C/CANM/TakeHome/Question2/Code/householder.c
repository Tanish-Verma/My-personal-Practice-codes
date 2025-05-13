// Note: In the screenshots of my code, comments have been intentionally omitted to ensure clear and unobstructed visibility of the code structure and logic.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Function to compute the Euclidean norm of a vector
double norm(double* v, int len) {
    // Initialize the sum of squares
    double sum = 0.0;
    // Iterate through the vector elements
    for (int i = 0; i < len; ++i)
        sum += v[i] * v[i]; // Add the square of each element to the sum
    // Return the square root of the sum (Euclidean norm)
    return sqrt(sum);
}

// Function to perform matrix multiplication
void matmul(double** A, double** B, double** C, int n) {
    // Iterate over rows of A
    for (int i = 0; i < n; ++i)
        // Iterate over columns of B
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0.0; // Initialize the result matrix element to 0
            // Perform the dot product of row i of A and column j of B
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }
}

// Function to compute the transpose of a matrix
void transpose(double** src, double** dst, int n) {
    // Iterate over rows and columns of the source matrix
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dst[j][i] = src[i][j]; // Assign the transposed value
}

// Function to compute the Householder matrix H
void compute_H(double* u, double** H, int n) {
    // Iterate over rows and columns of the matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            H[i][j] = (i == j) ? 1.0 : 0.0; // Initialize as identity matrix
            H[i][j] -= 2.0 * u[i] * u[j];  // Subtract the Householder term
        }
    }
}

// Function to perform QR decomposition using Householder reflections
void qr_householder(double** A, double** Q, double** R, int n) {
    // Copy A into R and initialize Q as the identity matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            R[i][j] = A[i][j]; // Copy A into R
            Q[i][j] = (i == j) ? 1.0 : 0.0; // Initialize Q as identity matrix
        }
    }

    // Allocate reusable temporary matrices
    double** tempR = (double**)malloc(n * sizeof(double*));
    double** tempQ = (double**)malloc(n * sizeof(double*));
    double** H = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        tempR[i] = (double*)calloc(n, sizeof(double)); // Temporary R matrix
        tempQ[i] = (double*)calloc(n, sizeof(double)); // Temporary Q matrix
        H[i] = (double*)calloc(n, sizeof(double));     // Householder matrix
    }

    // Iterate over each column to compute Householder reflections
    for (int i = 0; i < n; i++) {
        // Extract the column vector x starting from the diagonal
        double* x = (double*)malloc((n - i) * sizeof(double));
        for (int j = 0; j < n - i; j++) {
            x[j] = R[j + i][i]; // Copy the column elements into x
        }

        // Compute the norm of x
        double xnorm = norm(x, n - i);
        if (xnorm == 0) { // Skip if the norm is zero
            free(x);
            continue;
        }

        // Compute the Householder vector u
        double* u = (double*)calloc(n, sizeof(double));
        u[i] = xnorm - x[0]; // Set the first element of u
        u[i] /= 2 * xnorm;  
        u[i] = sqrt(u[i]);   // Take the square root
        for (int j = 1; j < n - i; j++) {
            u[j + i] = x[j] / (-2 * u[i] * xnorm); // Compute remaining elements
        }

        // Construct the Householder matrix H
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                H[j][k] = (j == k ? 1.0 : 0.0) - 2.0 * u[j] * u[k];
            }
        }

        // Update R by multiplying H with R
        matmul(H, R, tempR, n);
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                R[j][k] = tempR[j][k]; // Copy the result back to R
            }
        }

        // Update Q by multiplying Q with the transpose of H
        transpose(H, tempQ, n); // Compute the transpose of H
        matmul(Q, tempQ, tempR, n); // Multiply Q with H^T
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                Q[j][k] = tempR[j][k]; // Copy the result back to Q
            }
        }

        // Free temporary vectors
        free(x);
        free(u);
    }

    // Free temporary matrices
    for (int i = 0; i < n; i++) {
        free(tempR[i]);
        free(tempQ[i]);
        free(H[i]);
    }
    free(tempR);
    free(tempQ);
    free(H);
}

// Function to solve the system of linear equations using QR decomposition
void solve_using_qr(double** Q, double** R, double* b, double* x, int n) {
    // Compute Q^T * b
    double* Qtb = calloc(n, sizeof(double));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Qtb[i] += Q[j][i] * b[j]; // Multiply Q^T with b
        }
    }

    // Perform back substitution to solve R * x = Q^T * b
    for (int i = n - 1; i >= 0; --i) {
        x[i] = Qtb[i]; // Start with the current element of Qtb
        for (int j = i + 1; j < n; ++j) {
            x[i] -= R[i][j] * x[j]; // Subtract the known terms
        }
        x[i] /= R[i][i]; // Divide by the diagonal element of R
    }

    free(Qtb); // Free the temporary vector
}

// Function to read matrix A and vector b from a file
void read_file_input(int n, double **A, double *b) {
    FILE *file = fopen("inputs.txt", "r"); // Open the input file
    if (file == NULL) { // Check if the file was opened successfully
        fprintf(stderr, "Failed to open input file\n");
        exit(1);
    }

    // Read the matrix A from the file
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(file, "%lf", &A[i][j]) != 1) {
                fprintf(stderr, "Failed to read matrix A from file\n");
                exit(1);
            }
        }
    }

    // Read the vector b from the file
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%lf", &b[i]) != 1) {
            fprintf(stderr, "Failed to read vector b from file\n");
            exit(1);
        }
    }

    fclose(file); // Close the file
}

// Main function to execute the QR decomposition and solve the system
int main() {
    int n;
    printf("Enter the number of variables: ");
    scanf("%d", &n); // Read the size of the system

    // Allocate memory for matrix A and vector b
    double **A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }
    double *b = (double *)malloc(n * sizeof(double));

    // Read input from file
    read_file_input(n, A, b);

    // Allocate memory for matrices Q, R, and solution vector x
    double** Q = malloc(n * sizeof(double*));
    double** R = malloc(n * sizeof(double*));
    for (int i = 0; i < n; ++i) {
        Q[i] = calloc(n, sizeof(double));
        R[i] = calloc(n, sizeof(double));
    }
    double* x = calloc(n, sizeof(double));

    // Perform QR decomposition and measure runtime
    clock_t start = clock();
    qr_householder(A, Q, R, n);
    clock_t end = clock();

    // Solve the system of equations
    solve_using_qr(Q, R, b, x, n);

    // Print the solution vector
    printf("\n==============================\n");
    printf("Solution Vector (x):\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %10.6f\n", i + 1, x[i]);
    }
    printf("==============================\n");

    // Print runtime
    printf("\n==============================\n");
    printf("Runtime: %ld ns\n", (end - start) * 1000000000L / CLOCKS_PER_SEC);
    printf("==============================\n");

    // Print matrix Q
    printf("\n==============================\n");
    printf("Matrix Q (Orthogonal):\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%10.6f ", Q[i][j]);
        }
        printf("\n");
    }
    printf("==============================\n");

    // Free allocated memory
    free(x);
    for (int i = 0; i < n; ++i) {
        free(A[i]);
        free(Q[i]);
        free(R[i]);
    }
    free(A);
    free(Q);
    free(R);
    free(b);
    return 0;
}
