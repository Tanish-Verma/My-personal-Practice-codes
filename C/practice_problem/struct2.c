#include <stdio.h>
#include <ctype.h>

enum dtype{
    INT=1,
    FLOAT,
    CHAR
};

union data
{
    int a;
    float b;
    char c;
};


int main(){
    union  data data_type[5];
    int dataTypeTracker[5];

    for(int i=0;i<5;i++){
        int s;
        printf("Enter the data type (1=int,2=float,3=char): ");
        scanf("%d",&s);
        dataTypeTracker[i] = s;  // Store the data type entered by the user
        if(s==INT){
            printf("Enter the int: ");
            scanf("%d",&(data_type[i]).a);
        }
        else if(s==FLOAT){
            printf("Enter the float: ");
            scanf("%f",&(data_type[i]).b);
        }
        else{
            getchar();
            printf("Enter the char: ");
            // getchar();
            scanf("%c",&(data_type[i]).c);
        }

    }
    for (int i = 0; i < 5; i++) {
    if (dataTypeTracker[i] == INT) {
        printf("Data %d is of type INT: %d\n", i + 1, data_type[i].a);
    } else if (dataTypeTracker[i] == FLOAT) {
        printf("Data %d is of type FLOAT: %f\n", i + 1, data_type[i].b);
    } else if (dataTypeTracker[i] == CHAR) {
        printf("Data %d is of type CHAR: %c\n", i + 1, data_type[i].c);
    }
    }


    return 0;
}