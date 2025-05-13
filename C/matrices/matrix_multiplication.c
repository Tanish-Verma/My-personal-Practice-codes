#include <stdio.h>

int main(){
    int r1,r2,c1,c2;
    do
    {
        printf("Enter the number of rows for matrix 1: ");
        scanf("%d",&r1);
        printf("Enter the number of column for matrix 1: ");
        scanf("%d",&c1);
        printf("Enter the number of rows for matrix 2: ");
        scanf("%d",&r2);
        printf("Enter the number of column for matrix 2: ");
        scanf("%d",&c2);
        if (c1==r2)break;
        else{
            printf("The column of matrix 1 doesnt matches row of matrix 2.\nTry again\n");
        }
        
    } while (1);
    
        
    int matrix1[r1][c1],matrix2[r2][c2];
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            int k;
            printf("Enter the number for row %d and column %d for matrix 1: ",i+1,j+1);
            scanf("%d",&k);
            matrix1[i][j]=k;
        }
    }
    
    for(int i=0;i<r2;i++){
        for(int j=0;j<c2;j++){
            int l;
            printf("Enter the number for row %d and column %d for matrix 2: ",i+1,j+1);
            scanf("%d",&l);
            matrix2[i][j]=l;
            
        }
    }
    for (int i=0;i<r1;i++){
        printf("[ ");
        for(int j=0;j<c1;j++){
            printf("%d ",matrix1[i][j]);
        }
        printf("]\n");}
    printf("\tX\n");
    for (int i=0;i<r2;i++){
        printf("[ ");
        for(int j=0;j<c2;j++){
            printf("%d ",matrix2[i][j]);
        }
        printf("]\n");}
    
    int product[r1][c2];
    for(int i=0;i<r1;i++){
        for(int j=0;j<c2;j++){
            int result=0;
            for(int l=0;l<c1;l++){
                result+=matrix1[i][l]*matrix2[l][j];
            }
            product[i][j]=result;
        }
    }
    printf("\t=\n");
    for (int i=0;i<r1;i++){
        printf("[ ");
        for(int j=0;j<c2;j++){
            printf("%d ",product[i][j]);
        }  
        printf("]\n"); 
    
    }
    return 0;
}