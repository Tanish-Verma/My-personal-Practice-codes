#include <stdio.h>

int main() {
    FILE *ptr;
    ptr = fopen("students.csv", "r");
    if (ptr == NULL) {
        printf("File could not be opened");
        return 1;
    }
    
    char line[256],k;
    fgets(line,sizeof(line),ptr);
    int sum=0,count=0;
    while ((fgets(line,sizeof(line),ptr)!=NULL)) {
        char name[50];
        int age,marks;
        sscanf(line,"%49[^,],%d,%d",&name,&age,&marks);
        sum+=marks;
        count++;
    }
    printf("The average of the  marks is %.2f\n", (float)sum/count);

    fclose(ptr); // Close the file after reading
    return 0;
}