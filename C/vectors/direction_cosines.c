#include <stdio.h>
#include <math.h>


float modulus(int arr[]){
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
    float mod = modulus(coords);
    if (mod == 0) {
        printf("The vector is a zero vector; direction cosines are undefined.\n");
        return 0;
    }

    float direction_cosines[3];
    for (int i = 0; i < 3; i++){
        direction_cosines[i] = coords[i] / mod;
    }
    float angles[3];
    for(int i=0;i<3;i++){
        angles[i]=(acos(direction_cosines[i])*180)/3.14;
    }
    printf("The dc's of the vectors [%d %d %d] are [%f %f %f]",coords[0],coords[1],coords[2],direction_cosines[0],direction_cosines[1],direction_cosines[2]);
    printf(" and the angles are %f,%f,%f.",angles[0],angles[1],angles[2]);
    return 0;
}

