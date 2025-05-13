#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void Gauss_elimination(int n, double **A, double *b) {
    for(int k=0; k<n; k++){
        for(int i=k+1; i<n; i++){
            double m = A[i][k] / A[k][k];
            for(int j=k+1; j<n; j++){
                A[i][j] = A[i][j] - m * A[k][j];
            }
            b[i] = b[i] - m * b[k];
        }
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

void write_computed_values(int n, double *x_computed) {
    FILE *file = fopen("computed_values.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Could not open computed_values.txt for writing\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%f\n", x_computed[i]);
    }
    fclose(file);
}

void run_python_script(int n) {
    // Construct the command string to pass the values to the Python script
    char command[1024];
    snprintf(command, sizeof(command), "python3 compare_solutions.py %d", n);

    // Run the Python script with the command
    system(command);
}

void delete_text_files() {
    remove("input.txt");
    remove("solutions.txt");
    remove("computed_values.txt");
}

int main(){
    int n;
    printf("Enter the number of equations: ");
    scanf("%d", &n);
    char command[100];
    sprintf(command, "python3 Equations.py %d", n);
    system(command);
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

    read_file_input(n, A, b);
    Gauss_elimination(n, A, b);
    double *x = backward_substitution(n, A, b);
    for(int i=0; i<n; i++){
        printf("The value of x[%d] is: %lf\n", i+1, x[i]);
    }

    write_computed_values(n, x);
    run_python_script(n);

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