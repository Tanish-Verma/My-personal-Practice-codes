#include <stdio.h>
#include <math.h>

float modulus(int arr[3]){
    float k=0;
    k=sqrt(pow(arr[0],2)+pow(arr[1],2)+pow(arr[2],2));
    return k;
}


int main(){
    char axis[4]="xyz";
    int coords[3];
    int coords2[3];
    do{printf("For vector 1: \n");
    for(int i=0;i<3;i++){
        printf("Enter the value of %c coordinates for vector 1: ",axis[i]);
        scanf("%d",&coords[i]);
        }
    if (modulus(coords)==0){
        printf("The vector can not be a zero vector. Please input again.");
    }
    
    }while(modulus(coords)==0);
    printf("\n");
    do{printf("For vector 2: \n");
    for(int i=0;i<3;i++){
        printf("Enter the value of %c coordinates for vector 2: ",axis[i]);
        scanf("%d",&coords2[i]);
    }
    if (modulus(coords2)==0){
        printf("The vector can not be a zero vector. Please input again.");
    }
    }while(modulus(coords2)==0);


    int result=0;
    for(int i=0;i<3;i++){
        result+=coords2[i]*coords[i];
    }

    double angle_radian;
    angle_radian=acos(result/(modulus(coords)*modulus(coords2)));
    double angle_degree = 180*angle_radian/3.14159265359;
    printf("The angle between the vectors [%d %d %d] and [%d %d %d] is %lf in radian and %lf in degrees",coords[0],coords[1],coords[2],coords2[0],coords2[1],coords2[2],angle_radian,angle_degree);
    return 0;
}