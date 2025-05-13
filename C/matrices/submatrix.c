#include <stdio.h>

void getSubmatrix(int row, int col, int matrix[row][col], int submatrix[row-1][col-1], int r, int c) {
    int sub_j = 0, sub_i = 0;
    for (int i = 0; i < row; i++) {
        if (i == r) continue;
        sub_j = 0;
        for (int j = 0; j < col; j++) {
            if (j == c) continue;
            submatrix[sub_i][sub_j] = matrix[i][j];
            sub_j++;
        }
        sub_i++;
    }
}

int main() {
    int r, c;
    printf("Enter the number of rows: ");
    scanf("%d", &r);
    printf("Enter the number of columns: ");
    scanf("%d", &c);
    int matrix[r][c];
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int k = 0;
            printf("Enter the number for row %d and column %d for matrix: ", i + 1, j + 1);
            scanf("%d", &k);
            matrix[i][j] = k;
        }
    }

    int submatrix[r-1][c-1]; // Declare the submatrix

    getSubmatrix(r, c, matrix, submatrix, 3, 2); // Pass the submatrix as an argument

    printf("The submatrix is:\n");
    for (int i = 0; i < r-1; i++) {
        printf("[ ");
        for (int j = 0; j < c-1; j++) {
            printf("%d ", submatrix[i][j]);
        }
        printf("]\n");
    }

    return 0;
}
