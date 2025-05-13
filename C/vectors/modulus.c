#include <stdio.h>
#include <math.h>

float modulus(int []);



float modulus(int arr[3]){
    float k=0;
    k=sqrt(pow(arr[0],2)+pow(arr[1],2)+pow(arr[2],2));
    return k;
}

int main(){
    char axis[4]="xyz";
    int coords[3];
    printf("For vector 1: \n");
    for(int i=0;i<3;i++){
        printf("Enter the value of %c coordinates for vector 1: ",axis[i]);
        scanf("%d",&coords[i]);
    }
    
    printf("The modulus of the vector [ %d %d %d ] is %f",coords[0],coords[1],coords[2],modulus(coords));

    return 0;
}

