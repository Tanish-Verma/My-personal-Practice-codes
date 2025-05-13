#include <stdio.h>

int main(){
    int r,c;
    printf("Enter the number of rows: ");
    scanf("%d",&r);
    printf("Enter the number of columns: ");
    scanf("%d",&c);
    int matrix[r][c];
    for (int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            int k=0;
            printf("Enter the number for row %d and column %d for matrix: ",i+1,j+1);
            scanf("%d",&k);
            matrix[i][j]=k;

        }
    }
    printf("The given matrix is: \n");
    for (int i=0;i<r;i++){
        printf("[ ");
        for(int j=0;j<c;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("]\n");}
    printf("The transpose of the matrix is: \n");
    int transpose[c][r];
    for (int i=0;i<r;i++){
        for(int j=0;j<r;j++){
            transpose[j][i]=matrix[i][j];
        }
    }
    for(int i=0;i<c;i++){
        printf("[ ");
        for(int j=0;j<r;j++){
            printf("%d ",transpose[i][j]);
        }
        printf("]\n");
    }
    return 0;
}