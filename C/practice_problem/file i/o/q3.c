#include <stdio.h>

int main() {
    FILE *ptr;
    FILE *ptr2;
    ptr2=fopen("hello.txt","w");
    ptr = fopen("hi.txt", "r");
    if (ptr == NULL ||  ptr2 == NULL) {

        printf("File could not be opened");
        return 1;
    }
    
    char c;
    // Use fgetc to read one character at a time
    while ((c = fgetc(ptr)) != EOF) {
        fputc(c, ptr2);
    }
    
    fclose(ptr); // Close the file after reading
    fclose(ptr2); // Close the file after reading
    return 0;
}