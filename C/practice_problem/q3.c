#include <stdio.h>
#include <stdlib.h>

int **create_2d_array(int rows, int cols){
    int **ptr=(int **)calloc(rows,sizeof(int*));
    for(int i=0;i<rows;i++){
        ptr[i]=(int*)calloc(cols,sizeof(int));
        for (int j = 0; j < cols; j++)
        {
            ptr[i][j]=(i+1)*(j+1);
        }
    } 
    return  ptr;

}

int main(){
    int rows,cols;
    scanf("%d %d",&rows,&cols);
    int **result=create_2d_array(rows,cols);
    for(int i=0;i<rows;i++){
        for (int j = 0; j < cols; j++)
        {
            printf("%d ",*(*(result+i)+j));
        }
        printf("\n");
    }
    free;
    return 0;
}