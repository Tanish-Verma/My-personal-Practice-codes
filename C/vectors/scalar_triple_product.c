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

int scalar_triple_product(int coords1[3],int coords2[3], int coords3[3]){
    int matrix[3][3]={{coords1[0],coords1[1],coords1[2]},{coords2[0],coords2[1],coords2[2]},{coords3[0],coords3[1],coords3[2]}};
    int k=determinant(3,3,matrix);
    return k;
}

int main(){
   char axis[3] = {'x', 'y', 'z'};
    int coords[3];
    
    printf("For vector 1: \n");
    for (int i = 0; i < 3; i++) {
        printf("Enter the value of %c coordinates for vector 1: ", axis[i]);
        scanf("%d", &coords[i]);
    }
    
    int coords2[3];
    printf("\nFor vector 2: \n");
    for (int i = 0; i < 3; i++) {
        printf("Enter the value of %c coordinates for vector 2: ", axis[i]);
        scanf("%d", &coords2[i]);
    } 
    int coords3[3];
    printf("\nFor vector 3: \n");
    for (int i = 0; i < 3; i++) {
        printf("Enter the value of %c coordinates for vector 2: ", axis[i]);
        scanf("%d", &coords3[i]);
    } 

    printf("[[%d %d %d]X[%d %d %d].[%d %d %d]]=%d",coords[0],coords[1],coords[2],coords2[0],coords2[1],coords2[2],coords3[0],coords3[1],coords3[2],scalar_triple_product(coords2,coords3,coords));
    return 0;
}