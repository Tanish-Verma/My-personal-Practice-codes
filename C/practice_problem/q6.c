#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap2(int **a, int **b) {
    int *temp = *a;
    *a = *b;
    *b = temp;
}

void columnsort(int **arr, int l, int m, int cols) {
    // Calculate the sum of columns for the two rows
    int *sum = (int *)calloc(cols, sizeof(int));
    for (int k = 0; k < cols; k++) {
        sum[k] = arr[l][k] + arr[m][k];
    }

    // Sort the columns based on their sums
    for (int i = 0; i < cols - 1; i++) {
        for (int j = 0; j < cols - 1 - i; j++) {
            if (sum[j] > sum[j + 1]) {
                // Swap the column sums
                swap(&sum[j], &sum[j + 1]);
                
                // Swap the values in the respective columns of the two rows
                swap(&arr[l][j], &arr[l][j + 1]);
                swap(&arr[m][j], &arr[m][j + 1]);
            }
        }
    }

    free(sum);
}

void dynamic_sort(int **arr, int rows, int cols) {
    int *sum = (int *)calloc(rows, sizeof(int));
    
    // Calculate row sums
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum[i] += arr[i][j];
        }
    }

    // Sort rows based on row sums
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - 1 - i; j++) {
            if (sum[j] > sum[j + 1]) {
                // Swap row sums
                swap(&sum[j], &sum[j + 1]);
                
                // Swap the row pointers
                swap2(&arr[j], &arr[j + 1]);
            } else if (sum[j] == sum[j + 1]) {
                // If row sums are equal, sort the columns
                columnsort(arr, j, j + 1, cols);
            }
        }
    }

    free(sum);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int **matrix = (int **)calloc(n, sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)calloc(m, sizeof(int));
        for (int j = 0; j < m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Call the sorting function
    dynamic_sort(matrix, n, m);

    // Print the sorted matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
