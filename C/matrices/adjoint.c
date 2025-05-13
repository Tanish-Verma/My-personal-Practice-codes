#include <stdio.h>
#include <math.h>

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

int determinant(int row,int col,int arr[row][col]){
    int det=0;
    if (row==2 && col==2){
        return ((arr[0][0]*arr[1][1])-(arr[1][0]*arr[0][1]));
        }
    else{
        int submatrix[row-1][col-1];
        for(int l=0;l<row;l++){
            int sub_j=0,sub_i=0;
            for(int i=0;i<row;i++){
                if(i==l)continue;
                sub_j=0;
                for(int j=0;j<col;j++){
                    if(j==0)continue;
                    submatrix[sub_i][sub_j]=arr[i][j];
                    sub_j++;
                }
                sub_i++;
            }
            
            det+=pow(-1,l)*arr[l][0]*determinant(row-1,col-1,submatrix);
        }
    }
    return det;
}

void get_adjoint(int row,int col,int arr[row][col]){
    int cofactor[row][col];
    int adjoint[row][col];
    if (row==2){
        adjoint[0][0]=arr[1][1];
        adjoint[1][1]=arr[0][0];
        adjoint[0][1]=-1*arr[0][1];
        adjoint[1][0]=-1*arr[1][0];
        
    }
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            int submatrix[row-1][col-1];
            getSubmatrix(row,col,arr,submatrix,i,j);
            cofactor[i][j]=pow(-1,i+j)*determinant(row-1,col-1,submatrix);
        }
    }

    for (int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            adjoint[j][i]=cofactor[i][j];
        }
    }

    for(int i=0;i<col;i++){
        printf("[ ");
        for(int j=0;j<row;j++){
            printf("%d ",adjoint[i][j]);
        }
        printf("]\n");
    }
}
int main(){
    int r,c;
    do
    {
        printf("Enter the number of rows: ");
        scanf("%d",&r);
        printf("Enter the number of columns: ");
        scanf("%d",&c);
        if(r!=c){
            printf("The number of rows and column should be same\n");
        }
    } while (r!=c);
    

    int matrix[r][c];
    for (int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            int k=0;
            printf("Enter the number for row %d and column %d for matrix: ",i+1,j+1);
            scanf("%d",&k);
            matrix[i][j]=k;

        }
    }
    for(int i=0;i<c;i++){
        printf("[ ");
        for(int j=0;j<r;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("]\n");
    }

    printf("The adjoint of above matrix is: \n");
    get_adjoint(r,c,matrix);
    
    return 0;
}