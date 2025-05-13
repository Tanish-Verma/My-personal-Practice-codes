#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to print a matrix
void print_matrix(double **matrix, int rows, int cols) {
    printf("\nMatrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (j < cols - i) { // Only print valid entries in the forward difference matrix
                printf("%10.5lf ", matrix[i][j]);
            } else {
                printf("          "); // Print spaces for invalid entries
            }
        }
        printf("\n");
    }
}

double F(double x) {
    return exp(0.8 * x) - 1;
}

int read_data_from_file(const char *filename, double *x, double *f, int n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%lf %lf", &x[i], &f[i]) != 2) {
            fprintf(stderr, "Error: Invalid data format in file\n");
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

void compute_forward_differences(double *f, double **forward_diff, int n) {
    for (int i = 0; i < n; i++) {
        forward_diff[i][0] = f[i];
    }
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            forward_diff[i][j] = forward_diff[i + 1][j - 1] - forward_diff[i][j - 1];
        }
    }
}

double factorial(int n) {
    double result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

double newtonian_forward_polynomial(double *x, double **forward_diff, int degree, double x_i, int start_index) {
    double result = forward_diff[start_index][0];
    double term = 1.0;
    double u = (x_i - x[start_index]) / (x[start_index + 1] - x[start_index]);
    for (int i = 1; i <= degree; i++) {
        term *= (u - (i - 1));
        result += (term * forward_diff[start_index][i]) / factorial(i);
    }
    return result;
}

double *global_differences;

int compare_indices(const void *a, const void *b) {
    int index_a = *(const int *)a;
    int index_b = *(const int *)b;
    if (global_differences[index_a] < global_differences[index_b]) return -1;
    if (global_differences[index_a] > global_differences[index_b]) return 1;
    return 0;
}

int find_start_index(double *x, int n, double x_i, int degree) {
    double *differences = (double *)malloc(n * sizeof(double));
    int *indices = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        differences[i] = fabs(x_i - x[i]);
        indices[i] = i;
    }
    global_differences = differences;
    qsort(indices, n, sizeof(int), compare_indices);

    int *selected_points = (int *)malloc((degree + 1) * sizeof(int));
    for (int i = 0; i <= degree; i++) {
        selected_points[i] = indices[i];
    }
    int start_index = selected_points[0];
    for (int i = 1; i <= degree; i++) {
        if (selected_points[i] < start_index) {
            start_index = selected_points[i];
        }
    }
    free(differences);
    free(indices);
    free(selected_points);
    return start_index;
}

int main() {
    int n, degree;
    double x_i;
    printf("Enter the size of data: ");
    scanf("%d", &n);
    double *x = (double *)malloc(n * sizeof(double));
    double *f = (double *)malloc(n * sizeof(double));
    if (x == NULL || f == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }
    if (n < 2) {
        fprintf(stderr, "Error: The size of data (n) must be at least 2.\n");
        free(x);
        free(f);
        return 1;
    }
    if (!read_data_from_file("data.txt", x, f, n)) {
        free(x);
        free(f);
        return 1;
    }
    printf("Enter the degree of Newtonian polynomial: ");
    scanf("%d", &degree);
    if (degree >= n) {
        fprintf(stderr, "Error: The degree of the polynomial must be less than the size of data (n).\n");
        free(x);
        free(f);
        return 1;
    }
    printf("Enter the value of x: ");
    scanf("%lf", &x_i);
    if (x_i < x[0] || x_i > x[n - 1]) {
        fprintf(stderr, "Error: The input value of x is out of the range of the data.\n");
        free(x);
        free(f);
        return 1;
    }

    double h = x[1] - x[0];
    double **forward_diff = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        forward_diff[i] = (double *)malloc(n * sizeof(double));
    }
    compute_forward_differences(f, forward_diff, n);

    // Print the forward difference matrix
    print_matrix(forward_diff, n, n);

    int start_index = find_start_index(x, n, x_i, degree);
    double computed_value = newtonian_forward_polynomial(x, forward_diff, degree, x_i, start_index);
    double actual_value = F(x_i);
    double error = fabs(actual_value - computed_value);

    printf("\nResults:\n");
    printf("-------------------------------\n");
    printf("Input value of x: %20.10lf\n", x_i);
    printf("Degree of polynomial: %14d\n", degree);
    printf("Computed value of f(x): %15.10lf\n", computed_value);
    printf("Actual value of f(x): %17.10lf\n", actual_value);
    printf("Error: %30.20lf\n", error);
    printf("-------------------------------\n");

    for (int i = 0; i < n; i++) {
        free(forward_diff[i]);
    }
    free(forward_diff);
    free(x);
    free(f);

    return 0;
}