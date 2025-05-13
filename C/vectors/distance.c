#include <stdio.h>
#include <math.h>

void printvector(int arr[], int size){
    printf("[ ");
    for (int i=0;i<size;i++){
        printf("%d, ",arr[i]);
    }
    printf(" ]");
}
float distance(int arr1[3],int arr2[3]){
    float sum=0;
    for (int i=0;i<3;i++){
        sum+=pow(arr1[i]-arr2[i],2);
    }
    float dist=sqrt(sum);
    return dist;
}




int main(){
    char axis[4]="xyz";
    int coords[3];
    printf("For vector 1: \n");
    for(int i=0;i<3;i++){
        printf("Enter the value of %c coordinates for vector 1: ",axis[i]);
        scanf("%d",&coords[i]);
    }
    int coords2[3];
    printf("\n");
    printf("For vector 2: \n");
    for(int i=0;i<3;i++){
        printf("Enter the value of %c coordinates for vector 2: ",axis[i]);
        scanf("%d",&coords2[i]);
    }
    printf("The between the two vectors ");
    printf("[%d %d %d] and ",coords[0],coords[1],coords[2]);
    printf("[%d %d %d] is %f  ",coords2[0],coords2[1],coords2[2],distance(coords2,coords));
    
    return 0;
}