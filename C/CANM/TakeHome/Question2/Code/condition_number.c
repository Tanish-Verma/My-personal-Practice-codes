// Note: In the screenshots of my code, comments have been intentionally omitted to ensure clear and unobstructed visibility of the code structure and logic.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to read a square matrix from a file
void read_matrix(const char *filename, double **matrix, int n) {
    FILE *file = fopen(filename, "r"); // Open the file for reading
    if (!file) { // Check if the file was opened successfully
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read the matrix elements from the file
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%lf", &matrix[i][j]);
        }
    }

    fclose(file); // Close the file
}

// Function to calculate the  norm (maximum row sum) of a matrix
double calculate_norm(double **matrix, int n) {
    double norm = 0.0;
    // Iterate over each row
    for (int i = 0; i < n; i++) {
        double row_sum = 0.0;
        // Compute the sum of absolute values of elements in the row
        for (int j = 0; j < n; j++) {
            row_sum += fabs(matrix[i][j]);
        }
        // Update the norm if the current row sum is greater
        if (row_sum > norm) {
            norm = row_sum;
        }
    }
    return norm; // Return the infinity norm
}

// Function to calculate the determinant of a square matrix
double determinant(double **matrix, int n) {
    if (n == 1) { // Base case for 1x1 matrix
        return matrix[0][0];
    }
    if (n == 2) { // Base case for 2x2 matrix
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    double det = 0.0; // Initialize determinant
    // Iterate over the first row to expand along it
    for (int p = 0; p < n; p++) {
        // Allocate memory for the submatrix
        double **submatrix = (double **)malloc((n - 1) * sizeof(double *));
        for (int i = 0; i < n - 1; i++) {
            submatrix[i] = (double *)malloc((n - 1) * sizeof(double));
        }

        // Construct the submatrix by excluding the current row and column
        for (int i = 1; i < n; i++) {
            int col_index = 0;
            for (int j = 0; j < n; j++) {
                if (j != p) {
                    submatrix[i - 1][col_index++] = matrix[i][j];
                }
            }
        }

        // Recursive call to calculate the determinant of the submatrix
        det += (p % 2 == 0 ? 1 : -1) * matrix[0][p] * determinant(submatrix, n - 1);

        // Free the allocated memory for the submatrix
        for (int i = 0; i < n - 1; i++) {
            free(submatrix[i]);
        }
        free(submatrix);
    }
    return det; // Return the determinant
}

// Function to compute the adjoint of a square matrix
void adjoint(double **matrix, double **adj, int n) {
    if (n == 1) { // Base case for 1x1 matrix
        adj[0][0] = 1.0;
        return;
    }

    // Iterate over each element of the matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Allocate memory for the submatrix
            double **submatrix = (double **)malloc((n - 1) * sizeof(double *));
            for (int k = 0; k < n - 1; k++) {
                submatrix[k] = (double *)malloc((n - 1) * sizeof(double));
            }

            // Construct the submatrix by excluding the current row and column
            int row_index = 0;
            for (int row = 0; row < n; row++) {
                if (row == i) continue;
                int col_index = 0;
                for (int col = 0; col < n; col++) {
                    if (col == j) continue;
                    submatrix[row_index][col_index++] = matrix[row][col];
                }
                row_index++;
            }

            // Compute the cofactor and assign it to the adjoint matrix
            adj[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * determinant(submatrix, n - 1);

            // Free the allocated memory for the submatrix
            for (int k = 0; k < n - 1; k++) {
                free(submatrix[k]);
            }
            free(submatrix);
        }
    }
}

// Function to compute the inverse of a square matrix
void invert_matrix(double **matrix, double **inverse, int n) {
    double det = determinant(matrix, n); // Calculate the determinant
    if (fabs(det) < 1e-9) { // Check if the matrix is singular
        fprintf(stderr, "Matrix is singular or nearly singular.\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the adjoint matrix
    double **adj = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        adj[i] = (double *)malloc(n * sizeof(double));
    }

    adjoint(matrix, adj, n); // Compute the adjoint matrix

    // Compute the inverse by dividing the adjoint by the determinant
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = adj[i][j] / det;
        }
    }

    // Free the allocated memory for the adjoint matrix
    for (int i = 0; i < n; i++) {
        free(adj[i]);
    }
    free(adj);
}

// Main function to compute the condition number of a matrix
int main() {
    int n;
    printf("Enter the size of the matrix (n): ");
    scanf("%d", &n); // Read the size of the matrix

    // Allocate memory for the matrix and its inverse
    double **matrix = (double **)malloc(n * sizeof(double *));
    double **inverse = (double **)malloc(n * sizeof(double *));
    for (size_t i = 0; i < n; i++) {
        matrix[i] = (double *)malloc(n * sizeof(double));
        inverse[i] = (double *)malloc(n * sizeof(double));
    }

    // Read the matrix from the input file
    read_matrix("inputs.txt", matrix, n);

    // Calculate the norm of the matrix
    double norm = calculate_norm(matrix, n);

    // Calculate the inverse of the matrix
    invert_matrix(matrix, inverse, n);

    // Calculate the norm of the inverse matrix
    double inverse_norm = calculate_norm(inverse, n);

    // Compute the condition number as the product of the norms
    double condition_number = norm * inverse_norm;
    printf("Condition number of the matrix: %lf\n", condition_number);

    // Free the allocated memory
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
        free(inverse[i]);
    }
    free(matrix);
    free(inverse);

    return 0;
}
