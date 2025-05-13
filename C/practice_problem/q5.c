#include <stdio.h>
#include <stdlib.h>

 int **transpose_matrix(int **matrix, int rows, int cols){
    int ** transpose = (int**)calloc(rows,sizeof(int*));
    for(int i=0;i<rows;i++){
        int *col=(int *)calloc(cols,sizeof(int));
        for(int j=0;j<cols;j++){
            col[j]=matrix[j][i];
        }
        transpose[i]=col;
    }
    return  transpose;

 }

float ***specialmatrix(int ** matrix,int  rows,int cols){
    float *** special = (float ***)calloc(2,sizeof(float**));
    int **transpose=transpose_matrix(matrix,rows,cols);
    float **symmetric=(float**)calloc(rows,sizeof(float*));
    for(int i=0;i<rows;i++){
        float *col=(float *)calloc(cols,sizeof(float));
        for(int j=0;j<cols;j++){
            col[j]=(matrix[i][j]+transpose[i][j])/2.0;
        }
        symmetric[i]=col;
    }
    special[0]=symmetric;
    float **skewsymmetric=(float**)calloc(rows,sizeof(float*));
    for(int i=0;i<rows;i++){
        float *col=(float *)calloc(cols,sizeof(float));
        for(int j=0;j<cols;j++){
            col[j]=(matrix[i][j]-transpose[i][j])/2.0;
        }
        skewsymmetric[i]=col;
    }
    special[1]=skewsymmetric;
    return special;
}

float add(int a,int b){
    return (a+b)/2.0;
}
float subtract(int a,int b){
    return (a-b)/2.0;
}

float**funcpoinspecial(int**matrix,int rows,int cols,float (*func)(int a,int b)){
    int **transpose=transpose_matrix(matrix,rows,cols);
    float **symmetric=(float**)calloc(rows,sizeof(float*));
    for(int i=0;i<rows;i++){
        float *col=(float *)calloc(cols,sizeof(float));
        for(int j=0;j<cols;j++){
            col[j]=func(matrix[i][j],transpose[i][j]);
        }
        symmetric[i]=col;
    }
    return symmetric;
}

int main(){
    int n,m;
    printf("Enter the number of rows and columns of the matrix: ");
    scanf("%d %d",&n,&m);
    int  **matrix = (int**)calloc(n,sizeof(int*));
    for(int i=0;i<n;i++){
        int *row = (int *)calloc(m,sizeof(int));
        for(int j=0;j<m;j++){
            printf("Enter element for [%d][%d]: ",i+1,j+1);
            scanf("%d",&row[j]);
            }
            matrix[i]=row;
    }
    int **transpose=transpose_matrix(matrix,n,m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            printf("%d ",transpose[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // float***matrice=specialmatrix(matrix,n,m);
    // for(int i=0;i<2;i++){
    //     printf("%s matrix\n",!i?"Symmetric":"Skew-Symmetric");
    //     for(int j=0;j<n;j++){
    //         for(int k=0;k<m;k++){
    //             printf("%f ",matrice[i][j][k]);
    //         }
    //         printf("\n");
    //     }
    //     printf("\n");
    // }
    for(int i=0;i<2;i++){
        float** special=funcpoinspecial(matrix,n,m,(!i?&add:&subtract));
        printf("%s matrix\n",!i?"Symmetric":"Skew-Symmetric");
        for(int j=0;j<n;j++){
            for(int k=0;k<m;k++){
                printf("%.1f ",special[j][k]);
            }
            printf("\n");
        }
        for(int j=0;j<n;j++){
            free(special[j]);
        }
        free(special);
        printf("\n");
    }
    for(int i=0;i<n;i++){
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}