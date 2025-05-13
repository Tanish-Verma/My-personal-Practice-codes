#include <stdio.h>

void crossproduct(int arr[], int frr[], int result[3]) {
    // Calculate the cross product
    result[0] = arr[1] * frr[2] - arr[2] * frr[1];
    result[1] = arr[2] * frr[0] - arr[0] * frr[2];
    result[2] = arr[0] * frr[1] - arr[1] * frr[0];
}

void vector_triple_product(int coord1[3],int coord2[3],int coord3[3], int result[3]){
    int partial_product[3];
    crossproduct(coord1,coord2,partial_product);
    crossproduct(partial_product,coord3,result);
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
    int result[3];
    vector_triple_product(coords,coords2,coords3,result);

    printf("[%d %d %d]X[%d %d %d]X[%d %d %d]]=[%d %d %d]",coords[0],coords[1],coords[2],coords2[0],coords2[1],coords2[2],coords3[0],coords3[1],coords3[2],result[0],result[1],result[2]);
    
    return 0;
}