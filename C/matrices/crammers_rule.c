#include <stdio.h>
#include <stdlib.h>

double determinant(double **matrix, int n);

double *cramers_rule(double **matrix, double *vector, int n) {
    double *result = malloc(n * sizeof(double));
    double det = determinant(matrix, n);
    if (det == 0) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        double **temp = malloc(n * sizeof(double *));
        for (int j = 0; j < n; j++) {
            temp[j] = malloc(n * sizeof(double));
            for (int k = 0; k < n; k++) {
                temp[j][k] = matrix[j][k];
            }
        }
        for (int j = 0; j < n; j++) {
            temp[j][i] = vector[j];
        }
        result[i] = determinant(temp, n) / det;
        for (int j = 0; j < n; j++) {
            free(temp[j]);
        }
        free(temp);
    }
    return result;
}

double determinant(double **matrix, int n) {
    if (n == 1) {
        return matrix[0][0];
    }
    double det = 0;
    for (int i = 0; i < n; i++) {
        double **temp = malloc((n - 1) * sizeof(double *));
        for (int j = 0; j < n - 1; j++) {
            temp[j] = malloc((n - 1) * sizeof(double));
        }
        for (int j = 1; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (k < i) {
                    temp[j - 1][k] = matrix[j][k];
                } else if (k > i) {
                    temp[j - 1][k - 1] = matrix[j][k];
                }
            }
        }
        det += matrix[0][i] * determinant(temp, n - 1) * (i % 2 == 0 ? 1 : -1);
        for (int j = 0; j < n - 1; j++) {
            free(temp[j]);
        }
        free(temp);
    }
    return det;
}

int main() {
    int n;
    printf("Enter the number of equations: ");
    scanf("%d", &n);

    double **matrix = malloc(n * sizeof(double *));
    double *vector = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(n * sizeof(double));
        for (int j = 0; j < n; j++) {
            printf("Enter the coefficient of x%d for equation %d: ", j + 1, i + 1);
            scanf("%lf", &matrix[i][j]);
        }
        printf("Enter the constant for equation %d: ", i + 1);
        scanf("%lf", &vector[i]);
    }

    double *result = cramers_rule(matrix, vector, n);
    if (result == NULL) {
        printf("The system of equations has no solution\n");
    } else {
        printf("The solution is:\n");
        for (int i = 0; i < n; i++) {
            printf("x%d = %lf\n", i + 1, result[i]);
        }
        free(result);
    }

    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
    free(vector);

    return 0;
}