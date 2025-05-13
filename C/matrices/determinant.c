#include <stdio.h>
#include <math.h>

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
    printf("The determinant of above matrix is %d",determinant(r,c,matrix));
    return 0;
}