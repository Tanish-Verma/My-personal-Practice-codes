#include <stdio.h>
#include <math.h>

// Function to get the submatrix by removing the specified row and column
void getSubmatrix(int row, int col, int matrix[row][col], int submatrix[row-1][col-1], int r, int c) {
    int sub_j = 0, sub_i = 0;
    for (int i = 0; i < row; i++) {
        if (i == r) continue; // Skip the row to be removed
        sub_j = 0;
        for (int j = 0; j < col; j++) {
            if (j == c) continue; // Skip the column to be removed
            submatrix[sub_i][sub_j] = matrix[i][j];
            sub_j++;
        }
        sub_i++;
    }
}

// Function to calculate the determinant of a matrix
int determinant(int row,int col,int arr[row][col]){
    int det = 0;
    if (row == 2 && col == 2) { // Base case for 2x2 matrix
        return ((arr[0][0] * arr[1][1]) - (arr[1][0] * arr[0][1]));
    } else {
        int submatrix[row-1][col-1];
        for(int l = 0; l < row; l++) {
            int sub_j = 0, sub_i = 0;
            for(int i = 0; i < row; i++) {
                if (i == l) continue; // Skip the current row
                sub_j = 0;
                for(int j = 0; j < col; j++) {
                    if (j == 0) continue; // Skip the first column
                    submatrix[sub_i][sub_j] = arr[i][j];
                    sub_j++;
                }
                sub_i++;
            }
            // Recursive calculation of determinant using Laplace expansion
            det += pow(-1, l) * arr[l][0] * determinant(row-1, col-1, submatrix);
        }
    }
    return det;
}

// Function to calculate the adjoint of the matrix
void get_adjoint(int row, int col, int arr[row][col], int adjoint2[row][col]){
    int cofactor[row][col];
    int adjoint[row][col];
    if (row == 2) { // Special case for 2x2 matrix
        adjoint[0][0] = arr[1][1];
        adjoint[1][1] = arr[0][0];
        adjoint[0][1] = -1 * arr[0][1];
        adjoint[1][0] = -1 * arr[1][0];
    } else {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                int submatrix[row-1][col-1];
                getSubmatrix(row, col, arr, submatrix, i, j);
                // Calculate cofactor for each element
                cofactor[i][j] = pow(-1, i + j) * determinant(row-1, col-1, submatrix);
            }
        }
        // Transpose of the cofactor matrix to get the adjoint
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                adjoint[j][i] = cofactor[i][j];
            }
        }
    }
    // Copy the adjoint to the output parameter
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            adjoint2[i][j] = adjoint[i][j];
        }
    }
}

// Function to calculate the inverse of the matrix
void get_inverse(int row, int col, int arr[row][col], float inverse_stor[row][col]){
    float inverse[row][col];
    int adjoint[row][col];
    get_adjoint(row, col, arr, adjoint); // Get the adjoint of the matrix
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            // Calculate the inverse by dividing the adjoint by the determinant
            inverse[i][j] = (float)adjoint[i][j] / (determinant(row, col, arr));
        }
    }
    // Store the inverse in the provided array
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < row; j++) {
            inverse_stor[i][j] = inverse[i][j];
        }
    }

    // Print the inverse matrix
    for(int i = 0; i < row; i++) {
        printf("[ ");
        for(int j = 0; j < col; j++) {
            printf("%.2f ", inverse[i][j]);
        }
        printf("]\n");
    }
}

int main(){
    int r, c;
    // Ensure the matrix is square
    do {
        printf("Enter the number of rows: ");
        scanf("%d", &r);
        printf("Enter the number of columns: ");
        scanf("%d", &c);
        if(r != c) {
            printf("The number of rows and columns should be the same\n");
        }
    } while (r != c);
    
    int matrix[r][c];
    // Input matrix elements and ensure the determinant is not zero
    do {
        for (int i = 0; i < r; i++) {
            for(int j = 0; j < c; j++) {
                int k = 0;
                printf("Enter the number for row %d and column %d for matrix: ", i+1, j+1);
                scanf("%d", &k);
                matrix[i][j] = k;
            }
        }
        if (determinant(r, c, matrix) == 0) {
            printf("The determinant cannot be zero, please input different values.\n");
        }
    } while(determinant(r, c, matrix) == 0);

    // Print the input matrix
    for(int i = 0; i < c; i++) {
        printf("[ ");
        for(int j = 0; j < r; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("]\n");
    }

    float inverse[r][c];
    printf("The inverse of the above matrix is: \n");
    get_inverse(r, c, matrix, inverse); // Calculate the inverse

    // Verify the result by multiplying the original matrix by its inverse
    printf("Proof:\n");

    for (int i = 0; i < r; i++) {
        printf("[ ");
        for(int j = 0; j < c; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("]\n");
    }
    printf("\tX\n");
    for (int i = 0; i < r; i++) {
        printf("[ ");
        for(int j = 0; j < c; j++) {
            printf("%0.2f ", inverse[i][j]);
        }
        printf("]\n");
    }
    
    float product[r][c];
    // Multiply original matrix with its inverse to check if it gives the identity matrix
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            float result = 0;
            for(int l = 0; l < c; l++) {
                result += matrix[i][l] * inverse[l][j];
            }
            product[i][j] = result;
        }
    }
    printf("\t=\n");
    // Print the resulting product matrix
    for (int i = 0; i < r; i++) {
        printf("[ ");
        for(int j = 0; j < c; j++) {
            printf("%.2f ", product[i][j]);
        }  
        printf("]\n"); 
    }
    printf("Hence verified");
    return 0;
}
