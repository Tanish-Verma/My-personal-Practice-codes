#include <stdio.h>

void crossproduct(int arr[], int frr[], float result[3]) {
    // Calculate the cross product
    result[0] = arr[1] * frr[2] - arr[2] * frr[1];
    result[1] = arr[2] * frr[0] - arr[0] * frr[2];
    result[2] = arr[0] * frr[1] - arr[1] * frr[0];
}

int main() {
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
    
    float result[3];
    crossproduct(coords, coords2, result);
    
    printf("[%d %d %d] X [%d %d %d] = [%.0f %.0f %.0f]\n",
           coords[0], coords[1], coords[2],
           coords2[0], coords2[1], coords2[2],
           result[0], result[1], result[2]);
    
    return 0;
}
