#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct employee{
    int id;
    char* name;
    int age;
    float salary;
} emp;

float max_salary(emp *ptr[5]){
    float max=0;
    for(int i=0;i<5;i++){
        if(ptr[i]->salary>max){
            max=ptr[i]->salary;
        }
    }
    return  max;
}

int main(){

    emp* ptr[5];

    for(int i=0;i<5;i++){
        // char c[50];
        ptr[i]=(emp*)malloc(sizeof(emp));
        if(ptr[i]==NULL){
            printf("memory allocation failed");
            return 1;
        }
        ptr[i]->name = (char*)malloc(50 * sizeof(char));
        if (ptr[i]->name == NULL) {
            printf("Memory allocation for name failed\n");
            return 1; // Exit if memory allocation fails
        }
        printf("enter employee id: ");
        scanf("%d",&(ptr[i]->id));

        printf("Enter your name: ");
        scanf("%s",(ptr[i]->name));
        printf("Enter your age: ");
        scanf("%d",&(ptr[i]->age));
        printf("Enter your salary: ");
        scanf("%f",&(ptr[i]->salary));
        // printf("hi");

    }
    for(int i=0;i<5;i++){
        printf("id: %d\n",ptr[i]->id);
        printf("name: %s\n",ptr[i]->name);
        printf("age: %d\n",ptr[i]->age);
        printf("salary: %f\n",ptr[i]->salary);
    }

    printf("maximum salary is : %f\n",max_salary(ptr));

    for (int i = 0; i < 5; i++) {
        free(ptr[i]->name);
        free(ptr[i]);
    }
    return 0;
}