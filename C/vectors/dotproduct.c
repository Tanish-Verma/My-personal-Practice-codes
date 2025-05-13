#include <stdio.h>

void printvector(int arr[], int size){
    printf("[ ");
    for (int i=0;i<size;i++){
        printf("%d, ",arr[i]);
    }
    printf(" ]");
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
    int result=0;
    for(int i=0;i<3;i++){
        result+=coords2[i]*coords[i];
    }
    printvector(coords,3);
    printf(".");
    printvector(coords2,3);
    printf("=");
    printf("%d",result);
    return 0;
}